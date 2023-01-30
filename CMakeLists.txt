cmake_minimum_required(VERSION 3.16)

# Project name in the top-level CMakeLists
set(This LoadBalancer)

project(${This} C CXX)

# C/CPP standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # useful for mixed libraries

include_directories(include)

# dependencies
# add_subdirectory(lib/googletest)
# add_subdirectory(lib/map)

add_subdirectory(src)

# enable_testing()
# add_subdirectory(tests)