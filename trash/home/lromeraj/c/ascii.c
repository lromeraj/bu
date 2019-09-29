#include <stdio.h>

#define SIZE 10

int main() {

	char orig[SIZE+1], ces[SIZE+1];

	for (int i=0; i < SIZE; i++) {

		char c;
		printf("Type a char: ");

		scanf(" %c", &c);

		orig[i] = c;
		orig[i+1] = '\0';
		ces[i] = c+3;
		ces[i+1] = '\0';

}

	printf("Original string: %s\n",orig);
	printf("Cesar string: %s\n",ces);

	return 0;
}
