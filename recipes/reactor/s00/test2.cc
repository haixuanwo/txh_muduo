/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-10 16:25:07
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-10 16:50:11
 * @Description: file content
 */
#include "EventLoop.h"
#include "thread/Thread.h"

muduo::EventLoop* g_loop;

void threadFunc()
{
  g_loop->loop();
}

int main()
{
  muduo::EventLoop loop;
  g_loop = &loop;

  #if 1
  muduo::Thread t(threadFunc);
  t.start();
  t.join();
  #else
  loop.loop();
  #endif

  return 0;
}
