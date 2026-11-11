CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2

.PHONY: all test clean
all: sparse_matrix

sparse_matrix: main.cpp sparse_matrix.h
	$(CXX) $(CXXFLAGS) main.cpp -o $@

tests: tests.cpp sparse_matrix.h
	$(CXX) $(CXXFLAGS) tests.cpp -o $@

test: tests
	./tests

clean:
	$(RM) sparse_matrix tests
