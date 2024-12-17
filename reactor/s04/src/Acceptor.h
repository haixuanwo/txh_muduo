/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 19:24:09
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-12 16:54:28
 * @Description: file content
 */
#pragma once

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#include "Channel.h"
#include "Socket.h"

namespace muduo
{

class EventLoop;
class InetAddress;

///
/// Acceptor of incoming TCP connections.
///
class Acceptor : boost::noncopyable
{
 public:
  typedef boost::function<void (int sockfd,
                                const InetAddress&)> NewConnectionCallback;

  Acceptor(EventLoop* loop, const InetAddress& listenAddr);

  void setNewConnectionCallback(const NewConnectionCallback& cb)
  { newConnectionCallback_ = cb; }

  bool listenning() const { return listenning_; }
  void listen();

 private:
  void handleRead();

  EventLoop* loop_;
  Socket acceptSocket_;
  Channel acceptChannel_;
  NewConnectionCallback newConnectionCallback_;
  bool listenning_;
};

}
