#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addChar(char *str, char a) {
	int len = strlen( str );
	str[len] = a;
	str[len+1] = '\0';
}

int main() {

	char inp[255] = "", oldStr[20] = "";
	char splitter = '+';

 	double sum = 0;

	printf("Set splitter to: ");
	scanf("%c",&splitter);
	getchar();
	printf("Enter input: ");
	fgets(inp,250,stdin);

	printf("Has escrito: %s\n",inp);

	void addSum() {
		sum+=strtod( oldStr, NULL );
		oldStr[0] = '\0';
	}

	for (int i=0; i < 255; i++) {

		char c = inp[i];

		if (c == 0) {
			addSum();
			break;
		}

		if (c == splitter) {
			addSum();
		} else {
			addChar(oldStr,c);
		}
	}

	printf("%.2lf\n",sum);

  return 0;
}
