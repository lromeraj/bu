#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main()  {

	struct winsize win;

	while( 1 ) {
		ioctl( STDOUT_FILENO, TIOCGWINSZ, &win );
		printf("\033c");
		printf("%dx%d\n", win.ws_col, win.ws_row );
	}

	return 0;
}
