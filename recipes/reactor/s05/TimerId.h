/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-11 13:55:37
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-11 14:08:03
 * @Description: file content
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
  explicit TimerId(Timer* timer)
    : value_(timer)
  {
  }

  // default copy-ctor, dtor and assignment are okay

 private:
  Timer* value_;
};

}
