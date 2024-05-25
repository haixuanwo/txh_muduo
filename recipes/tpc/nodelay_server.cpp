/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-23 10:01:32
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-25 11:26:53
 * @Description: file content
 */

#include <thread>
#include <vector>
#include <iostream>
#include <string.h>
#include <sys/time.h>

#include "Common.h"
#include "Acceptor.h"
#include "InetAddress.h"
#include "TcpStream.h"

// an interative request-response server
int main(int argc, char* argv[])
{
    InetAddress listenAddr(3210);
    Acceptor acceptor(listenAddr);
    printf("Accepting... Ctrl-C to quit\n");

    int count = 0;
    bool nodelay = argc > 1 && strcmp(argv[1], "-D") == 0;

    while (true)
    {
        TcpStreamPtr tcpStream = acceptor.accept();
        printf("accepted no. %d client\n", ++count);
        if (nodelay)
        {
            tcpStream->setTcpNoDelay(true);
        }

        while (1)
        {
            int len = 0;
            int nr = tcpStream->receiveAll(&len, sizeof(len));
            if (nr <=0)
            {
                break;
            }

            printf("%f received header %d bytes, len = %d\n", now_seconds(), nr, len);
            assert(nr == sizeof(len));

            std::vector<char> payload(len);
            nr = tcpStream->receiveAll(payload.data(), len);
            printf("%f received payload %d bytes\n", now_seconds(), nr);
            assert(nr == len);

            int nw = tcpStream->sendAll(&len, sizeof len);
            assert(nw == sizeof len);
        }

        printf("no. %d client ended\n", count);
    }

    return 0;
}
