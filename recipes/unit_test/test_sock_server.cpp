/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-23 22:56:39
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-23 23:22:05
 * @Description: file content
 */

#include "../tpc/Socket.h"
#include "../tpc/InetAddress.h"
#include <strings.h>
#include <unistd.h>

int main()
{
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
        if (read(clientfd, buf, sizeof(buf)) >= 0)
        {
            printf("recv %s\n", buf);
        }
    }

    return 0;
}
