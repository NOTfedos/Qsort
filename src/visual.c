#include "myqsort.h"
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "string.h"
#include "time.h"


void output_array(double *arr, int n);


double * generate_random_array(int *n);


void write_array_to_file(const char *outputFileName, double *array, int n);


double * read_array_from_file(const char *inputFileName, int *n);


int main(int argc, char **argv){

	bool isRead = 0, isWrite = 0, toGenerate = 0;
	char *inputFileName, *outputFileName;


	// обрабатываем аргументы командной строки
	for(int i=1; i < argc; i++){ 

		if (!strcmp(argv[i], "-input") && !isRead){
			if (i < (argc - 1)){
				inputFileName = argv[i+1];
				isRead = 1;
			}
		}


		if (!strcmp(argv[i], "-output") && !isWrite){
			if (i < (argc - 1)){
				outputFileName = argv[i+1];
				isWrite = 1;
			}
		}

		if (!strcmp(argv[i], "-generate") && !toGenerate){
			toGenerate = 1;
		}

	}


	// данные нашего исходного массива(нуждающегося в сортировке)
	int n; double *array;


	// если указан флаг на генерацию входных данных
	if(toGenerate){
		
		inputFileName = "../datafiles/input.txt";
		outputFileName = "../datafiles/output.txt";
		isRead = 1;
		isWrite = 1;

		array = generate_random_array(&n);

		write_array_to_file(inputFileName, array, n);
	}


	// пытаемся прочитать массив из файла
	if (isRead){
		array = read_array_from_file(inputFileName, &n);
		if (array == NULL){
			free(array);
			printf("\t\tSome error while reading array from file\n");
			return 0;
		}
	}else{ 
		printf("No input files\n");
		free(array);
		return 0;
	}


	// сортируем массив
	myqsort(array, 0, n-1);


	// вывод в файл отсортированного массива
	if(isWrite){
		write_array_to_file(outputFileName, array, n);
		printf("\nSorted Array written into: %s\n", outputFileName);
	}else{
		printf("\nSorted Array is NOT written\n");
	}


	//освобождаем память
	free(array); 


	return 0;
}


void output_array(double *arr, int n){
	// вывод одномерного массива(DEBUG ONLY)
	printf("-------------------------------------\n");
	printf("%s\n", "ARRAY IS:");
	for(int i=0; i<n; i++){
		printf("%lf | ", arr[i]);
	}
	printf("\n");
	printf("-------------------------------------\n");
}


double * generate_random_array(int *n){
	srand(time(NULL));

	*n = rand();

	double * arr = (double *) malloc((*n) * sizeof(double));

	for(int i = 0; i < (*n); i++){
		arr[i] = (double) rand();
	}

	return arr;
}


void write_array_to_file(const char *outputFileName, double *array, int n){
	// выводим массив(отсортированный) в файл


	FILE *outputFile = fopen(outputFileName, "w");


	printf("\nTrying to write into file: %s\n", outputFileName);

	fflush(outputFile);
	fprintf(outputFile, "%d ", n);


	for(int i = 0; i < n; i++){
		fprintf(outputFile, "%lf ", array[i]);
	}
	fprintf(outputFile, "%s\n", "");
	

	fclose(outputFile);
	printf("\tSuccess\n");

}


double * read_array_from_file(const char *inputFileName, int *n){
	// считываем одномерный массив из файла
	

	FILE *datafile;


	printf("\nTrying to read file: %s\n", inputFileName);


	// открываем файл
	datafile = fopen(inputFileName, "r"); 
	if (datafile == NULL){ // если файл не существует
		printf("\tCan not open file %s\n", inputFileName);
		fclose(datafile);
		return NULL;
	}


	printf("\tSuccess\n");


	// сбрасываем буфер для файла
	fflush(datafile);
	// считываем кол-во элементов массива
	fscanf(datafile, "%d ", n);


	// выделяем память под массив
	double *array = (double *) malloc((*n) * sizeof(double));
	for(int i=0; i < (*n); i++){
		fscanf(datafile, "%lf ", &array[i]);
	}


	fclose(datafile);


	// DEBUG output array
	// output_array(array, *n);


	return array;
}