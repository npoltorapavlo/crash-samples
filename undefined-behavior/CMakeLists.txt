project(undefined-behavior)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)

add_executable(undefined-behavior-missing-return undefined-behavior-missing-return.cpp)

target_link_libraries(undefined-behavior-missing-return PRIVATE Threads::Threads)

install(TARGETS DESTINATION bin)
