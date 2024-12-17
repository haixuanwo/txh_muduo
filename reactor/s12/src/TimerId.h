/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-17 14:15:51
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-17 15:54:44
 * @Description: file content
 */

#pragma once

#include "copyable.h"

namespace muduo
{

class Timer;
class TimerId : public muduo::copyable
{
public:
  explicit TimerId(Timer* timer = NULL, int64_t seq = 0)
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
