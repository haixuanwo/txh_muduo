/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-25 14:05:20
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-25 14:49:24
 * @Description: file content
 */
#include <thread>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include "Common.h"
#include "Socket.h"
#include "InetAddress.h"

const int g_port = 3123;

struct Message
{
    int64_t request;
    int64_t response;
} __attribute__((packed));

static_assert(sizeof(Message) == 16, "Message size should be 16 bytes");

void runServer()
{
    Socket server(Socket::createUDP());
    server.bindOrDie(InetAddress(g_port));
    printf("Server listening on port %d\n", g_port);

    while (true)
    {
        Message message;
        struct sockaddr peerAddr;
        bzero(&message, sizeof(message));
        socklen_t addrLen = sizeof(peerAddr);

        ssize_t nr = ::recvfrom(server.fd(), &message, sizeof(message), 0, &peerAddr, &addrLen);
        if (nr == sizeof message)
        {
            message.response = now_us();
            ssize_t nw = ::sendto(server.fd(), &message, sizeof(message), 0, &peerAddr, addrLen);
            if (nw < 0)
            {
                perror("Error sending response\n");
            }
            else if (nw != sizeof message)
            {
                printf("sent message of  %zd bytes, expected %zd bytes\n", nw, sizeof message);
            }
        }
        else if (nr < 0)
        {
            perror("Error receiving request\n");
        }
        else
        {
            printf("received message of %zd bytes, expected %zd bytes\n", nr, sizeof message);
        }
    }
}

void runClient(const char* server_hostname)
{
    Socket sock(Socket::createUDP());
    InetAddress serverAddr(server_hostname, g_port);

    if (!InetAddress::resolve(server_hostname, &serverAddr))
    {
        printf("Error resolving %s\n", server_hostname);
        return;
    }

    if (sock.connect(serverAddr) != 0)
    {
        printf("Error connecting to server\n");
        return;
    }

    std::thread thr([&sock](){
        while (1)
        {
            Message message = {0, 0};
            message.request = now_us();
            ssize_t nw = sock.write(&message, sizeof(message));
            if (nw < 0)
            {
                perror("Error sending request\n");
            }
            else if (nw != sizeof message)
            {
                printf("sent message of  %zd bytes, expected %zd bytes\n", nw, sizeof message);
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

    });

    while (1)
    {
        Message message = {0, 0};
        ssize_t nr = sock.read(&message, sizeof(message));
        if (nr == sizeof message)
        {
            int64_t back = now_us();
            int64_t mine = (back - message.request)/2;
            printf("now %jd roundtrip %jd clock err %jd\n", back, back -message.request, message.response - mine);
        }
        else if (nr < 0)
        {
            perror("Error receiving response\n");
            break;
        }
        else
        {
            printf("received message of %zd bytes, expected %zd bytes\n", nr, sizeof message);
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s server|client [server_hostname]\n", argv[0]);
        return -1;
    }

    if (strcmp(argv[1], "-s") == 0)
    {
        runServer();
    }
    else
    {
        runClient(argv[1]);
    }

    return 0;
}
