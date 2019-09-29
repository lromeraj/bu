#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {

	int n;
	int sum=0;
	int i, j, k;
	int l1, l2, l3;

	l1 = l2 = l3 = 0;

	if ( argc < 2 ) return 1;
	n = atoi( argv[1]);

	for (i=1; i<=n; i++) {

		l1++;

		for (j=0; j<i*i; j++) {

			if ( (j%i) == 0 ) {
				l2++;

				for (k=0; k<j; k++) {
					l3++;
					sum++;
				}

				printf("%d\n", k);

			}

		}

	}

	printf("l1:%d, l2:%d, l3:%d\n", l1, l2, l3 );

}
