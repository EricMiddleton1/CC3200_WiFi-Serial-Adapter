/*
 * task_uart.c
 *
 *  Created on: Jul 30, 2016
 *      Author: eric
 */

#include "task_uart.h"

#define BAUD		115200
#define UART_ADDR	UARTA0_BASE

#define STACK_SIZE	1024

void task_uart();

void uart_init() {
	//Initialize the UART
	UARTConfigSetExpClk(UART_ADDR,
		MAP_PRCMPeripheralClockGet(PRCM_UARTA0),
		BAUD,
		UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
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

void task_uart() {
	osi_Sleep(1000);

	while(1) {
		//Wait for character
		if(UARTCharsAvail(UART_ADDR)) {
			//Set activity LED
			led_setActivity();

			while(UARTCharsAvail(UART_ADDR)) {
				long c = UARTCharGetNonBlocking(UART_ADDR);


				//Send it over the network if connected
				wifi_send(c);
			}
		}

		osi_Sleep(1);
	}
}

void uart_send(char* buf, int length) {
	char *end;

	for(end = buf + length; buf != end; buf++) {
		UARTCharPut(UART_ADDR, *buf);
	}
}
