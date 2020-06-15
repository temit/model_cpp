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
		template <typename type, typename = std::enable_if_t<
										std::is_same_v<collection_type<T>, std::remove_cv_t<std::decay_t<type>>>
									 || std::is_same_v<data_type<T>, std::remove_cv_t<std::decay_t<type>>> >,
									typename = std::enable_if_t<
										std::is_same_v<collection_type<T>, std::remove_cv_t<std::decay_t<type>>>
									 && !std::is_same_v<data_type<T>, std::remove_cv_t<std::decay_t<type>>>
								>>
		void to_json(Json::Value& js, type&& values)
		{
			js[values.key().data()] = Json::Value(Json::arrayValue);
			for(auto&& value : values.values() )
				js[values.key().data()].append(value);
		}
		template <typename type, typename = std::enable_if_t<
									std::is_same_v<data_type<T>, std::remove_cv_t<std::decay_t<type>>>
								>>
		void to_json(Json::Value& js, type&& value)
		{
			js[value.key().data()] = value.value();
		}

		template <typename type, typename t, typename = std::enable_if_t<
								std::is_same_v<Json::Value, std::remove_cv_t<std::decay_t<type>>>
							>>
		void from_json(type&& js, collection_type<t>& collection)
		{
			if(js.isMember(collection.key().data()))
				for (Json::ArrayIndex i=0; i < js[collection.key().data()].size(); i++)
					collection.values().emplace_back(js[collection.key().data()][i].template as<t>());
		}
		template <typename type, typename t, typename = std::enable_if_t<
								std::is_same_v<Json::Value, std::remove_cv_t<std::decay_t<type>>>
							>>
		void from_json(type&& js, data_type<t>& data)
		{
			if(js.isMember(data.key().data()))
				data.value() = js[data.key().data()].template as<t>();
		}
	};
}