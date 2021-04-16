cmake_minimum_required(VERSION 3.10)

project(NumericalMethods)

# specify the C++ standard
#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED True)


MAKE_DIRECTORY(output/simpson_integration)
#add_executable(simpson_integration src/simpson_integration/simpson_integration.cpp)
#add_executable(simpson_integration_v1 src/simpson_integration/simpson_integration_v1.cpp)


include(CheckCXXCompilerFlag)

check_cxx_compiler_flag(-std=c++14 HAVE_FLAG_STD_CXX14)
if(HAVE_FLAG_STD_CXX14)
    add_executable(simpson_integration_v1 src/simpson_integration/simpson_integration_v1.cpp)
else()
    add_executable(simpson_integration src/simpson_integration/simpson_integration.cpp)
endif()