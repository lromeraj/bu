#ifndef UI_H
#define UI_H

#define MAX_BOXES 10

typedef enum {
  BG_BLACK=40,
  BG_RED=41,
  BG_GREEN=42,
  BG_YELLOW=43,
  BG_BLUE=44,
  BG_PURPLE=45,
  BG_CYAN=46,
  BG_WHITE=47,
  FG_BLACK=30,
  FG_RED=31,
  FG_GREEN=32,
  FG_YELLOW=33,
  FG_BLUE=34,
  FG_PURPLE=35,
  FG_CYAN=36,
  FG_WHITE=37
} Color;

typedef enum {
  BOLD
} Theme;

// S - Set
// R - Reset
typedef enum {
  S_DEFAULT=0,
  S_BOLD=1,
  S_DIM=2,
  S_UNDERLINED=4,
  S_BLINK=5,
  S_REVERSE=7,
  S_HIDDEN=9,
  S_BOLD_UNDERLINED=100,
  S_DIM_UNDERLINED=101
} Format;

typedef struct _Ui_screen {
  int w, h;
} Ui_screen;

typedef struct _Ui_pix {
  Color fg, bg;
  Format format;
  char c; // cell char
} Ui_pix;

typedef struct _Ui_box {
  int id, x, y, w, h, __len, _i;
  Ui_pix **__pixs;
  Color bg;
} Ui_box;

typedef struct _Ui {
  Ui_screen scr; // user interface screen
  Ui_box *boxes[ MAX_BOXES ];
  Ui_pix **__pixs; // ui pixels
  int __len, n_boxes; // quantity of pixels
  Color __fg, __bg; // temporary colors
  Format __format; // temporary format
} Ui;

Ui *ui_init( int, int  );
Ui_pix **ui_alloc_pixs( int );
void ui_destroy( Ui* );
void ui_draw( Ui* );
void ui_clear( Ui* );
void ui_bg( Ui*, Color );
void ui_txt_bg( Ui*, Color );
void ui_txt_fg( Ui*, Color );
void frm( Ui*, Format );
void ui_box_bg( Ui*, int, Color );

void ui_new_box( Ui*, int, int, int, int, int );
Ui_box *ui_get_box( Ui*, int );
void ui_clear_box( Ui*, int );
void ui_box_put( Ui*, int, const char*, ... );
void ui_kill_box( Ui_box* );




 #endif
