project(NumericalMethods)

cmake_minimum_required(VERSION 3.10)
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++14 HAVE_FLAG_STD_CXX14)

find_package(GSL)

MAKE_DIRECTORY(output/simpson_integration)
MAKE_DIRECTORY(output/ODE)

if(HAVE_FLAG_STD_CXX14)
    add_executable(simpson_integration_v1 src/simpson_integration/simpson_integration_v1.cpp)
else()
    add_executable(simpson_integration src/simpson_integration/simpson_integration.cpp)
endif()

add_executable(ODE src/ODE/ODE.cpp)

add_executable(test test/ODE/test.cpp)
set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../test/ODE")

