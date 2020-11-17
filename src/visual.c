#include "myqsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdbool.h"
#include "string.h"


void output_array(char **arr, int array_size);


void write_array_to_file(const char *outputFileName, char **array, int array_size, int word_size);


char ** read_array_from_file(const char *inputFileName, int *array_size, int *word_size);


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
	int array_size, word_size; char **array;


	// если указан флаг на генерацию входных данных
	if(toGenerate){
		
		inputFileName = "../datafiles/input.txt";
		outputFileName = "../datafiles/output.txt";
		isRead = 1;
		isWrite = 1;

		// сгенерируем массив
		array = get_random_array(&array_size, &word_size);

		// записываем сгенерированный массив в input файл
		write_array_to_file(inputFileName, array, array_size, word_size);
	}


	// пытаемся прочитать массив из файла
	if (isRead){
		array = read_array_from_file(inputFileName, &array_size, &word_size);
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
	myqsort(array, 0, array_size-1);


	// вывод в файл отсортированного массива
	if(isWrite){
		write_array_to_file(outputFileName, array, array_size, word_size);
		printf("\nSorted Array written into: %s\n", outputFileName);
	}else{
		printf("\nSorted Array is NOT written\n");
	}


	//освобождаем память
	for(int i=0; i < array_size; i++){
	    free(array[i]);
	}
	free(array);


	return 0;
}


void output_array(char **arr, int array_size){
	// вывод одномерного массива(DEBUG ONLY)
	printf("-------------------------------------\n");
	printf("%s\n", "ARRAY IS:");
	for(int i=0; i<array_size; i++){
		printf("%s | ", arr[i]);
	}
	printf("\n");
	printf("-------------------------------------\n");
}


void write_array_to_file(const char *outputFileName, char **array, int array_size, int word_size){
	// выводим массив(отсортированный) в файл


	FILE *outputFile = fopen(outputFileName, "w");


	printf("\nTrying to write into file: %s\n", outputFileName);

	fflush(outputFile);

	fprintf(outputFile, "%d ", array_size);
	fprintf(outputFile, "%d ", word_size);


	for(int i = 0; i < array_size; i++){

	    for(int j = 0; j < word_size; j++){
	        fprintf(outputFile, "%c", array[i][j]);
	    }
	    fprintf(outputFile, "%s ", "");
	}

	fprintf(outputFile, "%s\n", "");
	

	fclose(outputFile);
	printf("\tSuccess\n");

}


char ** read_array_from_file(const char *inputFileName, int *array_size, int *word_size){
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


	// сбрасываем буфер для файла
	fflush(datafile);

	// считываем кол-во элементов массива
	fscanf(datafile, "%d ", array_size);
	fscanf(datafile, "%d ", word_size);

	// выделяем память под массив
	char **array = (char **) malloc((*array_size) * sizeof(char *));
	for(int i=0; i < (*array_size); i++){
		array[i] = (char *) malloc((*word_size) * sizeof(char));
		fscanf(datafile, "%s", array[i]);
	}


	fclose(datafile);

    printf("\tSuccess\n");

	// DEBUG output array
	// output_array(array, *array_size);


	return array;
}