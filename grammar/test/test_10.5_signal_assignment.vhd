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
--
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

architecture test of vhdl_signal_assignment is
begin

  o_led <= led;

  d_led <= transport led after 20 ns;

  zero <= (others => '0');

  func_result <= guarded my_func(param);

  led(led'high downto 6)   <= (1 => '1', others => '0');
  led(led'low to led'high) <= (1 => '1', others => '0');

end test;
