cmake_minimum_required(VERSION 3.16)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

add_compile_options(-std=gnu++2a -g3 -fsanitize=address -fno-omit-frame-pointer)
add_link_options(-fsanitize=address)

add_library(irc
    ${CMAKE_CURRENT_LIST_DIR}/messages/abstract_message.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/abstract_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/build_digest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/created_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/created.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/list.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/motd_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/motd.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/myinfo_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/myinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/nick_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/nick.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/notice_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/notice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/pass_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/pass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/ping_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/ping.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/pong_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/pong.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/user_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/user.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/welcome_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/welcome.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/yourhost_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/yourhost.cpp
    ${CMAKE_CURRENT_LIST_DIR}/handlers/abstract_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/handlers/motd_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/handlers/ping_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/handlers/notice_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/handlers/registration_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/handlers/list_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/client.cpp
)
