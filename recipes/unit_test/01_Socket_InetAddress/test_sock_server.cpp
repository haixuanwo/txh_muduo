/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-23 22:56:39
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-24 10:00:52
 * @Description: file content
 */
#include <strings.h>
#include <unistd.h>
#include <iostream>

#include "../tpc/Socket.h"
#include "../tpc/InetAddress.h"

int main(int argc, char* argv[])
{
    std::cout << "T -------- start --- " << argv[0]<< std::endl;

    Socket sock(Socket::createTCP());
    // sock.setReuseAddr(true);
    sock.bindOrDie(InetAddress(8888, false));
    sock.listenOrDie();

    int clientfd = sock.acceptOrDie();
    printf("accept clientfd[%d]\n", clientfd);

    char buf[1024] = {0};
    while (1)
    {
        bzero(buf, sizeof(buf));
        if (read(clientfd, buf, sizeof(buf)) <= 0)
        {
            std::cout << "T --- read end" << buf << std::endl;
            break;
        }

        std::cout << "T --- read "<< buf << std::endl;
    }

    std::cout << argv[0] <<" -------- end -----" << std::endl;
    return 0;
}
