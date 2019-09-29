//         _                                    _
//   ____ | |                                  (_)
//  / __ \| |_ __ ___  _ __ ___   ___ _ __ __ _ _
// / / _` | | '__/ _ \| '_ ` _ \ / _ \ '__/ _` | |
//| | (_| | | | | (_) | | | | | |  __/ | | (_| | |
// \ \__,_|_|_|  \___/|_| |_| |_|\___|_|  \__,_| |
//  \____/                                    _/ |
//                                           |__/ 

#include <stdio.h>

#define SIZE 50

int read_strs( char*, char*, char* );
int cmp_strs( char*, char*, char* );

int main() {

  char SRC_NAME[SIZE],  str1[SIZE], str2[SIZE];
  int res;

  printf("Enter source file name: ");
  scanf("%s",SRC_NAME);

  res = read_strs( SRC_NAME, str1, str2 );

  if ( res ) {
    printf("Error opening file %s\n",SRC_NAME);
  } else {

    res = cmp_strs( SRC_NAME, str1, str2 );

    if ( res ) {
      printf("Error writing on file\n");
    } else {
      printf("All done!\n");
    }


  }

  return 0;

}

int cmp_strs( char *src_name, char *str1, char *str2 ) {

  FILE *src_f;
  int flag, i, j, fnd[256] = {};

  flag = ( src_f = fopen( src_name, "a" ) ) ? 0 : 1;

  if (!flag) {

    for (i=0; str1[i]; i++) {
      short is = 0;
      char c1 = str1[i];

      if ( fnd[(int)c1] ) continue;

      for (j=0; str2[j]; j++) {
        char c2 = str2[j];
        if ( c1 == c2 ) { is = 1; fnd[(int)c1]++; }
      }

      if (is) {
        fprintf(src_f,"The char %c appears %d\n",c1,fnd[(int)c1]);
      } else {
        fprintf(src_f,"The char %c does not appear\n",c1);
      }

    }

    fclose( src_f );

  }

  return flag;
}

int read_strs( char *src_name, char *str1, char *str2 ) {

  FILE *src_f;
  int flag;

  src_f = fopen( src_name, "r" );

  flag = src_f ? 0 : 1;

  if (!flag) {

    fscanf(src_f,"%s",str1);
    fscanf(src_f,"%s",str2);

    fclose( src_f );

  }

  return flag;

}
