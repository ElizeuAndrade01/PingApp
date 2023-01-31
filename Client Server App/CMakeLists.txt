cmake_minimum_required(VERSION 3.0.0)
project(ClientServerApp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

set(CUSTOM_BUILD_PARAMS "-fno-exceptions")

include_directories(libs)

include_directories(client)
include_directories(server)

include_directories(googletest)

add_executable(ClientServerAppS server/main_server.cc server/server.cc src/icmp_packet.cc src/socket.cc)

add_executable(ClientServerAppC client/main_client.cc client/client.cc src/icmp_packet.cc src/socket.cc)

target_link_libraries(ClientServerAppS PUBLIC pthread)

target_link_libraries(ClientServerAppC PUBLIC pthread)

add_subdirectory(tests)

add_subdirectory(googletest)