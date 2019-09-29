#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int a, b, c;
} Try;

void try_free2( Try **t ) {
  if ( *t ) {
    free( *t );
    *t = NULL; // of course it does
  }
}

void try_free1( Try *t ) {
  if ( t ) {
    free( t );
    t = NULL; // does nothing
  }

}

Try *try_alloc( Try **t ) {
  *t = (Try*) calloc(1,sizeof(Try));
  return *t;
}

void try_fusion( const Try *src, Try **dest ) {
  *dest = (Try*)src;
}

int main() {

  Try *t = NULL;
  Try *k = NULL;

  try_alloc( &t );
  try_alloc( &k );

  try_fusion( t, &k );

  t->a = 19;
  printf("%d\n",k->a);
  k->a = 18;
  printf("%d\n",t->a);

  printf("free1...\n");
  printf("pointed address: %p\n",t);
  printf("pointer address: %p\n", &t);
  try_free1( t ); printf("after releasing...\n");
  printf("pointed address: %p\n",t);
  printf("pointer address: %p\n", &t);

  try_alloc( &t );

  printf("\nfree2...\n");
  printf("pointed address: %p\n",t);
  printf("pointer address: %p\n", &t);
  try_free2( &t ); printf("after releasing...\n");
  printf("pointed address: %p\n",t);
  printf("pointer address: %p\n", &t);

  return 0;
}
