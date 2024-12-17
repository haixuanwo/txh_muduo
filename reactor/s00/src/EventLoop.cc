/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-10 19:55:23
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-11 14:15:15
 * @Description: file content
 */

#include "EventLoop.h"
#include "Logging.h"
#include <assert.h>
#include <poll.h>

using namespace muduo;

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
    : looping_(false),
      threadId_(CurrentThread::tid())
{
    LOG_TRACE << "EventLoop created " << this << " in thread " << threadId_;

    if (t_loopInThisThread)
    {
        LOG_FATAL << "Another EventLoop " << t_loopInThisThread
                  << " exists in this thread " << threadId_;
    }
    else
    {
        t_loopInThisThread = this;
    }
}

EventLoop::~EventLoop()
{
    assert(!looping_);
    t_loopInThisThread = nullptr;
}

void EventLoop::loop()
{
    assert(!looping_);
    assertInLoopThread();

    looping_ = true;
    LOG_TRACE << "EventLoop " << this << " start looping";

    ::poll(NULL, 0, 5*1000);
    LOG_TRACE << "EventLoop " << this << " stop looping";
    looping_ = false;
}

void EventLoop::abortNotInLoopThread()
{
    LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
              << " was created in threadId_ = " << threadId_
              << ", current thread id = " << CurrentThread::tid();
}
