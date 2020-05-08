cd build
cmake ..
make
./Google_tests/Google_Tests_run
cd Google_tests/CMakeFiles/Google_Tests_run.dir/
gcov ConverterTests.cpp.gcno
cd ../../../..
gcovr -r . --branches --html --html-details -o coverage.html build --filter Cjson_lib/

