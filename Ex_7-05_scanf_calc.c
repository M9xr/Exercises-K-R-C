/* Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use "scanf" and/or "sscanf" to do the input and number conversion. */

#include <stdio.h>
#include <string.h>
void push(double);
double pop(void);

#define MAXOP 100
int main(void) {
	

   	double op2, num;
   	char s[MAXOP], c;

	while (scanf("%s%c", s, &c) == 2) { // found something. If EOF provided, this loop will terminate. However, if \n is provided, it will not terminate
	        if (sscanf(s, "%lf", &num) == 1) // found a number
        	    push(num);
        	else if (strlen(s) == 1) { // found an operator
			
			switch (*s) {	
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
					break;
				case '-':
					op2 = pop();
					push(pop() - op2);
					break;
				case '/':
					op2 = pop();
					if (op2 != 0.0)
						push(pop() / op2);
					else
						printf("error: zero divisor\n");
					break;
				case '\n':
					printf("\t%.8g\n", pop());
					break;
				default:
					printf("error: unknown command.\n");
				 	break;
			}
		}
		else 
			printf("ereor\n");
		if (c == '\n')
		            printf("\t%.8g\n", pop());

	}	
	return 0;
}



#define MAXVAL 100 	/* maximum depth of val stack */
int sp = 0;	/* next free stack position */
double val[MAXVAL];	/* value stack */;

/* push: push f onto value stack */
void push(double f) {

	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);	
}

/* pop: pop and return value from stack */
double pop(void) { 
	
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}
