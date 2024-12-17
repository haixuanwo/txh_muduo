/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 14:53:57
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-11 15:01:25
 * @Description: file content
 */

#pragma once

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

namespace muduo
{

class EventLoop;
class Channel : boost::noncopyable
{
public:
    typedef boost::function<void()> EventCallback;

    Channel(EventLoop* loop, int fd);

    void handleEvent();

    void setReadCallback(const EventCallback& cb)
    {
        readCallback_ = cb;
    }

    void setWriteCallback(const EventCallback& cb)
    {
        writeCallback_ = cb;
    }

    void setErrorCallback(const EventCallback& cb)
    {
        errorCallback_ = cb;
    }

    int fd() const
    {
        return fd_;
    }

    int events() const
    {
        return events_;
    }

    void set_revents(int revents)
    {
        revents_ = revents;
    }

    bool isNoneEvent() const
    {
        return events_ == kNoneEvent;
    }

    void enableReading()
    {
        events_ |= kReadEvent;
        update();
    }

    int index() const
    {
        return index_;
    }

    void setIndex(int index)
    {
        index_ = index;
    }

    EventLoop* ownerLoop()
    {
        return loop_;
    }

private:
    void update();

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop* loop_;
    const int fd_;
    int events_;
    int revents_;
    int index_;

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
};

}
