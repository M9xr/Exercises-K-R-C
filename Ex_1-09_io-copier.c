/* Exercise 1-9. Write a program to copy its input to itr output, replacing each string of on ore more blanks by a single blank. */

#include <stdio.h>

int main(void) {

	int c;
	long blanks = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ' && blanks == 0) {
			putchar(c);
			++blanks;
		}
		if (c != ' ') {
			putchar(c);
			blanks = 0;
		}

	}
}
