/* Exercise 5-1. As written, "getint" treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input */

#include <stdio.h>
#include <ctype.h>

int getch (void);
void ungetch (int);
int getint (int *);

#define SIZE 250

int main (void) {

	char s1[] = "The Earth = 12 740 - Uranus -51118 492.248 Ceres";
	int n, array[SIZE], rval;
	int i = 0;

	for (n = 0; n < SIZE && (rval = getint (&array[n])) != EOF; n++) {
		if (rval != 0)
			printf("Place:%d   Value:%d\n", n, array[n]);
		else {
			printf("Not a number for Place:%d Please, provide a number:\n", n);
			--n;
		}
	}

	return 0;
}

/* getint: get next integer from input into *pn */
/* Return 0 if input  is not a digit, EOF for end of file, a positive value if input contains a valid number */
int getint (int *pn) {

	int c, sign;

	while (isspace(c = getch()))	/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		//ungetch(c);	/* it is no a number /
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
		while (isspace(c))
			c = getch();
		if (!isdigit(c)) {
			ungetch(sign == -1 ? '-' : '+');
			return 0;
		}
		else
			;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch (void) {
	
//	printf("Getch Entry\n");
	return (bufp > 0 ? buf[--bufp] : getchar());
}

void ungetch (int c) {

	if (bufp >= BUFSIZE)
		printf("Error: ungetch - too many characters\n");
	else
		buf[bufp++] = c;
//	printf("Ungetch exit\n");
}
