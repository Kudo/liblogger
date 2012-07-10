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
#include <tPLSocket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>


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
		struct sockaddr_in their_addr; // connector's address information 
		int _sock = -1;
		*sock = (tPLSocket)-1;

		if ((_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket");
			return -1;
		}

		their_addr.sin_family = AF_INET;    // host byte order 
		their_addr.sin_port = htons( port );  // short, network byte order 
		their_addr.sin_addr.s_addr = inet_addr( server );
		memset(&(their_addr.sin_zero), '\0', 8);  // zero the rest of the struct 

		if (connect(_sock, (struct sockaddr *)&their_addr,
					sizeof(struct sockaddr)) == -1) 
		{
			close(_sock);
			perror("connect");
			return -1;
		}
		// connection succeeded.
		*sock = (tPLSocket)_sock;
		return 0;
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
	return send((int) sock,data,dataSize,0);
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
	close((int)*sock);
	*sock = (tPLSocket)-1;
}
