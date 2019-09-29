#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define AS 1
#define DOS 2
#define TRES 3
#define CUATRO 4
#define CINCO 5
#define SEIS 6
#define SIETE 7
#define SOTA 0.5
#define CABALLO 0.5
#define REY 0.5

#define MAX_PLAYERS 4

int ran(int a, int b) {
	return (int) (a + (double) rand() / (RAND_MAX-1) * (b - a + 1));
}

int main() {

  srand((unsigned) time(NULL));

  int nofp; //number of players

  double cards[40] = {
    AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA, CABALLO, REY,
    AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA, CABALLO, REY,
    AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA, CABALLO, REY,
    AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA, CABALLO, REY
  };

  do {

    printf("Introducir el número de jugadores: ");
    scanf("%d",&nofp);

    if (nofp < 1 || nofp > MAX_PLAYERS) {
      printf("Intervalo de jugadores: 1 - %d\n",MAX_PLAYERS);
    }

  } while ( nofp < 1 || nofp > MAX_PLAYERS );

  printf("Mixing... ");

  for (int i=0; i<100;i++) {

    int a = ran(0,39), b = ran(0,39);
    double temp = cards[a];
    cards[a] = cards[b];
    cards[b] = temp;

  }

  printf("Done\n");

  double players[4] = {};

  for (int i=0; i<nofp; i++) {

    printf("Jugador %d ==========\n",i+1);

    char c;

    do {

      int r = ran(0,39);

      players[i]+=cards[r];

      if ( players[i] > 7.5 ) {
        printf("¡Te has pasado! Te quedas con %lf\n",players[i]);
      } else {
        printf("Tu puntuación parcial es: %lf\n",players[i]);

        printf("Quieres carta(s/n)? ");
        getchar();
        scanf("%c",&c);
      }




    } while ( c != 'n' && players[i] <= 7.5 );


  }


}
