/* Exercise 4-3. Given the basic framework, it's straightforward to extend the calculator. Add the modulus (%) operator and provisions for negative numbers. */

#include <stdio.h>
#include <stdlib.h>	/* for atof() */

#define MAXOP 100	/* max size of operand or operator */
#define NUMBER '0'	/* signal that a number was found */

int getop (char []);
void push (double);
double pop (void);

/* reverse Polish calculator */

int main () {

	int type, ope2;
	double op2, val;
	char s[MAXOP];

	while ((type = getop (s)) != EOF) {
		switch (type) {
			case NUMBER:
			//	printf(" Test2 (num) \n");
				push (atof (s));
				break;
			case '+':
			//	printf(" Test5 (+) \n");
				push (pop() + pop());
				break;
			case '*':
				push (pop() * pop());
				break;
			case '-':
			//	printf(" Test1 (-) \n");
				op2 = pop();
				//printf(" Test6 (op=%f) \n", op2);
				push ((pop() - op2));
				//printf("\t%.8g\n", pop());
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push (pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				ope2 = pop();
				if (ope2 != 0) 
					push ((int) pop() % ope2); 
				else
					printf("error: zero divisior in modulo");
				break;
			case '\n':
			//	printf(" Test 3 (nl) \n ");
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

#define MAXVAL 100	/* maximum depth of val stack */

int sp = 0;		/* next free stack position */
double val[MAXVAL];	/* value stack */

/* push: push f onto value stack */
void push (double f) {
	//printf(" \t Push here ");
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop (void) {

	//printf(" PopHere \n");
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

#include <ctype.h>

int getch (void);
void ungetch (int);

/* getop: get next character or numeric operand */
int getop (char s[]) {

	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit (c) && c != '.' && c != '-')
		return c;	/* not a number */
	i = 0;
	if (c == '-' || isdigit (c))  /* collect integer(s), if any, after first digit found or after minus symbol found */
	       while (isdigit (s[++i] = c = getch()))
	       ;	       
	if (c == '.')		/* collect fraction part */
		while (isdigit (s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch (c);
	if (i == 1 && s[0] == '-')
		return '-';
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

int getch (void) {	/* get a (possibly push-back) character */

	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch (int c) {	/* push character back on input */

	if (bufp >= BUFSIZE)
		printf("ungetch: too many character\n");
	else
		buf[bufp++] = c;
}




