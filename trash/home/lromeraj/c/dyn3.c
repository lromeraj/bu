#include <stdio.h>
#include <stdlib.h>

void min_max( double*, long, double*, double* );

int main() {

  double *ns, min, max;
  long q;
  int i;

  printf("Data size: ");
  scanf("%ld",&q);

  ns = (double *) calloc(q,sizeof(double));

  if (!ns) {
    printf("Error requesting memory to SO");
    exit(1);
  }

  for (i=0; i<q; i++) {
    printf("Number %d: ",i+1);
    scanf("%lf",&ns[i]);
  }

  min_max( ns, q, &min, &max );

  printf("Min: %lf\nMax: %lf\n",min,max);


  return 0;
}


void min_max(
  double *nbs,
  long q,
  double *min,
  double *max )
{

  int i,j;


  for (i=0; i<q; i++) {

    for (j=i+1; j<q; j++) {

      if ( nbs[j] < nbs[i] ) {
        double temp = nbs[i];
        nbs[i] = nbs[j];
        nbs[j] = temp;
      }

    }

  }

  *min = nbs[0];
  *max = nbs[q-1];

}
