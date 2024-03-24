#include <stdio.h>

int main() {
    int number = 19; //число в десятичной системе
    int binary_array[20]; //массив битов
    int i = 0; //счетчик

    while(number){ //цикл пока num не равен 0
        binary_array[i] = number%2; // num%2 даст одну цифру двоичного числа
        number = number/2; //разделите число на 2, чтобы получить следующую цифру двоичного числа
        i++; //инкрементируем счетчик
    }

    while(i--) { //итерация по массиву в обратном порядке
        printf("%d", binary_array[i]);
    }
    return 0;
}
