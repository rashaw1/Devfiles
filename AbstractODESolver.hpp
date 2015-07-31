#ifndef ABSTRACTODESOLVERDEF
#define ABSTRACTODESOLVERDEF

/* Defines a class AbstractOdeSolver 
   that is parent to various types of solver for
   initial value problems of first-order
   ordinary differential equations. */

#include <fstream>

class AbstractOdeSolver
{
private:
  double stepSize;
  double initTime;
  double finTime;
  double initValue;
public:
  //Accessor Methods
  void setStepSize(double h);
  void setTimeInterval(double t0, double t1);
  void setInitialValue(double y0);
  double getStepSize() const { return stepSize;}
  double getInitTime() const { return initTime;}
  double getFinTime() const { return finTime;}
  double getInitValue() const { return initValue;}

  //Intrinsic functions to be inherited
  virtual double Function(double y, double t) = 0;
  virtual void SolveEquation(std::ofstream& output) = 0;
};

#endif
