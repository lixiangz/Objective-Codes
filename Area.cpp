#include <cstdlib>
#include <iostream>
using namespace std;
extern float f(float x);

int main(const int argc, const char* const argv[]) {
	int rc = 0;
	if (argc < 3){
		cerr << " Error: Expected 2 arguments; received "  << argc-1 <<"; exiting" << endl;
		return -1;
	}

	if (argc > 3){
		cerr << " Warning: Expected 2 arguments; received " << argc-1 <<"; ignoring extraneous arguments" << endl;
		rc = 1;
	}

	float A = atof(argv[1]);
	float B = atof(argv[2]);
	float dx = 0.01;
	float x = A;
	float area = 0;
	float sum = 0;

	if (A > B){
		cerr << "Error: A should be less than B" << endl;
		return -1;
	}

	if (A == B){
		sum = 0;
		cout << "The area under f(x) from" << A <<" to " << B << " is " << sum << endl;
		return rc;
	}

	while (x <= B) {
		area = 0.01 * ((f(x+dx)+f(x))/2);
		x = x + 0.01;
		sum = sum + area;
	}
	cout << "The area under f(x) from" << A <<" to " << B << " is " << sum << endl;

	return rc;
}
    