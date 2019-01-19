#include <iostream>
#include <math.h>
#include "ClassyPoly.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
//
// Public operators and methods


Polynomial Polynomial::dx() const {
	return derivative();
}

float Polynomial::operator()(const float x) const {
	return evaluate(x);
}

Polynomial Polynomial::operator+(const Polynomial& p) const {
	return add(p);
}

Polynomial Polynomial::operator*(const Polynomial& p) const {
	if ((_degree < 0) || (p._degree < 0)){
		Polynomial Mult(-1, NULL);
		return Mult;
	}


	int Mult_degree = _degree + p._degree;
	int x = 0;

	float* Mult_coeff = new float[Mult_degree+1];
	Polynomial Mult(Mult_degree, Mult_coeff);

	while (x < Mult_degree+1){
		Mult._coeff[x] = 0;
		x++;
	}
	
	for (int i = 0; i < _degree+1; i++) {
		for (int j = 0; j < p._degree+1; j++) {
			Mult._coeff[i + j] += _coeff[i] * p._coeff[j];
		}
	}

	return Mult;
}

void Polynomial::operator=(const Polynomial& p) {
	_degree = p._degree;
	
	float* coeff = new float[p._degree+1];
	
	for (int i = 0; i < p._degree ; i++){
		coeff[i] = p._coeff[i];
	}

	delete[] _coeff;

	_coeff = coeff;

	return;
}

bool Polynomial::operator==(const Polynomial& p) const {
	if (_degree < 0 || p._degree < 0){
		return false;
	}

	const float LIM = 10e-5;

	if (_degree == p._degree){
		for (int i = 0; i < _degree; i++){
			if (fabs(_coeff[i] - p._coeff[i]) > LIM){
				return false;
			}
		}
	}

	else {
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////
//
// Constructors and Destructor
//
// Note: no default constructor
//

Polynomial::Polynomial(const Polynomial& p) {
	_degree = p._degree;
	
	_coeff = new float[p._degree+1];
	
	for (int i = 0; i < p._degree+1 ; i++){
		_coeff[i] = p._coeff[i];
	}

}

Polynomial::Polynomial(const int degree, const float coeff[]) {
	if (degree < 0) {
		_degree = -1;
		_coeff = new float[1];
		_coeff[0] = 0;
	}
	else {
		_degree = degree;
		_coeff = new float[degree + 1];

		for (int i = 0; i < degree + 1; i++) {
			_coeff[i] = coeff[i];
		}
	}
}

Polynomial::~Polynomial() {
	delete[] _coeff;
}

///////////////////////////////////////////////////////////////////////////
//
// Private Methods
//

float Polynomial::evaluate(const float x) const {
	if (_degree < 0){
		return NAN;
	}

	int i = 0;
	float total = 0;
	
	while (i < _degree+1){
		total = (total*x) + _coeff[i];
		i++;
	}

	return total;
}

Polynomial Polynomial::add(const Polynomial& pIn) const {

	if ((_degree < 0) || (pIn._degree < 0)){
		Polynomial Add(-1, NULL);
		return Add;
	}
	
	int Degree = 0;
	int size;

	if (_degree >= pIn._degree){
		Degree = _degree;
		size = _degree-1;
	}

	else{
		Degree = pIn._degree;
		size = pIn._degree+1;	
	}

	float coeff[size];

	
	Polynomial Add(Degree, coeff);
	
	
	if (_degree > pIn._degree ){

		for(int count = 0; count < (_degree - pIn._degree ); count++){
			Add._coeff[count] = _coeff[count];
		}

		for (int i = _degree - pIn._degree; i < _degree + 1; i++){
			Add._coeff[i] = _coeff[i] + pIn._coeff [i - (_degree - pIn._degree)];
		}
	}

	else{

		for(int count = 0; count < (pIn._degree - _degree ); count++){
			Add._coeff[count] = pIn._coeff[count];
		}

		for (int i = pIn._degree - _degree; i < pIn._degree + 1; i++){
			Add._coeff[i] = pIn._coeff[i] + _coeff [i - (pIn._degree - _degree)];
		}
	}

	return Add;
}

Polynomial Polynomial::derivative() const {
	
	if (_degree < 0){
		Polynomial Der(-1, NULL);
		return Der;
	}

	int Degree = _degree-1;

	if (_degree == 0){
		Degree = 0;
	}

	int i = 0;
	float* Der_coeff = new float[_degree -1];
	Polynomial Der(Degree, Der_coeff);
	
	while (i <= Der._degree){
		Der._coeff[i] = _coeff[i]*(_degree-i);
		i++;
	}

	return Der;
}


///////////////////////////////////////////////////////////////////////////
//
// Test driver
// Some very limited testing; should test ==
// 
#ifndef MARMOSET_TESTING

int main() {
	float coeff[] = {1, 2, 3, 4};   // x^2 + 2x + 3
	Polynomial p0(1,coeff);
	Polynomial p1(2,coeff);
	Polynomial p2(3,coeff);

	cout << "When x = 2.2, \"" << p0 << "\" evalates to: " << p0(2.2) << endl << endl;
	cout << "When x = 2.2, \"" << p1 << "\" evalates to: " << p1(2.2) << endl << endl;
	cout << "When x = 2.2, \"" << p2 << "\" evalates to: " << p2(2.2) << endl << endl;

	Polynomial p = p1 + p2;
	Polynomial q = p1 * p2;											
	cout << "p1 + p2 =  " << p << endl << endl;
	cout << "p1 * p2 =  " << q << endl << endl;

	cout << "dp/dx =  " << p.dx() << endl;
	cout << "dq/dx =  " << q.dx() << endl;

	return 0;
}

#endif


