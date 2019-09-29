#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* str_alloc( unsigned long len ) {

  char *_str;

  if ( !len )
    return NULL;

  _str = (char*) calloc( len+1, sizeof( char ) );

  return _str;

}

char* str_clone( const char *str ) {

  char *_clone;
  unsigned long len;

  if ( !str )
    return NULL;

  len = strlen( str );
  _clone = str_alloc( len );

  if ( !_clone )
    return NULL;

  memcpy( _clone, str, len );
	printf("%p %p\n", str, _clone );

  return _clone;
}

void basename( char *dest, char *src, size_t size ) {

	char *_str, *tok1, *tok2;

	if ( !dest || !src )
		return;

	_str = str_clone( src );

	strcpy( _str, src );

	tok1 = tok2 = strtok( _str, "/" );

	while( tok2 ) {
		tok2 = strtok( NULL, "/" );
		tok1 = tok2 ? tok2 : tok1;
	}

	strcpy( dest, tok1 );

	free( _str );
}

int main( int argc, char *argv[] ) {

  char *tok1, *tok2;
  char *_tok1, *_tok2;

  char str1[] = "a w e s o m e=t e x t=b r o=o k=y e a h=j e j e j e";
  char *_str;
  int len;

  tok1 = strtok_r( str1, "=", &_tok1 );

	while ( tok1 ) {

    len = strlen( tok1 );

    _str = (char*) malloc( sizeof( char )*(len+1) );

    strcpy( _str, tok1 );
    printf("%s\n", tok1 );


    tok2 = strtok_r( _str, " ", &_tok2 );
    while ( tok2 ) {
      printf(" %s\n", tok2 );
      tok2 = strtok_r( NULL, " ", &_tok2 );
    }
    

    free( _str );

		tok1 = strtok_r( NULL, "=", &_tok1 );
	}

  return 0;
}
