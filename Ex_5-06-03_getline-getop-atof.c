/* Exercise 4-3. Given the basic framework, it's straightforward to extend the calculator. Add the modulus (%) operator and provisions for negative numbers. */
/* Exercise 4-4. Add the commands to print the top elements of the stack without popping, to duplicate it, and to swap the top two elements. Add a command to clear the stack */
/* Exercise 4-5. Add access to library function like "sin, exp," and "pow". See <math.h> in Appendix B, Section 4. */
/* Exercise 4-6. Add commands for handling variables. (It's easy to provide twenty-six variables with single-letter names.) Add a variable for the most recently printed value. */

/* Exercise 4-7. Write a routine "ungest (s)" that will push back an entire string onto the input. Should "ungest" know about "buf" and "bufp", or should it just use "ungetch"? */
/* Answer: It is safer to use "buf" and "bufp", so option no.1 */ 
// Kinda dumb exercise, I will make ungest saving the chosen result(s) and possibility to access them via char '@' and an number. The Exercise will be done separetely.

/* Exercuse 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. */

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
void ungest (void);
void xhelp (void), stack (void);
double xatof (char *);
/* reverse Polish calculator */

int main () {
	
	int type, ope2;
	double op2, val, stc, xvar;
	char s[MAXOP];

	xhelp();

	while ((type = getop (s)) != EOF) {
		switch (type) {
			case NUMBER:
			//	printf(" Test2 (num) \n");
				push (xatof (s));
				break;
			case 'p': case 'd': case 's': case 'c':
				command (type);
				break;
			case '!':
				trigonometry(getop (s));
				break;
			case 'F': case 'S': case 'L': case '$': case 'O': case '@':
				xvar = xvariables(type);
				if (xvar == 'x')
					break;
				else
					push (xvar);
				break;
			case 'U':
				ungest();
				break;
		//	case 'a':
		//		stack();
		//		break;
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
				stack();
			//	printf("\t%.8g\n", stc);
				break;
			case 'h':
				xhelp();
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

/* atof: convert s to double */
double xatof (char *s) {

	double val, base, val2;
	base = 0.1;
	val = val2 = 0.0;

	while (*s && *s != '.') {
		val = ((val * 10) + (*s++ - '0'));	// '0' is necessary because otherwise "s" would had been treated as the value of the machine code
	}
	if (*s == '.') {
		++s;
		while (*s) {
			val2 = val2 + base * (*s++ - '0');	// '0' also makes sure that expressions are treated as decimal values.
			base *= 0.1;
		}
	}
	return val + val2;
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

/* Ungest is a function that should be written under the commands... Whatever */
void ungest (void) {
	int c, i;
	for (i = bufp; i < BUFSIZE, (c = getchar()) != '\0'; i++, bufp++) {
		buf[bufp++] = c;
	}
}

/* command: print (p), duplicate (d), swap (s) or clear (c) the top value od the stack */
void command (int typec) {

	double i, j;
	if (typec == 'p')
		printf("\nThe top value of the stack is %g", val[sp-1]);
	if (typec == 'd') {
		val[sp] = val[sp-1];
		++sp;
		printf("\nDuplicated value %g to the next free place in the stack(%d)", val[sp-1], sp); }
	if (typec == 's') {
		i = val[sp - 2];
		val[sp - 2] = val[sp - 1];
		val[sp - 1] = i;
	       printf("\nSwap values: %g(%d) <--> %g(%d)\n  Currently: %g(%d), %g(%d)", val[sp-1], sp-1, val[sp-2], sp, val[sp-1], sp, val[sp-2], sp-1);	
	}
	if (typec == 'c') {
		sp = 0;
		val[0] = val[1] = 0;
		printf("\nRemoved all values from the stack");
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
double varxx = 0.0, action1 = 0.0, action2 = 0.0;
#define MAXVAR 40
/* Easy access to specific numbers in the stack and easy way to set up own variable */
double xvariables (int var) {
	
	static char vble[MAXVAR], vble2[MAXVAR];
	int c, i, j, stnum, action;
	i = j = 0;
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
			if ((c = getchar()) == '\n') {
			while ((isdigit (c = getchar())) || c == '.')  {
				vble[i++] = c;
			//	printf("The vble = %d   i = %d\n", vble[i], i);
				}
			}	
			vble[i] = '\0';
			varxx = xatof (vble);
		//	printf("Varx:%g\n", varxx);
			return 'x';
			break;
		case 'O':
			return varxx;
			break;
		case '@':
			printf("Specify the action:\n\tTo get the value from the stack - press (g)\n\tTo change the value from the stack - press (c)\n\tTo remove the value from the stack - press (r)\n");
			action = getchar() + '0';
			while (action != 'g' && action != 'c' && action != 'r') {
				printf("Error: Action for the provided value doesn't exists, please press one of the following letters: (g), (c), (r)\n");
				action = getchar();
			}
			printf("\nProvide the number of the value from the stack: ");
			if ((c = getchar()) == '\n') {
				while ((isdigit (c = getchar()))) {
						vble2[j++] = c;
						}
				}
			vble2[j] = '\0';
			stnum = (int) xatof (vble2);
			if (stnum > sp) {
				printf("Error: The provided number value doesn't exist.\n");
				return 'x';
			}
			else {
				if (action == 'g') {
					printf("The chosen number is: %d |the value is: %g\n", stnum, val[stnum-1]);
					return val[stnum-1];
					break;
				}
				else if (action == 'c') {
					printf("The chosen number is: %d |the value is: %g\n Please, provide the value for the replacement: ", stnum, val[stnum-1]);
					while ((isdigit (c = getchar())) || c == '.') {
						vble[i++] = c;
					}
					vble[i] = '\0';
					action1 = xatof (vble);
					val[stnum-1] = action1;
					printf("The current value of the place no.%d is:%g\n", stnum, val[stnum-1]);
					return 'x';
					break;	
				}
				else if (action == 'r') {
					action2 = val[stnum-1];
					j = stnum;
					for ( ;stnum < sp; ++stnum)
						val[stnum-1] = val[stnum];
					val[sp-1] = '\0';
					--sp;
					printf("\nThe value(%d)%g has been removed\n", j, action2);
					return 'x';
				}
			}
			return 'x';
			break;
		default:
			printf("I bet that you dont know what is cotangent, HUH?\n");
	}
}

void stack (void) {
	
	int stp;
	
	printf("\n  |--------------------------------------------------------------------------------------------THE STACK--------------------------------------------------------------------------------------------"
	       "--------------------------------------|\n  ");
	
	for (stp = 0; stp < sp; ++stp) {
		if (stp < 9)
			printf("|*0%d*: %g|\t", stp+1,val[stp]);
		else if (stp >= 9 && ((stp+1) % 10) != 0)
			printf("|*%d*: %g|\t", stp+1,val[stp]);
		else if (stp >= 9 && ((stp+1) % 10) == 0)
			printf("|*%d*: %g|\t\n  ", stp+1,val[stp]);
		else	
			printf("Whops! Something is wrong!\n");
		}

	printf("\n  |--------------------------------------------------------------------------------------------THE STACK--------------------------------------------------------------------------------------------"
	       "--------------------------------------|\n");
}
/* Description of the commands */
void xhelp (void) {

	printf("Available commands:\n\t(p) - print the top value of the stack\n\t(s) - swap the last two values\n\t(d) - duplicate the last value\n\t(c) - clear the whole stack\n\t(ENTER) - print all values stored in the stack\n\n"
	"Available functions:\n\t(!e) - exponential function\n\t(!s) - sine function\n\t(!c) - cosine function\n\t(!t) - tangent function\n\nAvailable variables:\n\t(F) - get the value from the bottom of the stack\n\t(S)" 			      " - get the second value from the bottom of the stack\n\t(L) - get the last value of the stack\n\t($) - set up your own variable\n\t(O) - get your variable\n\t(@) - get/change/remove the specific value from the stack\n\n");
}





