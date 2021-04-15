cmake_minimum_required(VERSION 3.10)

project(NumericalMethods)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


MAKE_DIRECTORY(output/simpson_integration)
add_executable(simpson_integration src/simpson_integration/simpson_integration.cpp)
add_executable(simpson_integration_v1 src/simpson_integration/simpson_integration_v1.cpp)
