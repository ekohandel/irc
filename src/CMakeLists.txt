cmake_minimum_required(VERSION 3.16)

add_compile_options(-fno-omit-frame-pointer -fsanitize=address)
add_link_options(-fno-omit-frame-pointer -fsanitize=address)

add_subdirectory(server)
add_subdirectory(message)
add_subdirectory(client)
