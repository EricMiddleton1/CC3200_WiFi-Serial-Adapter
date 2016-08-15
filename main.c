/*
 * UART <-> WiFi passthrough application for CPRE288 at Iowa State University
 *
 * Written by Eric Middleton
 */

#include <stdlib.h>
#include <string.h>

// Simplelink includes
#include "simplelink.h"

// driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "utils.h"

// free_rtos/ti-rtos includes
#include "osi.h"

// common interface includes
#include "common.h"
#ifndef NOTERM
#include "uart_if.h"
#endif

#define APP_NAME                "CPRE288 UART->WiFi adapter"
#define APPLICATION_VERSION     "1.1.1"
#define OSI_STACK_SIZE          2048

#include "pin_mux_config.h"


//Custom tasks
#include "task_uart.h"
#include "task_wifi.h"

#define SSID		"CPRE288 Test AP 2"


//*****************************************************************************
//
//! Board Initialization & Configuration
//! Note: Taken from wlan_ap example program
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void
BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
    //
    // Set vector table base
    //
#if defined(ccs) || defined(gcc)
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}

void task_wifi() {
	wifi_init(SSID, strlen(SSID), 1);
}

/*
 *  ======== main ========
 */
int main(void)
{
	//Board initialization
	BoardInit();

    //Initialize the pin configuration
    PinMuxConfig();

    uart_init();

    Message("CPRE288 test app\r\n\r\n[Info] Board initialized\r\n");

    int retval;

    //Start simplelink host
    retval = VStartSimpleLinkSpawnTask(SPAWN_TASK_PRIORITY);
    if(retval < 0) {
    	for(;;);
    }

    Message("[Info] SimpleLink task started\r\n");

    //Start wifi task
    retval = osi_TaskCreate(task_wifi, (const signed char*)"WiFi task",
    		OSI_STACK_SIZE, NULL, 1, NULL);

    if(retval < 0) {
    	for(;;);
    }

    Message("[Info] UART task started\r\n");

    uart_start();

    Message("[Info] Starting task scheduler\r\n");

    //Start task scheduler
    osi_start();

    return 0;
}
