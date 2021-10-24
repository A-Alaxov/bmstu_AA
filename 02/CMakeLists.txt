cmake_minimum_required(VERSION 3.20)
project(03)

set(CMAKE_CXX_STANDARD 14)

add_executable(03 main.cpp getCPUTime.hpp getCPUTime.cpp arr_gen.cpp arr_gen.hpp time_compare.cpp time_compare.hpp algorithms.cpp algorithms.hpp)
