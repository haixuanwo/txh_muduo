/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 14:53:57
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-12 19:22:51
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

    ~Channel();

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
    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
    EventCallback closeCallback_;
};

}
