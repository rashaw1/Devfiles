matrix.o : matrix.cpp matrix.hpp
	g++ -c -O matrix.cpp

matTest.o : matTest.cpp matrix.hpp
	g++ -c -O matTest.cpp

matTest : matrix.o matTest.o
	g++ -O -o matTest matrix.o matTest.o