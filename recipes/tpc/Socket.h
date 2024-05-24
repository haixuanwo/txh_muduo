/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-23 10:01:32
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-24 14:35:48
 * @Description: file content
 */
#pragma once

#include "Common.h"
#include <utility>

class InetAddress;

class Socket : noncopyable
{
public:
    explicit Socket(int sockfd);
    ~Socket();

    Socket(Socket&& rhs) : Socket(rhs.sockfd_)
    {
        rhs.sockfd_ = -1;
    }

    Socket& operator=(Socket&& rhs)
    {
        swap(rhs);
        return *this;
    }

    void swap(Socket& rhs)
    {
        std::swap(sockfd_, rhs.sockfd_);
    }

    int fd()
    {
        return sockfd_;
    }

    void bindOrDie(const InetAddress& addr);
    void listenOrDie();
    int acceptOrDie();
    int connect(const InetAddress& addr);
    void shutdownWrite();
    void setReuseAddr(bool on);
    void setTcpNoDelay(bool on);

    InetAddress getLocalAddress() const;
    InetAddress getPeerAddress() const;

    int read(void *buf, int len);
    int write(const void *buf, int len);

    static Socket createTCP();
    static Socket createUDP();

private:
    int sockfd_;
};
