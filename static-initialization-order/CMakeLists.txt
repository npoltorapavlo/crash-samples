project(static-initialization-order)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

add_executable(static-initialization-order-on-exit static-initialization-order-on-exit.cpp)

install(TARGETS DESTINATION bin)
