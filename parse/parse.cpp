//
//  parse.cpp
//  file_parser
//
//  Attempt at cross-platform file parsing in C++17
//
//  Copyright © 2022 Iain Waugh. All rights reserved.
//

#include <iostream>
//#include <fstream>
//#include <string>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "parse.hpp"
#include <peglib.h>
using namespace peg;

int parse(fs::path file_path)
{
    std::cout << file_path << " size is " << file_size(file_path) << '\n';

    parse_vhdl_2008(file_path);

//    std::string line;
//    fs::ifstream file_in;
//    std::cout << "This program only prints the file contents for now..." << std::endl;
//    file_in.open(file_path, std::ios::in);
//    while (getline(file_in, line)) {
//        std::cout << line << std::endl;
//    }
    return 0;
}
