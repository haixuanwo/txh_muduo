
#pragma once

#include "copyable.h"

namespace muduo
{

class Timer;
class TimerId : public muduo::copyable
{
public:
  explicit TimerId(Timer* timer) : value_(timer)
  {

  }

private:
  Timer* value_;
};

}
