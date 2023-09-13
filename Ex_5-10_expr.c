/* Exercise 5-10. Write the program "expr", which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument.
 * For example "expr 2 3 4 + *"  evaluates "2 * (3+4)". */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100

void error_func(void);

int main(int argc, char *argv[]) {

	if (argc < 3) {
		error_func();
		return -1;
	}

	int place = 0;
	char c;
	double buffer[MAXOP], val = 0.0, op2;

	while (--argc > 0 && place < MAXOP) {
		if (isdigit(c = **++argv))
			buffer[place++] = atof(*argv);
		else {
			if (place > 1) {
				switch (c) {
					case '+':
						val = (buffer[--place] + buffer[--place]);
						buffer[place++] = val;
						break;
					case '-':
						 op2 = buffer[--place];
						 val = buffer[--place] - op2;
						 buffer[place++] = val;
						 break;
					case '*':
						val = buffer[--place] * buffer[--place];
						buffer[place++] = val;
						break;
					case '/' :
						op2 = buffer[--place];
						val = buffer[--place] / op2;
						buffer[place++] = val;
						break;
					default:
						error_func();
						printf("Error, invalid operator \"%c\"\n", c);
						printf("If you use shell, remember that \"*\" is a glob, so you need to escape it with \"\\\"\n");
						return -1;
				}
			}
			else {
				error_func();
				printf("Error, lakcing operators for %c operator, exiting\n", c);
				return -1;
			}	
		}
	}

	if (place > 1) {
		error_func();
		printf("Error, too many operands\n");
		return -1;
	}
	printf("The value is: %g\n", buffer[--place]);
		
	return 0;
}

void error_func(void) {

	printf("\tReverse Polish Caluclator.\nUsage: \"expr 2 3 4 + *\" evaluates as \"2 * (3 + 4)\"\n");
}
