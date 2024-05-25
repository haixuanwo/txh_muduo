/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-23 10:01:32
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-25 11:50:19
 * @Description: file content
 */

#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "Common.h"
#include "InetAddress.h"
#include "TcpStream.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s [-b] [-D] [-n num] hostname message_lenght\n", argv[0]);
        printf(" -b Buffering request before sending.\n"
               " -D Set TCP_NODELAY.\n"
               " -n num send num concurrent requests, default is 1.\n");
        return -1;
    }

    int opt = 0;
    bool buffering = false;
    bool tcpnodelay = false;
    int num = 1;

    while (1)
    {
        opt = getopt(argc, argv, "bDn:");
        if (-1 ==opt)
        {
            break;
        }

        switch (opt)
        {
            case 'b':
                buffering = true;
                break;
            case 'D':
                tcpnodelay = true;
                break;
            case 'n':
                num = atoi(optarg);
                break;
            default:
                printf("Usage: %s [-b] [-D] [-n num] hostname message_lenght\n", argv[0]);
                return -1;
        }
    }


    if (optind > argc - 2)
    {
        printf("Please specify hostname and message_lenght\n");
        return -1;
    }

    const char* hostname = argv[optind];
    int len = atoi(argv[optind+1]);

    InetAddress addr(3210);
    if (!InetAddress::resolve(hostname, &addr))
    {
        printf("Failed to resolve %s\n", hostname);
        return -1;
    }

    printf("Connecting to %s\n", addr.toIpPort().c_str());
    TcpStreamPtr stream(TcpStream::connect(addr));
    if (!stream)
    {
        printf("Failed to connect to %s\n", addr.toIpPort().c_str());
        perror("");
        return -1;
    }

    if (tcpnodelay)
    {
        stream->setTcpNoDelay(true);
        printf("connected with TCP_NODELAY\n");
    }
    else
    {
        stream->setTcpNoDelay(false);
        printf("connected without TCP_NODELAY\n");
    }

    double start = now_seconds();
    for (int i = 0; i < num; ++i)
    {
        if (buffering)
        {
            std::vector<char> message(len + sizeof len, 'S');
            memcpy(message.data(), &len, sizeof len);
            int nw = stream->sendAll(message.data(), message.size());
            printf("%.6f send %d bytes\n", now_seconds(), nw);
        }
        else
        {
            stream->sendAll(&len, sizeof len);
            printf("%.6f send head %ld bytes\n", now_seconds(), sizeof len);
            usleep(1000);
            std::string payload(len, 'S');
            int nw = stream->sendAll(payload.data(), payload.size());
            printf("%.6f send %d bytes\n", now_seconds(), nw);
        }
    }

    printf("Sent all %d requests, receiving responses...\n", num);
    for (size_t i = 0; i < num; i++)
    {
        int ack = 0;
        int nr = stream->receiveAll(&ack, sizeof ack);
        printf("%.6f receive %d bytes ack = %d\n", now_seconds(), nr, ack);
    }
    printf("total %f seconds\n", now_seconds() - start);

    return 0;
}
