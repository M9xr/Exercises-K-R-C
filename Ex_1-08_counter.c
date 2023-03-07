/* Exercise 1-8. Write a program to count blanks, tabs, and newlines. */

#include <stdio.h>

int main(void) {

	long blanks = 0, tabs = 0, newlines = 0;
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\n')
			++newlines;
		if (c == '\t')
			++tabs;
		if (c == ' ')
			++blanks;
	}
	printf("blanks:%ld  tabs:%ld  newlines:%ld\n", blanks, tabs, newlines);
}

	

	
