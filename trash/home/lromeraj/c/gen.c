#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] ) {

  FILE *f;

  int sid, lid, i, j;
  int max = 0;

  sid = 1;
  lid = 1;

  char LBUFF[10000] = "";
  char SBUFF[10000] = "";

  int cps[4]; // cardinal points [N, E, S, W]
  int cpsi[4]; // values

  if ( argc < 2 ) {
    printf("too few args\n");
    return 1;
  }

  f = fopen( "data.dat", "w" );

  max = atoi( argv[1] );


  if ( !f ) {
    printf("Could not open the file\n");
    return 1;
  }


  for ( i=0; i < max; i++ ) {

    printf("Space#%d[N,E,S,W]: ", sid );

    scanf("%d %d %d %d", &cps[0], &cps[1], &cps[2], &cps[3] );

    for ( j=0; j<4; j++ ) {

      if ( cps[ j ] != -1 ) {
        sprintf( LBUFF + strlen( LBUFF ), "@l:%02d|Link %02d|%02d|%02d|0\n", lid, lid, sid, cps[ j ] );
        cpsi[ j ] = lid;
        lid++;
      } else {
        cpsi[ j ] = -1;
      }

    }
    sprintf( SBUFF + strlen( SBUFF ), "@s:%02d|Space %02d|%02d|%02d|%02d|%d\n", sid, sid, cpsi[0], cpsi[1], cpsi[2], cpsi[3] );

    sid++;

  }

  fprintf( f, "%s", SBUFF );
  fprintf( f, "%s", "\n" );
  fprintf( f, "%s", LBUFF );

  fclose( f );
}
