cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(this model_test)

set(Sources
	test_data_type.cpp
	test_collection_type.cpp)

add_executable(${this}
	${Sources})
target_link_libraries(${this}
	PUBLIC
		gtest_main)

add_test(
	NAME ${this}
	COMMAND ${this}
	)