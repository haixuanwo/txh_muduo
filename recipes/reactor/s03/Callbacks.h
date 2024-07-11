/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-11 10:50:05
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-11 10:50:11
 * @Description: file content
 */
#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "datetime/Timestamp.h"

namespace muduo
{
    // All client visible callbacks go here.
    typedef boost::function<void()> TimerCallback;
}
