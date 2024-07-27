/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-27 15:35:29
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-27 15:35:56
 * @Description: file content
 */
#pragma once
// internal header file

#include "muduo/base/Types.h"
#include "muduo/net/Buffer.h"

namespace pubsub
{
using muduo::string;

enum ParseResult
{
  kError,
  kSuccess,
  kContinue,
};

ParseResult parseMessage(muduo::net::Buffer* buf,
                         string* cmd,
                         string* topic,
                         string* content);
}  // namespace pubsub
