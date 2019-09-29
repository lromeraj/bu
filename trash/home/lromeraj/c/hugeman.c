#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORD_LEN 30
#define VOC_LEN 8
#define MAX_FAILS 5

int aleat(int a, int b) {
	return (int) (a + (double) rand() / (RAND_MAX-1) * (b - a + 1));
}

int indexOf( char c, char str[] ) {

	int a = -1;

	for (int i=0; i < (int)strlen(str); i++) {
		if ( str[i] == c) {
			a = i;
			break;
		}
	}

	return a;
}

int main() {

	srand((unsigned) time(NULL));

	const char voc[VOC_LEN][WORD_LEN] = {"pepito","casa","ordenador","atom","pc","karatee","tecla","bicho"};
	char word[WORD_LEN] = "", temp[WORD_LEN] = "";
	int wordLen;
	char used[20] = "";

	strcpy( word, voc[ aleat( 0, VOC_LEN ) ] );

	wordLen = strlen( word );

	int fails = 0, oldCmp = strcmp(word, temp);

	while ( strcmp(word, temp) && fails < MAX_FAILS ) {

		char c;

		printf("Introduce un caracter: ");
		scanf("%c", &c);

		int idx = indexOf( c, used ), append = 0;

		getchar();

		for (int i=0; i<wordLen; i++ ) {

			if (c == word[i]) {
				temp[i] = c;
				if (idx == -1) append = 1;
			} else if ( !temp[i] ) {
				temp[i] = '_';
			}

		}

		if (idx==-1) {
			used[ strlen( used ) ] = c;
			if (!append) {
				fails++;
			}
		}

		printf("Has usado: %s | ",used);
		printf("Averiguado: %s | ",temp);
		printf("Fallos: %d de %d ",fails, MAX_FAILS);

		printf("\n");
	}

}
