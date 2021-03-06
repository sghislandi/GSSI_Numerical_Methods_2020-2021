project(NumericalMethods)
cmake_minimum_required(VERSION 3.10)


include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++14 HAVE_FLAG_STD_CXX14)


MAKE_DIRECTORY(output/simpson_integration)
MAKE_DIRECTORY(output/ODE)
MAKE_DIRECTORY(output/PDE)

if(HAVE_FLAG_STD_CXX14)
    set(CMAKE_CXX_FLAGS "-O3 -ftree-vectorize -std=c++14")
    add_executable(simpson_integration_v1 src/simpson_integration/simpson_integration_v1.cpp)
else()
    set(CMAKE_CXX_FLAGS "-O3 -ftree-vectorize -std=c++11")
    add_executable(simpson_integration src/simpson_integration/simpson_integration.cpp)
endif()

add_executable(ODE src/ODE/ODE.cpp)
add_executable(test test/ODE/test.cpp)
set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../test/ODE")

add_executable(PDE src/PDE/PDE.cpp)
