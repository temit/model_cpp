cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(this model_cpp)

project(${this})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

set(Header
    json/json.h
    json/json-forwards.h)

set(Source
    jsoncpp.cpp)

add_library(jsoncpp
        STATIC
            ${Source}
            ${Header})

include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )

add_subdirectory(test)
