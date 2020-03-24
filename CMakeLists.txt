cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

project(qrpc)

include_directories(
    ${CMAKE_HOME_DIRECTORY}/include
)

add_subdirectory(example/echo/server)
add_subdirectory(example/echo/client)
include(cmake/qgen.cmake)
