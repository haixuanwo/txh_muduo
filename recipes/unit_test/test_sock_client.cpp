


#include "../tpc/Socket.h"
#include "../tpc/InetAddress.h"
#include <iostream>

int main()
{
    Socket sock(Socket::createTCP());
    if (sock.connect(InetAddress("127.0.0.1", 8888)) <0)
    {
        std::cout << "T --- connect --- fail" << std::endl;
        return -1;
    }

    std::cout << "-------- client -----" << std::endl;

    char buf[] = {"hello world"};
    while (1)
    {
        std::cout << "-------- 1 end -----" << std::endl;
        sock.write(buf, sizeof(buf));
        std::cout << "-------- 2 end -----" << std::endl;
    }

    std::cout << "-------- end -----" << std::endl;
    return 0;
}