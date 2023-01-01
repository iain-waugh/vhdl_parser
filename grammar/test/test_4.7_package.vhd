-------------------------------------------------------------------------------
--
-- Copyright (c) 2022 Iain Waugh
-- All rights reserved.
--
-- Non-functional VHDL code to test the PEG
--
-- Test VHDL-2008
--   Covers:
--     Section 4.3 - package
--
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.to_integer;

package test_package is

  type unsigned is array (natural range <>) of std_logic;
  type signed is array (natural range <>) of std_logic;
  subtype SMALL_INT is integer range 0 to 1;
  function ADD_UNSIGNED (L, R: UNSIGNED; C: STD_LOGIC) return UNSIGNED;
  SUBTYPE my_std_logic IS resolved std_ulogic;

  ----------------
  -- add operators
  ----------------
  function "+"(L : unsigned; R : unsigned) return unsigned;


end test_package;

package body test_package is
  function ADD_UNSIGNED (L, R: UNSIGNED; C: STD_LOGIC) return UNSIGNED is
    constant L_LEFT: INTEGER := L'LENGTH-1;
    variable RESULT : UNSIGNED(L'range);
    alias XL: UNSIGNED(L_LEFT downto 0) is L;
    alias XR: UNSIGNED(L_LEFT downto 0) is R;
    variable CBIT: STD_LOGIC := C;
  begin
    RESULT := UNSIGNED(STD_LOGIC_VECTOR(L) nand STD_LOGIC_VECTOR(R));
    RESULT(I) := CBIT xor XL(I) xor XR(I);    
    for I in 0 to RESULT'LEFT loop
      if (L_LEFT mod 2) = 0 then
        RESULT(I) := '0';
      else
        RESULT(I) := not '1';
      end if;
    end loop;
  end ADD_UNSIGNED;

  function "+"(L : unsigned; R : unsigned) return unsigned is
  begin
  end "+";

end package body test_package;
