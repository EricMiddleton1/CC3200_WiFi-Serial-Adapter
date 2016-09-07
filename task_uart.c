/*
 * task_uart.c
 *
 *  Created on: Jul 30, 2016
 *      Author: eric
 */

#include "task_uart.h"

#define BAUD		115200
#define UART_ADDR	UARTA0_BASE

#define STACK_SIZE	4096

#define BUFFER_SIZE	128

void task_uart();
void uart_intHandler();


typedef struct {
	char buffer[BUFFER_SIZE];
	int size;

	int commandFlag;
} UARTBuffer_t;

//UART Rx buffers
UARTBuffer_t _rxBuffers[2];
int _bufferSwitch;

void uart_init() {
	//Initialize the buffers
	_rxBuffers[0].size = 0;
	_rxBuffers[0].commandFlag = -1;

	_rxBuffers[1].size = 0;
	_rxBuffers[1].commandFlag = -1;

	_bufferSwitch = 0;

	//Initialize the UART
	UARTConfigSetExpClk(UART_ADDR,
		MAP_PRCMPeripheralClockGet(PRCM_UARTA0),
		BAUD,
		UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

	//Enable the FIFO
	UARTFIFOEnable(UART_ADDR);

	//Set UART FIFO level to 1/2
	UARTFIFOLevelSet(UART_ADDR, UART_FIFO_TX4_8, UART_FIFO_RX4_8);

	//Register interrupt handler
	UARTIntRegister(UART_ADDR, uart_intHandler);

	//Enable RX and RT interrupts
	UARTIntEnable(UART_ADDR, UART_INT_RT | UART_INT_RX);
}

void uart_start() {
	//Launch the UART task
	osi_TaskCreate(task_uart,
			(const signed char*)"UART Task",
			STACK_SIZE,
			NULL,
			1,
			NULL);
}

void uart_intHandler() {
	//Get interrupt flags
	unsigned long status = UARTIntStatus(UART_ADDR, 1);

	//Clear flags
	UARTIntClear(UART_ADDR, status);

	//Treat both of these interrupts the same
	if( (status & UART_INT_RT) || (status & UART_INT_RX) ) {
		//Get current rx buffer
		UARTBuffer_t *curBuffer = &(_rxBuffers[_bufferSwitch]);

		//Check for command mode flag
		int commandSet = GPIOPinRead(COMMAND_PORT, COMMAND_PIN);
		if((curBuffer->commandFlag == -1) && commandSet) {
			//Set command mode flag
			curBuffer->commandFlag = curBuffer->size;
		}

		//Get all characters in FIFO
		while(UARTCharsAvail(UART_ADDR)) {
			curBuffer->buffer[curBuffer->size++] = UARTCharGet(UART_ADDR);

		}
	}
}

void task_uart() {
	osi_Sleep(1000);

	//Store current buffer
	UARTBuffer_t *curBuffer = &(_rxBuffers[_bufferSwitch]);

	while(1) {
		//Check for characters in buffer
		if(curBuffer->size > 0) {
			//Swap buffers
			_bufferSwitch = !_bufferSwitch;

			//Set activity LED
			led_setActivity();

			//Check for the command flag
			if(curBuffer->commandFlag != -1) {
				//Send everything from before the command flag was set
				wifi_send(curBuffer->buffer, curBuffer->commandFlag);

				//Process the command
				Command_t* command;
				uint8_t retval = COMMAND_RET_INPROGRESS;
				int i;
				for(i = curBuffer->commandFlag; i < curBuffer->size && retval == COMMAND_RET_INPROGRESS; i++) {
					retval = command_processChar(curBuffer->buffer[i], &command);
				}

				if(retval == COMMAND_RET_SUCCESS) {
					//We have a finished command

					switch(command->type) {
						case WIFI_START:
							//Start WiFi system
							wifi_start((char*)command->param, command->length);
						break;

						case WIFI_STOP:
							//Stop WiFi system
							wifi_stop();
						break;
					}
				}

				if(retval != COMMAND_RET_INPROGRESS) {
					//Send return value
					UARTCharPut(UART_ADDR, retval);
				}
			}
			else {
				//Send the data over WiFi
				wifi_send(curBuffer->buffer, curBuffer->size);
			}

			//Clear the buffer
			curBuffer->size = 0;
			curBuffer->commandFlag = -1;

			//Swap buffer pointer
			curBuffer = &(_rxBuffers[_bufferSwitch]);
		}

		osi_Sleep(1);
	}
}

void uart_send(char* buf, int length) {
	//Check for command flag
	if(GPIOPinRead(COMMAND_PORT, COMMAND_PIN)) {
		//Don't send if in command mode
		return;

		//TODO: buffer this data until command mode is released
	}

	char *end;

	for(end = buf + length; buf != end; buf++) {
		UARTCharPut(UART_ADDR, *buf);
	}
}
