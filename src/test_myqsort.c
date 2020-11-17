#include <stdlib.h>
#include "myqsort.h"
#include "assert.h"
#include "time.h"
#include <stdio.h>
#include <string.h>


const int TEST_COUNT = 100;
int FAIL_COUNT = 0;


int array_size, word_size; char **array;


double * get_random_array(int *size_arr, int *size_word){
	
	// устанавливаем размеры массива
	*size_arr = rand();
	*size_word = (rand() % 10) + 1;

	//выделяем память под весь массив
	char **arr = (double **) malloc((*size) * sizeof(char *));
	
	
	for(int i=0; i < (*size_arr); i++){

		// выделяем память под слово
		arr[i] = (char *) malloc((*size_word) * sizeof(char));
		

		for (int j = 0; j < (*size_word); j++){
			arr[i][j] = (char) rand();
		}

	}
	
	return arr;
}


int test_sort_rand_array(){
	array = get_random_array(&array_size, &word_size);

	myqsort(array, 0, n-1);

	for(int i=1; i<n; i++){
		if (strcmp(array[i], array[i-1]) < 0){
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