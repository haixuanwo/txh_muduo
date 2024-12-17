/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 14:53:38
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-11 16:22:34
 * @Description: file content
 */

#pragma once

#include "Timestamp.h"
#include "Callbacks.h"
#include "TimerId.h"
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
    EventLoop();
    ~EventLoop();

    void loop();

    void quit();

    Timestamp pollReturnTime() const { return pollReturnTime_; }

    TimerId runAt(const Timestamp& time, const TimerCallback& cb);

    TimerId runAfter(double delay, const TimerCallback& cb);

    TimerId runEvery(double interval, const TimerCallback& cb);

    // internal use only
    void updateChannel(Channel* channel);
    // void removeChannel(Channel* channel);

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

    typedef std::vector<Channel*> ChannelList;
    bool quit_; /* atomic */
    bool looping_;
    const pid_t threadId_;

    Timestamp pollReturnTime_;
    boost::scoped_ptr<Poller> poller_;
    boost::scoped_ptr<TimerQueue> timerQueue_;
    ChannelList activeChannels_;
};

}
