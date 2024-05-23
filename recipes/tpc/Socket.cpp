
#include "Socket.h"
#include "InetAddress.h"

#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <iostream>

namespace {

typedef struct sockaddr SA;

const SA* sockaddr_cast(const struct sockaddr_in* addr)
{
    return static_cast<const SA*>(implicit_cast<const void*>(addr));
}

SA* sockaddr_cast(struct sockaddr_in* addr)
{
    return static_cast<SA*>(implicit_cast<void*>(addr));
}

} // namespace

Socket::Socket(int sockfd) : sockfd_(sockfd)
{
    assert(sockfd_ >= 0);
}

Socket::~Socket()
{
    if (sockfd_ >= 0)
    {
        int ret = ::close(sockfd_);
        assert(ret == 0);
        (void)ret;
    }
}

void Socket::bindOrDie(const InetAddress& addr)
{
    const struct sockaddr_in& saddr = addr.getSockAddrInet();
    int ret = ::bind(sockfd_, sockaddr_cast(&saddr), sizeof saddr);
    if (ret < 0)
    {
        perror("bind");
        abort();
    }
    std::cout << "bind success" << std::endl;
}

void Socket::listenOrDie()
{
    int ret = ::listen(sockfd_, SOMAXCONN);
    if (ret < 0)
    {
        perror("listen");
        abort();
    }
    std::cout << "listen success" << std::endl;
}

int Socket::acceptOrDie()
{
    std::cout << "block accept" << std::endl;
    return ::accept(sockfd_, nullptr, nullptr);
}

int Socket::connect(const InetAddress& addr)
{
    const struct sockaddr_in& saddr = addr.getSockAddrInet();
    return ::connect(sockfd_, sockaddr_cast(&saddr), sizeof saddr);
}

void Socket::shutdownWrite()
{
    ::shutdown(sockfd_, SHUT_WR);
}

void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    if (::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval) < 0)
    {
        perror("Socket::setReuseAddr");
    }
}

void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    if (::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof optval) < 0)
    {
        perror("Socket::setTcpNoDelay");
    }
}

InetAddress Socket::getLocalAddre() const
{
    struct sockaddr_in localaddr;
    bzero(&localaddr, sizeof localaddr);
    socklen_t addrlen = static_cast<socklen_t>(sizeof localaddr);
    if (::getsockname(sockfd_, sockaddr_cast(&localaddr), &addrlen) < 0)
    {
        perror("Socket::getLocalAddre");
    }
    return InetAddress(localaddr);
}

InetAddress Socket::getPeerAddre() const
{
    struct sockaddr_in peeraddr;
    bzero(&peeraddr, sizeof peeraddr);
    socklen_t addrlen = static_cast<socklen_t>(sizeof peeraddr);
    if (::getpeername(sockfd_, sockaddr_cast(&peeraddr), &addrlen) < 0)
    {
        perror("Socket::getLocalAddre");
    }
    return InetAddress(peeraddr);
}

int Socket::read(void *buf, int len)
{
    return ::read(sockfd_, buf, len);
}

int Socket::write(const void *buf, int len)
{
    std::cout << "Socket::write fd=" << sockfd_ << " len=" << len << std::endl;
    return ::write(sockfd_, buf, len);
}

Socket Socket::createTCP()
{
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);
    assert(sockfd >= 0);
    return Socket(sockfd);
}

Socket Socket::createUDP()
{
    int sockfd = ::socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
    assert(sockfd >= 0);
    return Socket(sockfd);
}
