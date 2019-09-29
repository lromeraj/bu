#include <stdio.h>

void nipnin( int*, int* );

int main() {
  int a , b;

  printf("NS: ");
  scanf("%d %d",&a,&b);

  nipnin(&a,&b);

  printf("%d %d\n",a,b);
  return 0;
}

void nipnin( int *a, int *b ) {
  if ( !((*a+*b)%2) ) (*b)++;
}
