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
 * @file socket.cpp
 * @author karthik rao
 * @date 05 March 2021
 * @brief File implements all the functions declared for Socket class
 *     
 */



#include "socket.h"



Socket::Socket(std::string host = "127.0.0.1", int port= 5000, std::string type_req = "tcp"):
host(host), port(port)
{
    if (!strcmp(type_req.c_str(),"tcp"))
    {
        type = socket_consts::socket_type::tcp;
       
    }
    else if (!strcmp(type_req.c_str(),"udp"))
    { 
        type = socket_consts::socket_type::udp;   
    }
    else if (!strcmp(type_req.c_str(),"tcp_and_udp"))
    { 
        type = socket_consts::socket_type::tcp_and_udp;   
    }
    else
    {
        type = socket_consts::socket_type::udp;   
    }
    std::cout << "Type of socket is " << type << std::endl;
    

    memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr(host.c_str());
    
}


bool Socket::init(){
    bool status = false;
    if (type == socket_consts::socket_type::tcp){
     if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "socket creation TCP failed" << std::endl;
		return status;
     }

    }
    else{
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		std::cout << "socket creation UDP failed" << std::endl;
		return status;
     }

    }
    if (connect(sockfd, (struct sockaddr*)&servaddr,
							sizeof(servaddr)) < 0) {
		std::cout << "Socket connect failed" << std::endl;
	}
}
Socket::~Socket(){}

bool Socket::send_data(std::string msg){

    buffer = msg;
    write(sockfd, buffer.c_str(), buffer.length());
    close(sockfd);

}

sockaddr_in& Socket::get_server_addr_data()
{
    return servaddr;
}


