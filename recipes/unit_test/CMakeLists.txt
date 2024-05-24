cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# project name and language
project(recipes LANGUAGES CXX)

# require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# example library
# add_library(sum_integers sum_integers.cpp)

# 添加头文件目录
include_directories(../tpc)

link_directories(lib)

# 01_Socket_InetAddress
add_executable(sockClient 01_Socket_InetAddress/test_sock_client.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp)
target_link_libraries(sockClient)

add_executable(sockServer 01_Socket_InetAddress/test_sock_server.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp)
target_link_libraries(sockServer)

# 02_Acceptor_TcpStream
add_executable(streamClient 02_Acceptor_TcpStream/test_stream_client.cpp ../tpc/Socket.cpp ../tpc/Acceptor.cpp ../tpc/TcpStream.cpp  ../tpc/InetAddress.cpp)
target_link_libraries(streamClient)

add_executable(streamServer 02_Acceptor_TcpStream/test_stream_server.cpp ../tpc/Acceptor.cpp ../tpc/TcpStream.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp)
target_link_libraries(streamServer)

# add_executable(main_test1 main_test.cpp src/sum_integers.cpp)
# target_link_libraries(main_test1 gtest_main gtest)

# 使能单元测试
# enable_testing()

# 添加测试用例
# add_test(
#     NAME google_test
#     COMMAND $<TARGET_FILE:main_test>
# )

# add_test(
#     NAME google_test1
#     COMMAND $<TARGET_FILE:main_test1>
# )
