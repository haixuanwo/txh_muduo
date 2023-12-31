
#ifndef ECHO_H
#define ECHO_H

#include "muduo/net/TcpServer.h"

// RFC 862
class EchoServer
{
public:
    EchoServer(muduo::net::EventLoop* loop,
        const muduo::net::InetAddress& listenAddr);

    void start(); // call server_.start();

private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    void onMessage(const muduo::net::TcpConnectionPtr& conn,
        muduo::net::Buffer* buf, muduo::Timestamp time);

    muduo::net::TcpServer server_;
};

#endif
