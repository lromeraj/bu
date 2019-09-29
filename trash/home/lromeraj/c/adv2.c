#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
  long base;
  char *sn;
} Number;


Number *allocNumber(long);
Number *decToBase(long, long);
Number *convert(Number*, long);
void freeNumber(Number*);
long toDec(Number*);
long nofd(long, long);

int main() {

  Number *n1, *n2;
  long dest_base;

  if ( !(n1 = allocNumber(100)) ) {
    printf("Error storing number 1");
    exit(1);
  }

  printf("Enter a base: "); scanf("%ld",&n1->base);
  printf("Enter number in base %ld: ",n1->base); scanf("%s",n1->sn);

  printf("Convert %s in base %ld to base: ", n1->sn, n1->base); scanf("%ld",&dest_base);

  if ( !(n2 = convert( n1, dest_base )) ) {
    printf("Error while converting");
    exit(1);
  } else {
    printf("%s{%ld} is %s{%ld}\n",n1->sn,n1->base,n2->sn,n2->base);
  }

  return 0;
}

Number *allocNumber( long size ) {

  Number *num = (Number*) calloc( 1, sizeof( Number ) );

  if (!num || size < 0) {
    num = NULL;
  } else {
    if ( !( num->sn = (char*) calloc( size, sizeof(char) ) ) ) {
      num = NULL;
      freeNumber( num );
    }
  }

  return num;
}

Number *decToBase(long dec, long base) {

  int i, r, len;
  Number *n;

  if ( base <= 0 || dec < 0 || !(n = allocNumber( nofd( dec, base ) )) ) {
    n = NULL;
  } else {
    n->base = base; // store dest base in the number

    for (i=0; dec>0; dec/=base, i++) {
      r=dec%base;
      n->sn[i] = r<10 ? r+'0' : r+'A'-10;
    }

    n->sn[i] = 0;

    len = i;

    for (len=i, i=len-1; i>=len/2; i--) {
      int to = len-1-i; char temp = n->sn[to];
      n->sn[to] = n->sn[i];
      n->sn[i] = temp;
    }
  }

  return n;
}

Number *convert(Number *n1, long base) {
  return decToBase( toDec( n1 ), base );
}

void freeNumber( Number *n ) {

  if ( n ) {
    if (n->sn) {
      free( n->sn );
      n->sn = NULL;
    }
    free( n );
    n = NULL;
  }

}

long nofd( long x, long b ) {
  return log(x)/log(b)+1;
}

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
