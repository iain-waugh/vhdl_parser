#!/bin/bash
mkdir -p results

echo "Testing section 9.3.2 : literals"
../peglint ../vhdl2008.peg --packrat --ast test_9.3.2_literal.vhd > results/result_9.3.2_literal.txt
grep - results/result_9.3.2_literal.txt | sed -e 's/^[ \t]*//' > results/summary_9.3.2_literal.txt

echo "Testing section 10.5  : signal assignment"
../peglint ../vhdl2008.peg --packrat --ast test_10.5_signal_assignment.vhd > results/result_10.5_signal_assignment.txt
grep - results/result_10.5_signal_assignment.txt | sed -e 's/^[ \t]*//' > results/summary_10.5_signal_assignment.txt

echo "Testing section 4.7   : package"
../peglint ../vhdl2008.peg --packrat --ast test_4.7_package.vhd > results/result_4.7_package.txt
grep - results/result_4.7_package.txt | sed -e 's/^[ \t]*//'> results/summary_4.7_package.txt

echo "Testing section 11.3  : process"
../peglint ../vhdl2008.peg --packrat --ast test_11.3_process.vhd > results/result_11.3_process.txt
grep - results/result_11.3_process.txt | sed -e 's/^[ \t]*//'> results/summary_11.3_process.txt

echo "Testing section 16.3  : standard library"
../peglint ../vhdl2008.peg --packrat --ast test_16.3_package_standard_utf8.vhd > results/result_16.3_package_standard_utf8.txt
grep - results/result_16.3_package_standard_utf8.txt | sed -e 's/^[ \t]*//'> results/summary_16.3_package_standard_utf8.txt
