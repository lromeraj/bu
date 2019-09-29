#include <stdio.h>
#include <math.h>

int isPrim( int );

int prims( int, int* );

int main() {

  int to, q = 0;

  do {

    printf("Introduce un entero positivo: ");
    scanf("%d",&to);

  } while ( !prims( to, &q ) );

  printf("El número %d tiene %d primos inferiores",to,q);
  return 0;
}

int prims(int n, int *q) {

  int sts = n < 0 ? 0 : 1; // flag

  int tq = 0; // temp quantity

  if (sts) {

    for (int i=2; i<n; i++) {
      if (isPrim(i)) {
        tq++;
        printf("%d es primo\n",i);
      }
    }

    *q = tq;
  }

  return sts;
}

int isPrim(int a) {

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
