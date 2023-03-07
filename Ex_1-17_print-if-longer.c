/* Exercise 1-17. Write a program to print all input lines that are longer than 80 characters */
 
#include <stdio.h>
#define MAXLINE 238	/* maximum input line length */

int xgetline(char line[], int maxline);

/* print the longest input line */
int main(void) {

	int len;		/* current line length */
	int max;		/* maximum length seen so far */
	char line[MAXLINE];	/* current input line */
	char longest[MAXLINE];	/* longest line saved here */
	long volume;		/* the length of a long line */
	int first = 0;		/* if it is the first entry of a long line first == 0 else 1 */
	max = volume = 0;
	while ((len = xgetline(line, MAXLINE)) > 0) {
		if (first == 0) {
			printf("\n\n");
			first = 1;
		}
		if (len >= 81)
			printf("%s", line);
	}

	return 0;
}

/* getline: read a line into s, return length */
int xgetline(char s[], int lim) {

	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}


