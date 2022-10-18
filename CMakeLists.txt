cmake_minimum_required(VERSION 3.6)
project(ping_protocol VERSION 0.1)

option(BUILD_TESTS "Build unit tests" ON)

find_package(rtac_asio REQUIRED)

list(APPEND ping_messages_headers
    include/ping_protocol/messages/common.h
    include/ping_protocol/messages/MessageBase.h
    include/ping_protocol/messages/Ping360Messages.h
    include/ping_protocol/messages/print_utils.h
)

add_library(ping_messages INTERFACE)
target_include_directories(ping_messages INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

list(APPEND ping_protocol_headers
    include/ping_protocol/PingClient.h
)
add_library(ping_protocol SHARED
    src/PingClient.cpp
)
target_include_directories(ping_protocol PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(ping_protocol PUBLIC
    ping_messages
    rtac_asio
)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
