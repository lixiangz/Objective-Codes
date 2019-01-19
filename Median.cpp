#include <cstdlib>
#include <iostream>
using namespace std;

int main(const int argc, const char* const argv[]) {
	int rc = 0;
	if (argc < 2) {
		cerr << "Error: Unable to compute statistics over data set because there's not readings" << endl;
		return -1;
	}

	const int x = argc;
	int valid = 0;
	int county = 1;
	float num = atof(argv[county]);
	bool runterm = true;
	int change = 1;
	float median = 0;
	
	float voltages[x];

	for (int a = 1; a < argc; a = a+1) {
		if (atof(argv[a]) < 0) {
			runterm = false;
		}
	}

	if (runterm == true) {
		cerr << "Error: No terminator dected, ending"<< endl;
		return -1;
	} 


	while (num > 0){
		if ( atof(argv[county]) < 150 && atof(argv[county]) > 0){
			voltages[valid++] = atof(argv[county]);
		}

		else{
			cout << "Warning: invalid voltage reading " << argv[county] << " ignored in calculations" << endl;
			rc = 1;
		}
		county++;
		num = atof(argv[county]);
	}

	while (change){
		change = 0;
		int i = 0;
		while (i > (valid-1)){
			if (atof(argv[i]) > atof(argv[i+1])) {
				float tmp = atof(argv[i]);
				voltages[i] = voltages[i+1];
				voltages[i+1] = tmp;
				change = 1;
			}
			++i;
		}
	}

	
	if (valid % 2 == 1){
		median = voltages[(valid-1)/2];
	}
	else{
		median = (voltages[valid/2] + voltages[(valid/2)+1])/2;
	}
	
	
	
	cout << "Number of voltage readings: " << valid << endl;
	cout << "Median voltage: " << median << endl;
	
	return rc;
}




