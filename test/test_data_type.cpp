#include <gtest/gtest.h>

#include "../data_type.hpp"
#include <string>

TEST(model_cpp, data_type_test_key)
{
	atom::data_type<std::string> first_name("first_name", "first_name");
	// test if key is generated the same
	EXPECT_STREQ("first_name",
				 first_name.key().data());
}

TEST(model_cpp, data_type_test_key_assignment)
{
	atom::data_type<std::string> first_name("first_name", "first_name");
	// test if key is generated the same
	EXPECT_STREQ("first_name",
				 first_name.key().data());
	first_name.key() = "last_name";
	EXPECT_STREQ("last_name",
				 first_name.key().data());
}

TEST(model_cpp, data_type_test_value)
{
	atom::data_type<std::string> first_name("first_name", "first_name");
	// test if the assigned value is the same
	EXPECT_STREQ("first_name",
				 first_name.value().c_str());
}

TEST(model_cpp, data_type_test_value_assignment)
{
	atom::data_type<std::string> first_name("first_name", "first_name");
	// test if the assigned value is the same
	EXPECT_STREQ("first_name",
				 first_name.value().c_str());
	first_name.value() = "Temesgen";
	EXPECT_STREQ("Temesgen",
				 first_name.value().c_str());
}
