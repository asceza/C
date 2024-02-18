#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 20 //длина массива
#define MAX_NUMBER 70 //максимальное число в массиве


void init_array(int *array) {
    srand(time(NULL)); //текущее время в качестве начального значения
    for (int i = 0; i < LENGTH; i++) {
        int r = rand()%MAX_NUMBER + 1; //псевдослучайное число 0..(MAX_NUMBER-1)
        array[i] = r;
    }
}

//вывод в консоль звездочки одной строки
void print_stars(int *c) {
    for (int i = 0; i < *c; i++) printf("*");
    printf("\n");
}

//вывод в консоль массива в обратном порядке (по строчно)
void print_array(int *array) {
    system("cls");
    for (int i = LENGTH - 1; i >= 0; i--) {
        printf("%2d ", array[i]);
        print_stars(&array[i]);
    }
}


void bubble_sort(int *array) {
    _Bool is_swap = 1; //были перестановки?
    int max = 0; //чтобы исключить сравнение с уже поднятыми числами
    while (is_swap != 0) {
        is_swap = 0;
        for (int i = 0; i < LENGTH - 1 - max; i++) {
            if (array[i] > array[i + 1]) {
                int tmp = array[i]; //временная переменная
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                is_swap = 1;
                print_array(array);
                usleep(100000); //пауза для визуализации
            }
        }
        max++;
    }
}


int main() {
    int array[LENGTH] = {0};
    init_array(array);
    print_array(array);

    bubble_sort(array);
}
