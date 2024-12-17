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
    printf("onConnection(): new connection [%s] from %s\n",
           conn->name().c_str(),
           conn->peerAddress().toHostPort().c_str());
  }
  else
  {
    printf("onConnection(): connection [%s] is down\n",
           conn->name().c_str());
  }
}

void onMessage(const muduo::TcpConnectionPtr& conn,
               const char* data,
               ssize_t len)
{
  printf("onMessage(): received %zd bytes from connection [%s]\n",
         len, conn->name().c_str());
}

int main()
{
  uint16_t port = 9981;
  printf("main(): pid = %d port[%d]\n", getpid(), port);

  muduo::InetAddress listenAddr(port);
  muduo::EventLoop loop;

  muduo::TcpServer server(&loop, listenAddr);
  server.setConnectionCallback(onConnection);
  server.setMessageCallback(onMessage);
  server.start();

  loop.loop();
}
