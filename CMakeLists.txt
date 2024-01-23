cmake_minimum_required(VERSION 3.20)
project(iter VERSION 1.0.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-source built.")
endif()

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(iter INTERFACE)
target_include_directories(iter INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(iter INTERFACE cxx_std_23)

add_executable(test test.cpp)
target_link_libraries(test PUBLIC iter)
target_compile_features(test PUBLIC cxx_std_23)

add_executable(examples examples.cpp)
target_link_libraries(examples PUBLIC iter)
target_compile_features(examples PUBLIC cxx_std_23)
