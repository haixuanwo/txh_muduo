/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-25 09:27:42
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-25 15:09:31
 * @Description: file content
 */
#include <thread>
#include <unistd.h>

#include "Acceptor.h"
#include "InetAddress.h"
#include "TcpStream.h"

void sender(const std::string& filename, TcpStreamPtr stream)
{
    FILE* fp = fopen(filename.c_str(), "rb");
    if (fp == nullptr)
    {
        printf("open file %s failed\n", filename.c_str());
        return;
    }

    printf("Sleep 10 seconds to wait for receiver...\n");
    sleep(10);

    printf("Start sending file %s...\n", filename.c_str());
    char buffer[8192];
    int nread;
    while ((nread = fread(buffer, 1, sizeof(buffer), fp)) > 0)
    {
        stream->sendAll(buffer, nread);
    }
    fclose(fp);
    printf("send file %s done\n", filename.c_str());

    // safe close connection
    stream->shutdownWrite();
    while ((nread = stream->receiveSome(buffer, sizeof(buffer))) > 0)
    {
        // do something
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::this_thread::yield();
    }

    printf("sender All done. thread exit\n");
    // TcpStream destructs here, close the TCP socket
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s filename port\n", argv[0]);
        return -1;
    }

    int port = atoi(argv[2]);
    // 双括号原因，编译器可能会错误地将这种构造方式解析为一个函数声明，而不是对象的构造
    Acceptor acceptor((InetAddress(port)));
    printf("Acceptor... Ctrl-C to exit\n");
    int count = 0;
    while (true)
    {
        TcpStreamPtr stream = acceptor.accept();
        printf("Accepted no. %d client\n", ++count);
        std::thread thr(sender, argv[1], std::move(stream));
        thr.detach();
    }

    return 0;
}
