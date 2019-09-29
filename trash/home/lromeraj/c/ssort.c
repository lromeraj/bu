#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* sort( int*, int, int );

void swap( int*, int* );


void swap( int *a, int *b ) {

  int temp;

  temp = *a;
  *a = *b;
  *b = temp;
}

int* ssort( int *arr, int f, int t ) {
  // select sort algorithm

  int i;

  while ( f < t ) {

    for (i=f+1; i < t; i++ ) {
      if ( arr[ i ] < arr[ f ] ) {
        swap( &arr[ i ], &arr[ f ] );
      }
    }

    f++;
  }

  return NULL;
}


void parr( int *arr, int size ) {

  int i;

  for (i=0; i < size; i++ ) {

    printf( "%d", arr[ i ] );

    if ( i < size-1 ) {
      printf(", ");
    }

  }

  printf("\n");

}

int main( int argc, char *argv[] ) {

  int i, *arr;
  int n, from, to;
  srand( time(NULL) );


  if ( argc < 4 )  {
    fprintf( stderr, "too few args\n" );
    return 1;

  }

  n = atoi( argv[1] );
  from = atoi( argv[2] );
  to = atoi( argv[3] );

  arr = (int*) calloc( n, sizeof(int) );

  // fill array with random numbers
  for ( i=0; i<n; i++ ) {
    arr[ i ] = rand()%100;
  }

  parr( arr, n );
  ssort( arr, 0, n );

  parr( arr, n );


}
