#include <stdio.h>
#include <string.h>

#define SIZE 5

/* random record description - could be anything */
struct rec
{
   int x,y,z;
};

/* writes and then reads 10 arbitrary records
  from the file "junk". */
int main()
{

  FILE *f;
  int n, i, j;
  char _buff[ 1024 ];
  char arr[ SIZE ][ 1024 ];

  for (i=0;i<SIZE;i++) {
    sprintf( _buff, "string#%d", i );
    strcpy( arr[ i ], _buff );
  }

  f = fopen( "arr", "wb" );

  for (i=0;i<SIZE;i++) {
    printf( "%d ", (unsigned int)sizeof( arr[ 0 ] ) );
    fwrite( arr[i], sizeof( arr[ i ] ), 1, f );
  }

  fclose( f );

  f = fopen( "arr", "rb" );

  for (i=0;i<SIZE;i++) {
    fread( arr[i], sizeof( arr[i] ), 1, f );
    printf( "%s ", arr[ i ] );
  }

  fclose( f );

  return 0;
}
