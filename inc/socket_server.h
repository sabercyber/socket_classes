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
 * @file socket_server.h
 * @author karthik rao
 * @date 05 March 2021
 * @brief File is contails the class of Socket_server that inherits from Socket to
 * implement server features.
 */

#include "socket.h"
#include <netinet/in.h>
#include <signal.h>
#include <cstdlib>

class Socket_server : public Socket
{
public:
Socket_server(int port,std::string type_data);
~Socket_server();
int run_server();
private:
void bind_to_tcp();
void bind_to_udp();
void bind_to_socket();


int listenfd, connfd, udpfd,nready, maxfdp1;

fd_set rset;
ssize_t n;
socklen_t len;
//const int on = 1;
struct sockaddr_in cliaddr/*, servaddr*/;
std::string message = "Hello Client";

int msg_backlog = 10;
char server_buffer[socket_consts::MAXLINE];

};