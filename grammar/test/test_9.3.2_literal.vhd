-------------------------------------------------------------------------------
--
-- Copyright (c) 2022 Iain Waugh
-- All rights reserved.
--
-- Non-functional VHDL code to test the PEG
--
-- Test VHDL-2008 'literal'
--   Covers:
--     Section 9.3.2
--     Section 15.4.1
--
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

architecture test of vhdl_literal is
begin

-- numeric_literal = abstract_literal or physical_literal
-- abstract_literal = decimal_literal or based_literal
-- decimal_literal
  sig01 <= 12;
  sig02 <= 0;
  sig03 <= 1E6;
  sig04 <= 123_456;
  sig05 <= 12.0;
  sig06 <= 0.0;
  sig07 <= 0.456;
  sig08 <= 3.14159_26;
  sig09 <= 1.34E-12;
  sig0a <= 1.0E+6;
  sig0b <= 6.023E+24;

-- based_literal
  sig11 <= 2#1111_1111#;
  sig12 <= 16#FF#;
  sig13 <= 016#0FF#;
  sig14 <= 16#E#E1;
  sig15 <= 2#1110_0000#;
  sig16 <= 16#F.FF#E+2;
  sig17 <= 2#1.1111_1111_111#E11;

-- physical_literal
  sig21 <= 20 ns;

-- enumeration_literal = identifier or character_literal
-- identifier = basic_identifier / extended_identifier
-- basic_identifier
  sig31 <= COUNT;
  sig32 <= X;
  sig33 <= X1;
  sig34 <= c_out;
  sig35 <= STORE_NEXT_ITEM;

-- extended_identifier
  sig41 <= \BUS\;
  sig42 <= \bus\;
  sig43 <= \a\\b\;
  
-- character_literal
  sig51 <= 'A';
  sig52 <= '*';
  sig53 <= ''';
  sig54 <= ' ';
  
-- string_literal
  sig61 <= "Setup time is too short"; -- An error message.
  sig62 <= "";
  sig63 <= " ";
  sig64 <= "A";
  sig65 <= """";
  sig66 <= "Characters such as $, %, and } are allowed in string literals.";
  sig67 <= "FIRST PART OF A SEQUENCE OF CHARACTERS " &
           "THAT CONTINUES ON THE NEXT LINE";
    
  -- bit_string_literal
  sig71 <= B"1111_1111_1111"; -- Equivalent to the string literal "111111111111".
  sig72 <= X"FFF"; -- Equivalent to B"1111_1111_1111".
  sig73 <= O"777"; -- Equivalent to B"111_111_111".
  sig74 <= X"777"; -- Equivalent to B"0111_0111_0111".
  sig75 <= B"XXXX_01LH"; -- Equivalent to the string literal "XXXX01LH"
  sig76 <= UO"27"; -- Equivalent to B"010_111"
  sig77 <= UO"2C"; -- Equivalent to B"011_CCC"
  sig78 <= SX"3W"; -- Equivalent to B"0011_WWWW"
  sig79 <= D"35"; -- Equivalent to B"100011"
  sig7a <= 12UB"X1"; -- Equivalent to B"0000_0000_00X1"
  sig7b <= 12SB"X1"; -- Equivalent to B"XXXX_XXXX_XXX1"
  sig7c <= 12UX"F-"; -- Equivalent to B"0000_1111_----"
  sig7d <= 12SX"F-"; -- Equivalent to B"1111_1111_----"
  sig7e <= 12D"13"; -- Equivalent to B"0000_0000_1101"
  sig7f <= 12UX"000WWW"; -- Equivalent to B"WWWW_WWWW_WWWW"
  sig7g <= 12SX"FFFC00"; -- Equivalent to B"1100_0000_0000"
  sig7h <= 12SX"XXXX00"; -- Equivalent to B"XXXX_0000_0000"

-- _null
  sig81 <= null;

end test;
