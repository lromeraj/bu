#include <stdio.h>
#include <stdlib.h>

int cb( int a ) {

  if ( a < 17 ) {
    a++;
    cb( a );
    printf("%d\n", a );
  }

  return a++;
}

int main() {


  cb( 0 );
  return 0;
}
