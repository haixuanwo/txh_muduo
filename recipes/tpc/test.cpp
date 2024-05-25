/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-24 13:00:04
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-25 17:26:45
 * @Description: file content
 */


#include <iostream>

#include "TcpStream.h"
#include "InetAddress.h"
#include "Socket.h"
#include "Acceptor.h"

int main()
{
    // Acceptor acceptor(InetAddress(9999));
    // Socket s = Socket::createTCP();
    // std::cout << "Hello, world!" << std::endl;

    for (size_t i = 0; i < 16; i++)
    {
        std::cout << "char: " << "0123456789ABCDEF"[i % 16] << std::endl;
    }

    return 0;
}
