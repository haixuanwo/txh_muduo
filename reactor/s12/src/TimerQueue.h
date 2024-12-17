/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-17 14:17:31
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-17 16:13:02
 * @Description: file content
 */
#pragma once

#include <set>
#include <vector>
#include <boost/noncopyable.hpp>

#include "Thread.h"
#include "TimerId.h"
#include "EventLoop.h"
#include "Timestamp.h"
#include "Mutex.h"
#include "Callbacks.h"
#include "Channel.h"

namespace muduo
{

class EventLoop;
class Timer;
class TimerId;
class TimerQueue : boost::noncopyable
{
public:
    TimerQueue(EventLoop* loop);
    ~TimerQueue();

    TimerId addTimer(const TimerCallback& cb, Timestamp when, double interval);
    void cancel(TimerId timerId);

private:
    typedef std::pair<Timestamp, Timer*> Entry;
    typedef std::set<Entry> TimerList;
    typedef std::pair<Timer*, int64_t> ActiveTimer;
    typedef std::set<ActiveTimer> ActiveTimerSet;

    void cancelInLoop(TimerId timerId);
    void handleRead();
    std::vector<Entry> getExpired(Timestamp now);
    void reset(const std::vector<Entry> &expired, Timestamp now);

    bool insert(Timer* timer);

    void addTimerInLoop(Timer* timer);

    EventLoop* loop_;
    const int timerfd_;
    Channel timerfdChannel_;
    TimerList timers_;

    // for cancel()
    bool callingExpiredTimers_; /* atomic */
    ActiveTimerSet activeTimers_;
    ActiveTimerSet cancelingTimers_;
};

}
