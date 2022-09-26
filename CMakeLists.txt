cmake_minimum_required(VERSION 3.21)

project(vhdl_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED program_options)

add_subdirectory(parse)

add_executable(vhdl_parser vhdl_parser.cpp)
target_link_libraries(vhdl_parser PUBLIC Boost::program_options parse)

install(TARGETS vhdl_parser
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
