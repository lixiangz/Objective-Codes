#include <stdlib.h>
#include <iostream>
#include <cmath>
bool same(float a, float b){
		return fabs(a-b < 0.1);
	}
int main(const int argc, const char* const argv[] ) {
		using namespace std;
		int rc = 0;
		if (argc < 7) {
				cerr << argv[0] << " Error: Expected 6 arguments; received "  << argc-1 <<"; exiting" << endl;
				return -1;
			}
		if (argc > 7) {
				cerr << argv[0] << " Warning: Expected 6 arguments; received " << argc-1 <<"; ignoring extraneous arguments" << endl;
				rc = 1;
			}

		char const *shape;
		char const *angle;
		float x1 = atof(argv[1]);
		float y1 = atof(argv[2]);
		float x2 = atof(argv[3]);
		float y2 = atof(argv[4]);
		float x3 = atof(argv[5]);
		float y3 = atof(argv[6]);
		float s1 = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
		float s2 = sqrt(pow(x2-x3,2) + pow(y2-y3,2));
		float s3 = sqrt(pow(x3-x1,2) + pow(y3-y1,2));
		float s = 0.5*(s1+s2+s3);
		float a = sqrt(s*(s-s1)*(s-s2)*(s-s3));
		float slope1 = (y3-y1)/(x3-x1);
		float slope2 = (y2-y1)/(x2-x1);
		float slope3 = (y3-y2)/(x3-x2);


		if (same(s1,s2) && same(s2,s3) && same(s1,s3)) {
				shape = "equilateral";
		}
		else if (same(s1,s2) != same(s2,s3) != same(s3,s1)) {
				shape = "scalene";
		}
		else shape = "isosceles";

		if (slope1 == -1/slope2) {
				angle = "right";
		}
		else if (slope2 == -1/slope3) {
				angle = "right";
		} 
		else if (slope3 == -1/slope1) {
				angle = "right";
		}
		else if (slope3 > -1/slope1) {
				angle = "acute";
		}
		else if (slope3 > -1/slope2) {
				angle = "acute";
		}
		else if (slope2 > -1/slope1) {
				angle = "acute";
		}
		else angle = "obtuse";

	
		cout <<"The triangle formed by points ("<< x1 <<"," << y1 <<"), (" << x2 <<","<< y2 <<"), and ("<< x3 << ","<< y3 << ") is: " << shape <<" "<< angle << endl;
		cout <<"The area of the triangle formed by points ("<< x1 <<"," << y1 <<"), (" << x2 <<","<< y2 <<"), and ("<< x3 << ","<< y3 << ") is: " << a << endl;
		return rc;
}
