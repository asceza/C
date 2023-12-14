#include <stdio.h>
#include <time.h>

#define MAX_NUMBER 6

int a, b;
int total_drop = 1000000;
int doubles_count = 0;

void drop_dice(int *pa, int *pb) {
    *pa = (rand()%MAX_NUMBER) + 1; // от 0..(MAX_NUMBER-1) включительно
    *pb = (rand()%MAX_NUMBER) + 1;
}

int main() {
    srand(time(NULL)); // текущее время в качестве семени seed
    for (int i = 0; i < total_drop; ++i) {
        drop_dice(&a, &b);
        //printf("%i : %i\n", a, b);

        if (a == 1 && b == 1) {
            doubles_count++;
        }
    }
    printf("total drop = %i\ndoubles = %i\n%.3f%%\n", total_drop, doubles_count,
           ((float)doubles_count/(float)total_drop)*100);

    return 0;
}
