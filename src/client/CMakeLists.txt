cmake_minimum_required(VERSION 3.16)

find_package(Boost 1.71 REQUIRED COMPONENTS system)

add_executable(client_test client.cpp client_test.cpp)
target_link_libraries(client_test gtest_main Boost::system pthread)
add_test(NAME ClientTest COMMAND client_test)
