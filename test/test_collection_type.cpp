#include <gtest/gtest.h>

#include "../collection_type.hpp"

TEST(model_cpp, collection_type_test_key)
{
	atom::collection_type<int> grades("grades");
	EXPECT_EQ("grades", grades.key());

	atom::collection_type<int> other_grades("grades", 90, 100, 99, 98, 94);
	EXPECT_EQ("grades", other_grades.key());
}