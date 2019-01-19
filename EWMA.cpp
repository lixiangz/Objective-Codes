#include <cstdlib>
#include <iostream>
using namespace std;

int main(const int argc, const char* const argv[]) {
 int rc = 0;

	float a = atof(argv[1]);
	int countx = 1;
	int county = 1;
	int s = 2;
	float num = atof(argv[countx]);
	bool end = false;
	bool runterm = true;
	float prevA = atof(argv[s]);
	
	if (argc < 4) {
		cerr << "Error: Unable to compute statistics over data set because there's not readings" << endl;
		return -1;
	}
	if (a <= 0) {
		cerr << "Error: Unable to compute statistics over data set because there's not enough readings"<< endl;
		return -1;
	}
	else if (a >= 1) {
		cerr << "Error: Unable to compute statistics over data set because there's not enough readings"<< endl;
		return -1;
	}
	
	for (int a = 1; a < argc; a = a+1) {
		if (atof(argv[a]) < 0) {
			runterm = false;
		}
	}

	if (runterm == true) {
		cerr << "Error: No terminator dected, ending"<< endl;
		return -1;
	} 
	cout <<"Sample   Value  EWMA" << endl;
	
	while (end == false) {
		countx = countx+1;
		county = county+1;
		num = atof(argv[countx]);
		
		while (atof(argv[s]) > 150){
		s = s+1;
		prevA = atof(argv[s]);
		}
		
		if (num >= 150){
			cout << "Warning: invalid voltage reading " << num << " ignored in calculation" << endl;
			rc = 1;
		}
		
		if (num < 0) {
			end = true;
		}

		if (num == 0){
			cout << "Warning: invalid voltage reading " << num << " ignored in calculation" << endl;
			rc = 1;
		}
		
		if ((num < 150) && (num > 0)){
			cout << (county-1) <<  "	 " << atof(argv[countx])  << "	" << (a * num) + ((1-a)*(prevA)) << endl;
		}
		
		if ((num < 150) && (num > 0)){
			prevA = (a * num) + ((1-a)*(prevA));
		}
	}

	if (county == 1) {
		cerr << "Error: Unable to compute statistics over data set because there's not enough readings"<< endl;
		return -1;
	}

	return rc;

}