/* Exercise 1-12. Write a program that prints its input one word per line. */

#include <stdio.h>

#define TRUE  1
#define FALSE 0

int main(void) {

	int c, word;
	word = FALSE;

	while ((c = getchar()) != EOF) {
		if (c != ' '  && c != '\t' && c != '\n') {
			putchar(c);
			word = TRUE;
		}
		else if ((c == ' ' || c == '\t') && word == TRUE) {
			putchar('\n');
			word = FALSE;
		}
		     else
				putchar(c);
	}
}


