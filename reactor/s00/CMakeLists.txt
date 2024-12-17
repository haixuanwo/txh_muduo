
cmake_minimum_required(VERSION 3.5)

project(Reactor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIRS})


# 指定头文件路径
include_directories(include)
include_directories(src)
include_directories(../common)

# 链接库路径
link_directories(common)

# 定义源文件，在src目录下所有.cpp和.h文件
file(GLOB_RECURSE SOURCES src/*.cc src/*.h ../common/*.cc ../common/*.h)

set(PROJECT_SOURCES
    ${SOURCES}
    # main.cc
)

add_executable(test1
    ${PROJECT_SOURCES} test1.cc
)

target_link_libraries(test1
    pthread
    ${Boost_LIBRARIES}
)

add_executable(test2
    ${PROJECT_SOURCES} test2.cc
)

target_link_libraries(test2
    pthread
    ${Boost_LIBRARIES}
)
