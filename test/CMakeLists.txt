cmake_minimum_required(VERSION 3.16)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

add_compile_options(-std=gnu++17 -g3 -fsanitize=address -fno-omit-frame-pointer)
add_link_options(-fsanitize=address)

find_package(Boost 1.71 REQUIRED COMPONENTS system)

add_executable(client_test client_test.cpp)
target_link_libraries(client_test irc gtest_main Boost::system pthread)
add_test(NAME ClientTest COMMAND client_test)

add_executable(message_test message_test.cpp)
target_link_libraries(message_test irc gtest_main)
add_test(NAME MessageTest COMMAND message_test)
