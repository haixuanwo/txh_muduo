/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-11 10:57:52
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-11 10:57:58
 * @Description: file content
 */
#pragma once

#include "thread/Condition.h"
#include "thread/Mutex.h"
#include "thread/Thread.h"

#include <boost/noncopyable.hpp>

namespace muduo
{

class EventLoop;

class EventLoopThread : boost::noncopyable
{
 public:
  EventLoopThread();
  ~EventLoopThread();
  EventLoop* startLoop();

 private:
  void threadFunc();

  EventLoop* loop_;
  bool exiting_;
  Thread thread_;
  MutexLock mutex_;
  Condition cond_;
};

}
