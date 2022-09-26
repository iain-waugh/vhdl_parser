# VHDL Parser

#  1 Overview

This project aims to provide a parser for VHDL 2008, staying as close to IEEE Std 1076-2008 as I could get without having left recursion in the grammar (I'm looking at you, `prefix`).

It is released under the MIT license.



##  1.1 Multi-Platform Build

This project requires `cmake` and the Boost library to build.

cmake -B build .



# 2 Thanks

This parser would not be possible without Y. Hirose's [cpp-peglib.h](https://github.com/yhirose/cpp-peglib), and debugging the PEG grammar was **greatly** assisted by Mirko Kunze's [pegdebug](https://github.com/mqnc/pegdebug.git) and the linter that's in cpp-pegilb.h.

