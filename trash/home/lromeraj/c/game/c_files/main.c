#include <stdio.h>
#include <stdlib.h>

#include "../h_files/game.h" // game logic
#include "../h_files/player.h" // player
#include "../h_files/board.h" // board
#include "../h_files/ui.h" // user interface

#define STR_LEN 100

#define DEVM 0 // developer mode 0 or 1

int main() {

  /* -------- CONFIG START -------- */

  setBoat( AIRCRAFT_CARRIER, "Aircraft carrier", 4, 2 );
  setBoat( BATTLESHIP, "Battleship", 3, 3 );
  setBoat( DESTROYER, "Destroyer", 2, 3 );
  setBoat( FRIGATE, "Frigate", 2, 1 );

  /* -------- CONFIG END -------- */

  Player *player1, *player2;

  char  name1[STR_LEN] = "Bot1",
        name2[STR_LEN] = "Bot2";

  int ROWS=5,
      COLS=5;

  if (!DEVM) { // do thing when developer mode is off

    // request board size
    do {

      printf("Enter board size [RxC]: ");
      scanf("%dx%d",&ROWS,&COLS);

      if ( validBoard( ROWS, COLS ) == FALSE ) {
        printf("Invalid board size\n");
      }

    } while( validBoard( ROWS, COLS ) == FALSE );

    // request player names
    printf("Name of player 1: ");
    scanf("%s",name1);

    getchar();

    printf("Name of player 2: ");
    scanf("%s",name2);

  } else { // do things if developer mode is on

  }

  bool battle = TRUE;
  int turn = 0, row, col;
  Cell *cell;
  Boat boat;

  Player **players = (Player**) calloc(2,sizeof(Player));
  Player *curr, *opp;

  if (!players) {
    printf("Could not reserve memory for players");
    exit(1);
  }

  // initialize players
  player1 = newPlayer(name1, ROWS, COLS);
  player2 = newPlayer(name2, ROWS, COLS);

  players[0] = player1;
  players[1] = player2;

  if (DEVM) {

    setArea(player1->board,_BOATS[0], 0, 0, 'H');
    setArea(player2->board, _BOATS[3], 0, 0, 'V');

    player1->boats+=1;
    player2->boats+=1;

  } else {
    reqBoats( player1 );
    reqBoats( player2 );
  }

  while( battle ) {

    curr = players[ turn ];
    opp  = players[ 1-turn ];

    printf("%s it's your turn\n",curr->name);
    printBoard(opp->board, FALSE);

    do {

      printf("RxC: ");
      scanf("%dx%d",&row,&col);

      cell = getCell(opp->board, row, col);

      if (!cell) {
        printf("Given coord does not exists, try again...\n");
      }

    } while( !cell );

    cell->sts = TOUCHED;
    curr->attemps++;

    if ( cell->content != WATER ) {

      boat = getBoat( cell->content );

      if ( isSunken( opp->board, row, col ) ) {
        curr->sags++;
        printBoard( opp->board, FALSE );
        printf("Nice! Touched and sunk: %s\n",boat.name);
      } else {
        printBoard( opp->board, FALSE );
        printf("Not bad! Touched: %s\n",boat.name);
      }

    } else {
      curr->fails++;
      printBoard(opp->board, FALSE);
      printf("Nothing touched! Best luck for the next time...\n");
    }

    if ( curr->sags == curr->boats ) {

      printf("AWESOME!!! You have sunk all the boats of %s\n",opp->name);
      printf("WINNER: %s\n",curr->name);
      printf("  Attepms: %d\n",curr->attemps);
      printf("  Fails: %d\n", curr->fails);

      break;
    }

    _wait();

    turn = 1-turn;
  }

  dropPlayer( player1 );
  dropPlayer( player2 );

  return 0;
}
