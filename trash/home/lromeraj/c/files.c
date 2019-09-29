#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char dni[10];
  int model, nac, nfa, nbl;
  double mark;
} Est;


int count_est( char* );

int main() {


  char F_NAME[] = "marks.txt";
  FILE *f;
  Est ust, *cls;

  int m=0;
  float ms=0;

  int i=0, usts=count_est( F_NAME );

  if (usts==-1) {
    printf("No se pudo abrir el archivo\n");
    exit(1);
  }

  cls = (Est*) calloc( usts, sizeof(Est) );

  if (!cls) {
    printf("No se pudo reservar memoria\n");
    exit(1);
  }

  f = fopen( F_NAME, "r" );

  if ( !f ) {
    printf("No se pudo abrir el archivo\n");
    exit(1);
  }

  while ( fscanf( f, "%s", ust.dni ) == 1 ) {

    fscanf (f, "%d", &ust.model);
    fscanf (f, "%d", &ust.nac);
    fscanf (f, "%d", &ust.nfa);
    fscanf (f, "%d", &ust.nbl);
    fscanf (f, "%lf", &ust.mark);

    if ( ust.mark >= 5 ) {
      ms+=ust.mark;
      m++;
    }

    cls[ i ] = ust;
    i++;

  }

  printf("Media de aprobados %lf\n",(float)ms/m);

  return 0;
}

int count_est( char *f_name ) {

  int n;
  FILE *f = fopen( f_name, "r" );
  Est ust;

  n = f ? 0 : -1;

  if (!n) {
    while ( fscanf( f, "%s", ust.dni ) == 1 ) {
      fscanf (f, "%d", &ust.model);
      fscanf (f, "%d", &ust.nac);
      fscanf (f, "%d", &ust.nfa);
      fscanf (f, "%d", &ust.nbl);
      fscanf (f, "%lf", &ust.mark);
      n++;
    }
  }

  fclose( f );

  return n;
}
