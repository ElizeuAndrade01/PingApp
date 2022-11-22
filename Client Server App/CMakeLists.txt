cmake_minimum_required(VERSION 3.0.0)
project(ClientServerApp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

set(CUSTOM_BUILD_PARAMS "-fno-exceptions")

include_directories(libs)

add_executable(ClientServerApp main.cpp)

include_directories(client)
include_directories(server)