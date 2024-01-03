#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define array_length 365
#define people_amount 23
#define takes 10000


void generate_bithday(int *y) {
    int d = (rand()%array_length); // от 0..(array_length-1) включительно == 0..364
    (*(y + d))++; // равнозначно y[d]++;
}

void print_array(int *y) {
    for (int i = 0; i < array_length; ++i) {
        if (i%7 == 0) printf("\t");
        if (i%28 == 0) printf("\n");
        if (*(y + i) == 0) { //*(y + i) == y[i]
            printf("0");
        } else {
            printf("%d", *(y + i)); //y[i]
        }
    }
}


void check_coincidence(int *y, int *n) {
    for (int i = 0; i < array_length; ++i) {
            if (*(y + i) > 1) {
                (*n)++;
                break; // прекращаем проверку
            }
        }
}

int main() {
    srand(time(NULL)); // текущее время в качестве семени seed
    int t = 0;
    int number_of_coincidences = 0;

    while (t < takes) {
    int year[array_length] = {0};
        for (int i = 1; i <= people_amount; ++i) {
            generate_bithday(year); //равнозначно generate_bithday(&year[0]);
        }
        //print_array(year);
        check_coincidence(year, &number_of_coincidences);
        ++t;

    }
    printf("\n%d", number_of_coincidences);


    return 0;
}


