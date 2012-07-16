/*
       Licensed to the Apache Software Foundation (ASF) under one
       or more contributor license agreements.  See the NOTICE file
       distributed with this work for additional information
       regarding copyright ownership.  The ASF licenses this file
       to you under the Apache License, Version 2.0 (the
       "License"); you may not use this file except in compliance
       with the License.  You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

       Unless required by applicable law or agreed to in writing,
       software distributed under the License is distributed on an
       "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
       KIND, either express or implied.  See the License for the
       specific language governing permissions and limitations
       under the License.
 */
/**
 * \file Implementation of the Socket Abstraction API for Win32 platform.
 * */
#include <tPLSocket.h>
#include <winsock2.h>
#include <winbase.h>
#include <stdio.h>
#include <win32_support.h>
#pragma comment(lib, "Ws2_32.lib")


/* Function to create a \b connected socket.
 * \param [in]  server 	The log server.
 * \param [in]  port	The log server port.
 * \param [out] sock	The socket handle.
 * \returns -1 on failure and \a sock will be -1 , or else 0 on success and sock will be non zero.
 * */
int PLCreateConnectedSocket(const char* server, int port, tPLSocket *sock)
{
	if(!server || !sock)
	{
		fprintf(stderr,"invalid args to %s",__func__);
		return -1;
	}
	else
	{
		//----------------------
		struct sockaddr_in clientService; 
		int iResult  = 0;
		SOCKET _sock = 0;
		// Initialize Winsock
		WSADATA wsaData;
		iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (iResult != NO_ERROR)
		{
			fprintf(stderr,"Error at WSAStartup()\n");
			goto WSA_CLEANUP_EXIT;
		}


		//----------------------
		// Create a SOCKET for connecting to server
		_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if ( _sock == INVALID_SOCKET ) {
			fprintf(stderr,"Error at socket(): %ld\n", WSAGetLastError());
			goto WSA_CLEANUP_EXIT;
		}

		//----------------------
		// The sockaddr_in structure specifies the address family,
		// IP address, and port of the server to be connected to.
		clientService.sin_family = AF_INET;
		clientService.sin_addr.s_addr = inet_addr( server );
		clientService.sin_port = htons( port );

		//----------------------
		// Connect to server.
		if ( connect( _sock, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR) {
			fprintf(stderr, "Failed to connect.\n" );
			goto WSA_CLEANUP_EXIT;
		}

		*sock = _sock;
		return 0;

WSA_CLEANUP_EXIT:
		if (_sock != INVALID_SOCKET)
			closesocket(_sock);
		WSACleanup();
		return -1;
	}
}

/* Send data over socket.
 * \param [in] tPLSocket 	The socket handle created via \ref CreateConnectedSocket.
 * \param [in] data			The data to send. 
 * \param [in] dataSize		The size of data.
 * \return On success, the amount of bytes sent, -1 otherwise.
 * */
int PLSockSend(tPLSocket sock,const void* data,const int dataSize)
{
	return send((SOCKET) sock,data,dataSize,0);
}

/* Close the Socket.
 * \param [in,out] sock	The socket handle created via \ref CreateConnectedSocket.
 * */
void PLDestroySocket(tPLSocket * sock)
{
	if(!sock)
	{
		// invalid args.
		fprintf(stderr,"invalid args to %s",__func__);
		return;
	}
	closesocket((SOCKET)*sock);
	*sock = INVALID_SOCKET;
}
