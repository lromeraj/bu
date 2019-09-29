#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100

void nWords(char*, long*);

int main() {

  long nW;
  char str[LEN];

  printf("Escribe una cadena de caracteres: ");
  fgets(str,LEN,stdin);

  nWords(str,&nW);

  printf("%ld\n",nW);


  return 0;
}

void nWords(char *str, long *nW) {

  long ws = *str != ' ' ? 1 : 0;

  while (*str) {
    if (*str==' ' && *(str+1) != ' ' && *(str+1) != '\n') {
      ws++;
    }
    str++;
  }

  *nW=ws;

}
