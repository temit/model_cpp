#pragma once

#include <vector>
#include <string_view>
#include <type_traits>

namespace atom
{
	template <typename T>
	class collection_type
	{
	public:
		template <typename Key, typename Value, typename = std::enable_if_t<
												std::is_constructible_v<std::string_view, std::remove_cv_t<std::decay_t<Key>>>
											 && std::is_constructible_v<std::vector<T>, std::remove_const_t<std::decay_t<Value>>> >>
		constexpr collection_type(Key&& key = Key(), Value&& values = Value())
		 : key_ { std::forward<Key>(key) },
		   values_ { std::forward<Value>(values) }
		{ }
		template <typename Key, typename... Value, typename = std::enable_if_t<
												std::is_constructible_v<std::string_view, std::remove_cv_t<std::decay_t<Key>>>
											 && std::conjunction_v<std::is_same<T, Value>...> >>
		constexpr collection_type(Key&& key, Value&&... values)
		 : key_ { std::forward<Key>(key) },
		   values_ { std::forward<Value>(values)... }
		{ }

		[[nodiscard]] const std::string_view& key() const noexcept
		{
			return key_;
		}
		[[nodiscard]] std::string_view& key() noexcept
		{
			return key_;
		}

		[[nodiscard]] const std::vector<T>& values() const noexcept
		{
			return values_;
		}
		[[nodiscard]] std::vector<T>& values() noexcept
		{
			return values_;
		}
	private:
		std::string_view key_;
		std::vector<T> values_;
	};
}