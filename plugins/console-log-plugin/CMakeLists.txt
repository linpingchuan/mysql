cmake_minimum_required(VERSION 3.10.2)
project(console_log_plugin)

set(CMAKE_CXX_STANDARD 14)


INCLUDE_DIRECTORIES(/usr/include/mysql)

add_library(console_log_plugin_lib SHARED library.cpp library.h)
