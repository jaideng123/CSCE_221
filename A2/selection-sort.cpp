//============================================================================
// Name        : selection-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
SelectionSort::sort(int A[], int size)				// main entry point
{
	num_cmps=0;
	int pos_min,temp;

	for (int i=0; i < size-1; i++)
	{
	    pos_min = i;//set pos_min to the current index of array
		
		for (int j=i+1; j < size; j++)
		{
		++num_cmps;
		if (A[j] < A[pos_min])
                   pos_min=j;
	//pos_min will keep track of the index that min is in, this is needed when a swap happens
		}
		
	//if pos_min no longer equals i than a smaller value must have been found, so a swap must occur
            if (pos_min != i)
            {
                 temp = A[i];
                 A[i] = A[pos_min];
                 A[pos_min] = temp;
            }
	}




  /* Complete this function with the implementation of selection sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
}
