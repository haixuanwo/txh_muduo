/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-24 15:00:37
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-24 17:00:38
 * @Description: file content
 */
#include "../thread/Atomic.h"
#include "../datetime/Timestamp.h"
#include "Acceptor.h"
#include "InetAddress.h"
#include "TcpStream.h"

#include <cstring>
#include <thread>

muduo::AtomicInt64 g_bytes;

std::string getMessage()
{
    std::string line;
    for (size_t i = 33; i < 127; i++)
    {
        line.push_back(char(i));
    }
    line += line;

    std::string message;
    for (size_t i = 0; i < 127-33; i++)
    {
        message += line.substr(i, 72) + '\n';
    }

    return message;
}

void measure()
{
    muduo::Timestamp start(muduo::Timestamp::now());
    while (true)
    {
        struct timespec ts = {1, 0};
        ::nanosleep(&ts, nullptr);
        int64_t bytes = g_bytes.getAndSet(0);

        muduo::Timestamp end(muduo::Timestamp::now());
        double elapsed = timeDifference(end, start);
        start = end;
        if (bytes)
        {
            printf("%.3f MiB/s\n", bytes / (1024.0*1024) /elapsed);
        }
    }
}

void chargen(TcpStreamPtr stream)
{
    std::string message = getMessage();
    while (true)
    {
        int nw = stream->sendAll(message.data(), message.size());
        g_bytes.add(nw);
        if (nw < static_cast<int>(message.size()))
        {
            break;
        }
    }
}

void server(char *argv[])
{
    int port = atoi(argv[2]);
    Acceptor acceptor((InetAddress(port)));
    printf("Accepting... port %d\n", port);

    int count = 0;
    while (true)
    {
        TcpStreamPtr stream = acceptor.accept();
        printf("Accepted no %d\n", ++count);

        std::thread thr(chargen, std::move(stream));
        thr.detach();
    }
}

void client(char *argv[])
{
    int port = atoi(argv[2]);
    InetAddress serverAddr(port);

    const char* hostname = argv[1];
    if (InetAddress::resolve(hostname, &serverAddr))
    {
        TcpStreamPtr stream(TcpStream::connect(serverAddr));
        if (stream)
        {
            printf("Connected to %s:%d\n", hostname, port);
            chargen(std::move(stream));
        }
        else
        {
            printf("Connect to %s:%d failed\n", hostname, port);
            perror("");
        }
    }
    else
    {
        printf("Resolve %s failed\n", hostname);
    }
}

// a thread per connection current chargen server and client
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s hostname port\n %s -l port", argv[0], argv[0]);
        return -1;
    }

    std::thread(measure).detach();

    if (strcmp(argv[1], "-l") == 0)
    {
        server(argv);
    }
    else
    {
        client(argv);
    }

    return 0;
}
