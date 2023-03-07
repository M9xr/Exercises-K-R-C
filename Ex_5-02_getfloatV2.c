/* Exercise 5-1. As written, "getint" treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input */
/* Exercuse 5-2. Write "getfloat", the floating-point analog of "getint". What type does "getfloat" return as its function value? */
// Getfloat returns integers.

#include <stdio.h>
#include <ctype.h>

int getch (void);
void ungetch (int);
int getint (int *);
int getfloat (double *);

#define SIZE 250

int main (void) {

	int n, array[SIZE], rval, rval2, n2, i2;
	int i = i2 = 0;
	double array2[SIZE];

	/*for (n = 0; n < SIZE && (rval = getint (&array[n])) != EOF; n++) {
		if (rval != 0)
			printf("Place:%d   Value:%d\n", n, array[n]);
		else {
			printf("Not a number for Place:%d Please, provide a number:\n", n);
			--n;
		}
	}*/
	for (n2 = 0; n2 < SIZE && (rval2 = getfloat (&array2[n2])) != EOF; n2++) {
		if (rval2 != 0)
			printf("Place:%d\tValue:%g\n", n2, array2[n2]);
		else {
			printf("Not a valid input for :%d\n", n2);
			--n2;
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

/* getfloat: get values from a input stream of characters. */
int getfloat (double *pm) {

	int c, sign;
	double dval, base;
	base = 1;
	dval = 0.0;

	while (isspace(c = getch()))	/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
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
	for (*pm = 0; isdigit(c); c = getch())
		*pm = 10 * *pm + (c - '0');
	
	if (c == '.') {
		while (isspace (c = getch()))
			;
		for (dval = 0.0, base = 0.1; isdigit(c); c = getch()) {
			dval = dval + ((c - '0') * base);
			base *= 0.1;
		}
	}
	*pm += dval;
	*pm *= sign;
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
