#pragma once

#include <string_view>
#include <type_traits>

namespace atom
{
	template <typename T>
	class data_type
	{
	public:
		template <typename Key, typename Value, typename = std::enable_if_t<
													std::is_constructible_v<std::string_view, std::remove_cv_t<std::decay_t<Key>>>
												 && std::is_constructible_v<T, std::remove_cv_t<std::decay_t<Value>>>
												>>
		constexpr data_type(Key&& key, Value&& value = T())
		 : _key { std::forward<Key>(key) },
		   _value { std::forward<Value>(value) }
		{ }

		[[nodiscard]] const std::string_view& key() const
		{
			return _key;
		}
		[[nodiscard]] std::string_view& key()
		{
			return _key;
		}

		[[nodiscard]] const T& value() const
		{
			return _value;
		}
		[[nodiscard]] T& value()
		{
			return _value;
		}
	private:
		std::string_view _key;
		T _value;
	};
}