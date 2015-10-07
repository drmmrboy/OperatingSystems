cmake_minimum_required(VERSION 3.3)
project(OperatingSystems)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES Project.c)
add_executable(OperatingSystems ${SOURCE_FILES})