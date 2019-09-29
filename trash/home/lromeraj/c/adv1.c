#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define SIZE 100

typedef struct {
  long base;
  char sn[SIZE];
} Number;

long toDec(Number *n) {

  int i, j;
  long dec;

  for (i=strlen(n->sn)-1, dec=0, j=1; i>=0; i--, j*=n->base) {

    char c = n->sn[i];

    if (c >= '0' && c <= '9') {
      c-='0';
    } else if ( c >= 'A' && c <= 'F' )  {
      c-='A'-10;
    } else if ( c >= 'a' && c <= 'f' ) {
      c-='a'-10;
    }

    dec+=c*j;
  }

  return dec;
}

short decToBase(long dec, Number *n) {

  int i, r, len;

  if ( n->base <= 0 || dec < 0 || !n ) return 1;

  for (i=0; dec>0; dec/=(n->base), i++) {

    if (i>=SIZE) return 2;

    r=dec%(n->base);

    if (r<10) {
      n->sn[i] = r+'0';
    } else {
      n->sn[i] = r+'A'-10;
    }

  }

  n->sn[i] = 0;

  len = i;

  for (len=i, i=len-1; i>=len/2; i--) {

    int to = len-1-i;
    char temp = n->sn[to];
    n->sn[to] = n->sn[i];
    n->sn[i] = temp;

  }

  return 0;
}

int main() {

  Number n1, n2;

  printf("Introduce una base: ");
  scanf("%ld",&n1.base);
  printf("Introduce un número en base %ld: ",n1.base);
  scanf("%s",n1.sn);

  printf("Convert %s in base %ld to base: ",n1.sn,n1.base);
  scanf("%ld",&n2.base);

  long n1dec = toDec( &n1 );

  decToBase( n1dec, &n2 );

  printf("%s\n",n2.sn);

  return 0;
}
