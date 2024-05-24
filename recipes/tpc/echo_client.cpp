/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-24 15:00:37
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-24 21:22:35
 * @Description: file content
 */
#include "InetAddress.h"
#include "TcpStream.h"

#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc > 3)
    {
        printf("Usage: %s hostname message_len [scp]\n", argv[0]);
        return -1;
    }

    InetAddress addr(3007);
    if (!InetAddress::resolve(argv[1], &addr))
    {
        printf("resolve %s failed\n", argv[1]);
        return -1;
    }

    printf("connecting to %s\n", addr.toIpPort().c_str());
    TcpStreamPtr stream(TcpStream::connect(addr));
    if (!stream)
    {
        printf("connect %s failed\n", addr.toIpPort().c_str());
        return -1;
    }

    printf("connected to %s, sending message bytes\n", addr.toIpPort().c_str());
    if (argc > 3)
    {
        for (char cmd : std::string(argv[3]))
        {
            switch (cmd)
            {
                case 's':
                {
                    printf("shutdown write\n");
                    stream->shutdownWrite();
                    break;
                }
                case 'p':
                {
                    printf("sleeping for 10 seconds\n");
                    ::sleep(10);
                    printf("done\n");
                    break;
                }
                case 'c':
                {
                    printf("close without reading response\n");
                    return 0;
                }
                default:
                {
                    printf("unknown command %c\n", cmd);
                    break;
                }
            }
        }
    }

    std::vector<char> receive(len);
    int nr = stream->receiveAll(receive.data(), receive.size());
    printf("received %d bytes: %s\n", nr, receive.data());

    if (nr != nw)
    {
        printf("received %d bytes, but expected %d\n", nr, nw);
    }

    return 0;
}
