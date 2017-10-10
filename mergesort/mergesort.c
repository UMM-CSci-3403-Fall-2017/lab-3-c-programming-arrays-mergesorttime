#include <stdlib.h>
#include <stdio.h>
#include "mergesort.h"

// Helper function to accomodate missing parameters to mergesort - low, high
void mergesorthelper(int values[], int low, int high) {
    int* merge_array;
    int size, mid, i, j, k;	


    size = high - low;
    // Empty or single element list checker
    if (size<=1) {
    	return;
    }

    mid = low + size / 2;

    // Recursive calls to sort the subarrays
    mergesorthelper(values, low, mid);
    mergesorthelper(values, mid, high);

    // Declare our temporary array to the current size of the subarray
    merge_array = (int*) calloc(size, sizeof(int));
    i = low;
    j = mid;
    for (k=0; k<size; ++k) {
        if (i == mid) {
	    merge_array[k] = values[j];
	    ++j;
        }
        else if (j == high) {
	    merge_array[k] = values[i];
	    ++i;
        }
        else if (values[j] < values[i]) {
	    merge_array[k] = values[j];
	    ++j;
        }
        else {
	    merge_array[k] = values[i];
	    ++i;
        }
    }
   
    // Array is now merged and sorted. Copy the sorted values into the correct position of the original array
    for (k=0; k<size; ++k) {
        values[low + k] = merge_array[k];
    }
    // Free the temporary array
    free(merge_array);
}

// Merge Sort - Implementation source: http://www.sanfoundry.com/java-program-implement-merge-sort/
void mergesort(int size, int values[]) {
    mergesorthelper(values, 0, size);
}

