#include "myqsort.h"
#include <string.h>
#include <stdlib.h>
#include "time.h"


const char *ALPHABET = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";

char ** get_random_array(int *size_arr, int *size_word){

    srand(time(NULL));

	// устанавливаем размеры массива
	*size_arr = rand();
	*size_word = (rand() % 10) + 1;

	//выделяем память под весь массив
	char **arr = (char **) malloc((*size_arr) * sizeof(char *));
	
	
	for(int i=0; i < (*size_arr); i++){

		// выделяем память под слово
		arr[i] = (char *) malloc((*size_word) * sizeof(char));

		// заполняем каждый символ
		for (int j = 0; j < (*size_word); j++){
			arr[i][j] = ALPHABET[ rand() % (52) ];
		}
	}
	
	return arr;
}



void swap(char **x, char **y){
	char *tmp = *x;
	*x = *y;
	*y = tmp;
}


int partition(char **arr, int start, int end){
	int marker = start;
	
	for(int i = start; i < end; i++){
		
		if ( strcmp(arr[i], arr[end]) < 0 ){ // берём последний элемент за опорный

			swap(&arr[i], &arr[marker]); // убираем в левую часть все элементы, меньшие опорного
			
			marker++; // увеличиваем вместимость левой части
		
		}

	}

	swap(&arr[marker], &arr[end]); // меняем опорный элемент на разделитель
	
	return marker;
}


void myqsort(char **arr, int start, int end){
	/*
		Функция быстрой сортировки массива arr с диапазоном 
		от элемента arr[start] до элемента arr[end].
		Чтобы отсортировать массив полностью, нужно вызвать 
		myqsort(your_array, 0, n-1)  <-  your_array будет отсортирован  
	*/
	
	if (start >= end){
		return;
	}

	int pivot = partition(arr, start, end); // находим опорный элемент
	myqsort(arr, start, pivot-1); // сортируем левую часть
	myqsort(arr, pivot+1, end); // сортируем правую часть
}