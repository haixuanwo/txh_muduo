/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 14:53:38
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-12 19:25:36
 * @Description: file content
 */

#pragma once

#include "Timestamp.h"
#include "Callbacks.h"
#include "TimerId.h"
#include "Mutex.h"
#include "Thread.h"
#include <boost/scoped_ptr.hpp>
#include <vector>

namespace muduo
{

class Channel;
class Poller;
class TimerQueue;
class EventLoop : boost::noncopyable
{
public:
    typedef boost::function<void()> Functor;

    EventLoop();
    ~EventLoop();

    void loop();

    void quit();

    /// Runs callback immediately in the loop thread.
    /// It wakes up the loop, and run the cb.
    /// If in the same loop thread, cb is run within the function.
    /// Safe to call from other threads.
    void runInLoop(const Functor& cb);

    /// Queues callback in the loop thread.
    /// Runs after finish pooling.
    /// Safe to call from other threads.
    void queueInLoop(const Functor& cb);

    Timestamp pollReturnTime() const { return pollReturnTime_; }

    TimerId runAt(const Timestamp& time, const TimerCallback& cb);

    TimerId runAfter(double delay, const TimerCallback& cb);

    TimerId runEvery(double interval, const TimerCallback& cb);

    void cancel(TimerId timerId);

    void wakeup();

    // internal use only
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

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
    void handleRead();  // waked up
    void doPendingFunctors();

    typedef std::vector<Channel*> ChannelList;
    bool quit_; /* atomic */
    bool callingPendingFunctors_; /* atomic */
    bool looping_;
    const pid_t threadId_;

    Timestamp pollReturnTime_;
    boost::scoped_ptr<Poller> poller_;
    boost::scoped_ptr<TimerQueue> timerQueue_;
    int wakeupFd_;
    // unlike in TimerQueue, which is an internal class,
    // we don't expose Channel to client.
    boost::scoped_ptr<Channel> wakeupChannel_;
    ChannelList activeChannels_;
    MutexLock mutex_;
    std::vector<Functor> pendingFunctors_; // @GuardedBy mutex_
};

}
