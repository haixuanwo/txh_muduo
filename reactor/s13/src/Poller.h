/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-12 19:24:15
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-12 19:30:50
 * @Description: file content
 */
#pragma once

#include <map>
#include <vector>

#include "Timestamp.h"
#include "EventLoop.h"

struct pollfd;

namespace muduo
{

class Channel;
class Poller : boost::noncopyable
{
public:
  typedef std::vector<Channel*> ChannelList;

  Poller(EventLoop* loop);

  ~Poller();

  Timestamp poll(int timeout, ChannelList* activeChannels);

  void updateChannel(Channel* channel);

  /// Remove the channel, when it destructs.
  /// Must be called in the loop thread.
  void removeChannel(Channel* channel);

  void assertInLoopThread()
  {
    ownerLoop_->assertInLoopThread();
  }

private:
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    typedef std::vector<struct pollfd> PollFdList;
    typedef std::map<int, Channel*> ChannelMap;

    EventLoop* ownerLoop_;
    PollFdList pollfds_;
    ChannelMap channels_;
};

}
