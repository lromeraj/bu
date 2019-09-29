#include <stdio.h>
#include <string.h>


void *split( char **to, char *a, char c ) {

  char str[100][100];

  int stri = 0, toi = 0;

  int alen = strlen( a );

  for (int i=0; a[i]; i++) {

    if (a[i] == c) {
      stri=0;
      i++;
      toi++;
    }

    if ( i == alen-1 && a[i] != c ) {
      str[toi][stri] = a[i];
    }

    to[toi]=str[toi];

    str[toi][stri] = a[i];

    stri++;

  }

  return 0;

}

int main() {

  char a[] = "Roberto,Alejandro,Javier;";
  char *names[100];

  split(names,a,',');

  printf("%s %s %s",names[0],names[1],names[2]);


  return 0;
}
