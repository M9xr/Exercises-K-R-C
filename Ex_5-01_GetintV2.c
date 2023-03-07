/* Exercise 5-1. As written, "getint" trats a + or - not followed by a digit as a valid representation of zero. Fix it to push a character back on the input. */

#include <stdio.h>

int getint (int *);

#define SIZE 1000

int main (void) {

	int n, array[SIZE], m;
	for (n = 0; n < SIZE && getint (&array[n]) != EOF; n++)
		;
	for (m = (n - 1); m >= 0; --m)
		printf("%d", array[m]);
	printf("\n");
}
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch (void) {

	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch (int c) {

	if (bufp >= BUFSIZE)
		printf("umgetch: too many characters\n");
	else
		buf[bufp++] = c;
}

#include <ctype.h>

/* getint: get next integer from input into *pn */
int getint (int *pn) {

	int c, sign;

	while (isspace (c = getch()))
		;
	if (!isdigit (c) && c != EOF && c != '+' && c != '-') {
		ungetch (c); // not a number
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit (c)) {
			ungetch (sign == 1 ? '+' : '-');
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch (c);
	return c;
}


/* getint-My_version_deLux */

int xgetint (int * pn) {

	int c, sign;

	while (isspace (c = getch()))
		;
	if (!isdigit (c) && c != EOF && c != '-' && c != '+')
		return 0;
	sign = (c == '-') ? : -1 : 1;
	if (c == '-' || c == '+') {
		c = getch();
		if (!isdigit (c))
			ungetch (c);
		else
			for (*pn = 0; isdigit (c = getch());)
				*pn = *pn * 10 + (c -'0');
	}
	*pn *= sign;
	if (c != EOF)
		ungetch (c);
	return c;
}


