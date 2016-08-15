/*
 * test_led.c
 *
 *  Created on: Aug 15, 2016
 *      Author: TA288
 */


#include "task_led.h"

#define LED_STACK_SIZE		512

#define ACTIVITY_RATE		25
#define BLINK_RATE			500

int _activityTick;

void task_led();

void led_init() {
	//Clear the LEDs
	GPIOPinWrite(LED_PORT, LED_RED | LED_ORANGE | LED_GREEN, 0);

	//Disable the activity tick
	_activityTick = -1;

	//Launch the LED task
	osi_TaskCreate(task_led,
			(const signed char*)"LED Task",
			LED_STACK_SIZE,
			NULL,
			1,
			NULL);
}


void task_led() {
	Message("[Info] LED task started\r\n");

	while(1) {
		static uint8_t leds = 0x00;
		static int blinkTick = 0;

		int update = 0;

		if(blinkTick == 0) {
			//Determine green LED state
			if(_apState == UNINITIALIZED) {
				leds &= ~LED_GREEN; //Off
			}
			else if(_apState == CONNECTED_WITH_IP) {
				leds |= LED_GREEN; //On
			}
			else {
				leds ^= LED_GREEN; //Toggle
			}

			//Determine orange LED state
			if(_socketState == CONNECTED) {
				leds |= LED_ORANGE; //On
			}
			else if(_socketState == LISTENING) {
				leds ^= LED_ORANGE; //Toggle
			}
			else {
				leds &= ~LED_ORANGE; //Off
			}

			update = 1;
		}

		if(_activityTick == 0) {
			//Set the activity LED
			leds |= LED_RED;

			update = 1;

			_activityTick = 1;
		}
		else if(_activityTick > 0) {
			_activityTick++;

			if(_activityTick > ACTIVITY_RATE) {
				//Clear the activity LED
				leds &= ~LED_RED;

				update = 1;

				//Disable the activity tick
				_activityTick = -1;
			}
		}

		if(update) {
			//Set the LED state
			GPIOPinWrite(LED_PORT, LED_GREEN | LED_ORANGE | LED_RED, leds);
		}

		//Increment the blink tick
		blinkTick = (blinkTick + 1) % BLINK_RATE;

		//Delay
		osi_Sleep(1);
	}
}

void led_setActivity() {
	_activityTick = 0;
}
