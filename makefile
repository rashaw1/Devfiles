matrix.o : matrix.cpp matrix.hpp
	g++ -c -O matrix.cpp

matTest.o : matTest.cpp matrix.hpp
	g++ -c -O matTest.cpp

matTest : matrix.o matTest.o
	g++ -O -o matTest matrix.o matTest.o

AbstractODESolver.o : AbstractODESolver.cpp AbstractODESolver.hpp
	g++ -c -O AbstractODESolver.cpp

ForwardEulerSolver.o : ForwardEulerSolver.cpp ForwardEulerSolver.hpp AbstractODESolver.hpp
	g++ -c -O ForwardEulerSolver.cpp

RungeKuttaFour.o : RungeKuttaFour.cpp RungeKuttaFour.hpp AbstractODESolver.hpp
	g++ -c -O RungeKuttaFour.cpp

odeTest.o : odeTest.cpp ForwardEulerSolver.hpp RungeKuttaFour.hpp
	g++ -c -O odeTest.cpp

odeTest : odeTest.o RungeKuttaFour.o ForwardEulerSolver.o AbstractODESolver.o 
	g++ -O -o odeTest AbstractODESolver.o ForwardEulerSolver.o RungeKuttaFour.o odeTest.o