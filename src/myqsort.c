#include "myqsort.h"


void swap(double *x, double *y){
	double tmp = *x;
	*x = *y;
	*y = tmp;
}


int partition(double *arr, int start, int end){
	int marker = start;
	for(int i = start; i < end; i++){
		if (arr[i] < arr[end]){ // берём последний элемент за опорный
			swap(&arr[i], &arr[marker]); // убираем в левую часть все элементы, меньшие опорного
			marker++; // увеличиваем вместимость левой части
		}
	}
	swap(&arr[marker], &arr[end]); // меняем опорный элемент на разделитель
	return marker;
}


void myqsort(double *arr, int start, int end){
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