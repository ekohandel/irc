cmake_minimum_required(VERSION 3.16)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

add_compile_options(-std=gnu++2a -g3 -fsanitize=address -fno-omit-frame-pointer)
add_link_options(-fsanitize=address)

add_library(irc
    ${CMAKE_CURRENT_LIST_DIR}/builders/abstract_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/build_digest.cpp

    ${CMAKE_CURRENT_LIST_DIR}/builders/commands/join_command_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/commands/nick_command_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/commands/notice_command_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/commands/pass_command_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/commands/ping_command_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/commands/pong_command_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/commands/privmsg_command_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/commands/user_command_builder.cpp

    ${CMAKE_CURRENT_LIST_DIR}/builders/replies/created_reply_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/replies/list_end_reply_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/replies/list_reply_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/replies/myinfo_reply_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/replies/welcome_reply_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builders/replies/yourhost_reply_builder.cpp

    ${CMAKE_CURRENT_LIST_DIR}/client/client.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/channel.cpp

    ${CMAKE_CURRENT_LIST_DIR}/handlers/abstract_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/handlers/join_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/handlers/list_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/handlers/ping_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/handlers/notice_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/handlers/private_message_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/handlers/registration_handler.cpp

    ${CMAKE_CURRENT_LIST_DIR}/messages/abstract_message.cpp

    ${CMAKE_CURRENT_LIST_DIR}/messages/commands/join_command.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/commands/list_command.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/commands/nick_command.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/commands/notice_command.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/commands/pass_command.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/commands/ping_command.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/commands/pong_command.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/commands/privmsg_command.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/commands/user_command.cpp

    ${CMAKE_CURRENT_LIST_DIR}/messages/replies/created_reply.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/replies/list_end_reply.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/replies/list_reply.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/replies/myinfo_reply.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/replies/welcome_reply.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messages/replies/yourhost_reply.cpp
)
