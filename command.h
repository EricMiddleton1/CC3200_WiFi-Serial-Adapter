/*
 * command.h
 *
 *  Created on: Aug 17, 2016
 *      Author: eric
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <stdint.h>

#define COMMAND_RET_SUCCESS			0x00
#define COMMAND_RET_INPROGRESS		0xFF
#define COMMAND_RET_INVALID_TYPE	0xFE
#define COMMAND_RET_INVALID_LENGTH	0xFD

#define MAX_PAYLOAD		64

typedef enum {
	WIFI_START = 0x00,
	WIFI_STOP,


	MAX_COMMAND
} CommandType_e;

typedef struct {
	CommandType_e type;

	uint8_t param[MAX_PAYLOAD];
	int length;
} Command_t;

uint8_t command_processChar(uint8_t c, Command_t** finishedCommand);

#endif /* COMMAND_H_ */
