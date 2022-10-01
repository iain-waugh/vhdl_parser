#!/bin/bash
echo "Testing section 9.3.2 : literals"
../peglint.exe ../vhdl2008.peg --ast test_9.3.2_literal.vhd > result_9.3.2_literal.txt

echo "Testing section 11.3  : process"
../peglint.exe ../vhdl2008.peg --ast test_11.3_process.vhd > result_11.3_process.txt
