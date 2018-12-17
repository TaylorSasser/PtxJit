#ifndef PTXJIT_OPERAND_HPP
#define PTXJIT_OPERAND_HPP

#include <string>


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

		friend std::ostream& operator<<(std::ostream& os, operand<T> const& op)
		{
			return os << op.name_;
		}
	protected:
		std::string const name_;
	};

	template<typename T>
	class param : public operand<T>
	{
	public:
		using base_class = operand<T>;

		explicit param(operand<T>& op)
			: operand<T>(std::move(op))
		{
			base_class::name_ = std::string(".param ") + std::string(type<T>::value) + base_class::name_;
		}
	};

	template<typename... Parameters>
	class params
	{
	public:
		using param_tuple = std::tuple<Parameters...>;

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
