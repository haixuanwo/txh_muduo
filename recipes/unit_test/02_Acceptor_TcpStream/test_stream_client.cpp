/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-24 09:46:43
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-24 14:51:12
 * @Description: file content
 */

#include <chrono>
#include <thread>
#include <iostream>

#include "Acceptor.h"
#include "InetAddress.h"
#include "TcpStream.h"

int main(int argc, char* argv[])
{
    std::cout << "T -------- start --- " << argv[0]<< std::endl;

    InetAddress addr("127.0.0.1", 8888);
    TcpStreamPtr tcpStream(TcpStream::connect(addr));

    char buf[] = {"hello world"};
    while (1)
    {
        tcpStream->sendAll(buf, sizeof(buf));
        std::cout << "T ---- write "<< buf << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    std::cout << argv[0] <<" -------- end -----" << std::endl;
    return 0;
}
