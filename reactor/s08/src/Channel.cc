/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 15:03:09
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-16 19:12:38
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
    index_(-1),
    eventHandling_(false)
{

}

Channel::~Channel()
{
  assert(!eventHandling_);
}

void Channel::update()
{
  loop_->updateChannel(this);
}

void Channel::handleEvent(Timestamp receiveTime)
{
  eventHandling_ = true;

  if (revents_ & POLLNVAL)
  {
    LOG_WARN << "Channel::handle_event() POLLNVAL";
  }

  if ((revents_ & POLLHUP) && !(revents_ & POLLIN)) {
    LOG_WARN << "Channel::handle_event() POLLHUP";
    if (closeCallback_) closeCallback_();
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
        readCallback_(receiveTime);
    }
  }

  if (revents_ & POLLOUT)
  {
    if (writeCallback_)
    {
        writeCallback_();
    }
  }

  eventHandling_ = false;
}
