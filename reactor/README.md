# Development Process

## s00
1. 添加EventLoop，并在线程中运行

## s01
1. 添加poller和channel类
2. timerfd超时触发poller读事件

## s02
1. 添加TimerQueue定时器队列
2. 实现定时回调

## s03
1. 添加EventLoopThread类

## s04
1. 添加套接字相关类，包括Acceptor, InetAddress, Socket, SocketOps

## s05
1. 添加TcpConnection和TcpServer类

## s06
1. 添加连接关闭时，删除通道功能

## s07
1.添加连buffer类

## s08
1. shutdownWrite
2. outputBuffer

## s09
1. WriteCompleteCallback
2. nodelay

## s10
1. thread pool

## s11
1. connector client

## s12
1. TcpClient

## s13
1. Epoller

# test case
- test1 :线程运行与EventLoop
- test2 :错误示范，不在同一线程运行EventLoop
- test3 :timerfd超时触发poller读事件
- test4 :定时运行功能，runAfter、runEvery、runAt
- test5 :EventLoop, runInLoop, queueInLoop
- test6 :EventLoopThread
- test7 :Acceptor
- test8 :TcpServer, connectCallback, messageCallback
- test9 :TcpServer设置多线程
- test10 :发送数据
- test11 :定时回调onWriteComplete
- test12 :Connector
- test13 :TcpClient重连
