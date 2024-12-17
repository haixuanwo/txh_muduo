/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 19:40:43
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-11 19:40:55
 * @Description: file content
 */
#include "Acceptor.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "SocketsOps.h"
#include <stdio.h>

void newConnection(int sockfd, const muduo::InetAddress& peerAddr)
{
  printf("newConnection(): accepted a new connection from %s\n",
         peerAddr.toHostPort().c_str());
  ::write(sockfd, "How are you?\n", 13);
  muduo::sockets::close(sockfd);
}

int main()
{
  uint16_t port = 9981;
  printf("main(): pid = %d, port[%d]\n", getpid(), port);

  muduo::InetAddress listenAddr(port);
  muduo::EventLoop loop;

  muduo::Acceptor acceptor(&loop, listenAddr);
  acceptor.setNewConnectionCallback(newConnection);
  acceptor.listen();

  loop.loop();
}
