cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(this model_cpp)

project(${this})

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(test)
