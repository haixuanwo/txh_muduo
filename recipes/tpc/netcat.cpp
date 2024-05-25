/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-24 15:00:37
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-25 10:36:47
 * @Description: file content
 */
#include <thread>
#include <cstring>
#include <unistd.h>

#include "Acceptor.h"
#include "InetAddress.h"
#include "TcpStream.h"

int write_n(int fd, const void* buf, int length)
{
    int written = 0;
    while (written < length)
    {
        int nw = ::write(fd, static_cast<const char*>(buf) + written, length - written);
        if (nw > 0)
        {
            written += nw;
        }
        else if (0 == nw)
        {
            break;
        }
        else if (EINTR != errno)
        {
            perror("write");
            break;
        }
    }
    return written;
}

void run(TcpStreamPtr stream)
{
    // Caution: a bad example, for closing connection
    std::thread thr([&stream](){

        char buf[8192];
        int nr = 0;

        while (true)
        {
            nr = stream->receiveSome(buf, sizeof(buf));
            if (nr <= 0)
            {
                break;
            }

            int nw = write_n(STDOUT_FILENO, buf, nr);
            if (nw < nr)
            {
                break;
            }
        }

        ::exit(0);
    });

    char buf[8192];
    int nr = 0;
    while (1)
    {
        nr = ::read(STDIN_FILENO, buf, sizeof(buf));
        if (nr <= 0)
        {
            break;
        }

        int nw = stream->sendAll(buf, nr);
        if (nw < nr)
        {
            break;
        }
    }

    stream->shutdownWrite();
    thr.join();
}

void server(int port)
{
    std::unique_ptr<Acceptor> acceptor(new Acceptor(InetAddress(port)));
    TcpStreamPtr stream = acceptor->accept();
    if (stream)
    {
        acceptor.reset();
        run(std::move(stream));
    }
    else
    {
        printf("Failed to accept\n");
    }
}

void client(const char* hostname, int port)
{
    InetAddress serverAddr(port);
    if (InetAddress::resolve(hostname, &serverAddr))
    {
        TcpStreamPtr stream(TcpStream::connect(serverAddr));
        if (stream)
        {
            run(std::move(stream));
        }
        else
        {
            printf("Failed to connect %s\n", serverAddr.toIpPort().c_str());
            perror("");
        }
    }
    else
    {
        printf("Failed to resolve %s\n", hostname);
        perror("");
    }
}


int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s ip port\n %s -l port", argv[0], argv[0]);
        return -1;
    }

    int port = atoi(argv[2]);
    if (strcmp(argv[1], "-l") == 0)
    {
        server(port);
    }
    else
    {
        client(argv[1], port);
    }
    return 0;
}
