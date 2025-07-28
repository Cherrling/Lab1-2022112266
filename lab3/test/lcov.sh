lcov --directory . --capture -o coverage.info --ignore-errors inconsistent,unsupported
genhtml coverage.info -o coverage
