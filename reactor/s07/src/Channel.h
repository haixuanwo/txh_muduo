/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 14:53:57
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-17 09:32:23
 * @Description: file content
 */
#pragma once

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <Timestamp.h>

namespace muduo
{

class EventLoop;
class Channel : boost::noncopyable
{
public:
    typedef boost::function<void()> EventCallback;
    typedef boost::function<void(Timestamp)> ReadEventCallback;

    Channel(EventLoop* loop, int fd);

    ~Channel();

    void handleEvent(Timestamp receiveTime);

    void setReadCallback(const ReadEventCallback& cb)
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

    void setCloseCallback(const EventCallback& cb)
    { closeCallback_ = cb; }

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

    void disableAll() { events_ = kNoneEvent; update(); }

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

    bool eventHandling_;
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
    EventCallback closeCallback_;
};

}
