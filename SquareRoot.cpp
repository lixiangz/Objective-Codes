#include <cstdlib>
#include <iostream>
using namespace std;
int main(const int argc, const char* const argv[]) {
 int rc = 0;
	if (argc < 2) {
		cerr << " Error: Expected 1 arguments; received "  << argc-1 <<"; exiting" << endl;
		return -1;
	}
	if (argc > 2) {
		cerr << " Error: Expected 1 arguments; received " << argc-1 <<"; ignoring extraneous arguments" << endl;
		rc = 1;
	}
	float n = atof(argv[1]);
	float x = 0;

	if (n < 0) {
		cerr << "Error: cannot compute square root of a negative number" << endl;
		return 0;
	}
	while (x*x < n){
		x += 0.1;
	}
	x -= 0.1;
	do 	{
		(x = (x + n/x)/2);
	} while ((n-x*x)/n > 0.001 || (n-x*x)/n < -0.001);

	cout << "The square root of " << n << " is " << x << endl;
	return rc;
}
