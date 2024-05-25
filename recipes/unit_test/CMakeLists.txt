cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# project name and language
project(recipes LANGUAGES CXX)

# require C++11
set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(Boost COMPONENTS program_options REQUIRED)

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

# 3 chargen
add_executable(chargen ../tpc/chargen.cpp ../datetime/Timestamp.cpp ../tpc/Acceptor.cpp ../tpc/TcpStream.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp)
target_link_libraries(chargen PRIVATE pthread)

# 4 discard
add_executable(discard ../tpc/discard.cpp ../datetime/Timestamp.cpp ../tpc/Acceptor.cpp ../tpc/TcpStream.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp)
target_link_libraries(discard PRIVATE pthread)

# 5 echo
add_executable(echo ../tpc/echo.cpp ../datetime/Timestamp.cpp ../tpc/Acceptor.cpp ../tpc/TcpStream.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp)
target_link_libraries(echo PRIVATE pthread)

add_executable(echo_client ../tpc/echo_client.cpp ../datetime/Timestamp.cpp ../tpc/Acceptor.cpp ../tpc/TcpStream.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp)
target_link_libraries(echo_client)

# 6 netcat
add_executable(netcat ../tpc/netcat.cpp ../datetime/Timestamp.cpp ../tpc/Acceptor.cpp ../tpc/TcpStream.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp)
target_link_libraries(netcat PRIVATE pthread)

# 7 nodelay
add_executable(nodelay ../tpc/nodelay.cpp ../datetime/Timestamp.cpp ../tpc/Acceptor.cpp ../tpc/TcpStream.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp ../tpc/Common.cpp)
target_link_libraries(nodelay PRIVATE pthread)

add_executable(nodelay_server ../tpc/nodelay_server.cpp ../datetime/Timestamp.cpp ../tpc/Acceptor.cpp ../tpc/TcpStream.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp ../tpc/Common.cpp)
target_link_libraries(nodelay_server PRIVATE pthread)

# 8 roundtrip_udp
add_executable(roundtrip_udp ../tpc/roundtrip_udp.cpp ../datetime/Timestamp.cpp ../tpc/Acceptor.cpp ../tpc/TcpStream.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp ../tpc/Common.cpp)
target_link_libraries(roundtrip_udp PRIVATE pthread)

# 9 roundtrip_udp
add_executable(sender ../tpc/sender.cpp ../datetime/Timestamp.cpp ../tpc/Acceptor.cpp ../tpc/TcpStream.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp ../tpc/Common.cpp)
target_link_libraries(sender PRIVATE pthread)

# 10 ttcp
add_executable(ttcp ../tpc/ttcp.cpp ../datetime/Timestamp.cpp ../tpc/Acceptor.cpp ../tpc/TcpStream.cpp ../tpc/Socket.cpp ../tpc/InetAddress.cpp ../tpc/Common.cpp)
target_link_libraries(ttcp PRIVATE pthread Boost::program_options)


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
