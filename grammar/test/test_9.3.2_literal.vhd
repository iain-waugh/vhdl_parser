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

-- enumeration_literal = identifier or character_literal
-- identifier = basic_identifier / extended_identifier
-- basic_identifier
  sig21 <= COUNT;
  sig22 <= X;
  sig23 <= X1;
  sig24 <= c_out;
  sig25 <= STORE_NEXT_ITEM;

-- extended_identifier
  sig31 <= \BUS\;
  sig32 <= \bus\;
  sig33 <= \a\\b\;
  
-- character_literal
  sig41 <= 'A';
  sig42 <= '*';
  sig43 <= ''';
  sig44 <= ' ';
  
-- string_literal
  sig51 <= "Setup time is too short"; -- An error message.
  sig52 <= "";
  sig53 <= " ";
  sig54 <= "A";
  sig55 <= """";
  sig56 <= "Characters such as $, %, and } are allowed in string literals.";
  sig57 <= "FIRST PART OF A SEQUENCE OF CHARACTERS " &
           "THAT CONTINUES ON THE NEXT LINE";
    
  -- bit_string_literal
  sig61 <= B"1111_1111_1111"; -- Equivalent to the string literal "111111111111".
  sig62 <= X"FFF"; -- Equivalent to B"1111_1111_1111".
  sig63 <= O"777"; -- Equivalent to B"111_111_111".
  sig64 <= X"777"; -- Equivalent to B"0111_0111_0111".
  sig65 <= B"XXXX_01LH"; -- Equivalent to the string literal "XXXX01LH"
  sig66 <= UO"27"; -- Equivalent to B"010_111"
  sig67 <= UO"2C"; -- Equivalent to B"011_CCC"
  sig68 <= SX"3W"; -- Equivalent to B"0011_WWWW"
  sig69 <= D"35"; -- Equivalent to B"100011"
  sig6a <= 12UB"X1"; -- Equivalent to B"0000_0000_00X1"
  sig6b <= 12SB"X1"; -- Equivalent to B"XXXX_XXXX_XXX1"
  sig6c <= 12UX"F-"; -- Equivalent to B"0000_1111_----"
  sig6d <= 12SX"F-"; -- Equivalent to B"1111_1111_----"
  sig6e <= 12D"13"; -- Equivalent to B"0000_0000_1101"
  sig6f <= 12UX"000WWW"; -- Equivalent to B"WWWW_WWWW_WWWW"
  sig6g <= 12SX"FFFC00"; -- Equivalent to B"1100_0000_0000"
  sig6h <= 12SX"XXXX00"; -- Equivalent to B"XXXX_0000_0000"

-- _null
  sig71 <= null;

end test;
