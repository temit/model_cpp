#pragma once

#include <string_view>
#include <type_traits>

namespace atom
{
	class data {};

	template <const char* key_value, typename type>
	class data_type : public data
	{
	public:
		data_type() = default;
		template <typename value_type, typename = std::enable_if_t<
		                                std::is_constructible_v<type, std::remove_cv_t<std::decay_t<value_type>>>
		                              >>
		data_type(value_type&& value_)
		 : value_ { std::forward<value_type>(value_) }
		{ }

		[[nodiscard]]std::string_view key() const noexcept
		{
		  return key_;
		}
		[[nodiscard]]type& value() noexcept
		{
		  return value_;
		}
		[[nodiscard]]const type& value() const noexcept
		{
		  return value_;
		}
	private:
		const char* key_ { key_value };
		type value_;
	};
}