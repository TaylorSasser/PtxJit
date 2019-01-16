#ifndef PTXJIT_OPERAND_HPP
#define PTXJIT_OPERAND_HPP

#include <string>

#include <ptxjit/type.hpp>
#include <ptxjit/detail/fragment.hpp>
#include <ostream>

namespace ptxjit
{
	template<typename T>
	class param : public operand<T>
	{
	public:
		using base_class = operand<T>;
		using type_class = type<T>;
		using value_type = typename type_class::value_type;

		explicit param(operand<T>& op)
			: operand<T>(std::move(op))
		{}

		friend std::ostream& operator<<(std::ostream &os, param<T> const& param)
		{
			return (os << ".param " << type_class::value << param.name());
		}
	};

	template<typename... Parameters>
	class params
	{
	public:
		using param_tuple = std::tuple<param<typename Parameters::operand_type>...>;

		explicit params(Parameters&&... operands) noexcept
			: parameters_(std::make_tuple(param{operands}...))
		{}

		template<typename... S>
		friend std::ostream& operator<<(std::ostream& os,params<S...> const& params)
		{
			return os << params.parameters_;
		}
	private:
		param_tuple const parameters_;
	};
}

#endif //PTXJIT_OPERAND_HPP
