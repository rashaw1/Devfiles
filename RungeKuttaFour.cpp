//Implements RungeKuttaFour class

#include "RungeKuttaFour.hpp"
#include <cmath>
#include <iomanip>

//Constructor
RungeKuttaFour::RungeKuttaFour(double (*pFunction)(double, double),
				       double h, double t0, double t1, double y0)
{
  mpFunction = pFunction;
  setStepSize(h);
  setTimeInterval(t0, t1);
  setInitialValue(y0);
}

/*Function is a generic placeholder function for all children of AbstractODESolver
  It's implementation here is to just return the value given by 
  the user-specified function - held privately by the class */
double RungeKuttaFour::Function(double y, double t)
{
  return (*mpFunction)(y, t);
}

/*The following implements the fourth-order Runge-Kutta method
  and prints the (y, t) values to a specified file stream.
  See e.g. Introduction to Numerical Analysis by E. Suli and D. Mayers  */
void RungeKuttaFour::SolveEquation(std::ofstream& output)
{
  //Dynamically allocate memory for value arrays
  double* tVals;
  double* yVals;
  double finTime = getFinTime();
  double initTime = getInitTime();
  double stepSize = getStepSize();
  double initValue = getInitValue();
  int N = int(fabs((finTime - initTime)/stepSize)); //No. of steps
  tVals = new double[N+1];
  yVals = new double[N+1];
  
  //Calculate tVals
  for(int i = 0; i<N+1; i++){
    tVals[i] = i*stepSize;
  }
  double k1, k2, k3, k4; //Placeholder variables
  //Start alogrithm
  yVals[0] = initValue;
  for(int i = 1; i<N+1; i++){
    k1 = stepSize*Function(yVals[i-1], tVals[i-1]);
    k2 = stepSize*Function(yVals[i-1] + 0.5*k1, tVals[i-1]+0.5*stepSize);
    k3 = stepSize*Function(yVals[i-1] + 0.5*k2, tVals[i-1]+0.5*stepSize);
    k4 = stepSize*Function(yVals[i-1] + k3, tVals[i-1] + stepSize);
    yVals[i] = yVals[i-1] + (k1 + 2*k2 + 2*k3 + k4)/6.0;
  }
  //Print to file, in formatted table
  output << std::setw(18) << "T Values" << std::setw(18) << "Y Values\n";
  for (int i = 0; i<N+1; i++){
    output << std::setw(18) << std::scientific << tVals[i];
    output << std::setw(18) << std::scientific << yVals[i] << "\n";
  }

  //Deallocate memory (should use Vector STL, really, but this is an exercise)
  delete[] tVals;
  delete[] yVals;
}
  
