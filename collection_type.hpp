#pragma once

#include <vector>
#include <string_view>
#include <type_traits>
#include <memory_resource>

namespace atom
{
	class collection {};

	template <const char* key_value, typename type>
	class collection_type : public collection
	{
	public:
		template <typename Value, typename = std::enable_if_t<
									std::is_constructible_v<std::pmr::vector<type>, std::remove_const_t<std::decay_t<Value>>>
								>>
		constexpr collection_type(Value&& values)
		 : values_ { std::forward<Value>(values) }
		{ }
		template <typename... Value, typename = std::enable_if_t<
											std::conjunction_v<std::is_constructible<type, std::remove_cv_t<std::decay_t<Value>>>...>
										>>
		constexpr collection_type(Value&&... values)
		 : allocator { stack_buffer, sizeof stack_buffer },
		   values_ { { std::forward<Value>(values)... }, &allocator }
		{ }
		
		constexpr collection_type()
		 : allocator { stack_buffer, sizeof stack_buffer },
		   values_ { &allocator }
		{ }

		[[nodiscard]]std::string_view key() const noexcept
		{
			return key_;
		}

		[[nodiscard]] const std::pmr::vector<type>& values() const noexcept
		{
			return values_;
		}
		[[nodiscard]] std::pmr::vector<type>& values() noexcept
		{
			return values_;
		}
	private:
		const char* key_ { key_value };
		std::byte stack_buffer[1024];
		std::pmr::monotonic_buffer_resource allocator;
		std::pmr::vector<type> values_;
	};
}