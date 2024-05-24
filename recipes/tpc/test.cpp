/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-24 13:00:04
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-24 14:43:30
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


    Socket s = Socket::createTCP();
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
