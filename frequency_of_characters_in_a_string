#include <stdio.h>

char str[100];
int i;
int freq[256] = {0}; // index is character code


void calculate_frequency(void) {
    // as the character is not zero
	for (i = 0; str[i] != '\0'; i++) {
		freq[str[i]]++; // add 1 time
	}
}


void print_result(void) {
	for (i = 0; i < 256; i++) {
		if (freq[i] != 0) { // print only used characters
			printf("\t'%c' = %d\n", i, freq[i]);
		}
	}
}

int main() {
	printf("Your string: ");
	scanf("%100[^\n]",&str);

    calculate_frequency();
    print_result();
	return 0;
}
