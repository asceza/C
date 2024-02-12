/*
 * https://m.youtube.com/@my_asceza
 * https://t.me/my_asceza
 * https://vk.com/my_asceza
 * https://github.com/asceza/C
 */

#include <stdio.h>
#include <stdint.h>
#include <windows.h>        // для работы с PlaySound()
//#include <mmsystem.h>

#define _USE_MATH_DEFINES   // для использования M_PI, перед #include <math.h>
#include <math.h>

#define DURATION    10      //длительность мелодии в секундах
#define SAMPLE_RATE 8000    //Частота дискретизации


//структура для заголовка WAV файла
typedef struct {
    char chunkId[4];
    uint32_t chunkSize;
    char format[4];
    char subchunk1Id[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char subchunk2Id[4];
    uint32_t subchunk2Size;
} WavHeader;


void generate_sound_data(FILE *file, WavHeader *h) {

    //массив для хранения семплов (частей аудиосигнала)
    uint8_t buffer[DURATION * SAMPLE_RATE] = {0};
    uint8_t output = 0;
    uint32_t t = 0, current_sample = 0;

    for(;; t++) {
        output = t*(0xCA98>>(t>>9&14)&15)|t>>8;
        //printf("%d ", output);

        //формируем массив алгоритмом bytebeat
        buffer[current_sample++] = output;

        if (current_sample == DURATION * SAMPLE_RATE - 1) break;
    }
    //записываем семплы в файл
    fwrite(buffer, sizeof(output) * DURATION * SAMPLE_RATE, 1, file);
    //аналогично fwrite(buffer, sizeof(uint8_t), DURATION * SAMPLE_RATE, file);
}


int main() {
    //открываем файл для записи в бинарном режиме
    FILE *file = fopen("melody.wav", "wb");

    //заполняем заголовок WAV файла
    WavHeader header = {
        .chunkId = "RIFF",
        .chunkSize = 36 + SAMPLE_RATE * DURATION, //размер файла - 36 байт + размер данных
        .format = "WAVE",
        .subchunk1Id = "fmt ",
        .subchunk1Size = 16,         //размер подчиненного блока
        .audioFormat = 1,            //формат аудио (PCM)
        .numChannels = 1,            //количество каналов (моно)
        .sampleRate = SAMPLE_RATE,   //частота дискретизации
        .byteRate = SAMPLE_RATE * 2, //байт в секунду (SAMPLE_RATE * numChannels * bitsPerSample / 8)
        .blockAlign = 1,             //байт на сэмпл (numChannels * bitsPerSample / 8)
        .bitsPerSample = 8,         //бит на сэмпл
        .subchunk2Id = "data",
        // Размер данных - SAMPLE_RATE * DURATION * numChannels * bitsPerSample / 8
        .subchunk2Size = SAMPLE_RATE * DURATION
    };

    //записываем заголовок в файл
    fwrite(&header, sizeof(header), 1, file);

    generate_sound_data(file, &header);

    //printf("UINT8_MAX: %d\n", UINT8_MAX); //255

    //закрываем файл
    fclose(file);

    PlaySound("melody.wav", NULL, SND_FILENAME | SND_SYNC);

    return 0;
}
