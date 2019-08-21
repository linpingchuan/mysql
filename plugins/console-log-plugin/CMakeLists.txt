cmake_minimum_required(VERSION 3.12)
project(console_log_plugin)

set(CMAKE_CXX_STANDARD 14)

add_library(console_log_plugin library.cpp library.h)

MYSQL_ADD_PLUGIN(console_log_plugin library.cpp library.h
        MODULE_ONLY MODULE_OUTPUT_NAME "console_log_plugin")