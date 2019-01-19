#include <stdlib.h>
#include <iostream>
#include <cmath>
using namespace std;

int main(const int argc, const char* const argv[] ) {
 int rc = 0;
	if (argc < 7) {
		cerr << " Error: Expected 6 arguments; received "  << argc-1 <<"; exiting" << endl;
		return -1;
	}
	if (argc > 7) {
		cerr << " Warning: Expected 6 arguments; received " << argc-1 <<"; ignoring extraneous arguments" << endl;
		rc = 1;
	}

	float y1 = atof(argv[2]);
	float x1 = atof(argv[1]);
	float x2 = atof(argv[3]);
	float y2 = atof(argv[4]);
	float x3 = atof(argv[5]);
	float y3 = atof(argv[6]);

	float s1 = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
	float s2 = sqrt(pow(x2-x3,2) + pow(y2-y3,2));
	float s3 = sqrt(pow(x3-x1,2) + pow(y3-y1,2));
	float s = 0.5*(s1+s2+s3);
	float a = sqrt(s*(s-s1)*(s-s2)*(s-s3));
	float slope1 = (y3-y2)/(x3-x2);
	float slope2 = (y2-y1)/(x2-x1);

	if ((s1 == 0 ) && (s2 == 0) && (s3 == 0)){
		cerr << " The points ("<< x1 <<"," << y1 <<"), (" << x2 <<","<< y2 <<"), and ("<< x3 << ","<< y3 << ") overlap; they do not form a triangle " << endl;
		return  -1;
	}

	if ((y3-y1)/(x3-x1) == (y2-y1)/(x2-x1)) {
		cerr << " The points ("<< x1 <<"," << y1 <<"), (" << x2 <<","<< y2 <<"), and ("<< x3 << ","<< y3 << ") form a line with slope: " << slope1 << endl;
		return -1;
	}
	else if ((y3-y2)/(x3-x2) == (y3-y1)/(x3-x1)) {
		cerr << " The points ("<< x1 <<"," << y1 <<"), (" << x2 <<","<< y2 <<"), and ("<< x3 << ","<< y3 << ") form a line with slope: " << slope1 << endl;
		return -1;
	}
	else if ((y2-y1)/(x2-x1) == (y3-y2)/(x3-x2)) {
		cerr << " The points ("<< x1 <<"," << y1 <<"), (" << x2 <<","<< y2 <<"), and ("<< x3 << ","<< y3 << ") form a line with slope: " << slope1 << endl;
		return -1;
	}
	else if ((y2-y1)/(x2-x1) == (y3-y1)/(x3-x1)) {
		cerr << " The points ("<< x1 <<"," << y1 <<"), (" << x2 <<","<< y2 <<"), and ("<< x3 << ","<< y3 << ") form a line with slope: " << slope2 << endl;
		return -1;
	}
	else 
		cout <<"The area of the triangle formed by points ("<< x1 <<"," << y1 <<"), (" << x2 <<","<< y2 <<"), and ("<< x3 << ","<< y3 << ") is: " << a << endl;
	return rc;
}
