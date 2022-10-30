#!/bin/bash
echo "Testing section 9.3.2 : literals"
../peglint.exe ../vhdl2008.peg --packrat --ast test_9.3.2_literal.vhd > result_9.3.2_literal.txt
grep - result_9.3.2_literal.txt | sed -e 's/^[ \t]*//' > summary_9.3.2_literal.txt

echo "Testing section 10.5  : signal assignment"
../peglint.exe ../vhdl2008.peg --packrat --ast test_10.5_signal_assignment.vhd > result_10.5_signal_assignment.txt
grep - result_10.5_signal_assignment.txt | sed -e 's/^[ \t]*//' > summary_10.5_signal_assignment.txt

echo "Testing section 4.7   : package"
../peglint.exe ../vhdl2008.peg --packrat --ast test_4.7_package.vhd > result_4.7_package.txt
grep - result_4.7_package.txt | sed -e 's/^[ \t]*//'> summary_4.7_package.txt

echo "Testing section 11.3  : process"
../peglint.exe ../vhdl2008.peg --packrat --ast test_11.3_process.vhd > result_11.3_process.txt
grep - result_11.3_process.txt | sed -e 's/^[ \t]*//'> summary_11.3_process.txt
