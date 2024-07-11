/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-11 14:27:40
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-11 14:32:40
 * @Description: file content
 */
// copied from muduo/net/tests/TimerQueue_unittest.cc

#include "EventLoop.h"

#include <boost/bind/bind.hpp>
using namespace boost::placeholders;

#include <stdio.h>

int cnt = 0;
muduo::EventLoop* g_loop;

void printTid()
{
  printf("pid = %d, tid = %d\n", getpid(), muduo::CurrentThread::tid());
  printf("now %s\n", muduo::Timestamp::now().toString().c_str());
}

void print(const char* msg)
{
  printf("msg %s %s\n", muduo::Timestamp::now().toString().c_str(), msg);
  if (++cnt == 20)
  {
    g_loop->quit();
  }
}

int main()
{
  printTid();
  muduo::EventLoop loop;
  g_loop = &loop;

  print("main");
  loop.runAfter(1, boost::bind(print, "once1"));
  loop.runAfter(1.5, boost::bind(print, "once1.5"));
  loop.runAfter(2.5, boost::bind(print, "once2.5"));
  loop.runAfter(3.5, boost::bind(print, "once3.5"));
  loop.runEvery(2, boost::bind(print, "every2"));
  loop.runEvery(3, boost::bind(print, "every3"));

  loop.loop();
  print("main loop exits");
  sleep(1);
}
