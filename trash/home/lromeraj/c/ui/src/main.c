#include "ui.h"
#include "bm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdbool.h>

enum { BOX1, BOX2, BOX3 };

int main() {

  int i;
  Ui *ui;
  Clk *init_clk, *draw_clk, *render_clk;
  setlocale( LC_ALL, "" );

  bm_build();

  ui = ui_init( 200, 50 );

  init_clk = bm_clk( "INIT_CLK" );
  draw_clk = bm_clk( "DRAW_CLK" );
  render_clk = bm_clk( "RENDER_CLK" );

	ui_bg( ui, "%s", "brgb(0,0,0)" );
  bm_clk_begin( init_clk );

  ui_new_box( ui, BOX1, 3, 0, 30, 5 );

  bm_clk_end( init_clk );

  ui_dump_box( ui, BOX1 );

  ui_box_bg( ui, BOX1, "brgb(255,255,255)" );

  for ( i=0; i < 15; i++ ) {


    bm_clk_begin( render_clk );

    ui_box_frm( ui, BOX1, 2, BG_BLACK, FG_WHITE );

    ui_box_put( ui, BOX1, " hola %i \n", i );

    ui_dump_box( ui, BOX1 );

    bm_clk_end( render_clk );

    bm_clk_begin( draw_clk );
    ui_draw( stderr, ui );
    bm_clk_end( draw_clk );


    bm_clk_print( init_clk );
    bm_clk_print( render_clk );
    bm_clk_print( draw_clk );


    usleep( 1000000 );
  }


  ui_dump_box( ui, BOX1 );
  ui_draw( stdout, ui );

  ui_destroy( ui );



  bm_destroy();

  return 0;
}
