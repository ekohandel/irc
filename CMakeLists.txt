cmake_minimum_required(VERSION 3.16)

project(irc)
enable_testing()

add_compile_options(-std=gnu++17 -g3 -fsanitize=address -fno-omit-frame-pointer)
add_link_options(-fsanitize=address)

include_directories(include)

add_subdirectory(tools)
add_subdirectory(test)