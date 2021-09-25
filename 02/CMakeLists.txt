cmake_minimum_required(VERSION 3.20)
project(02)

set(CMAKE_CXX_STANDARD 14)

add_executable(02 main.cpp getCPUTime.hpp getCPUTime.cpp arr_gen.cpp arr_gen.hpp time_compare.cpp time_compare.hpp sorts.cpp sorts.hpp)
