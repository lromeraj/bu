#ifndef GAME_H
#define GAME_H

#define BOAT_TYPES 4 // default 4
#define MIN_BOARD_ROWS 10
#define MAX_BOARD_ROWS 20
#define MIN_BOARD_COLS 10
#define MAX_BOARD_COLS 20

typedef enum {FALSE,TRUE} bool;

typedef enum { // game items
  WATER, // agua
  AIRCRAFT_CARRIER, // porta aviones
  BATTLESHIP, // acorazado
  DESTROYER, // destructor
  FRIGATE // fragata
} CellItem;

typedef struct {
  char name[50]; // boat name
  int len; // boat length
  int id; // reference id
  int amount; // max amount of self boat
} Boat;

// boats type definition
Boat _BOATS[ BOAT_TYPES ];

void setBoat( int, char*, int, int );
Boat getBoat( int );
void _wait();

#endif
