#ifndef PTXJIT_META_HPP
#define PTXJIT_META_HPP

#include <type_traits>
#include <tuple>
#include <string>

namespace ptxjit
{
	template<class TupType, size_t... I>
	void print(std::ostream& os,TupType const& tuple, std::index_sequence<I...>)
	{
		os << '[';
		(..., (os << (I == 0 ? "" : ", ") << std::get<I>(tuple)));
		os << ']' << '\n';
	}

	template<class... T>
	void print(std::ostream& os,std::tuple<T...> const& tuple)
	{
		print(os,tuple,std::make_index_sequence<sizeof...(T)>());
	}


	template <typename... TupleTypes>
	std::ostream& operator<<(std::ostream& os,std::tuple<TupleTypes...> const& tuple)
	{
		print(os,tuple);
		return os;
	}

}

#endif //PTXJIT_META_HPP
