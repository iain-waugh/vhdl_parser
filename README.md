# VHDL Parser

# 1 Overview

This project aims to provide an open-source parser for VHDL 2008, staying as close to IEEE Std 1076-2008 as I could get without having left-recursion in the grammar (I'm looking at you, `prefix`).

It is released under the MIT license.

## 1.1 Current status

It is currently abandoned because I've found a better, faster way to create an AST with tree-sitter.

At this point in time:

- The code will compile and the executable should parse some VHDL'93 files (but not all) and print its Abstract Syntax Tree (AST) to the standard output.
- VHDL 2008 may partially work, but isn't fully tested.
- 'special characters' with ASCII codes of 160 or higher are not parsed properly

At best, it's a reference for multi-platform builds.

If this project starts up again, I noticed that `cpp-peglib` now allows you to run a parse operation starting from any point in the PEG syntax, so you don't need to try to debug from the top-level all the time ([see this link]([Changing root feature · Issue #304 · yhirose/cpp-peglib · GitHub](https://github.com/yhirose/cpp-peglib/issues/304#issuecomment-2323518735))).  This is quite the game-changer and would allow for proper unit-testing to guarantee lower PEG syntax levels are working properly before trying more complex ones.  The `cpp-peglib.h` that supports this is in this project now.

## 1.2 Multi-Platform Build

This project requires `cmake` and the Boost library (for '`program_options`') to build.

Under Windows MSys2, `pacboy find boost :p` to see which libraries are available and `pacman -S <package>` to install.

**Example for 64-bit UCRT under MSys2:**

```bash
pacman -S mingw-w64-ucrt-x86_64-toolchain
pacman -S ucrt64/mingw-w64-ucrt-x86_64-boost
```

**Building:**

Set `BOOST_ROOT` to point to the Boost library install folder.

```bash
mkdir build && cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
```

Note: MSVC buids fail because it can't cope with the really, really long string that contains the PEG definition.

# 2 Thanks

This parser would not be possible without Y Hirose's [cpp-peglib.h](https://github.com/yhirose/cpp-peglib), and debugging the PEG grammar was **greatly** assisted by Mirko Kunze's [pegdebug](https://github.com/mqnc/pegdebug.git) and the linter that's in cpp-pegilb.h.

# 3 Testing

Build the [cpp-peglib.h](https://github.com/yhirose/cpp-peglib) project and copy `lint/peglint` into the `grammar` folder of this project.

Run individual tests with: `./peglint vhdl2008.peg --packrat tests/<test_name.vhd>`
