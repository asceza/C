#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // добавляет возможность вывода русских символов

// статусы экрана
#define ADD_PERSON         100
#define DELETE_PERSON      200
#define PRINT_PHONE_BOOK   300

// коды клавиш
#define F1                  59
#define F2                  60
#define F3                  61
#define ESCAPE              27
#define DOWN                80
#define UP                  72
#define DELETE              83

#define PRINT_LINE printf("----------------------------------------------------------------------------------------------\n");

// кол-во записей
#define ARR_LENGTH           5


char key;
unsigned int statement = 0;
unsigned int current_person_for_add = 0;
int current_person_for_delete = 0;
_Bool exit_status = 0;

struct person {
    char name[30];
    char surname[30];
    char phone_number[30];
};

struct person phone_book[ARR_LENGTH]; // массив структур

void print_main_header(void) {
    printf("\t\t\t\t\tТелефонная книга\n");
    printf("(F1) - Нов. запись    ");
    printf("(F2) - Стереть сущ. запись    ");
    printf("(F3) - Все записи    ");
    printf("(ESC) - Выход\n");
    PRINT_LINE
}

void print_sub_header(void) {
    switch(statement) {
    case ADD_PERSON:
        printf("\tМеню добавления\n");
        break;
    case DELETE_PERSON:
        printf("\tВыберите контакт для удаления (вверх/вниз) и (Delete) для удаления\n");
        break;
    case PRINT_PHONE_BOOK:
        printf("\tМеню отображения\n");
        break;
    default:
        printf("\n");
    }
    PRINT_LINE
}

void add_person() {
    printf("Введите имя: ");
    char name[30];
    scanf("%s", &name);

    printf("Введите фамилию: ");
    char surname[30];
    scanf("%s", &surname);

    printf("Введите номер телефона: ");
    char phone_number[30];
    scanf("%s", &phone_number);

    // обращение к текущему элементу
    sprintf(phone_book[current_person_for_add].name, name); // присвоить строку всему массиву, адрес не указывается, т.к. пременная массива уже содержит адрес памяти
    sprintf(phone_book[current_person_for_add].surname, surname);
    sprintf(phone_book[current_person_for_add].phone_number, phone_number);
    printf("\t-> Запись создана");
    statement = PRINT_PHONE_BOOK;
}

void print_delete_current_person() {
     printf("name: %s\nsurname: %s\nnumber: %s\n", phone_book[current_person_for_delete].name,
            phone_book[current_person_for_delete].surname, phone_book[current_person_for_delete].phone_number);
}

void print_all_persons() {
    int n = sizeof(phone_book)/sizeof(phone_book[0]);
    for (int i = 0; i < n; ++i) {
        printf("name: %s\nsurname: %s\nnumber: %s\n", phone_book[i].name, phone_book[i].surname, phone_book[i].phone_number);
        printf("--------------------\n");
    }
}

void set_statement(int *p_statement, char k) {
    if (k == F1) *p_statement = ADD_PERSON;
    if (k == F2) *p_statement = DELETE_PERSON;
    if (k == F3) *p_statement = PRINT_PHONE_BOOK;
    if (k == ESCAPE) exit_status = 1;
}

void print_frame(void) {
    if (statement == ADD_PERSON) add_person();
    else if (statement == DELETE_PERSON) print_delete_current_person();
    else if (statement == PRINT_PHONE_BOOK) print_all_persons();
}

char what_is_the_key(char key) {
    //обработка функциональных клавиш, пропуск ноля
    if(key <= 0) what_is_the_key(getch()); // для F1 = 0 и 59, для DELETE = -32 и 83
    else return key;
}

void set_number_of_current_person_for_add(void) {
    int n = sizeof(phone_book)/sizeof(phone_book[0]);
    for (int i = 0; i < n; ++i) {
        if (strlen(phone_book[i].name) == 0 || strlen(phone_book[i].surname) == 0 || strlen(phone_book[i].phone_number) == 0) {
            //printf("\n%d - свободно", i);
            current_person_for_add = i;
            return 0;
        }
    }
}

void check_free_space_in_phone_book(void) {
    int free_space_count = ARR_LENGTH;
    int n = sizeof(phone_book)/sizeof(phone_book[0]);
    for (int i = 0; i < n; ++i) {
        if (strlen(phone_book[i].name) != 0 || strlen(phone_book[i].surname) != 0 || strlen(phone_book[i].phone_number) != 0) {
            free_space_count--;
        }
    }
    printf("\n\t-> Свободно %d яч. памяти", free_space_count);
    if (free_space_count < 1) printf(" НЕ ХВАТАЕТ МЕСТА, УДАЛИТЕ ОДНУ ИЗ ЗАПИСЕЙ");
}

int main() {
    system("chcp 1251");
    setlocale(0, "Russian"); // добавляем возможность вывода русских символов
    while (!exit_status) {
        system("cls");
        print_main_header();
        print_sub_header();
        print_frame();

        set_number_of_current_person_for_add();
        printf("\n\t-> Номер текущей яч. для записи = %d", current_person_for_add);
        check_free_space_in_phone_book();

        key = what_is_the_key(getch());
        set_statement(&statement, key);

        // обработка удаления персоны //
        if (statement == DELETE_PERSON && key == DOWN) {
            current_person_for_delete++;
            if (current_person_for_delete >= ARR_LENGTH) current_person_for_delete = ARR_LENGTH - 1;
        }

        if (statement == DELETE_PERSON && key == UP) {
            current_person_for_delete--;
            if (current_person_for_delete < 0) current_person_for_delete = 0;
        }

        if (statement == DELETE_PERSON && key == DELETE) {
            sprintf(phone_book[current_person_for_delete].name, "");
            sprintf(phone_book[current_person_for_delete].surname, "");
            sprintf(phone_book[current_person_for_delete].phone_number, "");
        }
        // конец обработка удаления персоны //

    }
    return 0;
}
