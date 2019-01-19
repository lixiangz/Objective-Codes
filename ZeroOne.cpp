#include <iostream>
#include <math.h>

using namespace std;

enum State { START, DONE, GOT_ZERO, GOT_ONE };
int countZerosAndOnes(const int zeroOneData[], const int numSamples,int& zeroCount, int& oneCount){
	State s = START;
	zeroCount = 0;
	oneCount = 0;
	
	if (numSamples <= 0){
		return -1;
	}

	for (int i = 0; i < numSamples; i++){
		int input = zeroOneData[i];
		switch(s) {

		case START:
			if (zeroOneData[0] == 1){
				oneCount++;
				s = GOT_ONE;
			}

			if (zeroOneData[0] == 0){
				zeroCount++;
				s = GOT_ZERO;
			}

			if ((input != 0) && (input != 1)) {
				return -1;
			}

			break;

		case GOT_ONE:
			if (input == 0){
				zeroCount++;
				s = GOT_ZERO;
			}

			if ((input != 0) && (input != 1)) {
				return -1;
			}

			break;

		case GOT_ZERO:
			if (input == 1){
				oneCount++;
				s = GOT_ONE;
			}

			if ((input != 0) && (input != 1)) {
				return -1;
			}
			break;

		case DONE:
			break;

		default:
		cerr << "An unknown error occurred." << endl;
			return -1;
		}

	}
	return 0;
}

