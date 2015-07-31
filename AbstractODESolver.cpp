//Defines methods for AbstractOdeSolver class

#include "AbstractODESolver.hpp"
#include <cassert>

//Accessors
void AbstractOdeSolver::setStepSize(double h)
{
  assert(h > 0.0); //Only positive step sizes make sense
  stepSize = h;
}

void AbstractOdeSolver::setTimeInterval(double t0, double t1)
{
  assert(t1-t0 > 1e-10); 
  //t1 < t0 would seem silly physically, but would not break the solver
  //t1 = t0 might cause problems
  initTime = t0;
  finTime = t1;
}

void AbstractOdeSolver::setInitialValue(double y0)
{
  initValue = y0; //No restrictions
}
