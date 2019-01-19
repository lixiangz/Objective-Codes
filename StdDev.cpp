#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

int main(const int argc, const char* const argv[]) {
	int rc = 0;
	if (argc < 2) {
		cerr << "Error: Unable to compute standard deviations over data set because there's not enough readings" << endl;
		return -1;
	}
	
	const int x = argc;

	int valid = 0;
	float sum = 0;
	int county = 1;
	float num = atof(argv[county]);
	float average = 0;
	bool runterm = true;
	
	float voltages[x];

	for (int a = 1; a < argc; a = a+1) {
		if (atof(argv[a]) < 0) {
			runterm = false;
		}
	}

	if (runterm == true) {
		cerr << "Error: Unable to compute standard deviations over data set because no terminators"<< endl;
		return -1;
	} 

	while (num > 0){
		if (atof(argv[county]) < 150 && atof(argv[county]) > 0){
			voltages[valid++] = atof(argv[county]);
			sum = sum + atof(argv[county]);
		}

		else{
			cout << "Warning: invalid voltage reading " << argv[county] << " ignored in calculations" << endl;
			rc = 1;
		}
		county++;
		num = atof(argv[county]);

	}

	if (valid == 0){
		cerr << "Error: Unable to compute standard deviations over data set because no valid data" << endl;
		return -1;
	}
	

	average = sum/valid;
	float total = 0;
	
	int a = 0;

	while (a < valid){
		while (voltages[a] > 150){
			county ++;
		}
		float sumN = pow((voltages[a])-average,2);
		total = total + sumN;
		a++;
	}

	if ((valid == 0) && (total == 0)) {
		cout << "Number of voltage readings: " << valid << endl;
		cout << "Population standard deviation: positive infinity" << endl;
		cout << "Sample standard deviation: " << sqrt(total/(valid-1)) << endl;
	}

	else if (valid == 1) {
		cout << "Number of voltage readings: " << valid << endl;
		cout << "Population standard deviation: " << sqrt(total) << endl;
		cout << "Sample standard deviation: undefined" << endl;
	}

	else {
		cout << "Number of voltage readings: " << valid << endl;
		cout << "Population standard deviation: " << sqrt(total/valid) << endl;
		cout << "Sample standard deviation: " << sqrt(total/(valid-1)) << endl;
	}

	return rc;
}


