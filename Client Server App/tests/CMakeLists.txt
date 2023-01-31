set(BINARY ${CMAKE_PROJECT_NAME}T)

enable_testing()

file(GLOB_RECURSE TESTS LIST_DIRECTORIES false *.h *.cc)

set(SOURCES ${TESTS})

add_executable(${BINARY} ../src/icmp_packet.cc icmp_tests.cc)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC gtest_main)