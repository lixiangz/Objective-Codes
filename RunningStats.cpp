#include <cstdlib>
#include <iostream>
using namespace std;

int main(const int argc, const char* const argv[]) {
 int rc = 0;
	if (argc < 2) {
		cerr << "Error: Unable to compute statistics over data set because there's not readings" << endl;
		return -1;
	}
	if (argc == 2) {
		cerr << "Error: Unable to compute statistics over data set because there's not readings" << endl;
		return -1;
	}
	int countx = 0;
	int county = 0;
	int a = 0;
	float num = atof(argv[countx]);
	float sum = 0;
	bool end = false;
	bool runterm = true;
	bool runonce = false;
	float Minimum = atof(argv[countx+1]);
	float Maximum = atof(argv[countx+1]);
	
	if (atof(argv[1]) < 0) {
		cerr << "Error: Unable to compute statistics over data set because there's not enough readings"<< endl;
		return rc;
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

	cout <<"Sample   Value  Minimum Average Maximum" << endl;
	if (atof(argv[1]) > 150){
			Maximum = atof(argv[countx+2]);
			runonce = true;
		}	
	while (end == false) {
		countx = countx+1;
		county = county+1;
		num = atof(argv[countx]);

		if (num < 0) {
			end = true;
		}
		if (num > 150){
			cout << "Warning: invalid voltage reading " << num << " ignored in calculation" << endl;
			rc = 1;
		}
		
		if ((num < 150) && (num > 0)){

			if (num < Minimum){
				Minimum = num;
			}
			
			else if (num > Maximum) {
				Maximum = num;
			}
			sum = sum + num;
			cout << county <<  "	 " << atof(argv[countx]) << "	" << Minimum <<  "	" << sum/county << "	" << Maximum << endl;
		}
		
	}
	if (county == 0) {
		cerr << "Error: Unable to compute statistics over data set because there's not enough readings"<< endl;
		return rc;
	}
	
	return rc;
}