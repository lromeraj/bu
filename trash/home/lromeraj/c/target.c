#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define _RESET   		"\033[0m"
#define FG_RED     	"\033[31m"
#define FG_GREEN   	"\033[32m"
#define FG_YELLOW  	"\033[33m"
#define FG_BLUE    	"\033[34m"
#define FG_PURPLE 	"\033[35m"
#define FG_WHITE 		"\033[97m"
#define FG_CYAN    	"\033[36m"

#define FG_BRED     "\033[1;31m"
#define FG_BWHITE 	"\033[1;97m"
#define FG_BGREEN   "\033[1;32m"
#define FG_BYELLOW  "\033[1;33m"
#define FG_BBLUE    "\033[1;34m"
#define FG_BPURPLE 	"\033[1;35m"
#define FG_BCYAN    "\033[1;36m"

#define MAX_CONFIG 50
#define MAX_CHECKS 10

typedef enum {
	_ERROR,
	_WARN,
	_SUCCESS,
	_INFO,
	_TASK_START,
	_TASK_END
} PrintType;

typedef enum {
	NONE,
	TARGET,
	TARGET_ARGS,
	SRCDIR,
	INCDIR,
	OBJDIR,
	DISTDIR,
	DIST_IGNORE,
	SRCS,
	CLOG,
	CFLAGS,
	LDFLAGS,
	VGR_FLAGS,
	ASCII_TITLE,
	ASCII_VERSION,
	DEFAULT_ENV
} Conf_p;

typedef enum {
	_NULL_CHECK=1,
	_FILE_CHECK,
	_DIR_CHECK,
	_END_CHECK
} Conf_check;

typedef enum {
	_STR_ARR,
	_STR
} ConfType;

typedef struct _Argv {
	char **_argv;
	int _max, _n;
} Argv;

void _p( PrintType type, const char *frmt, ... );

int strcmptok( const char *str, char *strl, const char *del );

void conf_alloc_p( Conf_p p, ... );
void conf_free_p( Conf_p p );
void* conf_get_p( Conf_p, ... );
void conf_set_p( Conf_p p, ... );
int conf_check_p( Conf_p, ... );
void conf_free_all();
void conf_upd( char **__data, int size );
Conf_p conf_get_p_by_name( const char *_name );

bool exists_dir( const char *path );
bool exists_file( const char *f_path );
bool exists_cmd( const char *_cmd );

int env_load( const char*, const char* );

int print_file( FILE *stream, const char *f_name );
int _rm( const char *f_path );

Argv* argv_build();
void argv_add( Argv *_argv, const char *str );
char** argv_get( Argv *_argv );
void argv_free( Argv *_argv );

bool read_bool_ans();


void basename( char *dest, char *src, size_t size ) {

	int len;
	if ( !dest || !src )
		return;

	char *_str, *tok1, *tok2;

	len = strlen( src );
	_str = (char*) malloc( (len+1)*sizeof( char ) );
	strcpy( _str, src );

	tok1 = tok2 = strtok( _str, "/" );

	while( tok2 ) {
		tok2 = strtok( NULL, "/" );
		tok1 = tok2 ? tok2 : tok1;
	}

	strncpy( dest, tok1, size );

	free( _str );
}

void strcln();

int _comp();
int _link();
int _clean();
void _run();
void _dist();

bool read_bool_ans() {
	return false;
}

char* shift_collect_to(
	char **argv,
	int max,
	char *strl,
	const char *del,
	int *to
) {

	int i, len;
	char *_args;
	char _buff[ 1024 ] = "";

	for ( i=(*to+1); i<max; i++ ) {
		if ( !strcmptok( argv[ i ], strl, del ) ) {
			break;
		} else {
			strcat( _buff, argv[ i ] );
			strcat( _buff, " " );
		}
	}

	*to = --i;

	_args = NULL;
	len = strlen( _buff );

	if ( len ) {
		_args = (char*) malloc( (len+1)*sizeof( char ) );
		strcpy( _args, _buff );
	}

	return _args;
}

void shift_to(
	char **argv,
	int max,
	char *strl,
	const char *del,
	int *to
) {

	int i;

	for ( i=(*to+1); i<max; i++ ) {
		if ( !strcmptok( argv[ i ], strl, del ) )
			break;
	}

	*to = --i;

}

void strcln( char *str ) {

	int len;

	if ( !str )
		return;

	len = strlen( str );

	str[ len ? len - 1 : 0 ] = 0;
}

bool exists_cmd( const char *_cmd ) {

	int _sts;
	char _buff[ 128 ];

	sprintf( _buff, "command -v %s > /dev/null 2>&1 ", _cmd );
	_sts = system( _buff );

	return _sts ? false : true;
}



bool exists_dir( const char *path ) {

	DIR *dir;
	bool is;

	if ( !path )
		return false;

	dir = opendir( path );
	is = dir ? true : false;
	closedir( dir );

	return is;
}

bool exists_file( const char *f_path ) {

	if ( !f_path )
		return false;

	return access( f_path, F_OK ) != -1 ? true : false;
}

/* ===== GLOBAL ===== */
char ENV[100] = "";
const char CONF_FILE_NAME[] = "target.conf";
void *CONF_DATA[ MAX_CONFIG ];
ConfType CONF_TYPE[ MAX_CONFIG ];
char CONF_NAMES[ MAX_CONFIG ][ 128 ] = {{0}};

long _statmd( const char *f_path ) {

	time_t md;
	struct stat f_info = {};

	if ( !f_path )
		return -1;

	stat( f_path, &f_info );
	md = f_info.st_mtime;

	return (long)md;
}

void _run( const char *_args) {

	int i, sts;
	char _buff[ 128 ] = "";
	char _cmd[ 2048 ] = "";
	char **_target_args;
	char *_target;

	sts = 0;

	sts += conf_check_p( TARGET, _NULL_CHECK, _END_CHECK );

	if ( sts )
		return;

	_target = conf_get_p( TARGET, 1 );
	_target_args = ((char**)CONF_DATA[ TARGET_ARGS ]);

 	if ( !exists_file( _target ) ) {
		_p( _WARN, "not compiled yet\n" );
		return;
	}

	strcat( _cmd, "./" );
	strcat( _cmd, _target );
	strcat( _cmd, " " );

	if ( _args != NULL ) {
		strcat( _cmd, _args );
	} else if ( _target_args != NULL ) {

		for (i=1; _target_args[ i ]; i++ ) {
			sprintf( _buff, "%s ", _target_args[ i ] );
			strcat( _cmd, _buff );
		}

	}

	system( _cmd );

}

int main( int argc, char *argv[], char **env ) {

	int i, j, sts;
	FILE *_f;
	char *_arg, *_str;
	char _cmd[ 2048 ] = "";

	if ( argc < 2 ) {
		_p( _ERROR, "too few args\n");
		exit( 1 );
	}

	/* check for configuration file */
	_f = fopen( CONF_FILE_NAME, "r" );
	if ( !_f ) {
		_p( _ERROR, "%s%s%s: no such file\n", FG_BWHITE, CONF_FILE_NAME, _RESET );
		exit( 1 );
	}
	fclose( _f );


	/* set up configuration data */
	for ( i=0; i<MAX_CONFIG; i++ ) {
		CONF_DATA[ i ] = NULL;
	}

	/* set up configuration */
	CONF_TYPE[ DEFAULT_ENV ] = _STR_ARR;
	CONF_TYPE[ SRCDIR ] = _STR_ARR;
	CONF_TYPE[ INCDIR ] = _STR_ARR;
	CONF_TYPE[ OBJDIR ] = _STR_ARR;
	CONF_TYPE[ DISTDIR ] = _STR_ARR;
	CONF_TYPE[ DIST_IGNORE ] = _STR_ARR;
	CONF_TYPE[ CFLAGS ] = _STR_ARR;
	CONF_TYPE[ LDFLAGS ] = _STR_ARR;
	CONF_TYPE[ SRCS ] = _STR_ARR;
	CONF_TYPE[ TARGET ] = _STR_ARR;
	CONF_TYPE[ TARGET_ARGS ] = _STR_ARR;
	CONF_TYPE[ VGR_FLAGS ] = _STR_ARR;
	CONF_TYPE[ ASCII_VERSION ] = _STR_ARR;
	CONF_TYPE[ ASCII_TITLE ] = _STR_ARR;
	CONF_TYPE[ CLOG ] = _STR_ARR;


	strcpy( CONF_NAMES[ DEFAULT_ENV ], "DEFAULT_ENV" );
	strcpy( CONF_NAMES[ SRCDIR ], "SRCDIR" );
	strcpy( CONF_NAMES[ INCDIR ], "INCDIR" );
	strcpy( CONF_NAMES[ OBJDIR ], "OBJDIR" );
	strcpy( CONF_NAMES[ DISTDIR ], "DISTDIR" );
	strcpy( CONF_NAMES[ DIST_IGNORE ], "DIST_IGNORE" );
	strcpy( CONF_NAMES[ CFLAGS ], "CFLAGS" );
	strcpy( CONF_NAMES[ LDFLAGS ], "LDFLAGS" );
	strcpy( CONF_NAMES[ SRCS ], "SRCS" );
	strcpy( CONF_NAMES[ TARGET ], "TARGET" );
	strcpy( CONF_NAMES[ TARGET_ARGS ], "TARGET_ARGS" );
	strcpy( CONF_NAMES[ VGR_FLAGS ], "VGR_FLAGS" );
	strcpy( CONF_NAMES[ ASCII_VERSION ], "ASCII_VERSION" );
	strcpy( CONF_NAMES[ ASCII_TITLE ], "ASCII_TITLE" );
	strcpy( CONF_NAMES[ CLOG ], "CLOG" );

	/* load by default global configuration */
	env_load( CONF_FILE_NAME, "GLOBAL" );

	/* load default environment if it is defined */
	_str = conf_get_p( DEFAULT_ENV, 1 );

	if ( _str ) {
		env_load( CONF_FILE_NAME, _str );
		_p( _INFO, "[%s%s%s] as default environment\n", FG_YELLOW, _str, _RESET );
	}

	for ( i=1; i<argc; i++ ) {

		_arg = argv[ i ];

		if ( !strcmptok( _arg, "-e,--env", "," ) ) {

			if ( i == argc-1 || !strncmp( argv[ i + 1 ], "-", 1 ) ) {
				_p( _ERROR, "env: too few args\n", _arg );
				shift_to( argv, argc, "-e,--env", ",", &i );
			} else {

				sts = env_load( CONF_FILE_NAME, argv[ i + 1 ] );

				if ( !sts ) {
					// success
				} else if ( sts == 2 ) {
					_p( _ERROR, "env: [%s] not found\n", argv[ i + 1 ] );
				}

				if ( sts ) {
					shift_to( argv, argc, "-e,--env", ",", &i );
				} else {
					i++; // shift next
				}

			}

		} else if ( !strcmptok( _arg, "-d,--dist", "," ) ) {
			_p( _TASK_START, "DIST START" );
			_dist();
			_p( _TASK_END, "DIST END" );

		} else if ( !strcmptok( _arg, "-m,--cmem", "," ) ) {

			if ( !exists_cmd( "valgrind" ) ) {
				_p( _ERROR, "valgrind: command not found\n" );
				shift_to( argv, argc, "-e,--env", ",", &i );
			} else {

				strcpy( _cmd, "valgrind" );
				strcat( _cmd, " ./" );
				strcat( _cmd, conf_get_p( TARGET, 1 ) );
				strcat( _cmd, " " );

				_str = shift_collect_to( argv, argc, "-e,--env", ",", &i );

				if ( _str ) {
					strcat( _cmd, _str );
					free( _str );
					_str = NULL;
				} else {

					j=1;
					_str = conf_get_p( VGR_FLAGS, j );

					while ( _str ) {
						strcat( _cmd, _str );
						strcat( _cmd, " " );
						j++;
						_str = conf_get_p( VGR_FLAGS, j );
					}

				}

				system( _cmd );

			}

		} else if ( !strcmptok( _arg, "-r,--run", "," ) ) {

			_p( _TASK_START, "RUN START" );

			_str = shift_collect_to( argv, argc, "-e,--env", ",", &i );

			_run( _str );

			if ( _str ) {
				free( _str );
				_str = NULL;
			}

			_p( _TASK_END, "RUN END" );

		} else if ( !strcmptok( _arg, "-m,--cmem", "," ) ) {


		} else if ( !strcmptok( _arg, "-cl,--clean", "," ) ) {

			_p( _TASK_START, "CLEAN START" );
			_clean();
			_p( _TASK_END, "CLEAN END" );

		} else if ( !strcmptok( _arg, "-c,--comp", "," ) ) {

			_p( _TASK_START, "COMPILATION START" );

			/* print ascii decorations */
			printf("%s", FG_BPURPLE );
			print_file( stdout, (char*)conf_get_p( ASCII_TITLE, 1 ) );
			printf("%s", _RESET );

			printf("%s", FG_BYELLOW );
			print_file( stdout, (char*)conf_get_p( ASCII_VERSION, 1 ) );
			printf("%s", _RESET );

			sts = _comp();

			if ( sts <= 0 ) {

				if ( sts == 0 ) {

					if ( _link() == 0 ) {
						_p( _SUCCESS, "link success -> %s%s%s\n", FG_BCYAN, (char*)conf_get_p( TARGET, 1 ), _RESET );
					} else {
						_p( _ERROR, "link failed\n" );
					}

				} else {
					// nothing to be linked
				}

			} else {
				_p( _ERROR, "compilation failed\n");
			}
			_p( _TASK_END, "COMPILATION END" );

		} else {

			_p( _WARN, "unknown option '%s'\n", _arg );

		}

	}

	/* clean up config data */
	conf_free_all();

	return 0;
}

void conf_free_all() {
	int i;
	for ( i=0; i<MAX_CONFIG; i++ ) {
		conf_free_p( i );
	}
}

void conf_alloc_p( Conf_p p, ... ) {

	int i, q;
	va_list _list;

	if ( p < 0 || p >= MAX_CONFIG )
		return;

	conf_free_p( p );

	va_start( _list, p );

	if ( CONF_TYPE[ p ] == _STR_ARR ) {
		q = va_arg( _list, int )+1;
		CONF_DATA[ p ] = (char**)malloc( q*sizeof(char*) );
		for (i=0; i<q; i++) {
			((char**)CONF_DATA[ p ])[ i ] = NULL;
		}
	}

	va_end( _list );

}


void conf_set_p( Conf_p p, ... ) {

	int idx, len;
	char *str;
	va_list _list;
	char **__arr;

	if ( !CONF_DATA[ p ] || p < 0 || p >= MAX_CONFIG )
		return;

	va_start( _list, p );

	if ( CONF_TYPE[ p ] == _STR_ARR ) {
		idx = va_arg( _list, int );
		str = va_arg( _list, char* );
		len = strlen( str );

		__arr = ((char**)CONF_DATA[ p ]);

		if ( __arr[ idx ] ) {
			free( __arr[ idx ] );
		}
		__arr[ idx ] = (char*)malloc( (len+1)*sizeof( char ) );

		if ( __arr[ idx ] ) {
			strcpy( __arr[ idx ], str );
		}

	}

	va_end( _list );

}

Conf_p conf_get_p_by_name( const char *_name ) {

	int i;
	Conf_p _p;

	if ( !_name )
		return NONE;

	_p = NONE;

	for ( i=0; i<MAX_CONFIG; i++ ) {
		if ( !strcmp( CONF_NAMES[ i ], _name ) ) {
			_p = (Conf_p)i;
			break;
		}
	}

	return _p;
}

void* conf_get_p( Conf_p p, ... ) {

	int i, idx;
	void *vp;
	va_list _list;

	if ( !CONF_DATA[ p ] || p < 0 || p >= MAX_CONFIG )
		return NULL;

	vp = NULL;
	va_start( _list, p );

	if ( CONF_TYPE[ p ] == _STR_ARR ) {

		if ( CONF_DATA[ p ] ) {

			idx = va_arg( _list, int );
			i = 0;
			while ( i != idx ) {

				if ( !((char**)CONF_DATA[ p ])[ i ] ) {
					break;
				} else {
					i++;
				}
			}

			vp = ((char**)CONF_DATA[ p ])[ i ];

		}


	}

	va_end( _list );

	return vp;

}

void conf_free_p( Conf_p p ) {

	int i;

	if ( p < 0 || p >= MAX_CONFIG )
		return;

	if ( CONF_TYPE[ p ] == _STR_ARR ) {

		if ( CONF_DATA[ p ] ) {

			for (i=0; ((char**)CONF_DATA[p])[i]; i++) {
				free( ((char**)CONF_DATA[p])[i] );
			}

			free( CONF_DATA[ p ] );
		}

	}

}

int print_file( FILE *stream, const char *f_path ) {

	FILE *f;
	char c;

	if ( !f_path )
		return 1;

	f = fopen( f_path, "r" );

	if ( !f )
		return 2;

	while ( fscanf( f, "%c", &c ) == 1 ) {
		fprintf( stream, "%c", c );
	}

	fclose( f );

	return 0;
}

int conf_check_p( Conf_p p, ... ) {

	int i, j, sts;
	void *data;
	char *str;
	ConfType type;
	va_list _list;
	Conf_check chk;
	int to_check[ MAX_CHECKS ] = {};

	if ( p < 0 || p >= MAX_CONFIG )
		return -1;

	type = CONF_TYPE[ p ];
	data = CONF_DATA[ p ];
	sts = 0;

	va_start( _list, p );

	chk = va_arg( _list, Conf_check );

	while ( chk != _END_CHECK ) {

		if ( chk >= 0 && chk < MAX_CHECKS ) {
			to_check[ chk ] = 1;
		}
		chk = va_arg( _list, Conf_check );
	}

	for ( i=0; i < MAX_CHECKS; i++ ) {

		j = to_check[ i ];
		if ( j != 1 ) continue;

		if ( i == _NULL_CHECK ) {

			if ( !data ) {
				sts = _NULL_CHECK;
				_p( _ERROR, "$%s is not defined\n", CONF_NAMES[ p ] );
				break;
			}

		}

		str = conf_get_p( p, 1 );

		if ( str ) {

			if ( i == _FILE_CHECK && !exists_file( str ) ) {
				sts = _FILE_CHECK;
				_p( _ERROR, "%s: '%s' no such file\n", CONF_NAMES[ p ], str );
			}

			if ( i == _DIR_CHECK && !exists_dir( str ) ) {
				sts = _DIR_CHECK;
				_p( _ERROR, "%s: '%s' no such directory\n", CONF_NAMES[ p ], str );
			}

		}

	}

	va_end( _list );

	return sts;
}

void conf_upd( char **__data, int size ) {

	Conf_p p;
	char *pn; /* parameter name */

	p = NONE;

	if ( !__data )
		return;

	pn = __data[ 0 ];

	p = conf_get_p_by_name( pn );

	if ( p == NONE )
		return;

	if ( CONF_TYPE[ p ] == _STR_ARR ) {
		conf_free_p( p );
		CONF_DATA[ p ] = __data;
	}

}

int strcmptok(
	const char *str,
	char *strl,
	const char *del
) {

	char *tok;
	char _buff[1024];

	if ( !str || !strl || !del )
		return 1;

	strncpy( _buff, strl, sizeof( _buff ) );
	_buff[ sizeof( _buff ) - 1 ] = 0;

	tok = strtok( _buff, del );

	while ( tok ) {
		if ( !strcmp( tok, str ) )
			return 0;
		tok = strtok( NULL, del );
	}

	return 1;
}

int env_load( const char *f_name, const char *env ) {

	FILE *cf;

	int i, j,
			sts,
			vi, /* value index */
			len; /* used for string lengths */
	char c;
	Conf_p _p; /* conf parameter */
	char _line[ 1024 ] = "";
	char _sbuff[ 1024 ] = "";
	char _vbuff[ 100 ][ 256 ] = {{0}};
	bool	envSearch, /* environment search process */
				addChar, /* indicates is a char shold be added to the buffer */
				isArr, /* indicates if the current value is an array */
				isStr, /* indicates if the current value is a string */
				pend; /* indicates the end of a parameter */

	cf = fopen( f_name, "r" );

	if ( !cf )
		return -1;

	vi=0;
	sts=0;
	pend=false;
	isArr=false;
	isStr=false;
	envSearch = true;
	_p = NONE;

	while ( fgets( _line, sizeof( _line ), cf ) ) {

		_line[ strlen( _line ) - 1 ] = 0; /* cleans \n */

		/* env search */
		if ( envSearch ) {

			if ( !strncmp( _line, "[", 1 ) ) {

				i=1; j=0;
				while ( _line[ i ] != ']' ) {

					_sbuff[ j ] = _line[ i ];
					_sbuff[ j + 1 ] = 0;
					j++;
					i++;
				}

				if ( !strcmp( _sbuff, env ) ) {
					envSearch = false;
					j=0;
				}

			}
			continue;
		}

		/* stop parsing when other environment starts */
		if ( !envSearch && !strncmp( _line, "[", 1 ) ) {
			break;
		}

		len = strlen( _line ); /* get the length of the line */


		for (i=0; i<=len; i++) {

			c = _line[ i ];
			addChar = true;

			if (  c == '#' ) { pend=true; }

			if ( c == '=' && vi == 0 && !isStr ) {
				vi=1;
				j=0;
				addChar = false;
			}

			if ( c == ' ' || c == '\t' ) {
				addChar = false;
			}

			if ( c == '[' ) {
				isArr=true;
				addChar=false;
			}

			if ( c == ']' ) {
				isArr=false;
				addChar=false;
				pend = true;
			}

			if ( c == ',' && isArr && !isStr ) {
				vi++;
				j=0;
				addChar = false;
			}

			if ( c == '"' ) {
				isStr = !isStr;
				addChar = false;
			}

			if ( isStr && c != '"' ) addChar = true;

			if ( c == '\0' && vi == 1 && !isStr && !isArr) {
				pend = true;
				addChar = false;
			}

			if ( addChar && c ) {
				_vbuff[ vi ][ j ] = c;
				_vbuff[ vi ][ j + 1 ] = 0;
				j++;
			}

			if ( pend ) {

				vi++;
				_p = conf_get_p_by_name(  _vbuff[ 0 ] );

				if ( _p != NONE ) {

					conf_alloc_p( _p, vi );

					for ( j=0; j<vi; j++ ) {
						conf_set_p( _p, j, _vbuff[ j ] );
					}

				}

				/* clean buffers */
				for ( j=0; j<vi; j++ ) {
					_vbuff[ j ][ 0 ] = 0;
				}
				_sbuff[0] = 0;

				/* reset flags */
				j=0;
				vi=0;
				isArr=false;
				isStr=false;
				pend=false;
				addChar = false;
			}

		}

	}

	if ( envSearch ) {
		sts = 2;
	} else {
		strcpy( ENV, env );
	}

	fclose( cf );

	return sts;
}

void argv_free( Argv *argv ) {

	int i;

	if ( !argv )
		return;

	if ( argv->_argv ) {
		for ( i=0; i < argv->_n; i++ ) {
			free( argv->_argv[ i ] );
			argv->_argv[ i ] = NULL;
		}
		free( argv->_argv );
	}

	free( argv );

}

Argv* argv_build( int q ) {

	int i;
	Argv *argv;

	argv = (Argv*) malloc( sizeof( Argv ) );

	if ( argv ) {
		argv->_argv = (char**)malloc( q*sizeof( char* ) );
		if ( argv->_argv ) {
			for (i=0; i<q; i++) {
				argv->_argv[ i ] = NULL;
			}
			argv->_n = 0;
			argv->_max = q;

		} else {
			argv_free( argv );
		}
	}

	return argv;
}

void argv_add( Argv *argv, const char *str ) {

	int len;
	if ( !argv || !str )
		return;

	if ( argv->_n+1 < argv->_max ) {
		len = strlen( str );
		argv->_argv[ argv->_n ] = (char*) malloc( (len+1)*sizeof(char) );
		strcpy( argv->_argv[ argv->_n ], str );
		argv->_n++;
	}

}

char** argv_get( Argv *argv ) {
	if ( !argv )
		return NULL;

	return argv->_argv;
}


int _rm( const char *path ) {

	int sts;
	pid_t pid;

	if ( !path )
		return 1;

	sts = 1;

	if ( exists_file( path ) || exists_dir( path ) ) {

		pid = fork();
		if ( pid == 0 ) {
			_p( _INFO, "removing: %s%s%s\n", FG_BYELLOW, path, _RESET );
			execl( "/bin/rm", "rm", "-rf" , path, NULL );
		} else {
			waitpid( pid, &sts, 0 );
		}

	}	else {
		_p( _INFO, "already removed: %s%s%s\n", FG_BWHITE, path, _RESET );
	}


	return sts;
}

int _clean() {

	int i, sts;
	char *_obj = conf_get_p( OBJDIR, 1 );
	char *_target = conf_get_p( TARGET, 1 );
	char **_srcs = ((char**)CONF_DATA[ SRCS ]);
	char file_o[ 128 ] = ""; /* temporary object file name */

	sts = 0;

	if ( _target ) {
		_rm( _target );
	}

	if ( _srcs ) {

		for (i=1; _srcs[ i ]; i++ ) {
			sprintf( file_o, "%s/%s.o", _obj, _srcs[ i ] );
			_rm( file_o );
		}

	}

	return 0;

}

int _link( ) {

	int i, sts;
	pid_t pid; /* process id */
	char *_obj = conf_get_p( OBJDIR, 1 );
	char *_target = conf_get_p( TARGET, 1 );
	char **_srcs = ((char**)CONF_DATA[ SRCS ]);
	char **_ldflags = ((char**)CONF_DATA[ LDFLAGS ]);
	char file_o[ 128 ] = ""; /* temporary object file name */
	Argv *_argv;

	_argv = argv_build( 50 );

	argv_add( _argv, "gcc" );
	argv_add( _argv, "-fdiagnostics-color=always" );

	for (i=1; _srcs[ i ]; i++ ) {
		sprintf( file_o, "%s/%s.o", _obj, _srcs[ i ] );
		argv_add( _argv, file_o );
	}

	if ( _ldflags ) {
		for ( i=1; _ldflags[ i ]; i++ ) {
			argv_add( _argv, _ldflags[ i ] );
		}
	}

	argv_add( _argv, "-o" );
	argv_add( _argv, _target );

	sts = 0;
	pid = fork();
	if ( pid == 0 ) {
		execv( "/usr/bin/gcc", argv_get( _argv ) );
	} else {
		waitpid( pid, &sts, 0 );
	}

	argv_free( _argv );

	return sts;
}

void _dist() {

	int i, sts;
	FILE *pf;
	char _v[ 64 ];
	char _dir[ 256 ];
	char _cmd[ 1024 ];
	char _zname[ 256 ];
	char **_ignore;
	char *_ascii_v, *_target, *_dist, *_clog;
	time_t t;
	struct tm tm;

	sts = 0;

	sts += conf_check_p( TARGET, _NULL_CHECK, _END_CHECK );

	if ( sts )
	 	return;

	_cmd[0] = 0;
	_dir[0] = 0;
	_v[0] = 0;

	t = time(NULL);
	tm = *localtime(&t);

	_ignore = ((char**)CONF_DATA[ DIST_IGNORE ] );
	_target = conf_get_p( TARGET, 1 );
	_dist = conf_get_p( DISTDIR, 1 );
	_clog = conf_get_p( CLOG, 1 );

	getcwd( _dir, sizeof( _dir ) );
	basename( _dir, _dir, sizeof( _dir ) );

	if ( _clog ) {

		sprintf( _cmd, "grep -Po -m1 'v[0-9].*' %s", _clog );

		pf = popen( _cmd, "r" );
		while( fgets( _v, sizeof( _v ), pf ) );
		strcln( _v ); // clean \n

		pclose( pf );

	}

	if ( _v[0] ) {

		_ascii_v = conf_get_p( ASCII_VERSION, 1 );


		if ( exists_cmd( "figlet" ) && exists_file( _ascii_v ) ) {

			_p( _INFO, "updating ASCII file: %s%s%s\n", FG_BWHITE, _ascii_v, _RESET );

			sprintf( _cmd, "figlet %s > %s", _v, _ascii_v );
			system( _cmd );

			printf( "%s", FG_BYELLOW );
			print_file( stdout, _ascii_v );
			printf( "%s", _RESET );

		}

		sprintf( _zname, "%s_%s_%04d%02d%02d.zip", _target, _v, tm.tm_year+1900, tm.tm_mday, tm.tm_mon );
	} else {
		sprintf( _zname, "%s_%04d%02d%02d.zip", _target, tm.tm_year+1900, tm.tm_mday, tm.tm_mon );
	}

	sprintf( _cmd, "zip -r -y -q %s %s", _zname, _dir );

	if ( _ignore ) {

		strcat( _cmd, " -x ");
		for (i=1; _ignore[ i ]; i++ ) {
			strcat( _cmd, _dir );
			strcat( _cmd, "/" );
			strcat( _cmd, _ignore[ i ] );
			strcat( _cmd, " " );
		}
	}

	_p( _INFO, "zipping: %s%s%s ... ", FG_BYELLOW, _zname, _RESET );

	chdir( ".." );

	sts = system( _cmd );

	if ( !sts ) {

		printf("%sDONE%s\n", FG_BGREEN, _RESET );

		sprintf( _cmd, "mv %s %s", _zname, _dir );
		system( _cmd );

		chdir( _dir ); // go back again to the main project directory

		if ( exists_dir( _dist ) ) {
			sprintf( _cmd, "mv %s %s", _zname, _dist );
			system( _cmd );
		} else {
			_p( _WARN, "DISTDIR was ignored\n", CONF_NAMES[ DISTDIR ] );
		}

	} else {
		printf("%sERROR%s\n", FG_BRED, _RESET );
	}

	chdir( _dir );

}

int _comp() {

	int i, sts;
	int chgs; /* changes */
	pid_t pid; /* process id */
	bool cit; /* compile it flag */
	long md;
	char *_src = conf_get_p( SRCDIR, 1 );
	char *_inc = conf_get_p( INCDIR, 1 );
	char *_obj = conf_get_p( OBJDIR, 1 );
	char *_target = conf_get_p( TARGET, 1 );
	char **_srcs = ((char**)CONF_DATA[ SRCS ]);
	char file_h[ 128 ], file_c[ 128 ], file_o[ 128 ]; /* temporary file names */


	sts = 0;
	chgs = 0;

	sts += conf_check_p( TARGET, _NULL_CHECK, _END_CHECK );
	sts += conf_check_p( SRCDIR, _NULL_CHECK, _DIR_CHECK, _END_CHECK );
	sts += conf_check_p( OBJDIR, _NULL_CHECK, _DIR_CHECK, _END_CHECK );
	sts += conf_check_p( SRCS, _NULL_CHECK, _END_CHECK );


	if ( _inc ) {

		if ( !exists_dir( _inc ) ) {
			sts=1;
			_p( _ERROR, "invalid INCDIR: '%s'\n", _inc );
		}

	} else if ( sts == 0 ) {

		/* clone SRCDIR into INCDIR */
		conf_alloc_p( INCDIR, 2 );
		conf_set_p( INCDIR, 0, CONF_NAMES[ INCDIR ] );
		conf_set_p( INCDIR, 1, _src );
		_inc = conf_get_p( INCDIR, 1 );
		_p( _WARN, "using %s as %s%s%s\n", CONF_NAMES[ INCDIR ], FG_CYAN, _src, _RESET );
	}

	if ( sts != 0 )
		return 1;

	/* searh files in source directory */
	for ( i=1; _srcs[ i ]; i++ ) {

		sprintf( file_o, "%s/%s.o", _obj, _srcs[ i ] );
		sprintf( file_c, "%s/%s.c", _src, _srcs[ i ] );
		sprintf( file_h, "%s/%s.h", _inc, _srcs[ i ] );

		if ( !exists_file( file_c ) ) {
			sts=1;
			_p( _ERROR, "no such file: %s%s%s\n", FG_BRED, file_c, _RESET );
			break;
		}

		cit = true;

		if ( exists_file( _target ) ) {

			md = _statmd( _target );

			if ( md > _statmd( file_c ) && md > _statmd( file_h ) ) {
				cit=false;
			}

		} else {

			if ( exists_file( file_o ) ) {
				if ( _statmd( file_o ) > _statmd( file_c ) ) {
					cit=false;
				}
			}
		}

		if ( cit ) {

			chgs++;
			_p( _INFO, "compiling: %s%s%s -> %s\n", FG_BYELLOW, file_c, _RESET, file_o );

			pid = fork();

			if ( pid == 0 ) {

				execl(
					"/usr/bin/gcc",
					"gcc", "-fdiagnostics-color=always",
					"-I", _inc,
					"-c", file_c,
					"-o", file_o,
					NULL
				);

			} else {
				waitpid(pid,&sts,0);
			}

		} else {
			_p( _INFO, "up to date: %s%s%s -> %s\n", FG_BGREEN, file_c, _RESET, file_o );
		}

	}

	if ( chgs == 0 && exists_file( _target ) ) {
		sts = -1;
	}

	return sts;

}

void _p( PrintType type, const char *frmt, ... ) {

	va_list _list;
	char _buff[ 1024 ];

	va_start( _list, frmt );
	vsprintf( _buff, frmt, _list );
	va_end( _list );

	switch ( type ) {

		case _ERROR:
			printf( "%serror%s: %s", FG_BRED, _RESET, _buff );
			break;
		case _SUCCESS:
			printf( "%ssuccess%s: %s", FG_BGREEN, _RESET, _buff );
			break;
		case _INFO:
			printf( "%sinfo%s: %s", FG_BCYAN, _RESET, _buff );
			break;
		case _WARN:
			printf( "%swarn%s: %s", FG_BYELLOW, _RESET, _buff );
			break;
		case _TASK_START:
			printf("========== [%s%s%s] %s%s%s\n", FG_BPURPLE, ENV, _RESET, FG_BGREEN, _buff, _RESET );
			break;
		case _TASK_END:
			printf("========== [%s%s%s] %s%s%s\n", FG_BPURPLE, ENV, _RESET, FG_BRED, _buff, _RESET );
			break;
	}

	fflush( stdout );

}
