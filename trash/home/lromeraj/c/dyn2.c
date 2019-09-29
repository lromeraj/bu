#include <stdio.h>
#include <stdlib.h>


int concat( char*,char*,char*);

int main() {

  char *str1, *str2, *res;
  int max_len, res_len;

  printf("Enter string size: ");
  scanf("%d",&max_len);


  str1 = (char *) calloc(max_len,sizeof(char));
  str2 = (char *) calloc(max_len,sizeof(char));
  res = (char *) calloc(2*max_len,sizeof(char));

  if (!str1 || !str2 || !res) {
    printf("Error requestiong memory to SO");
    free(str1);
    free(str2);
    free(res);
    exit(1);
  }

  printf("First string: ");
  scanf("%s",str1);

  getchar();

  printf("Second string: ");
  scanf("%s",str2);

  res_len = concat(str1,str2,res);

  printf("%s+%s: %s, length: %d\n",str1,str2,res,res_len);

  return 0;
}

int concat( char *str1, char *str2, char *res ) {

  int str_i, i, len=0;

  char **strs;

  strs = (char **) calloc(2,sizeof(char*));

  strs[0] = str1;
  strs[1] = str2;

  for (str_i=0; str_i<2; str_i++) {
    for (i=0; strs[str_i][i]; i++) {
      res[len] = strs[str_i][i];
      res[len+1] = 0;
      len++;
    }
  }

  return len;
}
