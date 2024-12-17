/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-12 18:32:07
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-16 19:09:35
 * @Description: file content
 */

#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "Timestamp.h"

namespace muduo
{
class Buffer;
class TcpConnection;
typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef boost::function<void()> TimerCallback;
typedef boost::function<void (const TcpConnectionPtr&)> ConnectionCallback;
typedef boost::function<void (const TcpConnectionPtr&, Buffer* buf,
                              Timestamp)> MessageCallback;

typedef boost::function<void (const TcpConnectionPtr&)> WriteCompleteCallback;
typedef boost::function<void (const TcpConnectionPtr&)> CloseCallback;

}
