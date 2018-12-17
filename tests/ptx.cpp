#include <catch.hpp>
#include <iostream>

#include <ptxjit/kernel.hpp>

TEST_CASE("BASICS")
{
	SECTION("LITERALS")
	{
		using namespace ptxjit;

		ptxjit::kernel test("saxpy",params{"a"_u64,"b"_u64,"c"_u64,"d"_u64});
		std::cout << test << '\n';
	}
}
