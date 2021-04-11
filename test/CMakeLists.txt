cmake_minimum_required(VERSION 3.16)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

add_compile_options(-std=gnu++2a -g3 -fsanitize=address -fno-omit-frame-pointer)
add_link_options(-fsanitize=address)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.71 REQUIRED COMPONENTS system log)

add_executable(client_test client_test.cpp)
target_link_libraries(client_test irc gtest_main Boost::system Boost::log pthread)
add_test(NAME ClientTest COMMAND client_test)

add_executable(message_test message_test.cpp)
target_link_libraries(message_test irc gtest_main)
add_test(NAME MessageTest COMMAND message_test Boost::log)
