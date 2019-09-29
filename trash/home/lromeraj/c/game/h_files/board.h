#include "game.h"

#ifndef BOARD_H
#define BOARD_H

typedef enum { // cell status
  NOT_TOUCHED, // no tocado
  TOUCHED, // tocado
  SUNKEN // hundido
} CellSts;

typedef struct {
  CellItem content; // cell content
  CellSts sts; // cell status
  int from[2];
  char dir;
} Cell;

typedef struct {
  Cell *cells; // board cells
  int rows, // board rows
      cols; // board columns
} Board;

Board *createBoard( int, int );
void printBoard( Board*, bool );
bool validBoard( int, int );
Cell *getCell( Board*, int, int );
void setCell( Board*, int, int );
Cell *reqArea( Board*, Boat, int, int, char );
void setArea( Board*, Boat, int, int, char );
bool isSunken( Board*, int, int );

#endif
