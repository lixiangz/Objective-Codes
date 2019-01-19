#include <cstdlib>
#include <iostream>
using namespace std;

int main(const int argc, const char* const argv[]) {
	int rc = 0;
	if (argc < 2) {
		cerr << "Error: Unable to compute histogram over data set because there's not enough readings" << endl;
		return -1;
	}

	if (atof(argv[1]) < 0){
		cerr << "Error: Unable to compute histogram over data set because there's no valid readings" << endl;
		return -1;
	}

	int valid = 0;
	int county = 1;
	float num = atof(argv[county]);
	bool runterm = true;
	int bucket[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	bool end = false;
	

	for (int a = 1; a < argc; a = a+1) {
		if (atof(argv[a]) < 0) {
			runterm = false;
		}
	}

	if (runterm == true) {
		cerr << "Error: Unable to compute histogram over data set because no terminators"<< endl;
		return -1;
	} 


	while (end == false){

		if (num > 0 && num < 106){
			bucket[0] += 1;
		}

		else if ((num >= 106) && (num < 109)){
			bucket[1] += 1;
		}
		
		else if ((num >= 109) && (num < 112)){
			bucket[2] += 1;
		}
		
		else if ((num >= 112) && (num < 115)){
			bucket[3] += 1;
		}
		
		else if ((num >= 115) && (num < 118)){
			bucket[4] += 1;
		}

		else if ((num >= 118) && (num < 121)){
			bucket[5] += 1;
		}

		else if ((num >= 121) && (num < 124)){
			bucket[6] += 1;
		}


		else if ((num >= 124) && (num <= 127)){
			bucket[7] += 1;
		}

		else if ((num > 127) && (num < 150)){
			bucket[8] += 1;
		}
		
		else if (num >= 150){
			bucket[9] += 1;
			cout << "Warning: invalid voltage reading " << num << " ignored in calculations" << endl;
			rc = 1;
		}
		
		county++;
		num = atof(argv[county]);

		if (num < 0) {
			end = true;
		}
	}

	valid = bucket[0] + bucket[1] + bucket[2] + bucket[3] + bucket[4] + bucket[5] + bucket[6] + bucket[7] + bucket[8];

	cout << "Number of voltage readings: " << valid << endl;
	cout << "Voltage readings (0-106): " << bucket[0] << endl;
	cout << "Voltage readings [106-109): " << bucket[1] << endl;
	cout << "Voltage readings [109-112): " << bucket[2] << endl;
	cout << "Voltage readings [112-115): " << bucket[3] << endl;
	cout << "Voltage readings [115-118): " << bucket[4] << endl;
	cout << "Voltage readings [118-121): " << bucket[5] << endl;
	cout << "Voltage readings [121-124): " << bucket[6] << endl;
	cout << "Voltage readings [124-127]: " << bucket[7] << endl;
	cout << "Voltage readings (127-150): " << bucket[8] << endl;
	cout << "Invalid readings: " << bucket[9] << endl;


	return rc;

}