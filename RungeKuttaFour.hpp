#ifndef RUNGEKUTTADEF
#define RUNGEKUTTADEF

/* Defines child of AbstractOdeSolver : RungeKuttaFour
   which uses the fourth-order Runge-Kutta method for solving
   first-order ODE IVPs: 
   y' = F(t, y)
   The user can specify F(t, y) as Function.
*/

#include "AbstractODESolver.hpp"

class RungeKuttaFour : public AbstractOdeSolver
{
private:
  double (*mpFunction)(double y, double t);
public:
  //Constructor, specify Function, step, time, and IV
  RungeKuttaFour(double (*pFunction)(double, double), double h, double t0, 
		     double t1, double y0);
  double Function(double y, double t); 
  void SolveEquation(std::ofstream& output); //Prints output to specified file stream
};

#endif
