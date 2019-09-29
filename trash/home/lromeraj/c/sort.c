#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 5


void printArr( int *arr, int n ) {

	int i;

	for (i=0;i<n;i++) {
		printf( "%d ", arr[i] );
	}

	printf("\n");
}

int main() {

	int temp, i;
	bool chgd = false; // changed
	int *arr;

	arr = (int*) malloc( sizeof(int) * N );

	for (i=0;i<N;i++){
		printf("arr[%d]=", i );
		scanf("%d",&arr[i]);
	}

	printArr( arr, N );

	i=0;
	while (1) {

		if ( i == N ) {

			if ( !chgd ) break;
			i=0;
			chgd=false;
		}

		if ( i < N-1 ) {

			if ( arr[ i ] > arr[ i + 1 ] ) {

				temp = arr[ i ];
				arr[ i ] = arr[ i + 1 ];
				arr[ i + 1 ] = temp;
				chgd=true;
			}
		}

		i++;

	}

	printArr( arr, N );
}
