# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.16)
project(wstest VERSION 1.0.0
	DESCRIPTION "WebSocket Testing Tool"
	LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS WebSockets)

qt_add_executable(wstest
    batch_connect.cpp
    wstest.cpp
)

set_target_properties(wstest PROPERTIES
    WIN32_EXECUTABLE FALSE
)

target_link_libraries(wstest PUBLIC
    Qt::WebSockets
)
