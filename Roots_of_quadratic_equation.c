#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // ��������� ����������� ������ ������� ��������
#include <math.h>

#define PRINT_LINE printf("--------------------------------------------------\n");

float a, b, c, D, x1, x2;


void input_number(int *p, char c) {
    _Bool exit_status = 0;
    int number;
    while (!exit_status) {
        int number_status = scanf("%f", &number);
        fflush(stdin); // ������� ������ ����� (���� �� �����, ������ � ����������� ����)
        if (number_status == 1) {
            *p = number;
            if (a == 0) {
                printf("������� ����� �����, �� ������ ���� � = ");
                input_number(&a, 'a');
            }
            exit_status = 1;
        } else {
            printf("�� ����� �� �����, ���������� ��� ���, %c = ", c);
        }
    }
}


void calculate_d(float *p_D) {
    *p_D = b*b - 4*a*c;
}

void calculate_roots(float *p_x1, float *p_x2) {
    if (D > 0) {
        printf("\n\t������������ D = %.2f", D);
        x1 = (b * (-1) + sqrt(D))/(2 * a);
        x2 = (b * (-1) - sqrt(D))/(2 * a);
        printf("\n\tx1 = %.2f\n\tx2 = %.2f\n", x1, x2);
    } else if (D == 0) {
        printf("\n\t������������ D = %.2f", D);
        x1 = (b * (-1))/(2 * a);
        printf("\n\tx1 = x2 = %.2f\n", x1);
    } else if (D < 0) {
        printf("\n\t������������ D = %.2f", D);
        printf("\n\t�������������� ������ ���\n");
    }
    PRINT_LINE

}


int main() {
    system("chcp 1251");
    setlocale(0, "Russian"); // ��������� ����������� ������ ������� ��������
    system("cls");
    while (1) {
        printf("���������� ��������� ���� ax^2 + bx + c = 0\n");
        printf("������� ����� �����, �� ������ ���� � = ");
        input_number(&a, 'a');
        printf("������� ����� ����� b = ");
        input_number(&b, 'b');
        printf("������� ����� ����� c = ");
        input_number(&c, 'c');
        printf("\ta = %.2f", a);
        printf("\tb = %.2f", b);
        printf("\tc = %.2f", c);
        calculate_d(&D);
        calculate_roots(&x1, &x2);
    }
    return 0;
}

/* 5x^2 - 6x + 1 = 0
 * D = 16
 * x1 = 1
 * x2 = 0.2
 *
 * -9x^2 + 6x - 1 = 0
 * D = 0
 * x1 = x2 = 1/3
 *
 * 3x^2 + 7x - 6 = 0
 * D = 121
 * x1 = 2/3
 * x2 = -3
*/





