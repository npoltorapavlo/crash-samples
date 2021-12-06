project(do_lookup_x)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

add_executable(do_lookup_x do_lookup_x.cpp)
add_library(dl1 SHARED dl1.cpp)

target_link_libraries(do_lookup_x PRIVATE Threads::Threads ${CMAKE_DL_LIBS})

target_include_directories(dl1 PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_libraries(dl1 PRIVATE ${GLIB_LDFLAGS})

install(TARGETS DESTINATION bin)
