/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-10 17:43:57
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-10 17:44:02
 * @Description: file content
 */
#pragma once

#include <map>
#include <vector>

#include "datetime/Timestamp.h"
#include "EventLoop.h"

struct pollfd;

namespace muduo
{

class Channel;

///
/// IO Multiplexing with poll(2).
///
/// This class doesn't own the Channel objects.
class Poller : boost::noncopyable
{
 public:
  typedef std::vector<Channel*> ChannelList;

  Poller(EventLoop* loop);
  ~Poller();

  /// Polls the I/O events.
  /// Must be called in the loop thread.
  Timestamp poll(int timeoutMs, ChannelList* activeChannels);

  /// Changes the interested I/O events.
  /// Must be called in the loop thread.
  void updateChannel(Channel* channel);

  void assertInLoopThread() { ownerLoop_->assertInLoopThread(); }

 private:
  void fillActiveChannels(int numEvents,
                          ChannelList* activeChannels) const;

  typedef std::vector<struct pollfd> PollFdList;
  typedef std::map<int, Channel*> ChannelMap;

  EventLoop* ownerLoop_;
  PollFdList pollfds_;
  ChannelMap channels_;
};

}
