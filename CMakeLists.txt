cmake_minimum_required(VERSION 3.6)
project(ptxjit CXX)

set(CMAKE_CXX_STANDARD 17)

set(CXX_STANDARD "17" CACHE STRING "Use c++ standard")
set(CXX_STD "cxx_std_${CXX_STANDARD}")
set(CATCH_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/catch2)

add_library(ptxjit INTERFACE)
target_compile_features(ptxjit INTERFACE "${CXX_STD}")

target_compile_definitions(ptxjit INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:
        _SCL_SECURE_NO_WARNINGS
        _SILENCE_CXX17_UNCAUGHT_EXCEPTION_DEPRECATION_WARNING>)

target_include_directories(ptxjit INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

install(DIRECTORY include/ptxjit DESTINATION include)

enable_testing()
add_subdirectory(tests)