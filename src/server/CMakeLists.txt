cmake_minimum_required(VERSION 3.16)

add_executable(server_test server.cpp server_test.cpp)
target_link_libraries(server_test gtest_main)
add_test(NAME ServerTest COMMAND server_test)
