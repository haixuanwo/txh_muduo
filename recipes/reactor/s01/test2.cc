/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-10 17:15:41
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-10 17:15:47
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
  muduo::Thread t(threadFunc);
  t.start();
  t.join();
}
