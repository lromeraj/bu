
#include <stdio.h>
#include "diary.h"

int main () {

  Diary di;
  int code;
  char name[30];

  printf("Enter diary file name: ");

  scanf("%s", di.f_name);

  code = load_diary( &di );

  if (code == 1) {
    printf ("Error opening file\n");
    return 1;
  } else if (code == 2) {
    printf ("Error reading file\n");
    return 2;
  }

  Contact c = {"Javier","Romera",688904595};

  add_contact(&di,c);

  printf("Enter a name to find on the diary: ");
  scanf("%s", name);

  code = find(di, name);

  if (code == 0)
    printf ("%s was not found in the diary\n", name);
  else
    printf ("Phone number of %s is %d\n", name, code);

  return 0;

}
