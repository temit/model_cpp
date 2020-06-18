#include <gtest/gtest.h>

#include "../converter.hpp"

namespace keys
{
	const char numbers[] = "numbers";
	const char first_name[] = "first_name";
}

TEST(model_cpp, convertor_collection_to_json)
{
	atom::collection_type<keys::numbers, int> number(1, 2, 3, 4);
	Json::Value js;
	atom::converter<int>().to_json(js, number);

	EXPECT_EQ(js[keys::numbers][0].as<int>(), 1);
	EXPECT_EQ(js[keys::numbers][1].as<int>(), 2);
	EXPECT_EQ(js[keys::numbers][2].as<int>(), 3);
	EXPECT_EQ(js[keys::numbers][3].as<int>(), 4);
}

TEST(model_cpp, convertor_collection_from_json)
{
	Json::Value js;
	js[keys::numbers][0] = 1;
	js[keys::numbers][1] = 2;
	js[keys::numbers][2] = 3;
	js[keys::numbers][3] = 4;
	atom::collection_type<keys::numbers, int> number;
	atom::converter<int>().from_json(js, number);

	EXPECT_EQ(js[keys::numbers][0].as<int>(), number.values()[0]);
	EXPECT_EQ(js[keys::numbers][1].as<int>(), number.values()[1]);
	EXPECT_EQ(js[keys::numbers][2].as<int>(), number.values()[2]);
	EXPECT_EQ(js[keys::numbers][3].as<int>(), number.values()[3]);
}

TEST(model_cpp, convertor_data_to_json)
{
	atom::data_type<keys::first_name, int> first_name(1);
	Json::Value js;
	atom::converter<int>().to_json(js, first_name);

	EXPECT_EQ(js[keys::first_name].as<int>(), first_name.value());
}

TEST(model_cpp, convertor_data_from_json)
{
	Json::Value js;
	js[keys::first_name] = 1;
	atom::data_type<keys::first_name, int> first_name;
	atom::converter<int>().from_json(js, first_name);

	EXPECT_EQ(js[keys::first_name].as<int>(), first_name.value());	
}
