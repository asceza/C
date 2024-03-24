#include <stdio.h>
#define LENGTH 8

int main() {
    int number = 19; //число в десятичной системе
    int binary_array[LENGTH] = {0};
    for (int i = 0; i < LENGTH; i++) {
        binary_array[i] = (number >> i) & 1;
    }

    printf("direct order  - ");
    for (int i = 0; i < LENGTH; i++) {
        printf("%d", binary_array[i]);
    }

    printf("\nreverse order - ");
    for (int i = LENGTH - 1; i >= 0; i--) {
        printf("%d", binary_array[i]);
    }

    return 0;
}
