/* Exercise 5-1. As written, "getin" treats a + or - not followed by a digit as a valid represenatation of zero. Fix it to push such a character back on the input. */

#include <stdio.h>
#include <ctype.h>

#define MAXCHAR 1000
int getch (void);
void ungetch (int);
int getint (int *);

int main (void) {

	int array[MAXCHAR], n, sciernisko;

	for (n = 0; n < MAXCHAR && (sciernisko = getint (&array[n])) != EOF; n++) 
		printf("num[%d] = %d,\tvalue returned: %d (%s)\n", n, array[n], sciernisko, sciernisko != 0 ? "number" : "not a number");
	
	return 0;

}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch (void) {

	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch (int c) {

	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getint: get next integer from input into *pn */
int getint (int *pn) {

	int c, sign;

	while (isspace (c = getch()))	/* skip white space */
		;
	if (!isdigit (c) && c != EOF && c != '+' && c != '-') {
	//	ungetch (c);	it is not a number 
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit(c)) {
			ungetch (sign == 1 ? '+' : '-');
			return 0;
		}
	}
	for (*pn = 0; isdigit (c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch (c);
	return c;
}
