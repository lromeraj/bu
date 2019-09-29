#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void func( void *vp );

int main() {
  int a = 4;
  func(&a);
  return 0;
}

void func( void *vp ) {
  printf( "%d\n", *(int*)vp);
}
