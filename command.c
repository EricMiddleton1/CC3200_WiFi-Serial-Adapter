/*
 * command.c
 *
 *  Created on: Aug 17, 2016
 *      Author: eric
 */

#include "command.h"


typedef enum {
	PARAM_VARIABLE_LENGTH,	//Variable length parameter, ends in '\0'
	PARAM_FIXED_LENGTH,		//Fixed length parameter
	PARAM_NONE
} ParamType_e;

typedef struct {
	ParamType_e paramType;
	int paramSize;			//Indicates size of fixed length parameter, or max size of variable parameter
} CommandFormat_t;

CommandFormat_t commands[] = {
		{PARAM_VARIABLE_LENGTH, 32},	//WIFI_START
		{PARAM_NONE, 0}					//WIFI_STOP
};

Command_t _command;


uint8_t command_processChar(uint8_t c, Command_t** finishedCommand) {
	static int inProgress = 0;
	static CommandFormat_t* curFormat = 0;

	if(!inProgress) {
		//c should represend a command
		if(c >= (uint8_t)MAX_COMMAND) {
			//Not a valid command
			return COMMAND_RET_INVALID_TYPE;
		}
		//Initialize the command struct
		_command.type = c;
		_command.length = 0;

		//Check the command format
		int index = (int)_command.type;
		curFormat = &(commands[index]);

		if(curFormat->paramType == PARAM_NONE) {
			//If no parameters, we're done here
			*finishedCommand = &_command;

			return COMMAND_RET_SUCCESS;
		}
		else {
			//We have to read in the parameter

			//Set inProgress flag
			inProgress = 1;
		}
	}
	else {
		//We are currently in the middle of receiving a command

		if(curFormat->paramType == PARAM_FIXED_LENGTH) {
			//Fixed length parameter

			_command.param[_command.length++] = c;

			if(_command.length >= curFormat->paramSize) {
				//Param is done

				inProgress = 0;

				//Return the command
				*finishedCommand = &_command;
				return COMMAND_RET_SUCCESS;
			}
		}
		else {
			//Variable length parameter

			if(c == '\0') {
				//Param is done

				inProgress = 0;

				//Return the command
				*finishedCommand = &_command;
				return COMMAND_RET_SUCCESS;
			}
			else {
				//Param in progress

				if(_command.length >= curFormat->paramSize) {
					//The parameter is too big

					inProgress = 0;

					//Return error code
					return COMMAND_RET_INVALID_LENGTH;
				}
				else {
					_command.param[_command.length++] = c;
				}
			}
		}
	}

	return COMMAND_RET_INPROGRESS;
}
