#include <gtest/gtest.h>

#include "../collection_type.hpp"

namespace keys
{
	const char numbers[] = "numbers";
}

TEST(model_cpp, collection_type_test_key)
{
	atom::collection_type<keys::numbers, int> grades;
	EXPECT_EQ(keys::numbers, grades.key());
}

TEST(model_cpp, collection_type_test_key_with_vardiac_argument)
{
	atom::collection_type<keys::numbers, int> grades(1, 2, 3, 4, 5);
	EXPECT_EQ(keys::numbers, grades.key());
}

TEST(model_cpp, collection_type_test_key_with_vector)
{
	atom::collection_type<keys::numbers, int> grades(std::pmr::vector<int>{ 1, 2, 3, 4, 5 });
	EXPECT_EQ(keys::numbers, grades.key());
}