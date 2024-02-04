/*
 * https://m.youtube.com/@my_asceza
 * https://t.me/my_asceza
 * https://vk.com/my_asceza
 * https://github.com/asceza/C
 */

#include <stdio.h>
#include <stdint.h>
#include <windows.h> // для работы с PlaySound()

#define _USE_MATH_DEFINES   // для использования M_PI, перед #include <math.h>
#include <math.h>

#define DURATION    5       //длительность мелодии в секундах
#define AMPLITUDE   32767   //амплитуда - 16 битное значение 0..32767
#define FREQ        110     //частота
#define SAMPLE_RATE 44100   //Частота дискретизации // Частота дискретизации


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
    double k = 0.8; //коэффициент амплитудной модуляции
    double f = 0.1; //коэффициент частотной модуляции
    for (int i = 0; i < h->sampleRate * DURATION; i++) {
        double t = (double)i / h->sampleRate; // время в секундах

        if (i%200 == 0) f += 0.005;
        if (f > 6) f = 0.1;

        //амплитудно-модулированный сигнал
        double carrier = (double)((1 + k * sin(2.0 * M_PI * (FREQ * 4 * f) * t))); //несущая частота
        double signal = (double)(sin(2.0 * M_PI * (FREQ / f) * t)); //полезный сигнал
        int16_t sample = (int16_t)((AMPLITUDE * 0.5) * signal * carrier * exp(-0.8 * t));
        fwrite(&sample, sizeof(sample), 1, file);
    }
}


int main() {
    //открываем файл для записи в бинарном режиме
    FILE *file = fopen("melody.wav", "wb");

    //заполняем заголовок WAV файла
    WavHeader header = {
        .chunkId = "RIFF",
        .chunkSize = 36 + SAMPLE_RATE * DURATION * 2, // Размер файла - 36 байт + размер данных
        .format = "WAVE",
        .subchunk1Id = "fmt ",
        .subchunk1Size = 16,         //размер подчиненного блока
        .audioFormat = 1,            //формат аудио (PCM)
        .numChannels = 1,            //количество каналов (моно)
        .sampleRate = SAMPLE_RATE,   //частота дискретизации
        .byteRate = SAMPLE_RATE * 2, //байт в секунду (SAMPLE_RATE * numChannels * bitsPerSample / 8)
        .blockAlign = 2,             //байт на сэмпл (numChannels * bitsPerSample / 8)
        .bitsPerSample = 16,         //бит на сэмпл
        .subchunk2Id = "data",
        .subchunk2Size = SAMPLE_RATE * DURATION * 2 // Размер данных - SAMPLE_RATE * DURATION * numChannels * bitsPerSample / 8
    };

    //записываем заголовок в файл
    fwrite(&header, sizeof(header), 1, file);

    generate_sound_data(file, &header);

    //закрываем файл
    fclose(file);

        PlaySound("melody.wav", NULL, SND_FILENAME | SND_ASYNC);
        for(int i = DURATION; i >= 0; i--) {
        system("cls"); //очистка консоли
        printf("%d sec", i);
        Sleep(1000); //ожидание 1 сек

    }

    return 0;
}
