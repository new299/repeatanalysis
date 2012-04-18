CFILES = test_main.cpp  test_repeatscore.cpp

testall:
	echo $0
	g++ $(IFILES) -coverage -fprofile-arcs -ftest-coverage -fkeep-inline-functions -fno-default-inline -fkeep-inline-functions -O0 -lgcov $(CFILES)  -o test
#	lcov --directory . --zerocounters 1> lcov.output1
	./test
#	@echo
#	@echo
#	@echo "********* Generating coverage reports ./html/index.html"
#	gcov ./test_main.cpp --branch-counts 1> gcov.results
#	lcov -c --directory . --output-file test.info 1> lcov.output2
#	genhtml -o html test.info 1> genhtml.output
