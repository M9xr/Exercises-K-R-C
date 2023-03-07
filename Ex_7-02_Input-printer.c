/* Exercise 7.2 Write a prigram that will print arbitrary input in a sensible way.
 * As a mimimum it should print non-graphic characters in octal or hexadecimal according to local custom, and break long text lines. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXCHARS 120
#define FORMAT1 "%X"
#define FORMAT2 "%o"

int main(int argc, char *argv[]) {

	char *type = FORMAT1;
	if (argc > 1)
		if ((strcmp((argv[1]), "-octal") == 0))
			type = FORMAT2;
		
	int c, lim = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n')
			lim = 0;
		else if (++lim == MAXCHARS) {
			lim  = 0;
			putchar('\n');
		}

		if (isgraph(c) || isspace(c))
			putchar(c);
		else
			printf(type, c);
	}
	return 0;
}
	
