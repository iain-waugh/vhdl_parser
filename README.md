# VHDL Parser

#  1 Overview

This project aims to provide an open-source parser for VHDL 2008, staying as close to IEEE Std 1076-2008 as I could get without having left recursion in the grammar (I'm looking at you, `prefix`).

It is currently a work-in-progress, where the PEG definition file has been the focus of attention.  At this point, the code will compile and the executable should parse a VHDL'93 file and print its Abstract Syntax Tree (AST) to the standard output.  VHDL 2008 may partially work, but isn't tested.

It is released under the MIT license.



##  1.1 Multi-Platform Build

This project requires `cmake` and the Boost library (for '`program_options`') to build.

TODO: Add build instructions.



# 2 Thanks

This parser would not be possible without Y Hirose's [cpp-peglib.h](https://github.com/yhirose/cpp-peglib), and debugging the PEG grammar was **greatly** assisted by Mirko Kunze's [pegdebug](https://github.com/mqnc/pegdebug.git) and the linter that's in cpp-pegilb.h.



# 3 Testing

Build the [cpp-peglib.h](https://github.com/yhirose/cpp-peglib) project and copy `lint/peglint` into the `grammar` folder of this project.

Run individual tests with: `./peglint vhdl2008.peg --packrat tests/<test_name.vhd>`