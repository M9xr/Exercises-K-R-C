/* Exercise 2-2. Write a loop equivalent to the "for" loop above without using "&&" and "||". */

#include <stdio.h>

#define MAXLINE 1000

int xgetline(char line[], int maxline);

int main(void) {

	int len;
	char line[MAXLINE];

	while ((len = xgetline(line, MAXLINE)) > 0) 
		printf("%s", line);

	return 0;
}

int xgetline(char s[], int lim) {

	int c, i;

	for (i = 0; (i <= lim - 1) == ((c = getchar()) != EOF) == (c != '\n'); ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
	
