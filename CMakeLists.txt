project(NumericalMethods)


cmake_minimum_required(VERSION 3.10)
include(CheckCXXCompilerFlag)


MAKE_DIRECTORY(output/simpson_integration)

check_cxx_compiler_flag(-std=c++14 HAVE_FLAG_STD_CXX14)

if(HAVE_FLAG_STD_CXX14)
    add_executable(simpson_integration_v1 src/simpson_integration/simpson_integration_v1.cpp)
else()
    add_executable(simpson_integration src/simpson_integration/simpson_integration.cpp)
endif()


