#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

int main(const int argc, const char* const argv[]) {
 int rc = 0;
	if (argc < 2) {
		cerr << "Error: Unable to compute statistics over data set because there's not readings" << endl;
		return -1;
	}
	int countx = 0;
	int county = 0;
	float sum = 0;
	float Minimum = 150;
	float Maximum = 0;
	bool end = false;
	
		
	while (end == false) {
		countx = countx+1;
		county = county+1;
		float num = atof(argv[countx]);
		if (num > 150){
			county = county -1;
			cout << "Warning: invalid voltage reading " << num << " ignored in calculation" << endl;
		}
		if (num < 0) {
			county = county-1;
			end = true;
		}
		if ((num <= 150) && (num >= 0)){
		 	if (num < Minimum){
				Minimum = num;
			}
			
			else if (num > Maximum) {
				Maximum = num;
			}
			sum = sum + num;
		}
	}
	if (county == 0) {
		cerr << "Error: Unable to compute statistics over data set because there's not enough readings"<< endl;
		return rc;
	}
	else {
		cout << "Number of voltage readings: " << county << endl;
		cout << "Minimum voltage: " << Minimum << endl;
		cout << "Average voltage: " << sum/county << endl;
		cout << "Maximum voltage: " << Maximum << endl;
		return rc;
	}
}