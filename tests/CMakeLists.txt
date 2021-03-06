cmake_minimum_required(VERSION 3.10)
project(ptxjit-tests CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(tests_config INTERFACE)

add_custom_target(catch)

target_compile_options(tests_config INTERFACE
        ${tests_config}
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:
        -fno-strict-aliasing
        -Wall
        -Wcast-align
        -Wconversion
        -Wctor-dtor-privacy
        -Werror
        -Wextra
        -Wno-missing-braces
        -Wno-unknown-attributes
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wpedantic
        -Wshadow
        -Wsign-conversion
        >)

target_include_directories(tests_config INTERFACE ${CATCH_DIRECTORY})

target_compile_definitions(tests_config INTERFACE
        GSL_THROW_ON_CONTRACT_VIOLATION)

add_library(test_catch STATIC main.cpp)

target_link_libraries(test_catch
        ptxjit
        tests_config)

add_dependencies(test_catch catch)
set_property(TARGET test_catch PROPERTY FOLDER "PTXJIT_TESTS")

function(ptxjit_add_tests name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name}
            ptxjit
            test_catch
            tests_config)
    add_dependencies(${name} catch)
    add_test(
            ${name}
            ${name}
    )
    set_property(TARGET ${name} PROPERTY FOLDER "PTXJIT_TESTS")
endfunction()

ptxjit_add_tests(ptx)