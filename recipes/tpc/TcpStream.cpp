/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-24 10:19:44
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-24 14:43:07
 * @Description: file content
 */

#include "TcpStream.h"
#include "InetAddress.h"

#include <error.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>

namespace
{

class IgnoreSigPipe
{
public:
    IgnoreSigPipe()
    {
        ::signal(SIGPIPE, SIG_IGN);
    }
} initObj;

bool isSelfConnection(const Socket& sock)
{
    return sock.getLocalAddress() == sock.getPeerAddress();
}

}


TcpStream::TcpStream(Socket&& sock) : sock_(std::move(sock)) // sock must be connected
{

}

TcpStreamPtr TcpStream::connect(const InetAddress& serverAddr)
{
    return connectInternal(serverAddr, nullptr);
}

TcpStreamPtr TcpStream::connect(const InetAddress& serverAddr, const InetAddress& localAddr)
{
    return connectInternal(serverAddr, &localAddr);
}

// NOT thread safe
int TcpStream::receiveAll(void* buf, int len)     // read len bytes, unless error happens
{
    return ::recv(sock_.fd(), buf, len, MSG_WAITALL);
}

int TcpStream::receiveSome(void* buf, int len)    // read len or less bytes
{
    return sock_.read(buf, len);
}

int TcpStream::sendAll(const void* buf, int len)     // send len bytes, unless error happens
{
    int written = 0;
    while (written < len)
    {
        int nw = sock_.write(static_cast<const char*>(buf) + written, len - written);
        if (nw > 0)
        {
            written += nw;
        }
        else if (0 == nw)
        {
            break;
        }
        else if (errno != EINTR)
        {
            break;
        }
    }
    return written;
}

int TcpStream::sendSome(const void* buf, int len)    // send len or less bytes
{
    return sock_.write(buf, len);
}

// thread safe
void TcpStream::setTcpNoDelay(bool on)
{
    sock_.setTcpNoDelay(on);
}

void TcpStream::shutdownWrite()
{
    sock_.shutdownWrite();
}


TcpStreamPtr TcpStream::connectInternal(const InetAddress& serverAddr, const InetAddress* localAddr)
{
    TcpStreamPtr stream;
    Socket sock(Socket::createTCP());

    if (localAddr)
    {
        sock.bindOrDie(*localAddr);
    }

    if (sock.connect(serverAddr) == 0 && !isSelfConnection(sock))
    {
        stream.reset(new TcpStream(std::move(sock)));
    }

    return stream;
}
