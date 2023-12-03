#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // COORD

#define N 40

char text[N] = {0};

void print_array(char text[]) {
    for (int i = 0; i < N; ++i) {
        printf("%c", text[i]);
    }
    printf("\n");
}

void shift_array(char text[]) {
    // <- cyclic shift of array to the left
    int tmp = text[0];
    for (int i = 0; i < strlen(text) - 1; ++i) {
        text[i] = text[i + 1];
    }
    text[strlen(text) - 1] = tmp;
}



void clear_screen(void) {
    // set cursor to 0,0 coord
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    // send coord to pointer our window
    // you can change cursor color in preferences
    // your CMD to make it less noticeable
}



int main() {
    scanf("%40[^\n]", &text);

    while (1) {
        clear_screen();
        shift_array(text);
        print_array(text);
        usleep(100000);
    }
    return 0;
}
