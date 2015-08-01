//Implementation of matrix.hpp, class of matrices

#include "matrix.hpp"
#include <iomanip>
#include <new>

//Initialise arrays (to zero)
void Matrix::init(){
  elements = new double* [height];
  for (int i = 0; i < height; i++){
    elements[i] = new double[width];
    for(int j = 0; j < width; j++){
      elements[i][j] = 0.0;
    }
  }
}
  
//Default (dimensional) constructor
Matrix::Matrix(int n, int m)
{
  height = n;
  width = m;
  init();
}

//Constructor where elements are specified
Matrix::Matrix(double** M, int n, int m)
{
  height = n;
  width = m;
  init();
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      //Catch out_of_bounds errors, without breaking
      try {
      elements[i][j] = M[i][j];
      }
      catch (std::bad_alloc& ba) {
	std::cout << "Initialising matrix the wrong size!";
      } 
    }
  }
}

//Copy constructor
Matrix::Matrix(const Matrix& M){
  height = M.getHeight();
  width = M.getWidth();
  init();
  for(int i = 0; i < height; i++){
    for(int j = 0; j < height; j++){
      elements[i][j] = M.getElement(i, j);
    }
  }
}

//Destructor
Matrix::~Matrix()
{
  for(int i = 0; i<width; i++){
    delete[] elements[i];
  }
  delete[] elements;
}

//Accessors
int Matrix::getWidth() const
{
  return width;
}

int Matrix::getHeight() const
{
  return height;
}

double Matrix::getElement(int n, int m) const
{
  double retValue = 0.0;
  if((n>=height) || (m>=width)){
    std::cout << "Out of bounds: element " << n << ", " << m;
    std::cout << " does not exist for this matrix.\n";
  } else {
    retValue = elements[n][m];
  }
  return retValue;
}

void Matrix::setElement(double value, int n, int m)
{
  if((n>=height) || (m>=width)){
    std::cout << "Out of bounds: element " << n<< ", "<< m;
    std::cout << " does not exist for this matrix.\n";
  } else {
    elements[n][m] = value;
  }
}

//Intrinsic functions
//Returns the determinant of the matrix
double Matrix::det() const
{
  double d = 0.0;
  if(!isSquare()){
    std::cout << "Matrix is rectangular!\n";
  } else {
    if(width==1){
      d=getElement(0, 0);
    } else if (width==2){
      d = getElement(0, 0)*getElement(1, 1) - getElement(0, 1)*getElement(1, 0);
    } else {
      for(int i =0; i < width; i++){
	double cVal = getElement(0, i);
	if(cVal > 1e-8){
	  Matrix cM = copy(*this, i, 0);
	  d += pow(-1.0, i)*cVal*cM.det();
	}
      }
    }
  }
  return d;
}

//Returns the inverse matrix if it exists
Matrix Matrix::inverse() const
{
  //Code goes here
  Matrix M;
  return M;
}

//Prints out the matrix
void Matrix::print() const
{
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      std::cout << std::setw(10) << getElement(i, j) << "   ";
    }
    std::cout << "\n";
  }
}

//The following determine whether the matrix is singular (to a given precision),
//triangular, square, or symmetric, respectively.

//Default precision is 1e-6
bool Matrix::isSingular(double precision) const
{
  return (fabs(det())<precision);
}

bool Matrix::isTriangular(bool upper) const
{
  if(upper){
    for(int i = 0; i<width; i++){
      for(int j = i+1; j < height; j++){
	if(getElement(j, i) > 1e-12){
	  return false;
	}
      }
    }
  } else {
    for(int i = 0; i < height; i++){
      for(int j = i+1; j < width; j++){
	if(fabs(getElement(i,j)) > 1e-12){
	  return false;
	}
      }
    }
  }
  return true;
}

bool Matrix::isSquare() const
{
  return (height == width);
}

bool Matrix::isSymmetric() const
{
  if(!isSquare()){
    return false;
  } else {
    for (int i = 0; i < width; i++){
      for (int j = i+1; j < width; j++){
        if(fabs(getElement(i, j) - getElement(j, i)) > 1e-10){
          return false;
        }
      }
    }
  }
  return true;
}

//Friend functions

//Multiply by a scalar
Matrix Multiply(const Matrix& M, double scalar)
{
  int h = M.getHeight();
  int w = M.getWidth();
  Matrix mM(h, w);
  for(int i = 0; i<h; i++){
    for(int j = 0; j<w; j++){
      mM.setElement(scalar*M.getElement(i, j), i, j);
    }
  }
  return mM;
}

//Multiply by a matrix
Matrix Multiply(const Matrix& A, const Matrix& B)
{
  //Retrieve heights and widths of matrices
  int h = A.getHeight();
  int w = B.getWidth();
  int kw = A.getWidth();
  int kh = B.getHeight();
  Matrix M(h, w);
  //Check for compatibility
  if(kw!=kh){
    std::cout << "Matrices are incompatible!\n";
  } else { 
    // (AB)_ij = A_ik * B_kj (in subscript notation; summation convention)
    for(int i = 0; i < h; i++){
      for(int j = 0; j<w; j++){
	for(int k = 0; k<kw; k++){
	  double elem = A.getElement(i, k) * B.getElement(k, j);
	  M.setElement(elem, i, j);
	}
      }
    }
  }
  return M;
}

//This creates a copy of a matrix with column mCol and row mRow removed
Matrix copy(const Matrix& M, int mCol, int mRow)
{
  int w = M.getWidth();
  int h = M.getHeight();
  Matrix cM(h-1, w-1);
  //Copy in ignoring the missing column and row
  int row = 0;
  for(int i = 0; i < h; i++){
    if(i!=mRow){
      int col = 0;
      for(int j = 0; j < w; j++){
	if(j!=mCol){
	  cM.setElement(M.getElement(i, j), row, col);
	  col++;
	}
      }
      row++;
    }
  }
  return cM;
}

//Overloaded operators
Matrix& Matrix::operator=(const Matrix& M)
{
  height = M.getHeight();
  width = M.getWidth();
  init();
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      setElement(M.getElement(i, j), i, j);
    }
  }
  return *this;
}

Matrix Matrix::operator-() const
{
  Matrix M(height, width);
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      M.setElement(-1.0*getElement(i, j), i, j);
    }
  }
  return M;
}

Matrix Matrix::operator+(const Matrix& A) const 
{
  Matrix M(height, width);
  if((height != A.getHeight()) || (width!=A.getWidth())){
      std::cout << "Incompatible for addition!";
  } else {
    for(int i = 0; i < height; i++){
      for(int j = 0; j < width; j++){
	double sum = getElement(i, j) + A.getElement(i, j);
	M.setElement(sum, i, j);
      }
    }
  }
  return M;
}

Matrix Matrix::operator-(const Matrix& A) const
{
  Matrix M(height, width);
  if((height != A.getHeight()) || (width!=A.getWidth())){
    std::cout<< "Incompatible for subtraction!";
  } else {
    for(int i =0; i < height; i++){
      for(int j= 0; j < width;j++){
	double diff = getElement(i, j) - A.getElement(i,j);
	M.setElement(diff, i, j);
      } 
    }
  }
  return M;
}

//Overloading the insertion operator << for output
std::ostream& operator<<(std::ostream& output, const Matrix& M)
{
  int height = M.getHeight();
  int width = M.getWidth();
  output << "\n";
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      output << std::setw(10) << M.getElement(i, j) << "   ";
    }
    output << "\n";
  }
  return output;
}

	       

