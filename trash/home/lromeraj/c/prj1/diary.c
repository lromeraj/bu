#include <stdio.h>
#include <string.h>
#include "diary.h"

void add_contact(Diary *d, Contact c) {

  FILE *f;

  f = fopen( d->f_name, "a" );

  if (f) {
    d->list[d->size] = c;
    d->size++;
    fprintf(f,"%s %s %d\n",c.name,c.name2,c.phone);
    fclose( f );
  }

}

int load_diary(Diary * x) {

  FILE * f;

  f = fopen (x->f_name, "r");

  if (!f) return 1;

  for (x->size=0 ; fscanf(f, "%s", x->list[x->size].name) == 1; x->size++) {
    if (fscanf(f, "%s", x->list[x->size].name2) != 1)
      return 2;

    if (fscanf(f, "%d", &x->list[x->size].phone) != 1)
      return 2;
  }

  fclose( f );
  return 0;
}

int find(Diary x, char * name) {

  int i;

  for (i=0; i<x.size; i++) {
    if (!strcmp(name, x.list[i].name)) {
      return x.list[i].phone;
    }
  }

  return 0;
}
