#include <stdlib.h>
#include "myqsort.h"
#include "assert.h"
#include "time.h"
#include <stdio.h>


const int TEST_COUNT = 100;
int FAIL_COUNT = 0;

int n; double *array;


double * get_random_array(int *size){
	*size = rand();
	double *arr = (double *) malloc((*size) * sizeof(double));
	for(int i=0; i < (*size); i++){
		arr[i] = (double) rand();
	}
	return arr;
}


int test_sort_rand_array(){
	array = get_random_array(&n);

	myqsort(array, 0, n-1);

	for(int i=1; i<n; i++){
		if (array[i] < array[i-1]){
			return 1;
		}
	}

	return 0;
}


int main(){

	srand(time(NULL));

	for(int i=0; i < TEST_COUNT; i++){
		FAIL_COUNT += test_sort_rand_array();
	}
	
	printf("PASSED %d OF %d TESTS\n", (TEST_COUNT - FAIL_COUNT), TEST_COUNT);

	free(array);

	return 0;
}