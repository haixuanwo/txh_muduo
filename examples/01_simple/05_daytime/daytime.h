
#ifndef DAYTIME_H
#define DAYTIME_H

#include "muduo/net/TcpServer.h"

// RFC 867
class DaytimeServer
{
public:
    DaytimeServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr);

    void start();

private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time);

    muduo::net::TcpServer server_;
};

#endif
