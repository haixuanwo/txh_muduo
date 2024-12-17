/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 13:52:52
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-11 14:05:52
 * @Description: file content
 */
#include "EventLoop.h"
#include "Thread.h"

muduo::EventLoop* g_loop = nullptr;

void threadFunc()
{
    g_loop->loop();
}

int main()
{
    muduo::EventLoop loop;
    g_loop = &loop;

    muduo::Thread thread(threadFunc);
    thread.start();
    thread.join();
}
