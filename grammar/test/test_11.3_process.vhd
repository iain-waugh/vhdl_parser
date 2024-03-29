-------------------------------------------------------------------------------
--
-- Copyright (c) 2022 Iain Waugh
-- All rights reserved.
--
-- Non-functional VHDL code to test the PEG
--
-- Test VHDL-2008
--   Covers:
--     Section 11.3 - process
--     Section 10.3 - if
--
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

architecture test of vhdl_process is
begin

  process (pixel_clk)
    variable result : unsigned (A'range);
    variable L01    : UNSIGNED(SIZE-1 downto 0);
  begin
    if (rising_edge(pixel_clk)) then
      result := (others     => 'X');
      result := L01'(others => 'X');

      if (A_MSB < B_LSB or B_MSB < A_LSB) then
        pixel_red <= (others => '0');
      end if;

      if(frame_sync_local >= 1) then
        pixel_red <= pixel_red + 1;
      elsif (pixel_in_ready = 'Z') then
        null;
      else

        my_if : if (pixel_red = unsigned(all_ones(C_BITS_RED))) then
          pixel_green <= pixel_green + 1;

          if (pixel_green = unsigned(all_ones(C_BITS_GREEN))) then
            pixel_blue <= pixel_blue + 1;
          end if;
        end if my_if;
      end if;

    end if;
  end process;

  tiny : process
  begin
  end process tiny;

end test;
