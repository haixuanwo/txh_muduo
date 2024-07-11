/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-10 17:49:34
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-10 18:05:00
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
    explicit TimerId(Timer* timer) : value_(timer)
    {
    }

    // default copy-ctor, dtor and assignment are okay

private:
    Timer* value_;
};

}
