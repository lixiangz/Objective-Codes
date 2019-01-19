#include <iostream>
#include <math.h>

using namespace std;

enum State { START, DONE, GOT_ZERO, GOT_ONE,GOT_KTH_ZERO, GOT_KTH_ONE };
int countZerosAndOnes(const int zeroOneData[], const int numSamples,const int kMax,int& zeroCount, int& oneCount){
	State s = START;
	zeroCount = 0;
	oneCount = 1;
	int k = 0; 
	
	if (numSamples <= 0){
		return -1;
	}

	if (kMax < 0){
		return -1;
	}

	for (int i = 0; i < numSamples+1; i++){
		int input = zeroOneData[i];
		if ((input != 0) && (input != 1)) {
			return -1;
		}

		switch(s) {

		case START:
			
			if (zeroOneData[0] == 1){
				s = GOT_ONE;
			}

			else if (zeroOneData[0] == 0){
				s = GOT_KTH_ZERO;
			}

			else {
				return -1;
			}

			break;

		case GOT_KTH_ONE:

			if (k >= kMax){
				oneCount++;
				s = GOT_ONE;
			}

			else if (input == 1){
				++k;
			}
			
			else if (input == 0){
				k = 0;
				if (k >= kMax){
					zeroCount++;
				}
				s = GOT_ZERO;
			}

			else {
				return -1;
			}

			break;

		case GOT_ONE:	

			if (input == 0){
				k = 0;
				s = GOT_KTH_ZERO;
				if (k >= kMax) {
					zeroCount++;
					s = GOT_ZERO;
				}
			}

			else if (input == 1){
				s = GOT_ONE;
			}

			else {
				return -1;
			}

			break;

		case GOT_KTH_ZERO:

			if (k >= kMax){
				zeroCount++;
				s = GOT_ZERO;
			}
			
			else if (input == 1){
				k = 0;
				if (k >= kMax){
					oneCount++;
				}
				s = GOT_ONE;
			}

			else if (input == 0){
				++k;
			}

			else {
				return -1;
			}

			break;

		case GOT_ZERO:

			if (input == 1){
				k = 0;
				s = GOT_KTH_ONE;
				if (k >= kMax) {
					oneCount++;
					s = GOT_ONE;
				}

			}

			else if (input == 0){
				s = GOT_ZERO;
			}

			else {
				return -1;
			}

			break;

		case DONE:
			break;

		}	
	}
	return 0;
}

