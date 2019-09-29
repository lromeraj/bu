#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_LEN 50

int prim( int );
int gtPrim( int );
int minD( int );

char encode(char,int);
char decode(char,int);

int main() {

  int key;

  char str[MAX_LEN] = {}; // original
  char stren[MAX_LEN] = {}; // encoded
  char strde[MAX_LEN] = {}; // decoded => original

  printf("Introduce la clave de cifrado: ");
  scanf("%d",&key);

  printf("Introduce una palabra: ");
  scanf("%s",str);

  for (int i=0; i<(int)strlen( str ); i++) {
    stren[ i ] = encode( str[i], key );
    stren[ i+1 ] = 0;
  }

  for (int i=0; i<(int)strlen( stren ); i++ ) {
    strde[ i ] = decode( stren[ i ], key );
    strde[ i+1 ] = 0;
  }

  printf("Encoded: %s\n",stren);
  printf("Decoded: %s",strde);

  return 0;
}

char encode( char a, int key ) {
  return (a+key)%256;
}

char decode( char a, int key ) {
  return (a-key)%256;
}

int minD( int a ) {

  int min;

  for ( int i=2; i<=a; i++) {
    if (!(a%i)) {
      min=i;
      break;
    }
  }

  return min;

}


int gtPrim( int a ) {

  int p;

  for (int i=0; i<=a; i++) {
    p = prim( i ) ? i : p;
  }

  return p;

}

int prim( int a ) {

  int i=2;
  int is=1;

  is = a < 2 ? 0 : 1;

  for (;i<=sqrt( a ); i++) {
    if (!(a%i)) {
      is=0;
      break;
    }
  }

  return is;

}
