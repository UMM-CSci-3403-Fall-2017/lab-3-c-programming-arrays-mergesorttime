#include <stdlib.h>
#include "array_merge.h"
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

// Returns true if the element is in the list, false otherwise.
// Start at index 1 since the first element is the size of the array.
bool is_unique(int element, int* values, int size) {
    for (int i=1; i<size; ++i) {
    	if (values[i] == element) {
	    return false;	
	}	
    }
    return true;
}


// Returns an array containing the unsorted unique elements of the 2d array "values"
int* unique_array(int num_arrays, int* sizes, int** values) {
    int* unique_values;
    int i, j, size, current_value, initial_length, final_length, filled_memory, unused_memory;
    
    // Get the inital size of memory needed for the unique_values array.
    // Set the inital size to 1, since the first slot will store the size of the array to be returned.
    initial_length = 1;
    for (i=0; i<num_arrays; ++i) {
    	initial_length += sizes[i];
    }
    
    // Initialize the array
    unique_values = (int*) calloc(initial_length, sizeof(int));
    
    // Loop through each array in values and add all unique elements.
    // Keep track of the current "filled" memory and "unused" memory.
    filled_memory = 1;
    unused_memory = 0;
    for (i=0; i<num_arrays; ++i) {
    	size = sizes[i];
	for (j=0; j<size; ++j) {
	    current_value = values[i][j];
	    if (is_unique(current_value, unique_values, filled_memory)) {
	    	unique_values[filled_memory] = current_value;
		++filled_memory;	
	    }
	    else {
	    	++unused_memory;
	    }
	}
    }
    
    // Free up the unused space for the array, if any.
    final_length = initial_length - unused_memory;
    unique_values = (int*) realloc(unique_values, final_length);

    return (int*) unique_values;

}

int* array_merge(int num_arrays, int* sizes, int** values) {
   int* unique_values = unique_array(num_arrays, sizes, values);
   int* to_sort = (int*) unique_values + 1;
   mergesort(unique_values[0], to_sort);
   return (int*) unique_values;   
}
