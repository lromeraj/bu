#include <stdio.h>
#include <stdlib.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

double **build_matrix(int, int);
void clean_matrix(double**,int);

void show_matrix(int,int,int,int,double**);

int main() {

  int r=0, c=0;
  double **mat;

  do {
    printf("MxN: ");
    scanf("%dx%d",&r,&c);
    if (r <= 0 || c <= 0) {
      printf("Invalid size\n");
    }
  } while ( r <= 0 || c <= 0 );

  mat = build_matrix(r,c);

  for (int i=0; i<r; i++) {

    for (int j=0; j<c; j++) {
      show_matrix(r, c, i, j,mat);
      printf("\n[%d, %d] = ",i,j);
      scanf("%lf",&mat[i][j]);
    }

  }

  return 0;

}

void show_matrix(int rows, int cols, int row, int col, double **mat) {

  printf("\n");

  for (int i=0; i<rows; i++) {

    for (int j=0; j<cols; j++) {

      if (!j) printf("| ");

      if (i==row && j==col) {
        printf("%s%-*s%s",BOLDGREEN,4,"X",RESET);
      } else {
        printf("%04.1lf",mat[i][j]);
      }

      if (j==cols-1) {
        printf(" |");
      } else {
        printf("  ");
      }


    }

    printf("\n");

  }

}


double **build_matrix(int rows, int cols) {

  double **mat;

  mat  = (double**) calloc(rows,sizeof(double*));

  if (mat == NULL) return NULL;

  for (int i=0; i<cols; i++) {
    mat[i] = (double*) calloc(cols,sizeof(double));
    if (mat[i] == NULL) clean_matrix(mat, rows);
  }

  return mat;

}


void clean_matrix(double **mat, int rows) {

  for (int i=0; i<rows; i++) {
    free(mat[i]);
  }

  free(mat);

}
