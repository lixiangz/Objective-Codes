#include <cstdlib>
#include <iostream>
using namespace std;

int main(const int argc, const char* const argv[]) {
	int rc = 0;
	
	if (argc < 3) {
		cerr << "Error: Unable to compute statistics over data set because there's not enough readings" << endl;
		return -1;
	}
	if (atoi(argv[1]) <= 0) {
		cerr << "Error: Window size has to be positive"<< endl;
		return -1;
	}
	int Window = atoi(argv[1]);
	int countx = 2;
	int county = 2;
	int s = 2;
	float num = atof(argv[countx]);
	bool end = false;
	bool runterm = true;
	
	for (int a = 1; a < argc; a = a+1) {
		if (atof(argv[a]) < 0) {
			runterm = false;
		}
	}
 
	if (runterm == true) {
		cerr << "Error: No terminator dected, ending"<< endl;
		return -1;
	} 
	
	cout <<"Window Size: " << atoi(argv[1]) << endl;
	cout <<"Sample   Value   SWMinimum SWMaximum" << endl;
	
/*	while (atof(argv[s]) >= 150){
		s = s+1;
		float valid = atof(argv[s]);
		countx++;
		if (atof(argv[s]) >= 150){
			cout << "Warning: invalid voltage reading " << num << " ignored in calculation" << endl;
			county++;
			countx--;
		}
	} */
	
	while (end == false) {
	
		if (num == 0){
			cout << "Warning: invalid voltage reading " << num << " ignored in calculation" << endl;
			rc = 1;
		}
		else if (num >= 150){
			cout << "Warning: invalid voltage reading " << num << " ignored in calculation" << endl;
			rc = 1;
		}
		
		else{	
			float Maximum = 0;
			float Minimum = 150;
			for (int i = 0; i < Window; i++){
				if (atof(argv[countx]) >= 150 ){
					countx++;
				}
				else if ((countx-i > 1) && (atof(argv[countx-i]) > 0) && (atof(argv[countx-i]) < 150)){
					if (atof(argv[countx-i]) > Maximum){
						Maximum = atof(argv[countx-i]);
					}
					if (atof(argv[countx-i]) < Minimum){
						Minimum = atof(argv[countx-i]);
					}
				}
			}
			cout << county-1 <<  "	 " << atof(argv[countx]) << "	 " << Minimum <<  "	"  << Maximum << endl;
		}
		countx = countx+1;
		county = county+1;
		num = atof(argv[countx]);	
		if (num < 0) {
			end = true;
		}
	
	}

	if (county == 1) {
		cerr << "Error: Unable to compute statistics over data set because there's not enough readings"<< endl;
		return -1;
	}
	return rc;
}