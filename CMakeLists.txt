cmake_minimum_required(VERSION 3.17)
project(ColorGen)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 /W4 /WX")

add_executable(ColorGen main.cpp main.h ColorGen.o)