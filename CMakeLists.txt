cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(this model_cpp)

project(${this})

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCC)
	option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)
endif()

if(ENABLE_COVERAGE)
	add_compile_options(-lgcov --coverage -O0)
endif()

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

add_subdirectory(googletest)
add_subdirectory(test)
