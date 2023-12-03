#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define refresh_time 10 // 1 second

clock_t last_time, current_time;
int hour = 0;
int min = 0;
int sec = 0;


void time_increment(int *hour_pntr, int *min_pntr, int *sec_pntr) {
    // accessing variables by pointers
    *sec_pntr +=1;
    if (*sec_pntr > 59) {
        *sec_pntr = 0;
        *min_pntr += 1;
    }
    if (*min_pntr > 59) {
        *min_pntr = 0;
        *hour_pntr += 1;
    }
    if (*hour_pntr > 23) {
        *hour_pntr = 0;
    }
}


int main() {
    system("color 0b"); // console color
    last_time = clock();
    printf("%.2d:%.2d:%.2d", hour, min, sec);

    while (1) {
        current_time = clock();

        if (current_time >= last_time + refresh_time) {
            system("cls"); // clear console

            // passing variable addresses
            time_increment(&hour, &min, &sec);

            printf("%.2d:%.2d:%.2d", hour, min, sec);
            last_time = current_time;
        }
    }
}
