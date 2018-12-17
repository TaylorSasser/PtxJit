#ifndef PTXJIT_KERNEL_HPP
#define PTXJIT_KERNEL_HPP

#include <ptxjit/type.hpp>

namespace ptxjit
{
	template<typename... ParameterTypes>
	class kernel
	{
	public:
		using parameters_t = params<ParameterTypes...>;

		kernel(std::string name,params<ParameterTypes...> const& params) noexcept
			: kernel_name_{std::move(name)},parameters_{params}
		{}

		std::string const& name() const noexcept
		{
			return kernel_name_;
		}

		parameters_t const& parameters() const noexcept
		{
			return parameters_;
		}

		template<typename... ParameterTypes>
		friend std::ostream& operator<<(std::ostream& os,kernel<ParameterTypes...> const& kernel)
		{
			return (os << "name : \"" << kernel.name() << "\" parameters : " << kernel.parameters());
		}
	private:
		std::string const kernel_name_;
		parameters_t const parameters_;
	};
}

#endif //PTXJIT_KERNEL_HPP
