/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-11 11:10:38
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-11 11:10:44
 * @Description: file content
 */

#include "Timer.h"

using namespace muduo;

void Timer::restart(Timestamp now)
{
  if (repeat_)
  {
    expiration_ = addTime(now, interval_);
  }
  else
  {
    expiration_ = Timestamp::invalid();
  }
}
