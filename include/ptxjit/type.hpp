#ifndef PTXJIT_TYPE_HPP
#define PTXJIT_TYPE_HPP

#include <utility>
#include <string_view>
#include <sstream>

#include <ptxjit/detail/meta.hpp>
#include <ptxjit/detail/fragment.hpp>

namespace ptxjit
{

	template<typename T>
	class operand
	{
	public:
		using operand_type = T;

		explicit operand(std::string name) noexcept
			: name_{std::move(name)}
		{}

		std::string const& name() const noexcept
		{
			return name_;
		}
	protected:
		std::string name_;
	};

	namespace detail
	{
		static constexpr inline fragment unsigned_short_{".u16"};
		static constexpr inline fragment unsigned_int_{".u32"};
		static constexpr inline fragment unsigned_long_long_{".u64"};

		static constexpr inline fragment signed_short_{".s16"};
		static constexpr inline fragment signed_int_{".s32"};
		static constexpr inline fragment signed_long_long_{".s64"};

		static constexpr inline fragment float_{".f32"};
		static constexpr inline fragment double_{".f64"};
	}


	template<typename ValueType>
	struct type
	{
		using value_type = ValueType;
	};


	#define PTXJIT_DEFINE_TYPE(T,fragment,alias)                                                \
	using alias = type<T>;                                                                      \
																								\
	template<>                                                                                  \
	struct type<T>                                                                              \
	{                                                                                           \
		using value_type = T;                                                                   \
		constexpr static inline std::string_view value{fragment.begin(),fragment.size()};       \
	};                                                                                          \
																								\
	auto operator ""_##alias(const char* lit, size_t)                                           \
	{                                                                                           \
		return operand<T>{std::string(lit)};                                                    \
	};                                                                                          \

	PTXJIT_DEFINE_TYPE(unsigned short,detail::unsigned_short_,u16)
	PTXJIT_DEFINE_TYPE(unsigned short*,detail::unsigned_long_long_,u16_ptr)

	PTXJIT_DEFINE_TYPE(unsigned int,detail::unsigned_int_,u32)
	PTXJIT_DEFINE_TYPE(unsigned int*,detail::unsigned_long_long_,u32_ptr)

	PTXJIT_DEFINE_TYPE(unsigned long long,detail::unsigned_long_long_,u64)
	PTXJIT_DEFINE_TYPE(unsigned long long*,detail::unsigned_long_long_,u64_ptr)

	PTXJIT_DEFINE_TYPE(signed short,detail::signed_short_,s16)
	PTXJIT_DEFINE_TYPE(signed short*,detail::unsigned_long_long_,s16_ptr)

	PTXJIT_DEFINE_TYPE(signed int,detail::signed_int_,s32)
	PTXJIT_DEFINE_TYPE(signed int*,detail::unsigned_long_long_,s32_ptr)

	PTXJIT_DEFINE_TYPE(signed long long,detail::signed_long_long_,s64)
	PTXJIT_DEFINE_TYPE(signed long long*,detail::unsigned_long_long_,s64_ptr)

	PTXJIT_DEFINE_TYPE(float,detail::float_,f32)
	PTXJIT_DEFINE_TYPE(float*,detail::unsigned_long_long_,f32_ptr)

	PTXJIT_DEFINE_TYPE(double,detail::double_,f64)
	PTXJIT_DEFINE_TYPE(double*,detail::unsigned_long_long_,f64_ptr)
}


#endif //PTXJIT_TYPE_HPP
