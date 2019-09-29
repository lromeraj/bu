#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GW 10
#define GH 10

// typde definition of our custom data type

typedef char G_desc[ GH ][ GW ];

typedef struct _Sp {
	/*
	* Other fields ...
	*/
	G_desc desc;
} Sp;

/* basic initializer */
Sp *sp_init() {
	Sp *sp = (Sp*) malloc( sizeof(Sp) );
	return sp;
}

/* Get graphic data
* @param {Sp*} - Space pointer
* @return {G_desc*} - Returns a pointer to G_Desc
*/
G_desc *sp_get_desc( Sp *sp ) {
	return &sp->desc;
}

/* Set graphic data
* @param {Sp*} - Space pointer
* @param {const int} _i - Row
* @param {cont char*} str - Row word
*/
void sp_set_desc( Sp *sp, const int _i, const char *str ) {

	if ( !sp || !str )
		return;

	if ( _i >= GH || _i < 0 || strlen( str ) >= GW )
		return;

	strcpy( sp->desc[ _i ], str );
}


int main() {

	Sp *sp = sp_init();

	sp_set_desc( sp, 0, "hi" ); // sets word "hi" at row 0
	sp_set_desc( sp, 1, "bye" ); // sets word "bye" at row 1
	sp_set_desc( sp, 2, "hibye" ); // sets word "hibye" at row 2

	/* content of the graph shuld look like this:
	* {
	*		{ "hi" },
	*		{ "bye" },
	*		{ "hibye" }
	* }
	*/

	// how to print graph data ...
	printf( "%c\n", (*sp_get_desc( sp ))[0][1] ); // h
	printf( "%s\n", (*sp_get_desc( sp ))[0] ); // hi
	printf( "%s\n", (*sp_get_desc( sp ))[1] ); // bye
	printf( "%c\n", (*sp_get_desc( sp ))[1][2] ); // e
	printf( "%s\n", (*sp_get_desc( sp ))[2] ); // hibye


	return 0;
}
