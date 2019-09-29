#include <stdio.h>
#include <stdlib.h>

int count_char( char*, char );
int count_words( char* );

int main() {

  char F_NAME[50];
  char c;

  printf("Enter file name: ");
  scanf("%s",F_NAME);

  getchar();

  printf("Enter a char: ");
  scanf("%c",&c);


  int nw = count_words(F_NAME), nc = count_char(F_NAME,c);

  if (nw == -1 || nc == -1) {
    printf("Couldn't open the file\n");
    return 1;
  }

  printf("File %s contains %d words and the char %c appears %d times\n",F_NAME,nw,c,nc);

  return 0;
}

int count_char( char *f_name, char co ) {

  FILE *f;
  int n;
  char c;

  f = fopen( f_name, "r" );
  n = f ? 0 : -1;

  if (!n) {

    while ( fscanf(f,"%c",&c) == 1 ) {
      if (c == co) n++;
    }

  }

  fclose(f);

  return n;

}

int count_words( char *f_name ) {

  FILE *f;
  int n, inw = 0;
  char c;

  f = fopen( f_name, "r" );
  n = f ? 0 : -1;

  if (!n) {

    do switch ( c ) {
      case '\0': case '\t': case '\n': case ' ':
        if (inw) { n++; inw=0; }
        break;

      default:
        inw = 1;
    } while ( fscanf(f,"%c",&c) == 1 );

  }

  fclose(f);
  return n;
}
