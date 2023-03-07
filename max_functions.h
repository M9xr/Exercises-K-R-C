#ifndef MAX_FUNCTIONS
#define MAX_FUNCTIONS

#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

/* get a (possibly pushed-back) character */
int getch (void) {

	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch (int c) {

	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else {
		if (c != EOF)
			buf[bufp++] = c;
		else
			buf[bufp++] = '\0';
	}
}


/* getline: read a line into s, return length */
int xgetline(char s[], int lim) {

	int c, i;
	
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* strlen: retrun length of string s */
/*int strlen(char *s) {

	char *p = s;

	while (*p != '\0')
		p++;
	return p - s;
}
*/
#endif




