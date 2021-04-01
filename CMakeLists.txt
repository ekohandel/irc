cmake_minimum_required(VERSION 3.16)

project(irc)
enable_testing()

include_directories(include)

add_subdirectory(src)
add_subdirectory(tools)
add_subdirectory(test)