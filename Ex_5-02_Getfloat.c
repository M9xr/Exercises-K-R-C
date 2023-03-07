/* Exercise 5-1. As written, "getin" treats a + or - not followed by a digit as a valid represenatation of zero. Fix it to push such a character back on the input. */
/* Exercsie 5-2. Write "getfloat", the float-point analog of getint. What type does "getfloat" return as its function value? */
// It returns int I belive.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> // atof

#define MAXCHAR 1000
char getch (void);
void ungetch (char);
int xgetfloat (double *);

int main (void) {

	double array[MAXCHAR];
	int n, sciernisko;

	for (n = 0; n < MAXCHAR && (sciernisko = xgetfloat (&array[n])) != EOF; n++) 
		printf("num[%d] = %g,\tvalue returned: %d (%s)\n", n, array[n], sciernisko, sciernisko != 0 ? "number" : "not a number");
	
	return 0;

}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

char getch (void) {

	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch (char c) {

	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getint: get next integer from input into *pn */
int xgetfloat (double *pn) {

	int sign;
	double base = 0.1;
	int c;
	double rem;

	while (isspace (c = getch()))	/* skip white space */
		;
	if (!isdigit (c) && c != EOF && c != '+' && c != '-' && c != '.') {
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
	for (*pn = 0; isdigit (c); c = getch()) {
		*pn = 10 * *pn + (c - '0');
		printf("Test for digit\n");
	}
	if (c == '.'){
		c = (int) (getch() - '0');
		printf("VLAUE OD C = %d\n", c);
		base = 0.1;
	//	if (c >= '0' && c <= '9')
			for (rem = 0.0; isdigit(c); c = (getch() - 0.0)) {
				printf("rem=%g\tc=%d\tbase=%g\n\n", rem, c, base);
				rem = rem + ((c - 0) * base) - 0; 
				printf("rem =%g\t c = %d\tbase=%g\n", rem, c, base);
				base = base * 0.1; printf("base =%g\n", base);
			}
	//	else
	//		printf("Error\n");
	}
	*pn = ((*pn + rem) * sign);
	if (c != EOF)
		ungetch (c);
	return c;
}
