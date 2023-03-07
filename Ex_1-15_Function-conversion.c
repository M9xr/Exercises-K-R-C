/* Exercise 1.15. Rewrite the temperature conversion program of Section 1.2 to use a function for conversion. */

#include <stdio.h>

#define LOWER  0	/* lower limit of table */
#define UPPER  300	/* upper limit */
#define STEP   20	/* step size */

double fahr_to_cels(int fahrenheit);
//int fahr_to_cels();
int main() {

	int fahr;
	for (fahr = LOWER; fahr <= UPPER; fahr += STEP)
		printf("%6d*F %6.1f*C\n", fahr, fahr_to_cels(fahr));
	
	return 0;
}

double fahr_to_cels(int fahr) {
/*
fahr_to_cels(fahr)
	int fahr;
{
*/
	double cels;
	return cels = (5.0/9.0) * (fahr - 32);
}


