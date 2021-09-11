cmake_minimum_required(VERSION 3.20)
project(01)

set(CMAKE_CXX_STANDARD 17)

add_executable(01 main.cpp getCPUTime.hpp getCPUTime.cpp string_gen.cpp string_gen.hpp time_compare.cpp time_compare.hpp levenstein.cpp levenstein.hpp manual_input.cpp manual_input.hpp)
