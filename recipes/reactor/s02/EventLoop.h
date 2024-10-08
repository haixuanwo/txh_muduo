/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-10 17:41:22
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-10 17:41:28
 * @Description: file content
 */
#pragma once

#include "datetime/Timestamp.h"
#include "thread/Thread.h"
#include "Callbacks.h"
#include "TimerId.h"

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

  // force out-line dtor, for scoped_ptr members.
  ~EventLoop();

  ///
  /// Loops forever.
  ///
  /// Must be called in the same thread as creation of the object.
  ///
  void loop();

  void quit();

  ///
  /// Time when poll returns, usually means data arrivial.
  ///
  Timestamp pollReturnTime() const { return pollReturnTime_; }

  // timers

  ///
  /// Runs callback at 'time'.
  ///
  TimerId runAt(const Timestamp& time, const TimerCallback& cb);
  ///
  /// Runs callback after @c delay seconds.
  ///
  TimerId runAfter(double delay, const TimerCallback& cb);
  ///
  /// Runs callback every @c interval seconds.
  ///
  TimerId runEvery(double interval, const TimerCallback& cb);

  // void cancel(TimerId timerId);

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

  bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }

 private:

  void abortNotInLoopThread();

  typedef std::vector<Channel*> ChannelList;

  bool looping_; /* atomic */
  bool quit_; /* atomic */
  const pid_t threadId_;
  Timestamp pollReturnTime_;
  boost::scoped_ptr<Poller> poller_;
  boost::scoped_ptr<TimerQueue> timerQueue_;
  ChannelList activeChannels_;
};

}
