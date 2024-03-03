#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define WIDTH 640
#define HEIGH 480

#pragma pack(push, 1)

// Структура заголовка файла BMP (14 байт)
typedef struct {
    char signature[2]; //Сигнатура файла (2 байта) - обычно "BM" (0x42 0x4D)
    unsigned int fileSize; //Размер файла (4 байта) - размер всего файла в байтах
    unsigned int reserved; //Зарезервированное поле (4 байта) - обычно равно 0
    unsigned int dataOffset; //Смещение данных (4 байта) - смещение, с которого начинаются данные изображения
} BMPHeader;

// Структура заголовка информации BMP (40 байт)
typedef struct {
    unsigned int headerSize; //Размер заголовка информации (4 байта) - обычно равен 40
    int width; //Ширина изображения в пикселях (4 байта)
    int height; //Высота изображения в пикселях (4 байта)
    unsigned short planes; //Количество плоскостей (2 байта) - обычно равно 1
    unsigned short bitsPerPixel; //Глубина цвета (2 байта) - количество бит на пиксель
    unsigned int compression; //Сжатие (4 байта) - обычно 0 для несжатого изображения

    //Размер секции пиксельных данных (4 байта)
    //Если изображение несжато (то есть предыдущее поле установлено в 0), то здесь должен быть записан ноль
    unsigned int imageSize;

    int xResolution; //Горизонтальное разрешение (4 байта) - количество пикселей на метр по горизонтали
    int yResolution; //Вертикальное разрешение (4 байта) - количество пикселей на метр по вертикали

    unsigned int colorsUsed; //Количество используемых цветов (4 байта) - 0 для максимально возможного количества цветов

    //Это количество важных цветов.
    //Если это значение равно 0 (как это обычно и бывает), то все цвета считаются важными
    unsigned int importantColors;
} BMPInfoHeader;

#pragma pack(pop)


void generate_image_data (FILE *file) {
    //Генерируем случайные данные для заполнения изображения
    uint8_t data[WIDTH * HEIGH * 3]; //Ширина * высота * количество каналов цвета
    uint8_t color = 0;
    uint8_t a = 0;
    //printf ("%d", sizeof(data));
    for (int i = 0; i < sizeof(data); i+=3) {

     if (i%(WIDTH*37) <= rand() % 1200) {
        data[i] = a*(42&color>>1);
        data[i+1] = a*(2&color>>1);
        data[i+2] = a*(42&color>>1);
        }
        else {
         if (i%9876 == 0) {
                a+=(rand() % 50);
                color +=rand() % 8;
            }

         if (i%11 == 0) {
                a+=27;
                color +=rand() % 12;
            }

         if (i%888 < 50) {
                a+=180;
                color +=99;
            }

            data[i] = 0;
            data[i+1] = 0;
            data[i+2] = 0;
        }

    }


    for (int i = 0; i < (sizeof(data)/7) * 5; i+=3) {

     if (i%(WIDTH*3) <= rand() % 2000) {
        data[i] = color*(a<<2*((color>>2)|(a>>2))&(20|5>>a|(color<<3)));
        data[i+1] = (color>>6|color|a>>(color>>16))*10+((a>>11)&7);
        data[i+2] = 11|(color&data[i+1] + a<<2);
        }
        else {
         if (i%9876 == 0) {
                a+=(rand() % 50);
                color +=rand() % 8;
            }

         if (i%11 == 0) {
                a+=27;
                color +=rand() % 12;
            }

         if (i%888 < 50) {
                a+=180;
                color +=99;
            }

        data[i] = (((color*9)&(a>>4))|(color*5&a>>7)|(a*3&color/1024)-1);
        data[i+1] = color>>10&data[i] - a*4;
        data[i+2] = (data[i+2] & 12) + 71;
        }
    }

    // Записываем данные изображения в файл
    fwrite(data, sizeof(data), 1, file);
}





int main() {
    //Создаем и заполняем заголовок файла BMP
    BMPHeader header = {{'B', 'M'}, sizeof(BMPHeader) + sizeof(BMPInfoHeader),
    0, sizeof(BMPHeader) + sizeof(BMPInfoHeader)};

    //printf ("%d", sizeof(BMPHeader));

    //Создаем и заполняем заголовок информации BMP
    BMPInfoHeader infoHeader = { sizeof(BMPInfoHeader), WIDTH, HEIGH, 1, 24, 0, 0, 2755, 2755, 0, 0 };

    //Создаем файл BMP
    FILE *file = fopen("image.bmp", "wb");

    //Записываем заголовки в файл
    fwrite(&header, sizeof(header), 1, file);
    fwrite(&infoHeader, sizeof(infoHeader), 1, file);

    generate_image_data(file);

    // Закрываем файл
    fclose(file);

    return 0;
}
