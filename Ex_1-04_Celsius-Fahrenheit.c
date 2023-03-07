/* Exercise 1-3. Modify the temperature conversion program to print a heading above the table */
/* Exercise 1-4. Writa a program to print the corresponding Celsius to Fahrenheit table */

#include <stdio.h>

int main() {

	float fahr, celsius;
	float lower, upper, step;

	lower = 0;	/* lower limit of temperature scale */
	upper = 300;	/* upper limit */
	step = 20;	/* step size */

	printf("\n\t%s\n", "Celsius-Fahrenheit table");
	celsius = lower;
	while (celsius <= upper) {
		fahr = ((9.0/5.0) * celsius) -32;
		printf("\t%5.1fC %16.1fF\n", celsius, fahr);
		celsius = celsius + step;
	}
}
