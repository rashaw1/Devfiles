//Tests the matrix class
#include "matrix.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
  Matrix M(3, 3);
  M.setElement(1.0, 0, 0); M.setElement(0.0, 0, 1); M.setElement(0.0, 0, 2);
  M.setElement(4.0, 1, 0); M.setElement(2.0, 1, 1); M.setElement(0.0, 1, 2);
  M.setElement(5.0, 2, 0); M.setElement(3.0, 2, 1); M.setElement(1.0, 2, 2);
  //M.setElement(4.0, 3, 0); M.setElement(2.0, 3, 1); M.setElement(4.0, 3, 2);
  std::cout << "Width: " << M.getWidth() << "\nHeight: " << M.getHeight() << "\n";
  std::cout << "Determinant: " << M.det() << "\n";
  if(M.isSingular()){
    std::cout << "M is singular.\n";
  }
  if(M.isTriangular()){
    std::cout << "M is upper triangular.\n";
  }
  if(M.isTriangular(false)){
    std::cout << "M is lower triangular.\n";
  }
  if(M.isSquare()){
    std::cout << "M is square.\n";
  }
  if(M.isSymmetric()){
    std::cout << "M is symmetric.\n";
  }
  M.print();
  Matrix sM = Multiply(M, 3.5);
  std::cout << "3.5M is" << sM;
  Matrix M2 = Multiply(M, M);
  std::cout << "M squared is" << M2;
  M = sM;
  std::cout << "M is now \n";
  M.print();
  Matrix sum = M+M2;
  std::cout << "sM + M squared is:" << sum;
  std::cout << "Element 1,1 of sum is: " << sum.getElement(1, 1) << "\n";
  Matrix N(2, 2);
  std::cout << N;
  N = M2;
  std::cout << N;
  return 0;
}
