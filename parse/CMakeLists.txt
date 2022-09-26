#cmake_minimum_required(VERSION 3.21)

#project(file_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(Boost REQUIRED filesystem)

add_library(parse peglib.h parse_vhdl_2008.cpp parse.hpp parse.cpp)
#target_link_libraries(parse PUBLIC Boost::filesystem)
target_include_directories(parse PUBLIC .)
