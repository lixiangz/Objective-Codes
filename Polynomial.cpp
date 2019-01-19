#include <iostream>
#include <math.h>

using namespace std;

// The polynomial struct keeps the most significant coeff
// in the first coeff[] element, the second in the second
// and so on.

struct Polynomial {
  int    degree;
  float* coeff;
};

float evaluate(const Polynomial p, const float x) {
  int i = 0;
  float total = 0;
  int Current_degree = p.degree;
  while (i < p.degree){
    float Current_Value = pow(x,Current_degree) * p.coeff[i];
    total = total + Current_Value;
    Current_degree = Current_degree - 1;
    i++;
  }
  total = total + p.coeff[p.degree];
  return total;
}

Polynomial add(const Polynomial p1, const Polynomial p2) {
  Polynomial Add;

  if ((p1.degree < 0) || (p2.degree < 0)){
    Add.degree = -1;
    return Add;
  }
  
  if (p1.degree >= p2.degree){
    Add.degree = p1.degree;
  }
  else{
    Add.degree = p2.degree;
  }

  Add.coeff = new float[Add.degree+1];
  
  if (p1.degree > p2.degree ){

    for(int count = 0; count < (p1.degree - p2.degree ); count++){
      Add.coeff[count] = p1.coeff[count];
    }
    
    for (int i = p1.degree - p2.degree; i < p1.degree + 1; i++){
      Add.coeff[i] = p1.coeff[i] + p2.coeff [i - (p1.degree - p2.degree)];
    }
   }

  else{

    for(int count = 0; count < (p2.degree - p1.degree ); count++){
      Add.coeff[count] = p2.coeff[count];
    }

    for (int i = p2.degree - p1.degree; i < p2.degree + 1; i++){
      Add.coeff[i] = p2.coeff[i] + p1.coeff [i - (p2.degree - p1.degree)];
    }
  }

  return Add;
}

Polynomial derivative(const Polynomial pIn) {
  Polynomial Der;
  if (pIn.degree < 0){
    Der.degree = -1;
    return Der;
  }

  else if (pIn.degree == 0){
    Der.degree = 0;
  }

  else if (pIn.degree > 0){
    Der.degree = pIn.degree - 1;
  }

  int i = 0;
  Der.coeff = new float[Der.degree];

  while (i <= pIn.degree){
    Der.coeff[i] = pIn.coeff[i]*(pIn.degree-i);
    i++;
  }

  return Der;
}

int displayPolynomial(const Polynomial p) {
  if (p.degree < 0) {
    cerr << "Parameter p is not a polynomial; p.degree = " << p.degree << endl;
    return -1;
  }
  cout << "\"";
  for (int i = 0; i < p.degree; ++i) {
    if (p.coeff[i] == 1) 
      cout << "x";
    else
      cout << p.coeff[i] << "x";
    if ((p.degree - i) > 1) 
      cout <<  "^" <<  (p.degree - i);
    cout << " + ";
  }
  cout << p.coeff[p.degree] << "\"";
  return 0;
}

#ifndef MARMOSET_TESTING

int main() {
  float coeff[] = {1, 2, 3};   // x^2 + 2x + 3
  int degree = 2;
  Polynomial p0;
  Polynomial p1;
  Polynomial p2;
  
  p0.degree = 0;
  p0.coeff = coeff;
  p1.degree = 1;
  p1.coeff = coeff;
  p2.degree = 2;
  p2.coeff = coeff;

  cout << "When x = 2.2, ";
  displayPolynomial(p0);
  cout << " evalates to: " << evaluate(p0,2.2) << endl << endl;

  cout << "When x = 2.2, ";
  displayPolynomial(p1);
  cout << " evalates to: " << evaluate(p1,2.2) << endl << endl;

  cout << "When x = 2.2, ";
  displayPolynomial(p2);
  cout << " evalates to: " << evaluate(p2,2.2) << endl << endl;


  Polynomial p = add(p1,p2);
  cout << "p1 + p2 =  ";
  displayPolynomial(p);
  cout << endl;
 
  Polynomial pDer = derivative(p);
  cout << "dp/dx =  ";
  displayPolynomial(pDer);
  cout << endl;
 
  return 0;
}

#endif
