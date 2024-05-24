/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-24 10:06:49
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-24 14:30:54
 * @Description: file content
 */

#pragma once

#include "Common.h"
#include "Socket.h"
#include <memory>

class InetAddress;
class TcpStream;
typedef std::unique_ptr<TcpStream> TcpStreamPtr;

class Acceptor : noncopyable
{
public:
    explicit Acceptor(const InetAddress& listenAddr);

    ~Acceptor() = default;
    Acceptor(Acceptor&&) = default;
    Acceptor& operator=(Acceptor&&) = default;

    // thread safe
    TcpStreamPtr accept();

private:
    Socket listenSock_;
};
