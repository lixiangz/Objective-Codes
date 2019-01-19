#include <iostream>
#include "SafeMatrix.h"
#include <new>
using namespace std;

// Methods
void SafeMatrix::transpose() {
  INVARIANT_TEST(_numCols < 0, "deleteColumn");
  float* tran = new (nothrow) float[(_numCols + 1)*(_numRows)];

  int swap = _numRows;
  _numRows = _numCols;
  _numCols = swap;

  int x = 0;
  int y = 0;

  for (int i = 0; i < _numCols; i++){
    for (int j = 0; j <= _numRows; j++){
      x = j*_numCols + i;
      y = i*_numRows + j;
      tran[y] = _data[x];
    }
  }

  for (int i =0; i < _dataSpaceAllocated; i++){
    _data[i] = tran[i];

  }

  delete[] tran;
}

bool SafeMatrix::invert(){
  INVARIANT_TEST(_numRows<NOT_A_MATRIX, "invert");
  return true;
}

SafeMatrix SafeMatrix::solve(const SafeMatrix& A){
  INVARIANT_TEST(_numCols < NOT_A_MATRIX, "solve");
  INVARIANT_TEST(A._numCols < NOT_A_MATRIX, "solve");
  return A;
}

bool SafeMatrix::deleteRow(const int rowNumber){
  INVARIANT_TEST(_numCols < NOT_A_MATRIX, "deleteRow");
  if (rowNumber >= _numRows || rowNumber < 0){
    return false;
  }
  float* deleteRow = new (nothrow) float[_dataSpaceAllocated];
  if (!deleteRow){
    return false;
  }
  int x = 0;
  int i = 0;
  while(i < _dataSpaceAllocated){
    if (i/_numCols != rowNumber){
      deleteRow[x] = _data[i];
      x++;
    }
    i++;
  }
  _numRows -= 1;
  _dataSpaceAllocated -= _numCols;
  delete[] _data;
  _data = deleteRow;
  return true;
}

bool SafeMatrix::deleteColumn(const int colNumber){
  INVARIANT_TEST(_numCols < 0, "deleteColumn");
  if (colNumber >= _numCols || colNumber < 0){
    return false;
  }
  float* deleteColumn = new (nothrow) float[_dataSpaceAllocated];
  int x = 0;
  int i = 0;
  while(i < _dataSpaceAllocated){
    if (i%_numCols != colNumber){
      deleteColumn[x] = _data[i];
      x++;
    }
    i++;
  }
  _numCols -= 1;
  _dataSpaceAllocated -= _numRows;
  delete[] _data;
  _data = deleteColumn;
  return true;
}

bool SafeMatrix::appendRow(const int cols, const float data[]) {
  INVARIANT_TEST(_numCols < 0, "deleteColumn");
  if (cols == _numCols){
    _dataSpaceAllocated = _numCols*(_numRows+1);
    float* AppendRow = new (nothrow) float[(_numCols)*(_numRows+1)];

    for (int i = 0; i < _numRows*_numCols; i++){
      AppendRow[i] = _data[i];
    }

    for (int i = _numCols*_numRows; i < ((_numRows+1)*_numCols); i++){
      AppendRow[i] = data[i%_numCols];
    }

    _numRows++;

    delete[] _data;

    _data = new (nothrow) float[_dataSpaceAllocated];

    for (int i = 0; i < _dataSpaceAllocated; i++){
      _data[i] = AppendRow[i];
    }

    delete[] AppendRow;

    return true;
  }

  return false;
}

bool SafeMatrix::appendColumn(const int rows, const float data[]) {
  INVARIANT_TEST(_numCols < 0, "deleteColumn");
  float* AppendCol = new (nothrow) float[(_numCols + 1)*(_numRows)];

  if (rows != _numRows){
    return false;
  }

  for (int i = 0; i <_numRows; i++){
    for (int j = 0; j < (_numCols+1); j++){
      if (j < _numCols){
        AppendCol[i+j] = _data[i];
      }

      else if (j == _numCols){
        AppendCol[i+j] = data[i];
      }
    }
  }

  return true;
}

bool SafeMatrix::swapRow(const int row1, const int row2){
  INVARIANT_TEST(_numRows < 0, "swapRow");
  if (row1 >= _numRows || row2 >= _numRows || row2 < 0 || row1 < 0){
    return false;
  }
  float row1array[_numCols];
  float row2array[_numCols];
  int i = 0;
  while (i < _numCols){
    row1array[i] = _data[row1*_numCols+i];
    row2array[i] = _data[row2*_numCols+i];
    i++;
  }

  int j = 0;
  while (j < _numCols){
    MATRIX(*this, row1, j) = row2array[j];
    MATRIX(*this, row2, j) = row1array[j];
    j++;
  }
  return true;
}
bool SafeMatrix::swapColumn(const int column1, const int column2){
  INVARIANT_TEST(_numCols < 0, "swapColumn");
  if (column1 >= _numCols || column2 >= _numCols || column1 < 0 || column2 < 0){
    return false;
  }
  float col1[_numRows];
  float col2[_numRows];
  int i = 0;
  while (i < _numRows){
    col1[i] = _data[i*_numCols+column1];
    col2[i] = _data[i*_numCols+column2];
    i++;
  }

  int j = 0;
  while (j < _numRows){
    MATRIX(*this, j, column1) = col2[j];
    MATRIX(*this, j, column2) = col1[j];
    j++;
  }
  return true;
}
bool SafeMatrix::append(const SafeMatrix& m){
  INVARIANT_TEST(_numCols < 0, "deleteColumn");
  INVARIANT_TEST(m._numCols < 0, "append");
  return false;
}

bool SafeMatrix::isNaM() const{
  INVARIANT_TEST(_numCols < 0, "isNaM");
  if (_numCols == NOT_A_MATRIX){
    return true;
  }
  return false;
}                 

SafeMatrix SafeMatrix::row(const int rowNumber) const{
  INVARIANT_TEST(_numRows < 0, "row");
  float row[_numCols];
  int i = 0;
  while (i < _numCols){
    row[i] = _data[rowNumber*_numCols + i];
    i++;
  }
  SafeMatrix rowmatrix(1, _numCols);
  int j = 0;
  while (j < _numCols){
    MATRIX(rowmatrix, 0, j) = row[j];
    j++;
  }
  return rowmatrix;
}

SafeMatrix SafeMatrix::column(const int columnNumber) const{
  INVARIANT_TEST(_numCols < 0, "column");
  float column[_numRows];
  int i = 0;
  while (i < _numRows){
    column[i] = _data[i*_numCols + columnNumber];
    i++;
  }
  SafeMatrix columnmatix(_numRows,1);
  int j = 0;
  while (j < _numRows){
    MATRIX(columnmatix, j, 0) = column[j];
    j++;
  }
  return columnmatix;
}

Dimensions SafeMatrix::dimensions() const {
  INVARIANT_TEST(_numCols < 0, "deleteColumn");
  Dimensions newDimension;
  newDimension.rows = _numRows;
  newDimension.cols = _numCols;
  return newDimension;
}

SafeMatrix SafeMatrix::identity(const int n){
  if (n < 0){
    return SafeMatrix(-1, -1);
  }
}

// Operators
float& SafeMatrix::operator()(int i, int j) {
  INVARIANT_TEST(_numCols < 0, "deleteColumn");
  if (i >= _numRows || j >= _numCols){
    return _nan;
  }

  return MATRIX(*this,i,j);

  int m;

  for (int x = 0; x<i; x++){
    for (int y = 0; y < _numRows; y++){
      if (i == x && j == y){
        return _data[m];
      }
      m++;
    }
  }
}  

SafeMatrix SafeMatrix::operator+(const SafeMatrix& m) const {
  INVARIANT_TEST(_numCols < 0, "deleteColumn");
  INVARIANT_TEST(m._numCols < 0, "append");
  if (_numRows != m._numRows || _numCols != m._numCols){
    SafeMatrix Add(NOT_A_MATRIX, -1);
    return Add;
  }

  SafeMatrix Add(_numRows, _numCols);

  Add._data = new (nothrow) float[(_numCols+1)*(_numRows)];

  for (int i = 0; i < _numCols*_numRows; i++){
    Add._data[i] = _data[i] + m._data[i];
  }

  return Add;

}

SafeMatrix SafeMatrix::operator-(const SafeMatrix& m) const{
  INVARIANT_TEST(_numCols < 0, "deleteColumn");
  INVARIANT_TEST(m._numCols < 0, "append");

}

SafeMatrix SafeMatrix::operator*(const SafeMatrix& m) const {
  INVARIANT_TEST(_numCols < 0, "deleteColumn");
  INVARIANT_TEST(m._numCols < 0, "append");
  if (_numCols != m._numRows || _numCols != m._numRows){
    SafeMatrix Mult(-1,0);
    return Mult;
  }

  SafeMatrix Mult(_numRows, _numCols);
  Mult._data = new (nothrow) float[_numRows*m._numCols];

  for (int i = 0; i < _numRows; i++){
    for (int j = 0; j < m._numCols; j++){
      Mult._data[i*Mult._numCols+j] = 0;
      for (int k = 0; k < m._numRows; k++){
        Mult._data[i*Mult._numCols+j] += _data[i*_numCols+k] * m._data[k*m._numCols+j];
      }
    }
  }

  return Mult;
}

void SafeMatrix::operator=(const SafeMatrix& m) {
  INVARIANT_TEST(_numCols < 0, "deleteColumn");
  INVARIANT_TEST(m._numCols < 0, "append");
  _numCols = m._numCols;
  _numRows = m._numRows;
  _dataSpaceAllocated = m._dataSpaceAllocated;
  
  for (int i = 0; i < _dataSpaceAllocated; i++){
    _data[i] = m._data[i];
  }
}

bool SafeMatrix::operator==(const SafeMatrix& m) const{
  INVARIANT_TEST(_numRows < NOT_A_MATRIX, "operator ==");
  INVARIANT_TEST(m._numRows < NOT_A_MATRIX, "operator ==");
  if (_numRows != m._numRows || _numCols != m._numCols){
    return false;
  }
  if (_numRows < 0){
    return false;
  }
  int i = 0;
  while (i < _dataSpaceAllocated){
    if(labs(_data[i] - m._data[i]) > 0.0001){
      return false;
    }
    i++;
  }
}

bool SafeMatrix::operator!=(const SafeMatrix& m) const{
  INVARIANT_TEST(_numRows < NOT_A_MATRIX, "operator !=");
  INVARIANT_TEST(m._numRows < NOT_A_MATRIX, "operator !=");
  return !(*this == m);
}

  // Constructors/Destructor
SafeMatrix::SafeMatrix() {
  _numRows = 0;
  _numCols = 0;
  _dataSpaceAllocated = 0;
  _data = NULL;
}

SafeMatrix::SafeMatrix(const SafeMatrix& m) {
  if (m._numRows < 0 || m._numCols < 0){
    _numCols = -1;
    _numRows = -1;
    _data = NULL;
  }

  else {
    _numRows = m._numRows;
    _numCols = m._numCols;
    _dataSpaceAllocated = m._numRows*_numCols;
    _data = new (nothrow) float[_dataSpaceAllocated];

    for(int i = 0; i < _numCols*_numRows; i++){
      _data[i] = m._data[i];
    }   
    
  }
}

SafeMatrix::SafeMatrix(const Dimensions& d){
  _numCols = d.cols;
  _numRows = d.rows;
  if (_numRows >= 0 && _numCols >= 0){
    _dataSpaceAllocated = _numCols*_numRows;
  }
  else{
    _dataSpaceAllocated = 0;
    _numRows = -1;
    _numCols = -1;
  }

  float* dimension = new (nothrow) float[_dataSpaceAllocated];
  if (!dimension){
    _data = NULL;
    _numCols = -1;
    _numRows = -1;

  }
  else{
    int i = 0;
    while(i < _dataSpaceAllocated){
      dimension[i] = 0;
      i++;
    }
    _data = dimension;
  }
}

SafeMatrix::SafeMatrix(const int rows, const int cols) {
  if (rows < 0 || cols < 0){
    _numCols = -1;
    _numRows = -1;
    _data = NULL;
  }
  else {
    _numCols = cols;
    _numRows = rows;
    _dataSpaceAllocated = rows * cols;
    _data = new (nothrow) float[_dataSpaceAllocated];

    if (_data != 0){
      for (int i = 0; i < _dataSpaceAllocated; i++){
        _data[i] = 0;
      }
    }
  }
}

SafeMatrix::SafeMatrix(const Dimensions& d, const float initVal){
  _numRows = d.rows;
  _numCols = d.cols;
  if (_numCols < 0 || _numRows < 0){
    _dataSpaceAllocated = 0;
    _numRows = NOT_A_MATRIX;
    _numCols = NOT_A_MATRIX;
  }
  else{
    _dataSpaceAllocated = _numCols*_numRows;
  }
  float* dimension = new (nothrow) float[_dataSpaceAllocated];
  if (!dimension){
    _data = NULL;
    _numRows = -1;
    _numCols = -1;
  }
  else{
    int i = 0;
    while(i < _dataSpaceAllocated){
      dimension[i] = initVal;
      i++;
    }
    _data = dimension;
  }
}

SafeMatrix::SafeMatrix(const int rows, const int cols, const float initVal) {
  if (rows < 0 || cols < 0){
    _numCols = -1;
    _numRows = -1;
    _data = NULL;
  }

  else{
    _numRows = rows;
    _numCols = cols;
    _dataSpaceAllocated = rows * cols;
    _data = new (nothrow) float[_dataSpaceAllocated];
    
    if (_data != 0){
      for (int i = 0; i < _numRows*_numCols; i++){
        _data[i] = initVal;
      }
    }
  }
}
SafeMatrix::SafeMatrix(const int rows, const float data[]){
  _numRows = rows;
  _numCols = 1;
  if (_numRows < 0){
    _dataSpaceAllocated = 0;
    _numCols = -1;
    _numRows = -1;
  }
  else{
    _dataSpaceAllocated = _numRows;
  }
  float* dimension = new (nothrow) float[_dataSpaceAllocated];
  if (!dimension){
    _data = NULL;
    _numCols = -1;
    _numRows = -1;
  }
  else {
    int i = 0;
    while (i < _dataSpaceAllocated){
      dimension[i] = data[i];
      i++;
    }
    _data = dimension;
  }
}

SafeMatrix::~SafeMatrix() {
  if(_data != 0){
    delete[]_data;
    _numRows = 0;
    _numCols = 0;
    _dataSpaceAllocated = 0;
  }
}

std::ostream& operator<<(std::ostream& os, const SafeMatrix& m) {
  INVARIANT_TEST(m._numRows < NOT_A_MATRIX, "ostream::operator<<()");
  if (m._numRows < NOT_A_MATRIX) {
    m.errorMsg("Method ostream::operator<<: attempting to output deleted SafeMatrix");
    abort();
  }
  if (m._numRows == NOT_A_MATRIX) {
    os << "Not-a-Matrix";
    return os;
  }
  if (m._numRows == 0)
    os << "[]";
  for (int i = 0; i < m._numRows; ++i) {
    os << "[";
    for (int j = 0; j < m._numCols; ++j) {
      os << MATRIX(m,i,j);
      if (j < (m._numCols - 1))
        os << ", ";
    }
    os << "]";
    if (i < (m._numRows - 1))
      os << std::endl;
  }
  return os;
}

void SafeMatrix::errorMsg(const char msg[]) const {
  std::cerr << msg << std::endl;
}
