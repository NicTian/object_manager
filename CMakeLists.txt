cmake_minimum_required(VERSION 3.1)
project(object_manager)

set (SRC clearup.cpp objectmanagerbase.cpp objectmanager.cpp singleton.cpp main.cpp)

#set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(object_manager ${SRC})