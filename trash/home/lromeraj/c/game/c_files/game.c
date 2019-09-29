#include <string.h>
#include <stdio.h>
#include "../h_files/game.h"

/* Set up boats configuration
* @param {int} id - Boat id
* @param {char} name - Boat name
* @param {int} len - Max boat length
* @param {int} amount - max amount of self board
*/
void setBoat( int id, char *name, int len , int amount ) {

  static int idx = 0;

  if ( idx >= BOAT_TYPES ) return;

  _BOATS[ idx ].id = id;
  _BOATS[ idx ].len = len;
  _BOATS[ idx ].amount = amount;

  strcpy( _BOATS[ idx ].name, name );

  idx++;

}

/* Returns boat properties
* @param {int} - boat id
* @return {Boat} - returns boat structure
*/
Boat getBoat( int id ) {

  Boat b = {};
  int i;

  for (i=0; i<BOAT_TYPES; i++) {
    if ( _BOATS[ i ].id == id ) {
      b = _BOATS[ i ];
      break;
    }
  }

  return b;
}

/* Waits for user ENTER key input */
void _wait() {
  char c;
  printf("Press ENTER key to continue...\n");
  getchar();
  scanf("%c",&c);
}
