#include <stdio.h>
#include <stdlib.h>

#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_ENTER   13
#define KEY_RIGHT   77
#define KEY_LEFT    75
#define KEY_ESCAPE  27


char key; //текущая нажатая клавиша
int current_menu_paragraph = 0; //текущий пункт меню


struct MENU {
    char list[5][20]; //массив строк [не более 5 строк][не более 19 символов + '\0']
    int amount_of_paragraph; //длина списка
    char menu_name[20]; //название меню
};


struct MENU MAIN_MENU = {
    .list = {"MENU_A", "MENU_B", "MENU_C"},
    .amount_of_paragraph = 3,
    .menu_name = "MAIN_MENU"
};


struct MENU MENU_A = {
    .list = {"MENU_A1", "MENU_A2", "MENU_A3"},
    .amount_of_paragraph = 3,
    .menu_name = "MENU_A"
};


struct MENU MENU_B = {
    .list = {"MENU_B1", "MENU_B2", "MENU_B3", "MENU_B4"},
    .amount_of_paragraph = 4,
    .menu_name = "MENU_B"
};


struct MENU MENU_C = {
    .list = {"MENU_C1", "MENU_C2"},
    .amount_of_paragraph = 2,
    .menu_name = "MENU_C"
};


struct MENU *current_menu = &MAIN_MENU; //указатель на текущее меню


void print_current_menu (void) {
    //печатать текущее меню
    system("cls");
    printf("\t\t\t%s\n\n", current_menu->menu_name);
    for (int i = 0; i < current_menu->amount_of_paragraph; ++i) {
        if (i == current_menu_paragraph) {
            printf("-> ");
        }
        printf("%s\n", current_menu->list[i]);
    }
}


void key_processing(char key) {
    //обработать нажатие клавиши
    if (key == KEY_DOWN) {
        current_menu_paragraph++;
        if (current_menu_paragraph >= (current_menu->amount_of_paragraph)) {
            current_menu_paragraph = current_menu->amount_of_paragraph - 1;
        }
    }

    if (key == KEY_UP) {
        current_menu_paragraph--;
        if (current_menu_paragraph < 0) {
            current_menu_paragraph = 0;
        }
    }

    if (key == KEY_RIGHT) {
        set_current_menu(KEY_RIGHT);
    }

    if (key == KEY_LEFT) {
        set_current_menu(KEY_LEFT);
    }
}


void set_current_menu(int key) {
    //устанавить текущее меню
    if (key == KEY_RIGHT){
        if (current_menu == &MAIN_MENU && current_menu_paragraph == 0) {
            current_menu = &MENU_A;
        }

        if (current_menu == &MAIN_MENU && current_menu_paragraph == 1) {
            current_menu = &MENU_B;
        }

        if (current_menu == &MAIN_MENU && current_menu_paragraph == 2) {
            current_menu = &MENU_C;
        }
    }

    if (key == KEY_LEFT){
        if (current_menu == &MENU_A || current_menu == &MENU_B || current_menu == &MENU_C) {
            current_menu = &MAIN_MENU;
        }
    }
    current_menu_paragraph = 0;
}


int main() {
    do {
        print_current_menu();
        key = getch(); // ожидает нажатие клавиши и сразу возвращает символ
        key_processing(key);
    } while(key != KEY_ESCAPE);

    return 0;
}
