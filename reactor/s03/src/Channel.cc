/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 15:03:09
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-11 15:38:44
 * @Description: file content
 */

#include "Channel.h"
#include "EventLoop.h"
#include "Logging.h"

#include <sstream>

#include <poll.h>

using namespace muduo;

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop, int fdArg)
  : loop_(loop),
    fd_(fdArg),
    events_(0),
    revents_(0),
    index_(-1)
{

}

void Channel::update()
{
  loop_->updateChannel(this);
}

void Channel::handleEvent()
{
  if (revents_ & POLLNVAL)
  {
    LOG_WARN << "Channel::handle_event() POLLNVAL";
  }

  if (revents_ & (POLLERR | POLLNVAL))
  {
    if (errorCallback_)
    {
        errorCallback_();
    }
  }

  if (revents_ & (POLLIN | POLLPRI | POLLRDHUP))
  {
    if (readCallback_)
    {
        readCallback_();
    }
  }

  if (revents_ & POLLOUT)
  {
    if (writeCallback_)
    {
        writeCallback_();
    }
  }
}
