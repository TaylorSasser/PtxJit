#include <catch.hpp>
#include <iostream>

#include <ptxjit/assembler.hpp>
#include <ptxjit/kernel.hpp>


using namespace ptxjit;

TEST_CASE("BASICS")
{
	SECTION("LITERALS")
	{
		kernel test("saxpy",params{"a"_f32,"b"_f32,"c"_f32,"d"_f32});
		std::cout << test << '\n';

		assembler a{};


	}
}
