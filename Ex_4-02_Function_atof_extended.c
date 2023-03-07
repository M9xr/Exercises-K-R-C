/* Exercise 4-2. Extend "atof" to handle scientific notation of the form 123.45e-6 where a floating-point number may be followed by e or E and an optionally signed exponent. */

#include <stdio.h>
#include <ctype.h>
#define MAXLINE 100

/* rudimentary calculator */
int main (void) {

	int xatoi (char[]), sum2;
	double sum, atof (char[]);
	char line[MAXLINE];
	int xgetline (char line[], int max);

	sum = sum2 = 0;
	while (xgetline (line, MAXLINE) > 0) {
		printf("\t%g\n", sum += atof (line));
		//printf("\n\t\t%d\n", sum2 += xatoi(line));
	}
	return 0;
}

/* atof: convert string s to double */
double atof (char s[]) {

	double val, power, base, p;
	int i, sign, exp;
	
	for (i = 0; isspace (s[i]); i++)	/* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit (s[i]); i++) 
		val = 10.0 * val + (s[i] - '0'); 
	if (s[i] == '.') 
		i++;
	for (power = 1.0; isdigit (s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}	
	
	if (s[i] == 'e' || s[i] == 'E') 
		i++;
	else
		return sign * val / power;
	
	base = (s[i] == '-') ? 0.1 : 10.0;
	if (s[i] == '+' || s[i] == '-')
			i++;
	for (exp = 0; isdigit (s[i]); i++)
		exp = 10 * exp + (s[i] - '0');
	for (p = 1; exp > 0; --exp)
		p = p * base;
	
	return (sign * val / power) * p;
	
		
}

/* xatoi: convert string s to integer using atof */
int xatoi (char s[]) {
	
	double atof (char s[]);
	return (int) atof(s);
}

/* xgetline: get line into s, return length */
int xgetline (char s[], int lim) {

	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
