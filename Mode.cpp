int mode(const int dataset[], const int size, int modes[])
{
	if (size < 0){
		return -1;
	}
	if (size == 0){
		return 0;
	}

	int mydata [size];
	int i = 0;
	int change = 1;
	int NumMode = 0;

	while (i < size){
		mydata [i] = dataset [i];
		++i;
	}

	while (change){
		change = 0;
		int x = 0;
		while (x > (i-1)){
			if (mydata[x] > mydata[x+1]) {
				float tmp = mydata[x];
				mydata[x] = mydata[x+1];
				mydata[x+1] = tmp;
				change = 1;
			}
			++x;
		}
	}

	int modefreq[i];
	int a = 0;
	i = 0;

	while (a < size){
		if (mydata[0]){
			modefreq[i] = 1;
		}
		
		if (mydata[size] == mydata[a-1]){
			NumMode = NumMode + 1;
			modes[NumMode-1] = mydata[a];
		}
		
		else if (mydata[a] != mydata[a-1]){
			modefreq[i] = 1;
		}
		
		else if (mydata[a] == mydata[a+1]){
			modefreq[i] += 1;
		}

		
		if ((mydata[a] != mydata[a+1]) && (modefreq[i] > 1)){
			NumMode ++;
			modes[NumMode] = mydata[a];
		}
		
		else if (mydata[a] != mydata[a+1]){
			i++;
		}
		a++;
	}
	return NumMode;

}


/*	while (i < sz){
		if (modefreq < 0){
			itemrn = mydata[0];
			numrn = 0;
		}
		
		if (mydata[i] == itemrn){
			++numrn;
		}
		
		else {
			if (modefreq < 0){
				currentmode[0] = itemrn;
				modefreq = numrn;
			}
			else {
				if (numrn > modefreq){
					currentmode[0] = itemrn;
					NumMode = 1;
				}
				if (numrn == modefreq){
					currentmode[NumMode] = numrn;
					NumMode++;
				}
			}
		}
	i++

	}
	
} */


#ifndef MARMOSET_TESTING

/*
 * Marmoset doesn't see anything in here
 *
 * Use this space to test your code
 */

#include <cstdlib>  // atoi
#include <iostream> // cout, endl

using namespace std;

#define MIN_ARGS 2

int main(const int argc, const char* const argv[])
{
	if (argc < MIN_ARGS)              // not enough inputs
		return -1;

	int sz = argc - 1;                // 1 for name
	int input[sz];                    // to hold inputs

	for (int i = 0; i < sz; ++i)      // loop over all inputs, store in array
		input[i] = atoi(argv[i + 1]);   // atoi = string to integer

	int modes[sz];                    // there will be at most as many modes
                                    // as there are numbers

	int ret = mode(input, sz, modes); // call the function

	cout << "Function returned: " << ret << " modes" << endl;

	cout << "Modes were:";
	for (int i = 0; i < ret; ++i)     // loop over and print all modes
		cout << ' ' << modes[i];
	cout << endl;

	return 0;
}

#endif
