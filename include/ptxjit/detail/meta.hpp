#ifndef PTXJIT_META_HPP
#define PTXJIT_META_HPP

#include <type_traits>
#include <tuple>
#include <string>

namespace ptxjit
{
	template <typename Tuple, size_t Index>
	struct print_tuple_helper
	{
		std::ostream& operator()(std::ostream& s,Tuple const& t,std::string const& delimiter)
		{
			return print_tuple_helper<Tuple, Index - 1>{}(s, t,", ") << std::get<Index - 1>(t) << delimiter;
		}
	};

	template <typename Tuple>
	struct print_tuple_helper<Tuple,0>
    {
		std::ostream& operator()(std::ostream& s,Tuple const& t,std::string const& delimiter)
		{
			return s;
		}
	};

	template <typename... TupleTypes>
	std::ostream& operator<<(std::ostream& os,std::tuple<TupleTypes...> const& tuple)
	{
		using tuple_type = std::tuple<TupleTypes...>;
		os << '[';
		print_tuple_helper<tuple_type,std::tuple_size_v<tuple_type>> printer{};
		printer(os,tuple,std::string{""});
		os << ']';
		return os;
	}
}

#endif //PTXJIT_META_HPP
