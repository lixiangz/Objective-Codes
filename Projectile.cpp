#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

float projectileDestination(const float initialHeight, const float initialVelocity, const float mass, const float initialAngle){
		
	if (initialHeight < 0){
		return NAN;
	}
	if (initialAngle > 90){
		return NAN;
	}
	if (initialAngle < -90){
		return NAN;
	}
	if (mass <= 0){
		return NAN;
	}
	if (initialVelocity < 0){
		return NAN;
	}



	double Vx = initialVelocity * cos(initialAngle * (M_PI/180));

	double Vy = initialVelocity * sin(initialAngle * (M_PI/180));
	

	double time = 0;
	double time1 = (-1*Vy + (sqrt(pow(Vy,2)+19.6*initialHeight)))/(-1*9.8);
	double time2 = (-1*Vy - (sqrt(pow(Vy,2)+19.6*initialHeight)))/(-1*9.8);


	if (time1 > 0){
		time = time1;
	}
	else if (time2 > 0){
		time = time2;
	}

	float distance = time * Vx;

	return distance;

	}

#ifndef MARMOSET_TESTING

/*
 * Marmoset doesn't see anything in here
 *
 * Use this space to test your code
 */

#include <iostream> // cout, endl

using namespace std;

int main(void)
{
float velocity = 10;
	  // parameters
	float height   = 10;
	float mass     = 1;
	float angle    = 30;

  // call the function and print the result
	float dest = projectileDestination(height, velocity, mass, angle);
	cout << "The desination of a projectile with: " << endl
	<< "Height: "   << height   << endl
	<< "Velocity: " << velocity << endl
	<< "Mass: "     << mass     << endl
	<< "Angle: "    << angle    << endl
	<< "is: "       << dest     << endl;

	return 0;
}

#endif

	