#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

char *dechex(int a) {

  char *hex = malloc(sizeof(char)*100);

  int r=0,i=0;

  do {
    r=a%16;
    a=a/16;

    if (r<10) {
      hex[i] = (char)(r+48);
    } else {
      hex[i] = (char)(r+55);
    }
    i++;
  } while (a);

  char *cp = malloc(sizeof(char)*100);

  strcpy(cp, hex);

  int len = strlen(cp);

  for (int i=0; i<len; i++) {
    hex[len-i-1] = cp[i];
  }

  return hex;

}


int main () {

  printf("%s",dechex( 7562 ));

  return 0;
}
