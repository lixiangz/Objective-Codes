
int partition(int data[], const int lo, const int hi)
{
  if (lo < 0){
    return -1;
  }
  if (hi < 0){
    return -1;
  }
  if (hi-lo < 1){
    return -1;
  }
 
  float pivot = data[hi];
  int pIndex = lo;
  int i = lo;
  while (i < hi){
    if (data[i] <= pivot){
  
      int tmp = 0;
      tmp = data[i];
      data[i] = data[pIndex];
      data[pIndex] = tmp;
      pIndex++;

    }
    i++;
  }
  
  int tmp = 0;

  tmp = data[pIndex];
  data[pIndex] = data[hi];
  data[hi] = tmp;

  return pIndex;
}


void quickSortHelper(int data[], const int lo, const int hi)
{ 

  if ((hi-lo) > 0){
    int pivot = partition(data, lo, hi);
    quickSortHelper(data, pivot+1, hi);
    quickSortHelper(data, lo, pivot-1);
  }
  return;
}



int quickSort(int data[], const int numElements)
{
  if (numElements <= 1){
    return 0;
  }

  if (numElements == 0){
    return 0;
  }

  int lo = 0;
  int hi = numElements-1;
  quickSortHelper(data, lo, hi);
  return 0;
}


#ifndef MARMOSET_TESTING

/*
 * Marmoset doesn't see anything in here
 *
 * Use this space to test your code
 */

#include <iostream> // cout, endl
#include <stdlib.h> // srandom(), random()

using namespace std;

// print an array in comma separated format
void printArray(const int data[], const int numElements)
{
  int i = 0;
  while (i < numElements-1) {
    cout << data[i] << ", ";
    ++i;
  }
  cout << data[numElements-1] << endl;
}


int main(void)
{
  int numElements = 10; // array size

  srandom(0);  // deterministic seed for random()
               // change 0 to a different number to get a different random array 

  int data[10] = {10, 2, 3, 1, 4, 5, 8, 7, 6, 9};

  cout << "Array is: ";
  printArray(data, numElements);

  int ret = quickSort(data, numElements); // sort the array

  cout << "After sorting, array is: ";
  printArray(data, numElements);

  // check the return code
  if (ret < 0)
    cout << "quickSort() indicated error" << endl;
  else if (ret > 0)
    cout << "quickSort() indicated warning" << endl;

  return 0;
}


#endif
