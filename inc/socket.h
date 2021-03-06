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
 * @file socket.h
 * @author karthik rao
 * @date 05 March 2021
 * @brief file is the basis of abstration of socket interface. This is does to simplify
 * Socket operation use to as shown in client_app.cpp.
 * It looks something as shown below
 *      @param1 is the host address
 *      @param2 is the port operation 
 *      @param3 is the protocol. tcp or udp
 * 
 *      Socket local_socket("127.0.0.1", 5000, tcp);
        local_socket.init();
        local_socket.send_data("From class sockets");
 */


#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


namespace socket_consts {

  const int MAXLINE = 2048;
  enum socket_type {
      tcp=1,
      udp,
      tcp_and_udp // reserved for server operation 
  };
}



class Socket {
public:
Socket(std::string host, int port, std::string type);
bool init();
virtual ~Socket();
bool send_data(std::string msg);
sockaddr_in & get_server_addr_data(); 

protected:
int sockfd;
std::string buffer;
struct sockaddr_in servaddr;
std::string host;
socket_consts::socket_type type;
int port;

};