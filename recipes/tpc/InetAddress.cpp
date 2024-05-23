/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-22 21:34:35
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-23 23:25:32
 * @Description: file content
 */

#include "InetAddress.h"
#include <netdb.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <iostream>

InetAddress::InetAddress(StringArg ip, uint16_t port)
{
    ::bzero(&saddr_, sizeof(saddr_));
    saddr_.sin_family = AF_INET;
    saddr_.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &saddr_.sin_addr);
    std::cout << "InetAddress success IP: " << ip.c_str() << "port: " << port << std::endl;
}

InetAddress::InetAddress(StringArg ipPort)
{

}

InetAddress::InetAddress(uint16_t port, bool loopbackonly)
{
    ::bzero(&saddr_, sizeof(saddr_));
    saddr_.sin_family = AF_INET;
    saddr_.sin_port = htons(port);
    saddr_.sin_addr.s_addr = htonl(loopbackonly ? INADDR_LOOPBACK : INADDR_ANY);
    std::cout << "InetAddress success port: "<< port << std::endl;
}

std::string InetAddress::toIp() const
{
    char buf[32] = "";
    ::inet_ntop(AF_INET, &saddr_.sin_addr.s_addr, buf, sizeof(buf));
    return buf;
}

std::string InetAddress::toIpPort() const
{
    char buf[32] = "";
    ::inet_ntop(AF_INET, &saddr_.sin_addr.s_addr, buf, sizeof(buf));
    int end = strlen(buf);
    uint16_t port = portHostEndian();
    snprintf(buf + end, sizeof(buf) - end, ":%u", port);
    return buf;
}

static const int kResolveBufSize = 4096;

// resolve hostname to IP address, not changing port or sin_family
// return true on success
// thread safe
bool InetAddress::resolve(StringArg hostname, InetAddress *out)
{
    assert(out);
    char buf[kResolveBufSize];
    struct hostent hent;
    struct hostent *he = nullptr;
    int herrno = 0;
    bzero(&hent, sizeof(hent));

    int ret = gethostbyname_r(hostname.c_str(), &hent, buf, sizeof(buf), &he, &herrno);
    if (0 == ret && he != NULL)
    {
        assert(he->h_addrtype == AF_INET && he->h_length == sizeof(uint32_t));
        out->saddr_.sin_addr = *reinterpret_cast<struct in_addr*>(he->h_addr);
        return true;
    }
    else if (ERANGE == ret)
    {
        return resolveSlow(hostname.c_str(), out);
    }
    else
    {
        if (ret)
        {
            perror("InetAddress::resolve");
        }
        return false;
    }
}

std::vector<InetAddress> InetAddress::resolveAll(StringArg hostname, uint16_t port)
{
    return {};
}

bool InetAddress::resolveSlow(const char *hostname, InetAddress *out)
{
    std::vector<char> buf(2*kResolveBufSize);
    struct hostent hent;
    struct hostent *he = nullptr;
    int herrno = 0;
    bzero(&hent, sizeof(hent));

    while (buf.size() == 16*kResolveBufSize) // 64 KiB
    {
        int ret = gethostbyname_r(hostname, &hent, buf.data(), buf.size(), &he, &herrno);
        if (0 == ret && he != NULL)
        {
            assert(he->h_addrtype == AF_INET && he->h_length == sizeof(uint32_t));
            out->saddr_.sin_addr = *reinterpret_cast<struct in_addr*>(he->h_addr);
            return true;
        }
        else if (ERANGE == ret)
        {
            buf.resize(buf.size() * 2);
        }
        else
        {
            if (ret)
            {
                perror("InetAddress::resolve");
            }
            return false;
        }
    }

    return false;
}
