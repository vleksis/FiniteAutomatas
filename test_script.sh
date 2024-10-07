cd build || exit
ctest || exit

lcov --directory . --capture --output-file coverage.info --ignore-errors mismatch,gcov,gcov || exit
lcov --remove coverage.info --ignore-errors unused '/usr/*' '*/tests/*' '*gtest*' '*gmock*' --output-file coverage_filtered.info || exit
genhtml coverage_filtered.info --output-directory coverage
echo "coverage in build/coverage"