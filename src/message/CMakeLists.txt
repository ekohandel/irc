cmake_minimum_required(VERSION 3.16)

add_executable(message_test message.cpp message_test.cpp)
target_link_libraries(message_test gtest_main)
add_test(NAME MessageTest COMMAND message_test)
