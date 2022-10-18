cmake_minimum_required(VERSION 3.6)
project(ping_protocol VERSION 0.1)

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

add_subdirectory(tests)
