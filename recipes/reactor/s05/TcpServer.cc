/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-11 13:55:37
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-11 14:21:35
 * @Description: file content
 */
// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "TcpServer.h"

#include "logging/Logging.h"
#include "Acceptor.h"
#include "EventLoop.h"
#include "SocketsOps.h"

#include <boost/bind/bind.hpp>
using namespace boost::placeholders;

#include <stdio.h>  // snprintf

using namespace muduo;

TcpServer::TcpServer(EventLoop* loop, const InetAddress& listenAddr)
  : loop_(CHECK_NOTNULL(loop)),
    name_(listenAddr.toHostPort()),
    acceptor_(new Acceptor(loop, listenAddr)),
    started_(false),
    nextConnId_(1)
{
  acceptor_->setNewConnectionCallback(
      boost::bind(&TcpServer::newConnection, this, _1, _2));
}

TcpServer::~TcpServer()
{
}

void TcpServer::start()
{
  if (!started_)
  {
    started_ = true;
  }

  if (!acceptor_->listenning())
  {
    loop_->runInLoop(
        boost::bind(&Acceptor::listen, get_pointer(acceptor_)));
  }
}

void TcpServer::newConnection(int sockfd, const InetAddress& peerAddr)
{
  loop_->assertInLoopThread();
  char buf[32];
  snprintf(buf, sizeof buf, "#%d", nextConnId_);
  ++nextConnId_;
  std::string connName = name_ + buf;

  LOG_INFO << "TcpServer::newConnection [" << name_
           << "] - new connection [" << connName
           << "] from " << peerAddr.toHostPort();
  InetAddress localAddr(sockets::getLocalAddr(sockfd));
  // FIXME poll with zero timeout to double confirm the new connection
  TcpConnectionPtr conn(
      new TcpConnection(loop_, connName, sockfd, localAddr, peerAddr));
  connections_[connName] = conn;
  conn->setConnectionCallback(connectionCallback_);
  conn->setMessageCallback(messageCallback_);
  conn->connectEstablished();
}
