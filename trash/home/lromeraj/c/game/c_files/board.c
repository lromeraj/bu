#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../h_files/board.h"

/* Check if given paramters for a new board are valid
* @param {int} i - number of rows
* @param {int} j - number of columns
* @return {bool} - returns 0 if valid and 1 if not
*/
bool validBoard( int rows, int cols ) {
  return (bool)(
    rows <= MAX_BOARD_ROWS
    && rows >= MIN_BOARD_ROWS
    && cols >= MIN_BOARD_COLS
    && cols <= MAX_BOARD_COLS
  );
}

/* Returns a pointer that points to the requested cell
* @param {Board} brd - player's board
* @param {int} i - board row
* @param {int} j - board column
*/
Cell *getCell( Board *brd, int i, int j ) {

  Cell *cell;

  if (i<0 || i>=brd->rows || j<0 || j>=brd->cols) {
    cell = NULL;
  } else {
    cell = &(brd->cells[ j + i*brd->cols ]);
  }

  return cell;
}

/* Sets an area with a given boat
* @param {Board} brd - board for placement
* @param {Boat} boat - boat to be placed
* @param {int} row - starting row of placement
* @param {int} col - starting col of placement
* @param {char} dir - direction of placement
*/
void setArea( Board* brd, Boat boat, int row, int col, char dir ) {

  Cell *cell;
  int q, i, j;

  q=0; i=row; j=col;

  while ( q < boat.len ) {

    cell = getCell(brd, i, j);

    cell->content = boat.id;
    cell->dir = dir;
    cell->from[0] = row;
    cell->from[1] = col;

    if ( dir == 'H' ) {
      j++;
    } else if ( dir == 'V' ) {
      i++;
    }

    q++;
  }


}

/* Checks if an area is free or available
* @param {Board} brd - player's board
* @param {Boat} boat - boat to be located
* @param {int} row - starting row
* @param {int} col - starting column
* @param {char} dir - set the direction of placement
* @retun {Cell*} - if area is available returns a pointer to the
* first cell, if area is not available returns null
*/
Cell *reqArea( Board *brd, Boat boat, int row, int col, char dir ) {

  int q, i, j;
  Cell *cell;

  q=0; i=row; j=col;
  while (q < boat.len ) {

    cell = getCell(brd, i, j);

    printf("Checking cell %d %d\n", i,j);

    if ( dir == 'H' ) { // horizontal
      j++;
    } else if (dir == 'V') { // vertical
      i++;
    }

    if (!cell || cell->content != WATER ) {
      cell = NULL;
      break;
    }

    q++;

  }

  return cell;

}


/* Check if a boat is sunken
* if it is, it will replace the content of
* each cell to sunken
* @param {Board*} brd - board to check
* @param {int} row - cell row
* @param {int} col - cell col
* @return {bool} -  if the area corresponds
* to a sunken boat returns true else returns false
*/
bool isSunken( Board *brd, int row, int col ) {

  bool sunken = TRUE;
  Cell *cell;
  Boat boat;
  char dir;

  cell = getCell( brd, row, col );
  boat = getBoat( cell->content );
  dir = cell->dir;

  int q, i, j;
  int i0 = cell->from[0],
      j0 = cell->from[1];
  int ia=0, ja=0;

  if ( dir == 'H' ) {
    ja=1;
  } else if ( dir == 'V' ) {
    ia=1;
  }

  for (q=0, i=i0, j=j0; q<boat.len; q++) {

    cell = getCell( brd, i, j );

    if ( cell->sts != TOUCHED ) {
      sunken = FALSE;
      break;
    }

    i+=ia;
    j+=ja;

  }

  if ( sunken ) {

    for (q=0, i=i0, j=j0; q<boat.len; q++) {

      cell = getCell( brd, i, j );
      cell->sts = SUNKEN;
      i+=ia;
      j+=ja;

    }

  }

  return sunken;
}


/* Prints a board
* @param {Board} brd - player's board
* @param {bool} critical - show privy info
*/
void printBoard( Board *brd, bool privy ) {

  const char  sep[] = "|";

  int rows = brd->rows, // board rows
      cols = brd->cols; // board columns
  int cpr = 1, // chars per row
      cpc = 5; // chars per column
  int i, j, len;

  cpr+=1; cpc+=1;

  i=0;
  while (i<cpc) {
    printf(" ");
    i++;
  }

  for (i=0; i<=cpc*cols; i++) { // draw first row

    len = (int)floor( log10( i<cpc ? 1 : i/cpc ) + 1 );

    if ( i%cpc == cpc/2 ) {
      printf("%d",i/cpc);
      i+=len;
    }

    if ( !(i%cpc) ) {
      printf( sep );
    } else {
      printf(" ");
    }

  }

  printf("\n");

  for (i=0; i<=cpr*rows; i++) { // each row char

    len = (int)floor( log10( i<cpr ? 1 : i/cpr ) + 1 );

    for (j=0; j<=cpc*(cols+1); j++) { // each col char

      if ( !(i%cpr) ) { // row separation
        printf("-");
      } else {

        // prints left coords
        if ( j == cpc/2 && i%cpr == cpr/2 ) {
          printf("%d",i/cpr);
          j+=len;
        }

        if ( j%cpc == cpc/2 && i%cpr == cpr/2 ) {

          char sym[5] = " ";

          Cell *cell = getCell( brd, (int)floor(i/cpr), (int)floor(j/cpc-1) );

          if ( privy ) { // prints private data

            if ( cell->content == WATER )  {
              strcpy(sym, " ");
            } else {
              strcpy(sym, "@");
            }

          } else {

            if ( cell->sts == TOUCHED && cell->content == WATER ) {
              strcpy(sym,"X");
            } else if ( cell->sts == TOUCHED && cell->content != WATER ) {
              strcpy(sym,"O");
            } else if ( cell->sts == SUNKEN ) {
              strcpy(sym,"#");
            }

          }

          printf("%s", sym );
          j+=strlen( sym );


        }

        if ( !(j%cpc) ) {
          printf( sep );
        } else {
          printf(" ");
        }

      }

    }

    printf("\n");

  }

}
