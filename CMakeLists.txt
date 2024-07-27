
cmake_minimum_required(VERSION 2.6)

project(echo CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "debug")
endif()

if(NOT MUDUO_PATH)
  #set(MUDUO_PATH "/home/$ENV{USER}/build/${CMAKE_BUILD_TYPE}-install")
  set(MUDUO_PATH ".")
endif()

set(CXX_FLAGS
 -g
 # -DVALGRIND
 # -DMUDUO_STD_STRING
 -Wall
 -Wextra
 # -m32
 -Werror
 -Wconversion
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 # -std=c++0x
 -rdynamic
 )
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

find_path(Muduo_INCLUDE_DIR muduo "${MUDUO_PATH}/include")
find_path(Muduo_LIBRARY_DIR libmuduo_net.a "${MUDUO_PATH}/lib")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${Muduo_LIBRARY_DIR})
message(STATUS ${Muduo_INCLUDE_DIR})
message(STATUS ${Muduo_LIBRARY_DIR})

include_directories(${Muduo_INCLUDE_DIR})
find_library(muduo_base muduo_base)
find_library(muduo_net muduo_net)
find_library(muduo_inspect muduo_inspect)
message(STATUS ${muduo_base})
message(STATUS ${muduo_net})
message(STATUS ${muduo_inspect})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(client examples/02_asio/01_chat/client.cc)
target_link_libraries(client ${muduo_net} ${muduo_base} pthread rt)

add_executable(loadtest examples/02_asio/01_chat/loadtest.cc)
target_link_libraries(loadtest ${muduo_net} ${muduo_base} pthread rt)

add_executable(server examples/02_asio/01_chat/server.cc)
target_link_libraries(server ${muduo_net} ${muduo_base} pthread rt)

add_executable(server_threaded examples/02_asio/01_chat/server_threaded.cc)
target_link_libraries(server_threaded ${muduo_net} ${muduo_base} pthread rt)

add_executable(server_threaded_efficient examples/02_asio/01_chat/server_threaded_efficient.cc)
target_link_libraries(server_threaded_efficient ${muduo_net} ${muduo_base} pthread rt)

add_executable(server_threaded_highperformance examples/02_asio/01_chat/server_threaded_highperformance.cc)
target_link_libraries(server_threaded_highperformance ${muduo_net} ${muduo_base} pthread rt)

# hub
# add_executable(hub examples/03_hub/hub.cc examples/03_hub/codec.cc)
# target_link_libraries(hub muduo_inspect  pthread rt)

# add_library(muduo_pubsub examples/03_hub/pub.cc examples/03_hub/codec.cc)
# target_link_libraries(muduo_pubsub ${muduo_net})

# add_executable(pub examples/03_hub/pub.cc)
# target_link_libraries(pub muduo_pubsub)

# add_executable(sub examples/03_hub/sub.cc)
# target_link_libraries(sub muduo_pubsub)


# add_executable(echo src/echo.cc)
# target_link_libraries(echo ${muduo_net})
# target_link_libraries(echo ${muduo_base})
# target_link_libraries(echo pthread rt)

# add_executable(echo1
#     examples/01_simple/01_echo/echo.cc
#     examples/01_simple/01_echo/main.cc)
# target_link_libraries(echo1 ${muduo_net})
# target_link_libraries(echo1 ${muduo_base})
# target_link_libraries(echo1 pthread rt)

# add_executable(discard
#     examples/01_simple/02_discard/discard.cc
#     examples/01_simple/02_discard/main.cc)
# target_link_libraries(discard ${muduo_net})
# target_link_libraries(discard ${muduo_base})
# target_link_libraries(discard pthread rt)

# add_executable(chargen
#     examples/01_simple/03_chargen/chargen.cc
#     examples/01_simple/03_chargen/main.cc)
# target_link_libraries(chargen ${muduo_net})
# target_link_libraries(chargen ${muduo_base})
# target_link_libraries(chargen pthread rt)

# add_executable(chargenclient examples/01_simple/04_chargenclient/chargenclient.cc)
# target_link_libraries(chargenclient ${muduo_net})
# target_link_libraries(chargenclient ${muduo_base})
# target_link_libraries(chargenclient pthread rt)

# add_executable(daytime
#     examples/01_simple/05_daytime/daytime.cc
#     examples/01_simple/05_daytime/main.cc)
# target_link_libraries(daytime ${muduo_net})
# target_link_libraries(daytime ${muduo_base})
# target_link_libraries(daytime pthread rt)

# add_executable(time
#     examples/01_simple/06_time/time.cc
#     examples/01_simple/06_time/main.cc)
# target_link_libraries(time ${muduo_net})
# target_link_libraries(time ${muduo_base})
# target_link_libraries(time pthread rt)

# add_executable(timeclient examples/01_simple/07_timeclient/timeclient.cc)
# target_link_libraries(timeclient ${muduo_net})
# target_link_libraries(timeclient ${muduo_base})
# target_link_libraries(timeclient pthread rt)

# add_executable(allinone examples/01_simple/08_allinone/allinone.cc
#     examples/01_simple/06_time/time.cc
#     examples/01_simple/05_daytime/daytime.cc
#     examples/01_simple/03_chargen/chargen.cc
#     examples/01_simple/02_discard/discard.cc
#     examples/01_simple/01_echo/echo.cc)
# target_link_libraries(allinone ${muduo_net})
# target_link_libraries(allinone ${muduo_base})
# target_link_libraries(allinone pthread rt)
