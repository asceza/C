#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // COORD

#define LENGTH 390

char arr[LENGTH];


void init(void) {
    SetConsoleOutputCP(437); //Code page 437
    srand(time(NULL)); // current time as a seed
}


void generate_arr(void) {
    for (int i = 0; i < LENGTH; ++i) {
        arr[i] = ' ';
    }
}


void print_arr(void) {
    int count = 0;
    for (int i = 0; i < LENGTH; ++i) {
    printf("%c", arr[i]);
        if (count == 0) {
            count++;
            continue;
        }
        count++;
        if (count%30 == 0) {
            printf("\n");
        }
    }
}


void add_element(void) {
    int rand_elem = rand()%LENGTH; // 0..(LENGTH-1) include
    if (arr[rand_elem] == ' ') {
        arr[rand_elem] = 176;
    } else if (arr[rand_elem] == (char)176) {
        arr[rand_elem] = 177;
    } else if (arr[rand_elem] == (char)177) {
        arr[rand_elem] = 178;
    } else if (arr[rand_elem] == (char)178) {
        arr[rand_elem] = 219;
    }
}


void clear_screen(void) {
    // set cursor to 0,0 coord
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // send coord to poiner our window
    // you can change cursor color in preferences
    // your CMD to make it less noticeable
}


int main() {
    init();
    generate_arr();
    while (1) {
        add_element();
        print_arr();
        //usleep(100000);
        clear_screen();
    }
    return 0;
}
