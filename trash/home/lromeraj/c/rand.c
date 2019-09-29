#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

typedef int (*random_prototype)( int, int );

int randomBtw( int, int );
void rndBench( int, int, int, random_prototype );

int main( int argc, char *argv[] ) {

  int _N, _min, _max;

  srand( getpid() );

  if ( argc < 4 ) {
    _N = 1000;
    _min = 0, _max = 10;
  } else {
    _N = atoi( argv[1] );
    _min = atoi( argv[2] );
    _max = atoi( argv[3] );
  }

  rndBench( _N, _min, _max, randomBtw );

}


int randomBtw( int min, int max ) {

  double coe;
  int diff, r;

  diff = max - min + 1;
  coe = rand()/(double)RAND_MAX;

  r = diff*coe;

  return min+r;

}


void rndBench( int N, int min, int max, random_prototype rnd_fn ) {

  int i;

  for (i=0; i<N; i++ ) {
    printf("%d ",rnd_fn( min, max ) );
  }

}
