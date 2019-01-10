#ifndef PTXJIT_ASSEMBLER_HPP
#define PTXJIT_ASSEMBLER_HPP

#include <ptxjit/param.hpp>

namespace ptxjit
{
	class instruction;




	class assembler
	{
	public:

	private:
		template<typename T>
		std::uint32_t emit(
			instruction inst,
			operand<T> const& op1,
			operand<T> const& op2);

	};
}

#endif //PTXJIT_ASSEMBLER_HPP
