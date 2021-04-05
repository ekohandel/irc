cmake_minimum_required(VERSION 3.16)

find_package(Boost 1.71 REQUIRED COMPONENTS system)

add_executable(client_test client_test.cpp)
target_link_libraries(client_test gtest_main Boost::system pthread)
add_test(NAME ClientTest COMMAND client_test)

add_executable(message_test message_test.cpp)
target_link_libraries(message_test gtest_main)
add_test(NAME MessageTest COMMAND message_test)
