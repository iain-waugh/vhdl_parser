-------------------------------------------------------------------------------
--
-- Copyright (c) 2022 Iain Waugh
-- All rights reserved.
--
-- Non-functional VHDL code to test the PEG
--
-- Test VHDL-2008
--   Covers:
--     Section 10.5 - signal assignment
--     Section 9.1  - expression
--
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

architecture test of vhdl_signal_assignment is
begin

  sig11 <= led;

  sig12 <= transport led after 20 ns;

  sig13 <= (others => '0');
  sig14 <= my_array(7 downto 0);
  sig15 <= my_array(0 to 4);
  sig16 <= std_logic_vector(signed(a) + signed(b));

  sig17 <= guarded my_func(param);

  sig18(led'high -1 downto 6) <= (1 => '1', others => '0');
  sig19(led'low to led'high)  <= (1 => '1', 2 => 'X', others => '0');

end test;
