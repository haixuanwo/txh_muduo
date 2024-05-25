/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-25 09:12:04
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-25 09:28:16
 * @Description: file content
 */
#include "Acceptor.h"
#include "InetAddress.h"
#include "TcpStream.h"

#include <thread>
#include <string.h>

int main(int argc, char* argv[])
{
    InetAddress listenAddr(3007);
    Acceptor acceptor(listenAddr);

    int count = 0;
    bool nodelay = argc > 1 && strcmp(argv[1], "-D") == 0;

    while (1)
    {
        TcpStreamPtr tcpStream = acceptor.accept();
        printf("accepted ---\n");

        if (nodelay)
        {
            tcpStream->setTcpNoDelay(true);
        }

        // C++11 doesn't allow capturing unique_ptr in lambda, C++14 allows.
        std::thread thr([count] (TcpStreamPtr&& stream) {
            printf("thread for no. %d client started\n", count);
            char buffer[4096];
            int nr = 0;

            while (1)
            {
                nr = stream->receiveSome(buffer, sizeof(buffer));
                if (nr <= 0)
                {
                    break;
                }
                printf("received %d bytes from client\n", nr);

                int nw = stream->sendAll(buffer, nr);
                if (nw < nr)
                {
                    break;
                }
            }

            printf("thread for no. %d client ends.\n", count);
        }, std::move(tcpStream));

        thr.detach();
    }

    return 0;
}
