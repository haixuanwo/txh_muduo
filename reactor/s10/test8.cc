/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-12 19:04:32
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-12 19:04:42
 * @Description: file content
 */
#include "TcpServer.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include <stdio.h>

void onConnection(const muduo::TcpConnectionPtr& conn)
{
  if (conn->connected())
  {
    printf("onConnection(): tid=%d new connection [%s] from %s\n",
           muduo::CurrentThread::tid(),
           conn->name().c_str(),
           conn->peerAddress().toHostPort().c_str());
  }
  else
  {
    printf("onConnection():  tid=%d connection [%s] is down\n",
           muduo::CurrentThread::tid(),
           conn->name().c_str());
  }
}

void onMessage(const muduo::TcpConnectionPtr& conn,
               muduo::Buffer* buf,
               muduo::Timestamp receiveTime)
{
  printf("onMessage(): tid=%d received %zd bytes from connection [%s] at %s\n",
         muduo::CurrentThread::tid(),
         buf->readableBytes(),
         conn->name().c_str(),
         receiveTime.toFormattedString().c_str());

  printf("onMessage(): [%s]\n", buf->retrieveAsString().c_str());
}

int main(int argc, char* argv[])
{
  uint16_t port = 9981;
  printf("main(): pid = %d port[%d]\n", getpid(), port);

  muduo::InetAddress listenAddr(port);
  muduo::EventLoop loop;

  muduo::TcpServer server(&loop, listenAddr);
  server.setConnectionCallback(onConnection);
  server.setMessageCallback(onMessage);

  if (argc > 1) {
    server.setThreadNum(atoi(argv[1]));
  }

  server.start();

  loop.loop();
}
