#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // содержит функцию getch()

#define KEY_UP  72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT  77
#define KEY_ESCAPE 27

int main()
{
    char mas[10][21]; // создаем массив, можно представить как десять строк по 20 символов (плюс символ конца строки)
    int i; // иттератор
    int x = 10, y = 5; // координаты ячейки с собакой
    int ox, oy; // координаты собаки до перемещения
    char key; // переменная хранит нажатый символ
    int ax = 5, ay = 7; // координаты яблока
    srand(time(NULL)); // задaем последовательность псевдослучайных чисел
    int score = 0;

    do
    {
         /*Отрисовка поля*/
        sprintf(mas[0], "--------------------"); // записать символы первой строки

        for (i = 1; i < 9; i++) // строки 2..9
        {
            sprintf(mas[i], "|                  |");
        }

        sprintf(mas[9], "--------------------"); // записать символы последней строки

        mas[y][x] = '@'; // поместим собаку в локацию, y - первая координата (строки)
        mas[ay][ax] = 'o'; // поместим яблоко
        /*Конец: Отрисовка поля*/

        system("cls"); // очищаем экран

        for (i=0; i < 10; i++)
        {
            printf("%s\n", mas[i]); // выводим каждую строку
        }
        printf("    score = %d\n", score);
        printf("--------------------\n");
        printf("'Escape' for quit");

        key = getch(); // ожидает нажатие клавиши и сразу возвращает символ

        // до перемещения запищем текущие координаты
        ox = x;
        oy = y;

        if (key == KEY_UP) y--;
        if (key == KEY_DOWN) y++;
        if (key == KEY_LEFT) x--;
        if (key == KEY_RIGHT) x++;

        /*Реакция на касание стены*/
        // если символ координат собаки равны символу стены, то вернутся на предыдущий шаг
        if (mas[y][x] == '-' || mas[y][x] == '|' )
        {
            x = ox;
            y = oy;
        }
        /*Конец: Реакция на касание стены*/

        /*Реакция на касание яблоки*/
        // если символ координат собаки равен символу яблоку
        if (mas[y][x] == 'o') // можно if ((x == ax) && (y == ay))
        {
            score++;

             // функция rand() генерирует  случайное число от 0..RAND_MAX -> 0..18-> прибавляя 1 -> 0..19
             // один из операндов = 1.0, это нужно чтобы было не целочисленное вычисления, а вещественное
             // и далее происходит не явное преобразование к целочисленной координате путем отбасывания дробной части
            ax = rand() * 1.0 / RAND_MAX * 18 + 1;
            ay = rand() * 1.0 / RAND_MAX * 8 + 1;
        }
         /*Конец: Реакция на касание яблоки*/

    }
    while (key != KEY_ESCAPE);

    return 0;
}

/* TODO
- Указание имени игрока передачей аргумента при запуске
- Добавить истекающее время игры (например: 30 с)
- Добавить запись очков/имени игрока  в файл
*/
