
#pragma once

#include "Thread.h"

namespace muduo
{

class EventLoop : boost::noncopyable
{
public:
    EventLoop();
    ~EventLoop();

    void loop();

    void assertInLoopThread()
    {
        if (!isInLoopThread())
        {
            abortNotInLoopThread();
        }
    }

    bool isInLoopThread() const
    {
        return threadId_ == CurrentThread::tid();
    }

private:
    void abortNotInLoopThread();

    bool looping_;
    const pid_t threadId_;
};

}