//*****************************************************************************
// pin_mux_config.h
//
// configure the device pins for different signals
//
// Copyright (c) 2016, Texas Instruments Incorporated - http://www.ti.com/
// All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

// This file was automatically generated on 7/30/2016 at 3:56:43 PM
// by TI PinMux version
//
//*****************************************************************************

#ifndef __PIN_MUX_CONFIG_H__
#define __PIN_MUX_CONFIG_H__

#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "gpio.h"

#include "prcm.h"
#include "rom.h"
#include "rom_map.h"


#define LED_PORT	GPIOA1_BASE

#define LED_RED		0x2
#define LED_ORANGE	0x4
#define LED_GREEN	0x8

#define ADDR0_PORT	GPIOA0_BASE
#define ADDR0_PIN	0x2

#define ADDR1_PORT	GPIOA0_BASE
#define ADDR1_PIN	0x40

#define ADDR2_PORT	GPIOA0_BASE
#define ADDR2_PIN	0x80

/*
#define ADDR3_PORT	GPIOA2_BASE
#define ADDR3_PIN	0x40
*/

#define ADDR4_PORT	GPIOA3_BASE
#define ADDR4_PIN	0x80

#define ADDR3_PORT	ADDR4_PORT
#define ADDR3_PIN	ADDR4_PIN

extern void PinMuxConfig(void);

#endif //  __PIN_MUX_CONFIG_H__
