/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 14:53:38
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-11 15:25:05
 * @Description: file content
 */

#pragma once

#include "Thread.h"
#include <boost/scoped_ptr.hpp>
#include <vector>

namespace muduo
{

class Channel;
class Poller;
class EventLoop : boost::noncopyable
{
public:
    EventLoop();
    ~EventLoop();

    void loop();

    void quit();

    // internal use only
    void updateChannel(Channel* channel);
    // void removeChannel(Channel* channel);

    void assertInLoopThread()
    {
        if (!isInLoopThread())
        {
            abortNotInLoopThread();
        }
    }

    bool isInLoopThread() const
    {
        return threadId_ == CurrentThread::tid();
    }

private:
    void abortNotInLoopThread();

    typedef std::vector<Channel*> ChannelList;
    bool quit_; /* atomic */
    bool looping_;
    const pid_t threadId_;
    boost::scoped_ptr<Poller> poller_;
    ChannelList activeChannels_;
};

}
