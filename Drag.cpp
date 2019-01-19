#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

float projectileDestinationWithDrag(const float initialHeight,const float initialVelocity,const float mass,const float initialAngle,const float k,const float deltaT){
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
	if (initialVelocity <= 0){
		return NAN;
	}
	
	float angle = (initialAngle * (M_PI/180));

	//x
	float Velocityx = initialVelocity * cos(angle);
	float positionx = 0;
	float accerlerationx = 0;

	//y
	float velocityy = initialVelocity * sin(angle);
	float positiony = initialHeight;
	float accerlerationy = 0;

	//forces
	float drag = 0;
	float velocity = 0;

	while (positiony > 0){
		velocity = sqrt(pow(Velocityx,2) + pow(velocityy,2));
		angle = atan(fabs(velocityy)/fabs(Velocityx));

		drag = k * pow(velocity,2);

		accerlerationx = (-drag/mass)*cos(angle);
		if (angle > 0){
			accerlerationy = -9.8 - (drag/mass)*sin(angle);
		}
		else if (angle < 0){
			accerlerationy = -9.8 + (drag/mass)*sin(angle);
		}
		else {
			accerlerationy = -9.8;
		}

		Velocityx = Velocityx + accerlerationx*deltaT;
		velocityy = velocityy + accerlerationy*deltaT;

		positionx = positionx + Velocityx*deltaT + ((1/2)*Velocityx*pow(deltaT,2));
		positiony = positiony + velocityy*deltaT + ((1/2)*velocityy*pow(deltaT,2));
	}


	float d = positionx;
	return d;

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
	float velocity = 65.3452;
	  // parameters
	float height   = 74.8871;
	float mass     = 82.4008;
	float angle    = 45.4396;
	float k = 0.254214;
	float deltaT = 0.001;

  // call the function and print the result
	float dest = projectileDestinationWithDrag(height, velocity, mass, angle, k, deltaT);
	cout << "The desination of a projectile with: " << endl
	<< "Height: "   << height   << endl
	<< "Velocity: " << velocity << endl
	<< "Mass: "     << mass     << endl
	<< "Angle: "    << angle    << endl
	<< "k: "    << k   << endl
	<< "deltaT: "    << deltaT    << endl
	<< "is: "       << dest     << endl;

	return 0;
}

#endif

