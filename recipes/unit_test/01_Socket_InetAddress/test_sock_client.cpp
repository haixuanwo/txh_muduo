/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-24 09:46:43
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-24 10:01:28
 * @Description: file content
 */

#include <chrono>
#include <thread>
#include <iostream>

#include "../tpc/Socket.h"
#include "../tpc/InetAddress.h"

int main(int argc, char* argv[])
{
    std::cout << "T -------- start --- " << argv[0]<< std::endl;

    Socket sock(Socket::createTCP());
    if (sock.connect(InetAddress("127.0.0.1", 8888)) <0)
    {
        std::cout << "T --- connect --- fail" << std::endl;
        return -1;
    }

    char buf[] = {"hello world"};
    while (1)
    {
        sock.write(buf, sizeof(buf));
        std::cout << "T ---- write "<< buf << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    std::cout << argv[0] <<" -------- end -----" << std::endl;
    return 0;
}
