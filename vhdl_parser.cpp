//
//  vhdl_parser.cpp
//
//  Cross platform VHDL parser
//
//  Copyright (C) 2022 Iain Waugh. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE

#include <iostream>

#include <filesystem>
namespace fs = std::filesystem;

#include <boost/program_options.hpp>    // For CLI parsing: link with "-lboost_program_options"
namespace po = boost::program_options;

#include <iostream>
#include <iterator>
#include <parse.hpp>

int main(int argc, char* argv[])
{
    std::string hdl_file_name = "";
//    std::string ast_file_name = "";

    // Set up the command-line options and parse them
    try {
        po::options_description cliOpts("Program options");
        cliOpts.add_options()
        ("help,h", "produce help message")
        ("input-file,i", po::value< std::string >(), "input file")
//        ("output-file,o", po::value< std::string >(), "AST output file")
        ;

        po::options_description cliOptions;
        cliOptions.add(cliOpts);

        po::positional_options_description posOptD;
        posOptD.add("input-file", -1);
//        posOptD.add("output-file", -1);

        po::variables_map varMap;
        po::store(po::command_line_parser(argc, argv).options(cliOptions).positional(posOptD).run(), varMap);
        po::notify(varMap);

        // Respond to the "help" request first
        if (varMap.count("help")) {
            // Print the help messages
            std::cout << cliOpts << "\n";
            // Exit the program without doing anything more
            return 0;
        }

        if (varMap.count("input-file") > 0)
        {
            hdl_file_name = varMap["input-file"].as< std::string >();
        }
        else
        {
            // Print the help messages
            std::cout << cliOpts << "\n";
            // Exit the program without doing anything more
            return 0;
        }
//        if (varMap.count("output-file") > 0)
//        {
//            ast_file_name = varMap["output-file"].as< std::string >();
//        }
    }
    catch(std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        std::cerr << "An error happened while parsing your command lines!\n";
        return 1;
    }

    // Now do something with the command line information

    fs::path hdl_file_path(hdl_file_name);
//    fs::path ast_file_path(ast_file_name);

    if (exists(hdl_file_path))
    {
        if (fs::is_regular_file(hdl_file_path))
        {
            // Yes!
            // Pass it on to the parsing subroutine
            parse_vhdl_2008(hdl_file_path);
        }
        else
        {
            std::cout << "Error: " << hdl_file_path << " exists, but is not a file; please specify a file.\n";
            return 1;
        }
    } else {
        std::cout << "Error: " << hdl_file_path << " does not exist; please specify a file.\n";
        return 1;
    }

    return 0;
}
