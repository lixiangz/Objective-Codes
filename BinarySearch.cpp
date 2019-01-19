
int binarySearchHelper(const int data[], const int numberToFind, const int lo, const int hi){
	
	int middle = (hi+lo)/2;
	
	if (numberToFind == data[middle]){
		return middle;
	}

	else if (numberToFind < data[middle]){
		return binarySearchHelper(data, numberToFind, lo, middle -1);
	}

	else if (numberToFind > data[middle]){
		return binarySearchHelper(data, numberToFind, middle + 1, hi);
	}

	return 0;
}

int binarySearch(const int data[],const int numElements,const int numberToFind){

	if (numElements == 1){
		if (data[0] == numberToFind){
			int position = 0;
			return position;
		}
		else{
			return -1;
		}
	}

	if (numElements == 0){
		return -1;
	}

	if (numElements < 0){
		return -1;
	}

	if (data[numElements-1] < numberToFind){
		return -1;
	}

	if (data[0] > numberToFind){
		return -1;
	}
	

	int hi = numElements-1;
	int lo = 0;
	int position = binarySearchHelper(data, numberToFind, lo, hi);
	return position;
}

