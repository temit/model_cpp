#include <type_traits>

#include "json/json.h"

#include "data_type.hpp"
#include "collection_type.hpp"

namespace atom
{

	template <typename T, typename = std::enable_if_t<
							std::is_pod_v<T>
						>>
	class converter
	{
	public:
		template <typename value_type, typename = std::enable_if_t<
										std::is_constructible_v<collection, std::remove_cv_t<std::decay_t<value_type>>>
									 || std::is_constructible_v<data, std::remove_cv_t<std::decay_t<value_type>>>
									>,
									typename = std::enable_if_t<
										std::is_constructible_v<collection, std::remove_cv_t<std::decay_t<value_type>>>
									>>
		void to_json(Json::Value& js, value_type&& values)
		{
			js[values.key().data()] = Json::Value(Json::arrayValue);
			for(auto&& value : values.values() )
				js[values.key().data()].append(value);
		}

		template <typename value_type, typename = std::enable_if_t<
										std::is_constructible_v<data, std::remove_cv_t<std::decay_t<value_type>>>
									>>
		void to_json(Json::Value& js, value_type&& value)
		{
			js[value.key().data()] = value.value();
		}

		template <typename json_type, typename value_type, typename = std::enable_if_t<
															std::is_constructible_v<Json::Value, std::remove_cv_t<std::decay_t<json_type>>>
														 && std::is_lvalue_reference_v<value_type>
														 && (std::is_constructible_v<collection, std::remove_cv_t<std::decay_t<value_type>>>
														  || std::is_constructible_v<data, std::remove_cv_t<std::decay_t<value_type>>>)
														>, typename = std::enable_if_t<
															std::is_constructible_v<collection, std::remove_cv_t<std::decay_t<value_type>>>
														>>
		void from_json(json_type&& js, value_type&& values)
		{
			if(js.isMember(values.key().data()))
				for (Json::ArrayIndex i=0; i < js[values.key().data()].size(); i++)
					values.values().emplace_back(js[values.key().data()][i].template as<T>());
		}
		template <typename json_type, typename value_type, typename = std::enable_if_t<
															std::is_constructible_v<data, std::remove_cv_t<std::decay_t<value_type>>>
														>>
		void from_json(json_type&& js, value_type&& value)
		{
			if (js.isMember(value.key().data()))
				value.value() = js[value.key().data()].template as<T>();
		}
	};
}