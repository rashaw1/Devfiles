// Defines a class of matrices, with basic matrix operations 

#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF

#include <iostream>
#include <cmath>

class Matrix
{
private:
  int width, height;
  double** elements;
  void init(); //Initialises arrays; must be called after height and width set 
public:
  Matrix(int n = 2, int m = 2); //Specify dimensions
  Matrix(double** M, int n = 2, int m = 2); //Specify elements
  Matrix(const Matrix& M); //Copy constructor
  ~Matrix(); //Destructor
  //Accessors
  int getWidth() const;
  int getHeight() const;
  double getElement(int n, int m) const;
  void setElement(double value, int n, int m);
  //Intrinsic Functions
  double det() const;
  Matrix inverse() const;
  void print() const;
  bool isSingular(double precision = 1e-6) const;
  bool isTriangular(bool upper = true) const;
  bool isSquare() const;
  bool isSymmetric() const;
  //Friend functions
  friend Matrix Multiply(const Matrix& M, double scalar);
  friend Matrix Multiply(const Matrix& A, const Matrix& B);
  friend Matrix copy(const Matrix& M, int mCol, int mRow);
  //Overloaded operators
  Matrix& operator=(const Matrix& M);
  Matrix operator-() const;
  Matrix operator+(const Matrix& M) const;
  Matrix operator-(const Matrix& M) const;
  friend std::ostream& operator<<(std::ostream& output, const Matrix& M);  
};

#endif
