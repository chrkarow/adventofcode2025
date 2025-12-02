cmake_minimum_required(VERSION 4.0)
project(adventofcode2025)

set(CMAKE_CXX_STANDARD 23)

add_executable(adventofcode2025 aoc.cpp)

find_package(Boost)
target_link_libraries(adventofcode2025 boost::boost)