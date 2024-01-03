#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define array_length 365
#define people_amount 23


void generate_bithday(int *y) {
    int d = (rand()%array_length); // от 0..(array_length-1) включительно == 0..364
    (*(y + d))++; // равнозначно y[d]++;
}

void print_array(int *y) {
    for (int i = 0; i < array_length; ++i) {
        if (i%7 == 0) printf("\t");
        if (i%28 == 0) printf("\n");
        if (*(y + i) == 0) { //равнозначно y[i]
            printf("-");
        } else {
            printf("%d", *(y + i)); //равнозначно y[i]
        }
    }
}


int main() {
    int year[array_length] = {0};

    srand(time(NULL)); // текущее время в качестве семени seed

    for (int i = 1; i <= people_amount; ++i) {
        //равнозначно generate_bithday(&year[0]); адрес на первый элемент массива
        generate_bithday(year);
    }

    print_array(&year[0]);

    return 0;
}

