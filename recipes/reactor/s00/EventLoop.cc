/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-10 15:00:21
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-10 16:49:40
 * @Description: file content
 */

#include "EventLoop.h"
#include "logging/Logging.h"

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
    printf("1 EventLoop %p destroyed in thread %d\n", this, threadId_);
    assert(!looping_);
    printf("2 EventLoop %p destroyed in thread %d\n", this, threadId_);

    t_loopInThisThread = nullptr;
}

void EventLoop::loop()
{
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;

    ::poll(nullptr, 0, 5*1000);

    LOG_TRACE << "EventLoop " << this << " stop looping";
    looping_ = false;
}

void EventLoop::abortNotInLoopThread()
{
    LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
            << " was created in threadId_ = " << threadId_
            << ", current thread id = " <<  CurrentThread::tid();
}
