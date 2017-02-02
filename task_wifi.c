/*
 * task_wifi.c
 *
 *  Created on: Aug 8, 2016
 *      Author: eric
 */

#include "task_wifi.h"

#define AP_SSID "MicroCART"
#define AP_PSK  "m1cr0cart"
#define AP_CHANNEL  6


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



void wifi_init() {
	//Update states
	_apState = UNINITIALIZED;
	_socketState = STOPPED;

	//Launch the socket task
	int retval = osi_TaskCreate(task_socket,
			(const signed char*)"Socket Task",
			SOCK_STACK_SIZE,
			NULL,
			1,
			&_socketTaskHandle);
}

uint8_t wifi_start(char *ssid, char *psk) {

	if(_apState != UNINITIALIZED) {
		//Turn off WiFi before starting it again
		wifi_stop();
	}

	//Ititialize WiFi subsystem using blocking call
	//May take tens of milliseconds
	if(sl_Start(0, 0, 0) < 0) {
		//Error starting wifi subsystem
		return WIFI_ERROR_START;
	}

	//Wait for system to be fully ready
	//Task_sleep(100);

	//Set WLAN mode to AP
	sl_WlanSetMode(ROLE_AP);

	//Generate SSID and channel number
	uint8_t channel = AP_CHANNEL;

	//Set AP specific configuration settings
	sl_WlanSet(SL_WLAN_CFG_AP_ID, 0, strlen(ssid), (unsigned char*)ssid);	//SSID
	sl_WlanSet(SL_WLAN_CFG_AP_ID, 3, 1, &channel);						//Channel

	//Set security settings
	uint8_t secType = SL_SEC_TYPE_WPA_WPA2;
	sl_WlanSet(SL_WLAN_CFG_AP_ID, WLAN_AP_OPT_SECURITY_TYPE, 1, &secType); //WPA2
	sl_WlanSet(SL_WLAN_CFG_AP_ID, WLAN_AP_OPT_PASSWORD, strlen(psk), psk);

	/*	Use default IP settings:
	 * 		IP:			192.168.1.1
	 * 		Gateway: 	192.168.1.1
	 * 		DNS:		192.168.1.1
	 * 		Subnet:		255.255.255.0
	 */

	//_NetCfgIpV4Args_t ipV4;

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
	if(sl_Start(NULL, NULL, NULL) < 0) {
		//Error starting wifi subsystem
		return WIFI_ERROR_START;
	}

	//Start DHCP server (should start by default)
	sl_NetAppStart(SL_NET_APP_DHCP_SERVER_ID);
	//sl_NetCfgSet(SL_IPV4_STA_P2P_CL_DHCP_ENABLE)

	_apState = DISCONNECTED;

	return 0;
}

void wifi_stop() {
	//Make sure that WiFi is currently on
	if(_apState != UNINITIALIZED) {
		//Change AP state
		_apState = UNINITIALIZED;

		//Stop simplelink
		sl_Stop(100);
	}
}

void SimpleLinkWlanEventHandler(SlWlanEvent_t* event) {
	switch(event->Event) {
		case SL_WLAN_STA_CONNECTED_EVENT:
			//New station has connected to AP

			//Update state
			_apState = CONNECTED_NO_IP;
		break;

		case SL_WLAN_STA_DISCONNECTED_EVENT:
			//Station has disconnected from AP

			//Update state
			_apState = DISCONNECTED;
		break;

		default:
			//Unknown event
		break;
	}
}

void SimpleLinkGeneralEventHandler(SlDeviceEvent_t* event) {
	//This handler should only be called on error
}

void SimpleLinkHttpServerCallback(SlHttpServerEvent_t* event, SlHttpServerResponse_t* response) {
	//Not using HTTP server right now
}

void SimpleLinkNetAppEventHandler(SlNetAppEvent_t* event) {
	switch(event->Event) {
		case SL_NETAPP_IPV4_IPACQUIRED_EVENT:
			//This device has aquired an IP address
		break;

		case SL_NETAPP_IP_LEASED_EVENT:
			//A station has connected and received an IP address

			//Update state
			_apState = CONNECTED_WITH_IP;
		break;

		case SL_NETAPP_IP_RELEASED_EVENT:
			//The connected station has released it's IP address

			//Update state
			_apState = CONNECTED_NO_IP;
		break;

		default:
			//Unknown event
		break;
	}
}


void SimpleLinkSockEventHandler(SlSockEvent_t* event) {
	//TODO
}

void task_socket() {
    wifi_start(AP_SSID, AP_PSK);

	while(1) {
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
			//Failed to create listen socket

			osi_Sleep(10);

			continue;
		}

		listenAddr.sin_family = SL_AF_INET;
		listenAddr.sin_port = sl_Htons(TCP_PORT);
		listenAddr.sin_addr.s_addr = 0;

		//Bind the listen socket to the TCP_PORT
		if(sl_Bind(listenSocket, (SlSockAddr_t*)&listenAddr, sizeof(SlSockAddrIn_t)) < 0) {
			//Failed to bind listening socket to IP address

			sl_Close(listenSocket);

			osi_Sleep(10);

			continue;
		}

		//Start listening
		if(sl_Listen(listenSocket, 0) < 0) {
			//Failed to start listening for connections

			sl_Close(listenSocket);

			osi_Sleep(10);

			continue;
		}

		//Update state
		_socketState = LISTENING;

		//Make socket nonblocking
		if(makeSocketNonblocking(listenSocket) < 0) {
			//Failed to make listen socket nonblocking

			osi_Sleep(10);

			sl_Close(listenSocket);

			continue;
		}

		while(_apState == CONNECTED_WITH_IP) {
			//Wait for client to connect
			_clientSocket = waitForClient(listenSocket, (SlSockAddr_t*)&clientAddr, addrLen);

			//Make sure the socket is valid
			if(_clientSocket < 0)
				continue;

			//Make socket nonblocking
			if(makeSocketNonblocking(_clientSocket) < 0) {
				//Failed to make client socket nonblocking

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

					//Forward data to UART
					uart_send(recvBuffer, retval);
				}

				//Sleep to give other tasks processor time
				osi_Sleep(1);
			}

			//The client has disconnected here

			//Update state
			_socketState = LISTENING;

			//Close client socket
			sl_Close(_clientSocket);
		}

		//Close listen socket
		sl_Close(listenSocket);

		//Update state
		_socketState = STOPPED;

		//The listen socket has stopped
	}
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
