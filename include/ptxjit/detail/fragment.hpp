#ifndef PTXJIT_FIXED_STRING_HPP
#define PTXJIT_FIXED_STRING_HPP

#include <utility>
#include <cstddef>
#include <ostream>

namespace ptxjit
{
	template<typename CharType,std::size_t N>
	class fragment
	{
	public:
		using char_type = CharType;

		template<std::size_t... Is>
		constexpr fragment(char_type const(&input)[N],std::index_sequence<Is...> const&) noexcept
			: data_{input[Is]...}
		{}

		template <std::size_t M,std::size_t... SeqA,std::size_t... SeqB>
		constexpr fragment(fragment<char_type,M> const a, fragment<char_type,N - M + 1> const b, std::index_sequence<SeqA...>,std::index_sequence<SeqB...>)
			: data_{a[SeqA]...,b[SeqB]...}
		{}

		constexpr explicit fragment(char_type const(&input)[N]) noexcept
			: fragment(input,std::make_index_sequence<N>())
		{}

		constexpr size_t size() const noexcept
		{
			return N;
		}

		constexpr char_type const operator[](std::size_t index) const noexcept
		{
			return data_[index];
		}

		constexpr char_type const* begin() const noexcept
		{
			return data_;
		}

		constexpr char_type const* end() const noexcept
		{
			return data_ + N;
		}

		constexpr char_type const* data() const noexcept
		{
			return data_;
		}

		friend std::ostream &operator<<(std::ostream &os, fragment const& string)
		{
			return (os << string.data_);
		}
	private:
		char_type data_[N];
	};

	template<typename CharType>
	class fragment<CharType,0>
	{
	public:
		using char_type = CharType;

		constexpr fragment(char_type const*) noexcept
		{}

		constexpr size_t size() const noexcept
		{
			return 0;
		}

		constexpr char_type const* begin() const noexcept
		{
			return nullptr;
		}

		constexpr char_type const* end() const noexcept
		{
			return nullptr;
		}
	};

	namespace detail
	{
		template<std::size_t...>
		struct to_chars { static const char value[]; };

		template<std::size_t... digits>
		constexpr char to_chars<digits...>::value[] = {('0' + digits)..., 0};

		template<std::size_t rem, std::size_t... digits>
		struct explode : explode<rem / 10, rem % 10, digits...> {};

		template<std::size_t... digits>
		struct explode<0, digits...> : to_chars<digits...> {};
	}

	template<std::size_t num>
	struct num_to_string : detail::explode<num> {};

	template<std::size_t N,std::size_t M>
	constexpr auto operator+(fragment<char,N> const& s1,fragment<char,M> const& s2)
		-> fragment<char,N + M - 1>
	{
		return fragment<char,N + M - 1>(s1, s2,std::make_index_sequence<N - 1>(),std::make_index_sequence<M>());
	}

}

#endif //PTXJIT_STRING_HPP
