#include <stdio.h>
#include <string.h>

#define STR_LEN 500
#define ASCII_SIZE 255

int main() {

  char ASCII[ASCII_SIZE] = {};
  char str[STR_LEN];

  printf("Introduce una cadena de caracteres: ");
  fgets(str,STR_LEN,stdin);

  for (int i=0; i < strlen( str ); i++) {
    ASCII[ str[ i ] ]++;
  }

  for (int i=0; i < ASCII_SIZE; i++) {

    if (ASCII[i]) {

      switch ( i ) {
        case '\n':
          printf("\\n");
          break;
        default:
          printf("`%c`",i);
      }

      printf(" appears %d\n",ASCII[i]);

    }

  }

  return 0;
}
