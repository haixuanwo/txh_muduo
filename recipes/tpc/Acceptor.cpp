/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-24 10:06:49
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-24 14:34:01
 * @Description: file content
 */

#include "Acceptor.h"
#include "TcpStream.h"
#include <stdio.h>
#include <sys/socket.h>

Acceptor::Acceptor(const InetAddress& listenAddr)
    : listenSock_(Socket::createTCP())
{
    listenSock_.setReuseAddr(true);
    listenSock_.bindOrDie(listenAddr);
    listenSock_.listenOrDie();
}

// thread safe
TcpStreamPtr Acceptor::accept()
{
    int sockfd = ::accept(listenSock_.fd(), nullptr, nullptr);
    if (sockfd >= 0)
    {
        return TcpStreamPtr(new TcpStream(Socket(sockfd)));
    }
    else
    {
        perror("Acceptor::accept");
        return TcpStreamPtr();
    }
}
