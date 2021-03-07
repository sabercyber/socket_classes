
/****************************************************************************
#include "socket.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Incorrect syntax : User <app> hostname port tcp or upd" << std::endl;
    }
    else 
    {
        Socket local_socket(argv[1], atoi(argv[2]), argv[3]);
        local_socket.init();
        local_socket.send_data("From class sockets");
        //test code 
         struct sockaddr_in &local = local_socket.get_server_addr_data();
         std::cout << local.sin_port << std::endl;
    }
    

    return 0;
}