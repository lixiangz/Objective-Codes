
int maxLocation (const int data[], const int numElements){
	int maxvalue = 0;
	int maxarray = 0;
	int x = 0;
	if (numElements < 1){
		return -1;
	}
	
	while (x < numElements){
		if (data[x] >= maxvalue){
			maxvalue = data[x];
			maxarray = x;
		}
		x++;
	}

	return maxarray;
}

int selectionSort (int data[], const int numElements){
	if (numElements <= 1){
		return 0;
	}

	if (numElements == 0){
		return 0;
	}
	
	int max = maxLocation(data, numElements);

	int tmp = 0;
	tmp = data[numElements-1];
	data[numElements-1] = data[max];
	data[max] = tmp;

	selectionSort (data, numElements-1);

	return 0;

}

