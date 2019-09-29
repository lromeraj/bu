#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../h_files/player.h"

/* Deletes a player
* @param {Player*} p - a pointer to the player's content
*/
void dropPlayer( Player* p ) {

  if (p) {
    if ( p->board->cells ) {
      free( p->board->cells );
    }
    free( p );
    p = NULL;
  }

}

/* Creates a new player
* @param {char} name - player's name
* @param {int} rows - player's board width
* @param {int} cols - player's board height
*/
Player* newPlayer( char* name, int rows, int cols) {

  Player *p;
  Cell *cells;
  int i, j;
  int init = 0;

  p = (Player*) calloc( 1, sizeof(Player) );

  if ( p ) {

    p->board = (Board*) calloc(1,sizeof( Board ));

    p->board->rows = rows;
    p->board->cols = cols;

    cells = (Cell*) calloc( rows*cols, sizeof(Cell) );

    if ( cells ) {

    } else {
      init = 1;
      dropPlayer( p );
    }

  }

  if ( !init ) { // no errors reserving memory

    // point the cells to the player's board
    p->board->cells = cells;

    // store player name
    strcpy(p->name, name);

    // set default content of the cells
    for (i=0;i<rows;i++) {
      for (j=0;j<cols;j++) {
        getCell( p->board, i, j )-> content = WATER;
      }
    }

  }

  return p;
}

/* Requests to the given player all needed boats
* @param {Player} player - player to request the boats
*/
void reqBoats( Player *player ) {

  Board *brd = player->board;
  int i, j;

  for (i=0; i<BOAT_TYPES; i++) {

    Boat boat = getBoat( _BOATS[i].id );

    player->boats+= boat.amount;

    for (j=0; j<boat.amount; j++) {

      Cell *cell = NULL;
      int row, col;
      char dir;

      printBoard(brd, TRUE);

      printf(">> %s - Place \"%s\" %d of %d, size: %d\n",
              player->name,
              boat.name,
              j+1,
              boat.amount,
              boat.len);

      do {

        printf("RxC: ");
        scanf("%dx%d",&row,&col);

        getchar();

        printf("Direction (H/V): ");
        scanf("%c",&dir);

        if ( dir != 'H' && dir != 'V' ) {
          printf("Invalid direction\n");
        } else {

          // request area
          cell = reqArea( brd, boat, row, col, dir );

          if (!cell) {
            printf("Invalid area, try again...\n");
          }

        }

      } while ( !cell );

      setArea( brd, boat, row, col, dir );

    }

  }

}
