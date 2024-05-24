/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-23 22:56:39
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-24 14:45:13
 * @Description: file content
 */
#include <strings.h>
#include <unistd.h>
#include <iostream>

#include "Acceptor.h"
#include "InetAddress.h"
#include "TcpStream.h"

int main(int argc, char* argv[])
{
    std::cout << "T -------- start --- " << argv[0]<< std::endl;

    std::cout << "T --- accept ---" << std::endl;
    Acceptor acceptor(InetAddress(8888));
    TcpStreamPtr tcpStream = acceptor.accept();

    char buf[1024] = {0};
    while (1)
    {
        bzero(buf, sizeof(buf));
        if (tcpStream->receiveSome(buf, sizeof(buf)) <= 0)
        {
            std::cout << "T --- read end" << buf << std::endl;
            break;
        }

        std::cout << "T --- read "<< buf << std::endl;
    }

    std::cout << argv[0] <<" -------- end -----" << std::endl;
    return 0;
}
