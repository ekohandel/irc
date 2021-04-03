cmake_minimum_required(VERSION 3.16)

find_package(Boost 1.71 REQUIRED COMPONENTS system)

add_compile_options(-g3)

add_executable(client_test client_test.cpp
    ../src/client/client.cpp
    ../src/message/message.cpp)
target_link_libraries(client_test gtest_main Boost::system pthread)
add_test(NAME ClientTest COMMAND client_test)

add_executable(message_test message_test.cpp
    ../src/message/message.cpp
)
target_link_libraries(message_test gtest_main)
add_test(NAME MessageTest COMMAND message_test)

add_executable(server_test server_test.cpp
    ../src/server/server.cpp
)
target_link_libraries(server_test gtest_main)
add_test(NAME ServerTest COMMAND server_test)



