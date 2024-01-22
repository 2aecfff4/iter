cmake_minimum_required(VERSION 3.20)
project(Tundra VERSION 1.0.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-source built.")
endif()

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test test.cpp)
