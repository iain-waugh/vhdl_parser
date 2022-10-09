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

package test_package is

  type unsigned is array (natural range <>) of std_logic;
  type signed is array (natural range <>) of std_logic;
  subtype SMALL_INT is integer range 0 to 1;

  ----------------
  -- add operators
  ----------------
  function "+"(L : unsigned; R : unsigned) return unsigned;


end test_package;

package body test_package is
  function ADD_UNSIGNED (L, R: UNSIGNED; C: STD_LOGIC) return UNSIGNED is
    constant L_LEFT: INTEGER := L'LENGTH-1;
    alias XL: UNSIGNED(L_LEFT downto 0) is L;
  begin
  end ADD_UNSIGNED;


end package body test_package;
