/*
 * task_wifi.c
 *
 *  Created on: Aug 8, 2016
 *      Author: eric
 */

#include "task_wifi.h"


/*	int task_wifi_init(void)
 * 	This function configures the simplelink system:
 * 		Initialize WiFi subsystem in AP mode
 * 		Initialize DHCP server
 *
 *	Returns 0 on success, error code (< 0) on error
 */

//Stack size for socket task
#define SOCK_STACK_SIZE		4096

#define RECV_BUFFER_SIZE	128

//Port for TCP connection
#define TCP_PORT			42880

APState_e volatile _apState = UNINITIALIZED;

SockState_e volatile _socketState = STOPPED;

int _clientSocket;

//task handles
OsiTaskHandle _socketTaskHandle;

//Local prototypes
void task_socket();
int waitForClient(int listenSocket, SlSockAddr_t* clientAddr, SlSocklen_t addrLen);
int makeSocketNonblocking(int socket);

int wifi_init(char *ssid, int ssidLen, uint8_t channel) {
	//Ititialize WiFi subsystem using blocking call
	//May take tens of milliseconds
	if(sl_Start(0, 0, 0) == 0) {
		//Error starting wifi subsystem
		return WIFI_ERROR_START;
	}

	//Wait for system to be fully ready
	//Task_sleep(100);

	//Set WLAN mode to AP
	sl_WlanSetMode(ROLE_AP);

	//Set AP specific configuration settings
	sl_WlanSet(SL_WLAN_CFG_AP_ID, 0, ssidLen, (unsigned char*)ssid);	//SSID
	sl_WlanSet(SL_WLAN_CFG_AP_ID, 3, 1, &channel);						//Channel

	/*	Use default IP settings:
	 * 		IP:			192.168.1.1
	 * 		Gateway: 	192.168.1.1
	 * 		DNS:		192.168.1.1
	 * 		Subnet:		255.255.255.0
	 */

	/*	Use default DHCP server settings:
	 * 		lease time:		24 hours
	 * 		IP start:		192.168.1.2
	 * 		IP end:			192.168.1.254
	 */

	/*	Using default URN:
	 * 		mysimplelink
	 */

	//Restart simplelink to allow above changes to take ef
	sl_Stop(100);
	if(sl_Start(NULL, NULL, NULL) == 0) {
		//Error starting wifi subsystem
		return WIFI_ERROR_START;
	}

	//Start DHCP server (should start by default)
	sl_NetAppStart(SL_NET_APP_DHCP_SERVER_ID);

	//Update states
	_apState = DISCONNECTED;
	_socketState = STOPPED;

	//Launch the socket task
	osi_TaskCreate(task_socket,
			(const signed char*)"Socket Task",
			SOCK_STACK_SIZE,
			NULL,
			1,
			&_socketTaskHandle);

	Message("[Info] WiFi setup complete\r\n\r\nSSID: ");
	Message(ssid);
	Message("\r\n\r\n");

	return 0;
}

void SimpleLinkWlanEventHandler(SlWlanEvent_t* event) {
	switch(event->Event) {
		case SL_WLAN_STA_CONNECTED_EVENT:
			//New station has connected to AP

			//Update state
			_apState = CONNECTED_NO_IP;

			Message("[Info] New station connected\r\n");
		break;

		case SL_WLAN_STA_DISCONNECTED_EVENT:
			//Station has disconnected from AP

			//Update state
			_apState = DISCONNECTED;

			Message("[Info] Station disconnected\r\n");
		break;

		default: {
			char str[2];
			str[0] = event->Event + '0';
			str[1] = '\0';

			Message("[Warning] Unknown wlan event: ");
			Message(str);
			Message("\r\n");
		}
		break;
	}
}

void SimpleLinkGeneralEventHandler(SlDeviceEvent_t* event) {
	//This handler should only be called on error
	Message("[Warning] SimpleLinkGeneralEventHandler: A device error has occurred\r\n");
}

void SimpleLinkHttpServerCallback(SlHttpServerEvent_t* event, SlHttpServerResponse_t* response) {
	//TODO
}

void SimpleLinkNetAppEventHandler(SlNetAppEvent_t* event) {
	switch(event->Event) {
		case SL_NETAPP_IPV4_IPACQUIRED_EVENT:
			Message("[Info] Device IPV4 address aquired\r\n");
		break;

		case SL_NETAPP_IP_LEASED_EVENT:
			//Update state
			_apState = CONNECTED_WITH_IP;

			Message("[Info] IP leased\r\n");
		break;

		case SL_NETAPP_IP_RELEASED_EVENT:
			//Update state
			_apState = CONNECTED_NO_IP;

			Message("[Info] IP released\r\n");
		break;

		default:
			Message("[Warning] SimpleLinkNetAppEventHandler: Unimplemented event\r\n");
		break;
	}
}


void SimpleLinkSockEventHandler(SlSockEvent_t* event) {
	//TODO
}

void task_socket() {
	Message("[Info] Socket task started\r\n");

	while(_apState != UNINITIALIZED) {
		int listenSocket;
		SlSockAddrIn_t listenAddr, clientAddr;
		SlSocklen_t addrLen = sizeof(clientAddr);

		//Wait until a device is connected
		while(_apState != CONNECTED_WITH_IP) {
			osi_Sleep(1);
		}

		//Create the listen socket
		//	IPV4
		//	TCP
		listenSocket = sl_Socket(SL_AF_INET, SL_SOCK_STREAM, 0);

		if(listenSocket < 0) {
			Message("[Error] task_socket: Unable to create listen socket\r\n");

			osi_Sleep(10);

			continue;
		}

		listenAddr.sin_family = SL_AF_INET;
		listenAddr.sin_port = sl_Htons(TCP_PORT);
		listenAddr.sin_addr.s_addr = 0;

		//Bind the listen socket to the TCP_PORT
		if(sl_Bind(listenSocket, (SlSockAddr_t*)&listenAddr, sizeof(SlSockAddrIn_t)) < 0) {
			Message("[Error] task_socket: Unable to bind listen socket to port\r\n");

			sl_Close(listenSocket);

			osi_Sleep(10);

			continue;
		}

		//Start listening
		if(sl_Listen(listenSocket, 0) < 0) {
			Message("[Error] Unable to listen\r\n");

			sl_Close(listenSocket);

			osi_Sleep(10);

			continue;
		}

		//Update state
		_socketState = LISTENING;

		//Make socket nonblocking
		if(makeSocketNonblocking(listenSocket) < 0) {
			Message("[Error] Unable to make socket nonblocking\r\n");

			osi_Sleep(10);

			sl_Close(listenSocket);

			continue;
		}

		while(_apState == CONNECTED_WITH_IP) {
			char buffer[64];
			sprintf(buffer, "%d\r\n", TCP_PORT);
			Message("[Info] Accepting connections on port ");
			Message(buffer);

			//Wait for client to connect
			_clientSocket = waitForClient(listenSocket, (SlSockAddr_t*)&clientAddr, addrLen);

			//Make sure the socket is valid
			if(_clientSocket < 0)
				continue;

			Message("[Info] Client connected\r\n");

			//Make socket nonblocking
			if(makeSocketNonblocking(_clientSocket) < 0) {
				Message("[Error] Unable to make client socket nonblocking\r\n");

				osi_Sleep(10);

				sl_Close(_clientSocket);

				continue;
			}

			//Update state
			_socketState = CONNECTED;

			int retval = 1;
			while(_apState == CONNECTED_WITH_IP && (retval > 0 || retval == SL_EAGAIN)) {
				uint8_t recvBuffer[RECV_BUFFER_SIZE];

				//Fetch characters from TCP receive buffer
				//Will return SL_EAGAIN if no characters in buffer
				//Or 0 if client has disconnected
				retval = sl_Recv(_clientSocket, recvBuffer, RECV_BUFFER_SIZE, 0);

				if(retval > 0) {
					//Set activity LED
					led_setActivity();

					uart_send(recvBuffer, retval);
				}
				else if(retval != 0 && retval != SL_EAGAIN) {
					sprintf(buffer, "[Warning] sl_Recv returned %d\r\n", retval);
					Message(buffer);
				}

				osi_Sleep(1);
			}

			Message("[Info] Client disconnected\r\n");

			//Update state
			_socketState = LISTENING;

			//Close client socket
			sl_Close(_clientSocket);
		}

		//Close listen socket
		sl_Close(listenSocket);

		//Update state
		_socketState = STOPPED;

		Message("[Info] No longer accepting connections\r\n");
	}

	Message("[Info] Exiting socket task\r\n");
}

int wifi_send(char *buffer, int size) {
	if(_socketState == CONNECTED) {
		//Send the character
		sl_Send(_clientSocket, buffer, size, 0);

		return 0;
	}
	else {
		return -1;
	}
}

int waitForClient(int listenSocket, SlSockAddr_t* clientAddr, SlSocklen_t addrLen) {
	int clientSocket = -1;

	while(clientSocket < 0 && _apState == CONNECTED_WITH_IP) {
		clientSocket = sl_Accept(listenSocket, clientAddr, &addrLen);

		osi_Sleep(1);
	}

	return clientSocket;
}

int makeSocketNonblocking(int socket) {
	long nonBlocking = 1;
	if(sl_SetSockOpt(socket, SL_SOL_SOCKET, SL_SO_NONBLOCKING,
			&nonBlocking, sizeof(nonBlocking)) < 0) {

		return -1;
	}
	else {
		return 0;
	}
}
