/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-17 15:51:01
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-17 15:51:10
 * @Description: file content
 */

#include "Timer.h"

using namespace muduo;

AtomicInt64 Timer::s_numCreated_;

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
