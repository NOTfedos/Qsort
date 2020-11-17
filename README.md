# Qsort

Учебный проект. Предназначен для демонстрации работы алгоритма быстрой сортировки Хоара. Реализован на языке C. 
Сортирует массив строк.

## Как запустить сортировку данных из файла

1. Компилируем файл **visual.c**: `gcc src/visual.c src/myqsort.c -o bin/visual`
2. Запускаем `cd ./bin && visual [OPTIONS]`: 
```
  -generate           генерирует рандомно массив в файл `datafiles/input.txt`
                      и сортирует его в файл `datafiles/output.txt`
  -input [filename]   указывает название файла из которого нужно считать массив
                      (обязан быть расположен в папке `datafiles/`)
  -output [filename]  указывает название файла, в который нужно записать отсортированный массив
                      (будет расположен в `datafiles/`)
```

## Формат входных и выходных данных

`ЧИСЛО СЛОВ` `ДЛИНА СЛОВА` `СЛОВО 1` `СЛОВО 2` `СЛОВО 3`...

## Тестирование правильности сортировки

1. Компилируем файл **test_myqsort.c**: `gcc src/test_myqsort.c src/myqsort.c -o bin/test_myqsort`
2. Запускаем `cd ./bin && test_myqsort`



(c) Клиентов Григорий, 2020
