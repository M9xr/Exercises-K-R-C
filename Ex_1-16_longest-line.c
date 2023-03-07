/* Exercise 1-16. Revise the main routine of the longest-line program so it will correctly print the length of arbitrary long input lines, and as much as possible of the text. */

#include <stdio.h>
#define MAXLINE 40	/* maximum input line length */

int xgetline(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line */
int main(void) {

	int len;		/* current line length */
	int max;		/* maximum length seen so far */
	char line[MAXLINE];	/* current input line */
	char longest[MAXLINE];	/* longest line saved here */
	int len2, cond;		/* if line is longer than limit, cond == 1 */
	char line2[MAXLINE];	/* If line is longer than limit, line2 copies characters after the limit. 
				   The purpose is to properly process the rest of the input, and continously save it into array "line"  */

	max = cond = len2 = 0;
	while ((len = xgetline(line, MAXLINE)) > 0) {
		if (cond == 1)
			;
		else if (max == MAXLINE - 1) {
			copy(line2, line);
			len2 = len;
			cond = 1;
		}
		else if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0)				/* there was a line */
		printf("\n%s", longest);
	if (len2 > 0) {				/* it was bigger than limit */
		printf("%s", line2);
		if (line2[len2-1] != '\n')	/* the line hasn't reached '\n' */
			printf("\n");		
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

/* copy: copy 'from' into 'to'; assume 'to' is big enough */
void copy(char to[], char from[]) {

	int i;
	
	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}

