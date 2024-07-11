/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-11 17:11:30
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-11 17:16:08
 * @Description: file conte
 */
#pragma once

#include "datetime/copyable.h"

namespace muduo
{

class Timer;

///
/// An opaque identifier, for canceling Timer.
///
// class TimerId : public muduo::copyable
class TimerId
{
 public:
  TimerId(Timer* timer = NULL, int64_t seq = 0)
    : timer_(timer),
      sequence_(seq)
  {
  }

  // default copy-ctor, dtor and assignment are okay

  friend class TimerQueue;

 private:
  Timer* timer_;
  int64_t sequence_;
};

}
