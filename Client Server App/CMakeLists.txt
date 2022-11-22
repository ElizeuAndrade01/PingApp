cmake_minimum_required(VERSION 3.0.0)
project(ClientServerApp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

set(CUSTOM_BUILD_PARAMS "-fno-exceptions")



include_directories(libs)

include_directories(client)
include_directories(server)

add_executable(ClientServerApp main.cpp server/server.cpp icmpPacket.cpp socket.cpp utils.cpp)

add_executable(ClientServerAppC main.cpp client/client.cpp icmpPacket.cpp socket.cpp utils.cpp)

target_link_libraries(ClientServerApp PUBLIC pthread)