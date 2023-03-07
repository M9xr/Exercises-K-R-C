/* Exercise 7-1. Write a program that converts upper case to lower or lower case to upper, depending on the name it is invoked with, as found in argv[0]. */

#include <stdio.h>
#include <string.h>

void f_lower(void);
void f_upper(void);

int main(int argc, char *argv[]) {
	
	int case_no, c, higher_than, lower_than, difference;
	case_no = ((strcmp("./ex_7-01_lcase", argv[0]) == 0) ? 0 : 1);

	difference = 'a' - 'A';
	if (case_no == 0) {
		lower_than = 'Z';
		higher_than = 'A';
	}
	else {
		lower_than = 'z';	
		higher_than = 'a';
		difference *= (-1);
	}
	
	while ((c = getchar()) != EOF) {
		if (c >= higher_than && c <= lower_than)
			c += difference;
		putchar(c);
	}

	return 0;
}

