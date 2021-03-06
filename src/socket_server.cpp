
/****************************************************************************
 * Copyright (C) 2021 by Karthik Rao (sabercyber)                                  *
 *                                                                          *
 * This file is part of C++ socket classes .                                                *
 *                                                                          *
 *   MIT License



Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 ****************************************************************************/

/**
 * @file socket_server.cpp
 * @author karthik rao
 * @date 05 March 2021
 * @brief File implements class of Socket_server which is inherited from Socket
 *     
 */

#include "socket_server.h"

Socket_server::Socket_server(int port,std::string type_data)
: Socket("",port,type_data)
{
    Socket::servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
}
    

Socket_server::~Socket_server()
{
    
}


void Socket_server::bind_to_tcp()
{
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(listenfd, 10);
}

void Socket_server::bind_to_udp()
{
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
	// binding server addr structure to udp sockfd
	bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
}

void Socket_server::bind_to_socket()
{
    bind_to_tcp();
    /* create UDP socket */
    bind_to_udp();
	
}
int Socket_server::run_server()
{
    // clear the descriptor set
	FD_ZERO(&rset);

    if (Socket::type == socket_consts::socket_type::tcp)
    {
        bind_to_tcp();
        maxfdp1 = listenfd +1;
       
    }
    else if (Socket::type == socket_consts::socket_type::udp)
    {
        bind_to_udp();
        maxfdp1 = udpfd +1;
        
       
    }
    else 
    {
        bind_to_socket();
        maxfdp1 = std::max(listenfd, udpfd) + 1;
        
    }

    

    for (;;) {

		// set listenfd and udpfd in readset
        if (Socket::type == socket_consts::socket_type::tcp_and_udp)
        {
		    FD_SET(listenfd, &rset);
            FD_SET(udpfd, &rset);
        }
		else if(Socket::type == socket_consts::socket_type::udp)
            FD_SET(udpfd, &rset);
        else if(Socket::type == socket_consts::socket_type::tcp)
            FD_SET(listenfd, &rset);

		// select the ready descriptor
		printf("Entering Select call\n");
		nready = select(maxfdp1, &rset, NULL, NULL, NULL);

		// if tcp socket is readable then handle
		// it by accepting the connection
		if (FD_ISSET(listenfd, &rset)) {
			len = sizeof(cliaddr);
			connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
			
				
				bzero(server_buffer, sizeof(server_buffer));
				printf("Message From TCP client: ");
				read(connfd, server_buffer,sizeof(server_buffer));
				
				std::cout <<"Message receieved : " << server_buffer<< std::endl;
				write(connfd, (const char*)message.c_str(),sizeof(server_buffer));
				close(connfd);
				
			
			
		}
		// if udp socket is readable receive the message.
		if (FD_ISSET(udpfd, &rset)) {
			len = sizeof(cliaddr);
			bzero(server_buffer, sizeof(server_buffer));
			printf("\nMessage from UDP client: ");
			n = recvfrom(udpfd,server_buffer, sizeof(server_buffer), 0,
						(struct sockaddr*)&cliaddr, &len);
			std::cout <<"Message receieved : " << server_buffer<< std::endl;
			sendto(udpfd, (const char*)message.c_str(), sizeof(server_buffer), 0,
				(struct sockaddr*)&cliaddr, sizeof(cliaddr));
		}
	}

}