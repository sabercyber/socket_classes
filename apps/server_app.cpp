
#include "socket_server.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << " Incorrect Syntax: <app> port tcp/upd/tcp_and_udp"<<std::endl;
    }
    else
    {
        Socket_server myserver(atoi(argv[1]),argv[2]);
        std::cout << " about to call run_server" << std::endl;
        myserver.send_data("Hi there from server");
        myserver.run_server();
    }
    return 0;
}