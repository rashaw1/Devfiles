//Test out ODE Solvers

#include "ForwardEulerSolver.hpp"
#include "RungeKuttaFour.hpp"
#include <cassert>

//Define function f(y, t) in the y' = f(y, t) problem to be solved
double myFunc(double y, double t)
{
  return (1.0 + t);
}

int main (int argc, char* argv[])
{
  //Do it by Forward Euler
  std::ofstream output("eulerSolution.dat");
  assert(output.is_open());
 
  ForwardEulerSolver solver(&myFunc, 0.05, 0.0, 1.0, 2.0);
  solver.SolveEquation(output);

  output.close();

  //Do it by R-K 4
  std::ofstream output2("rkSolution.dat");
  assert(output2.is_open());
  
  RungeKuttaFour solver2(&myFunc, 0.05, 0.0, 1.0, 2.0);
  solver2.SolveEquation(output2);
  
  output2.close();
}
  
