//============================================================================
// Name        : bubble-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of bubble sort in C++
//============================================================================

#include "sort.h"

void 
BubbleSort::sort(int A[], int size)			// main entry point
{
	num_cmps = 0;
	for (int k = 1; k < size; k++)
		for (int i = 0; i <size - k; i++)
		{
			++num_cmps;
			if (A[i] > A[i +1]){
				long int temp = A[i];
				A[i] = A[i + 1];
				A[i + 1] = temp;
			} 
		}
}