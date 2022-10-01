#!/bin/bash
echo "Testing section 9.3.2 : literals"
../peglint.exe ../vhdl2008.peg --ast test_9.3.2_literal.vhd > result_9.3.2_literal.txt
grep - result_9.3.2_literal.txt > summary_9.3.2_literal.txt

echo "Testing section 10.5  : signal assignment"
../peglint.exe ../vhdl2008.peg --ast test_10.5_signal_assignment.vhd > result_10.5_signal_assignment.txt
grep - result_10.5_signal_assignment.txt > summary_10.5_signal_assignment.txt

echo "Testing section 11.3  : process"
../peglint.exe ../vhdl2008.peg --ast test_11.3_process.vhd > result_11.3_process.txt
grep - result_11.3_process.txt > summary_11.3_process.txt
