#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char dni[10];
  int model, nac, nfa, nbl;
  double mark;
} Est;



int main() {

  char SRC_NAME[] = "marks.txt";
  char OUT_NAME[] = "out.txt";

  FILE *src_f, *out_f;
  Est ust;

  src_f = fopen( SRC_NAME, "r" );

  if ( !src_f ) {
    printf("No se pudo abrir el archivo %s\n",SRC_NAME);
    exit(1);
  }

  out_f = fopen( OUT_NAME, "w" );

  if ( !out_f ) {
    printf("No se pudo abrir el archivo %s\n",OUT_NAME);
    exit(1);
  }

  char ss_mark[5][30] = {"Suspenso","Aprobado","Notable","Sobresaliente","null"};

  while ( fscanf( src_f, "%s", ust.dni ) == 1 ) {

    char *s_mark;

    fscanf(src_f, "%d", &ust.model);
    fscanf(src_f, "%d", &ust.nac);
    fscanf(src_f, "%d", &ust.nfa);
    fscanf(src_f, "%d", &ust.nbl);
    fscanf(src_f, "%lf", &ust.mark);

    if ( ust.mark < 5 ) {
      s_mark = ss_mark[0];
    }  else if ( ust.mark < 7 ) {
      s_mark = ss_mark[1];
    } else if ( ust.mark < 9 ) {
      s_mark = ss_mark[2];
    } else if ( ust.mark <= 10 ) {
      s_mark = ss_mark[3];
    } else {
      s_mark = ss_mark[4];
    }

    fprintf(out_f,"%s %f %s\n",ust.dni,ust.mark,s_mark);

  }

  fclose(src_f);
  fclose(out_f);

  return 0;

}
