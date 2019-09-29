#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

int main()
{

	wchar_t wc = L'\u2649';

	setlocale(LC_ALL, "");

	printf("size: %d, HEX: %x, sym: \e[45m%lc\e[0m\n", (int)sizeof(wc), wc, wc );

	return 0;
}
