cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

set(this model_test)

set(Sources
	test_data_type.cpp
	test_collection_type.cpp
	test_converter.cpp)

add_executable(${this}
	${Sources})
target_link_libraries(${this}
	PUBLIC
		gtest_main
		jsoncpp
		gcov)
target_compile_options(${this}
	PUBLIC 
		--coverage
		-O0)

add_test(
	NAME ${this}
	COMMAND ${this}
	)
