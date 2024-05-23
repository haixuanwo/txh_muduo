
#include "../tpc/Socket.h"
#include "../tpc/InetAddress.h"
#include <strings.h>
#include <unistd.h>

int main()
{
    Socket sock(Socket::createTCP());
    sock.bindOrDie(InetAddress(8080, false));
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
