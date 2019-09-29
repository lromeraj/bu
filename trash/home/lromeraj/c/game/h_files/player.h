#include "board.h"

#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
  Board *board; // tabla del jugador
  char name[20]; // nombre del jugador
  int attemps; // intentos
  int sags; // hundimientos
  int fails; // player fails
  int boats; // number of boats
} Player;

void dropPlayer( Player* );
Player *newPlayer( char*, int, int );
void reqBoats( Player* );

#endif
