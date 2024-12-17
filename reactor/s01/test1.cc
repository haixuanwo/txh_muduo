/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 13:52:52
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-11 13:53:15
 * @Description: file content
 */
#include "EventLoop.h"
#include "Thread.h"
#include <stdio.h>

void threadFunc()
{
  printf("threadFunc(): pid = %d, tid = %d\n",
         getpid(), muduo::CurrentThread::tid());

  muduo::EventLoop loop;
  loop.loop();
}

int main()
{
  printf("main(): pid = %d, tid = %d\n",
         getpid(), muduo::CurrentThread::tid());

  muduo::EventLoop loop;

  muduo::Thread thread(threadFunc);
  thread.start();

  loop.loop();
  pthread_exit(NULL);
}
