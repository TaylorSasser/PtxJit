#ifndef PTXJIT_TYPE_HPP
#define PTXJIT_TYPE_HPP

#include <utility>
#include <string_view>
#include <sstream>

#include <ptxjit/operand.hpp>
#include <ptxjit/detail/meta.hpp>
#include <ptxjit/detail/fragment.hpp>


namespace ptxjit
{
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
	template<>                                                                                  \
	struct type<T>                                                                              \
	{                                                                                           \
		using value_type = T;                                                                   \
		constexpr static inline std::string_view value{fragment.begin(),fragment.size()};       \
	};                                                                                          \
	using alias = type<T>;                                                                      \
	auto operator "" _##alias(const char* lit, size_t)                                          \
	{                                                                                           \
		return operand<T>{std::string(lit)};                                                    \
	};                                                                                          \

	PTXJIT_DEFINE_TYPE(unsigned short,detail::unsigned_short_,u16)
	PTXJIT_DEFINE_TYPE(unsigned int,detail::unsigned_int_,u32)
	PTXJIT_DEFINE_TYPE(unsigned long long,detail::unsigned_long_long_,u64)

	PTXJIT_DEFINE_TYPE(signed short,detail::signed_short_,s16)
	PTXJIT_DEFINE_TYPE(signed int,detail::signed_int_,s32)
	PTXJIT_DEFINE_TYPE(signed long long,detail::signed_long_long_,s64)

	PTXJIT_DEFINE_TYPE(float,detail::float_,f32)
	PTXJIT_DEFINE_TYPE(double,detail::double_,f64)
}


#endif //PTXJIT_TYPE_HPP
