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
    std::string fileName = "";

    // Set up the command-line options and parse them
    try {
        po::options_description cliOpts("Program options");
        cliOpts.add_options()
        ("help,h", "produce help message")
        ("input-file,i", po::value< std::string >(), "input file")
        ;

        po::options_description cliOptions;
        cliOptions.add(cliOpts);

        po::positional_options_description posOptD;
        posOptD.add("input-file", -1);

        po::variables_map varMap;
        po::store(po::command_line_parser(argc, argv).options(cliOptions).positional(posOptD).run(), varMap);
        po::notify(varMap);

        // respond to the "help" request first
        if (varMap.count("help")) {
            // Print the help messages
            std::cout << cliOpts << "\n";
            // Exit the program
            return 0;
        }

        if (varMap.count("input-file"))
        {
            fileName = varMap["input-file"].as< std::string >();
        }
        else
        {
            // Print the help messages
            std::cout << cliOpts << "\n";
            // Exit the program
            return 0;
        }

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

    fs::path file_path(fileName);  // avoid repeated path construction below

    if (exists(file_path))    // does path p actually exist?
    {
        if (fs::is_regular_file(file_path))        // is <file_path> pointing to a regular file?
            // Yes!
            // Pass it on to the parsing subroutine
            parse(file_path);

        else if (fs::is_directory(file_path))      // is path p a directory?
        {
            std::cout << "Error: " << file_path << " is a directory; please specify a file.\n";
            return 1;
        } else {
            std::cout << "Error: " << file_path << " exists, but is not a regular file or directory; please specify a file.\n";
            return 1;
        }
    } else {
        std::cout << "Error: " << file_path << " does not exist; please specify a file.\n";
        return 1;
    }

    return 0;
}
