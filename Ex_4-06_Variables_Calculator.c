/* Exercise 4-3. Given the basic framework, it's straightforward to extend the calculator. Add the modulus (%) operator and provisions for negative numbers. */
/* Exercise 4-4. Add the commands to print the top elements of the stack without popping, to duplicate it, and to swap the top two elements. Add a command to clear the stack */
/* Exercise 4-5. Add access to library function like "sin, exp," and "pow". See <math.h> in Appendix B, Section 4. */
/* Exercise 4-6. Add commands for handling variables. (It's easy to provide twenty-six variables with single-letter names.) Add a variable for the most recently printed value. */

#include <stdio.h>
#include <stdlib.h>	/* for atof() */
#include <math.h>

#define MAXOP 100	/* max size of operand or operator */
#define NUMBER '0'	/* signal that a number was found */

int getop (char []);
void push (double);
double pop (void);
void command (int);
void trigonometry (int);
double xvariables (int);

/* reverse Polish calculator */

int main () {

	int type, ope2;
	double op2, val, stc, xvar;
	char s[MAXOP];

	printf (" Available commands: (p) - print the last number: (d) - duplicate the last number: (s) - swap the two last numbers: (c) - clear the whole stack\n Available functions: (!e) - exponential function: (!s) - function sine "            	"(!c) - function cosine: (!t) - function tangent: (!p) - function power x,y\n You can acess the first and the second number with (F) and (S) respectevily, also the last one with (L)."
	"\n If you want set up your own variable, please press ($), provide the number and press enter; To access it, press (O)\n");  
	while ((type = getop (s)) != EOF) {
		switch (type) {
			case NUMBER:
			//	printf(" Test2 (num) \n");
				push (atof (s));
				break;
			case 'p': case 'd': case 's': case 'c':
				command (type);
				break;
			case '!':
				trigonometry(getop (s));
				break;
			case 'F': case 'S': case 'L': case '$': case 'O':
				xvar = xvariables(type);
				push (xvar);
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
			//	printf("\t%.8g\n", pop());
				stc = pop(); 			/* get the value last from the stack */
				push (stc);			/* get back the value to the stack */
				printf("\t%.8g\n", stc);
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
	if (sp < MAXVAL) {
		val[sp] = f;
		++sp; }
	else
		printf("error: stack full, can't push %g\n", f);
//	printf("Value of sp: %d\n", sp);
}

/* pop: pop and return top value from stack */
double pop (void) {

	//printf(" PopHere \n");
	if (sp >= 0)
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
/* command: print (p), duplicate (d), swap (s) or clear (c) the top value od the stack */
void command (int typec) {

	double i, j;
	if (typec == 'p')
		printf("The top value of the stack is %g \n", val[sp-1]);
	if (typec == 'd') {
		val[sp] = val[sp-1];
		++sp;
		printf("The value of sp in command (d) is: %d  and val: %f\n", sp, val[sp-1]); }
	if (typec == 's') {
		i = val[sp - 2];
		val[sp - 2] = val[sp - 1];
		val[sp - 1] = i; }
	if (typec == 'c') {
		sp = 0;
		val[0] = val[1] = 0;
	}
}
/* add access to library functions sin, cos, tang, exp, pow */
void trigonometry (int function) {

	/* sin, exp, pow */
	// cc progarm.c -o program -lm
	
	double opx;

	switch (function) {
		case 's':
			push(sin(pop()));
			break;
		case 'c':
			push(cos(pop()));
			break;
		case 't':
			push(tan(pop()));
			break;
		case 'e':
			push(exp(pop()));
			break;
		case 'p':
			opx = pop();
			push (pow (pop(), opx));
			break;
		default:
			printf("Still problems with trigonometry, HUH>?\n");
	}
}
double varxx = 1.0;
#define MAXVAR 40
/* Easy access to specific numbers in the stack and easy way to set up own variable */
double xvariables (int var) {
	
	char vble[MAXVAR];
	int c, i;
	i = 0;
	switch (var) {
		case 'F':
			return val[0];
			break;
		case 'S':
			return val[1];
			break;
		case 'L':
			return val[sp - 1];
			break;
		case '$':
			printf("\nProvide your variable: ");
			while ((c = getchar()) != '\n')  {
				vble[i] = c;
				++i;
			//	printf("The vble = %d   i = %d\n", vble[i], i);
			}	
			vble[i] = '\0';
			varxx = atof (vble);
			printf("Varx:%g\n", varxx);
			break;
		case 'O':
			return varxx;
			break;
		default:
			printf("I bet that you dont know what is cotangent, HUH?\n");
	}
}







