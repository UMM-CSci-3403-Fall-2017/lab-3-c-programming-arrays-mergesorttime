#include <stdlib.h>
#include <stdio.h>
#include "mergesort.h"

void mergesort(int size, int values[]) {
    
    void mergesorthelper(int values[], int low, int high) {
	int* merge_array;
	int size, mid, i, j, k;	

	size = high - low;
	if (size =< 1) {
	    return;
	}

	mid = low + size / 2;

	sort(values, low, mid);
	sort(values, mid, high);

	merge_array = (int*) calloc(size, sizeof(int));
	i = low;
	j = mid;
	for (k=0; k < size; ++k) {
	    if (i == mid) {
	    	merge_array[k] = values[++j];
	    }
	    else if (j == high) {
	    	merge_array[k] = values[++i];
	    }
	    else if (values[j] < values[i]) {
	    	merge_array[k] = values[++j];
	    }
	    else {
	    	merge_array[k] = values[++i];
	    }
	}

	for (k = 0; k < size; ++k) {
	    values[low + k] = merge_array[k];
	}

	for (k = 0; k < size; ++k) {
	    values[k] = merge_array[k];
	}

	free(merge_array);
    }

    mergesorthelper(values, 0, size);
}
