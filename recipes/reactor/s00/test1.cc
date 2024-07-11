/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-10 15:08:13
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-10 16:42:07
 * @Description: file content
 */

#include "EventLoop.h"
#include "thread/Thread.h"
#include <stdio.h>

void threadFunc()
{
    printf("threadFunc running pid = %d, tid = %d\n", getpid(), muduo::CurrentThread::tid());
    muduo::EventLoop loop;
    loop.loop();
}

int main()
{
    printf("main pid = %d, tid = %d\n", getpid(), muduo::CurrentThread::tid());

    muduo::EventLoop loop;
    muduo::Thread thread(threadFunc);

    thread.start();
    loop.loop();

    pthread_exit(nullptr);
    return 0;
}
