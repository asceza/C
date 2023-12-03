/* https://www.youtube.com/shorts/pw1WY1pOAoc */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 20
#define MAX_NUMBER 70

int A[LENGTH] = {0};

void init_array(int *A) {
    srand(time(NULL)); // current time as a seed
    for (int i = 0; i < LENGTH; i++) {
        int r = rand()%MAX_NUMBER; // random numbers between 0..(MAX_NUMBER-1)
        A[i] = r;
    }
}

// add stars to each lines
void print_stars(int c) {
    for (int i = 0; i < c; i++) printf("*");
}

// print in reverse order
void print_array(int *A) {
    system("cls");
    for (int i = LENGTH - 1; i >= 0; i--) {
        printf("%2d ", A[i]);
        print_stars(A[i]);
        printf("\n");
    }
    usleep(100000); // pause for visual dynamics
}


void bubble_sort(int *A) {
    _Bool flag = 1; // was there a change in array?
    int max = 0; // exclude comparison with raised numbers
    while (flag != 0) {
        flag = 0;
        for (int i = 0; i < LENGTH - 1 - max; i++) {
            if (A[i] > A[i + 1]) {
                int tmp = A[i]; // temporary buffer variable
                A[i] = A[i + 1];
                A[i + 1] = tmp;
                flag = 1;
                print_array(A);
            }
        }
        max++;
    }
}


int main() {
    init_array(A);
    print_array(A);
    bubble_sort(A);
}
