/*
 * task_uart.h
 *
 *  Created on: Jul 30, 2016
 *      Author: eric
 */

#ifndef TASK_UART_H_
#define TASK_UART_H_

#include "hw_memmap.h"
#include "hw_types.h"
#include "rom_map.h"
#include "uart.h"
#include "task_wifi.h"
#include "prcm.h"


void uart_init(void);

void uart_start(void);

void uart_send(char* buf, int length);

#endif /* TASK_UART_H_ */
