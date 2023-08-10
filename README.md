# VHDL Parser

#  1 Overview

This project aims to provide an open-source parser for VHDL 2008, staying as close to IEEE Std 1076-2008 as I could get without having left recursion in the grammar (I'm looking at you, `prefix`).

It is released under the MIT license.



## 1.1 Current status

It is currently abandoned because I've found a better, faster way to create an AST.

At this point in time:

- The code will compile and the executable should parse a VHDL'93 file and print its Abstract Syntax Tree (AST) to the standard output.
- VHDL 2008 may partially work, but isn't fully tested.
- 'special characters' with ASCII codes of 160 or higher are not parsed properly

At best, it's a reference for multi-platform builds.



##  1.2 Multi-Platform Build

This project requires `cmake` and the Boost library (for '`program_options`') to build.

Under MSys2, `pacboy find boost` to see which libraries are available and `pacman -S <package>` to install.

**Example for 64-bit MinGW under MSys2:**

`pacman -S mingw64/mingw-w64-x86_64-boost`

**Building:**

```bash
mkdir build && cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
```



# 2 Thanks

This parser would not be possible without Y Hirose's [cpp-peglib.h](https://github.com/yhirose/cpp-peglib), and debugging the PEG grammar was **greatly** assisted by Mirko Kunze's [pegdebug](https://github.com/mqnc/pegdebug.git) and the linter that's in cpp-pegilb.h.



# 3 Testing

Build the [cpp-peglib.h](https://github.com/yhirose/cpp-peglib) project and copy `lint/peglint` into the `grammar` folder of this project.

Run individual tests with: `./peglint vhdl2008.peg --packrat tests/<test_name.vhd>`