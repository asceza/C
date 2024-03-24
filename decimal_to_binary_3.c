#include <stdio.h>
#include <stdlib.h> //для _itoa

int main() {
    int number = 19; //число в десятичной системе
    int binary_array[20]; //массив битов

    //number - указываем число
    //binary_array - указатель на символьный массив, для записи результата
    //2 - система счисления (2, 8, 10, 16)
    _itoa(number, binary_array, 16);
    printf("%s\n", binary_array);

    _itoa(number, binary_array, 10);
    printf("%s\n", binary_array);

    _itoa(number, binary_array, 8);
    printf("%s\n", binary_array);

    _itoa(number, binary_array, 2);
    printf("%s\n", binary_array);

    return 0;
}
