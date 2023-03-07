/* Exercuse 5-10. Write hte program "expr", which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. 
 * For example, (expr 2 3 4 + *) evaluates 2 * (3+4) */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100

int main (int argc, char *argv[]) {

	int place = 0, c;
	double array1[MAXOP], val = 0.0, op2;
	printf("Argc count:%d\n", argc);
	
	while (--argc > 0 && place < MAXOP) {
			c = *(++argv)[0];
			if (isdigit (c)) {
				printf("before atof:%s\n", *argv);
				array1[place++] = atof(*argv);
			}
			else {
				if (place > 1) {
					switch (c) {
						case '+':
					        	val = (array1[--place] + array1[--place]);
					        	array1[place++] = val;
					        	break;
						case '-':
						        op2 = array1[--place];
						        val = array1[--place] - op2;
						        array1[place++] = val;
						        break;
						case 'x':
							val = ((array1[--place]) * (array1[--place]));
							array1[place++] = val;
							break;
						case '/':
							op2 = array1[--place];
							val = (array1[--place] / op2);
							array1[place++] = val;
							break;
						default:
							printf("error: no such operator\n");
							return -1;
						}
				}
				else {
					printf("Error: invalid input\n");
					return -1;
				}
			}	
		}
        if (place > 1) {
		printf("Error: Too many values for provided operators. %d operands left.\n", place);
		return -1;
	}
			
	printf("The value is: %g\n", array1[--place]);
	return 0;
}

		





