/* Exercise 7-4. Write a private version of "scanf" analogous to "minprintf" from the previous section */

struct data_dump {
	char *name;
	char *surename;
	int age;
	int number;
	struct data_dump *next;
};



#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "max_functions.h"
#include <ctype.h>

int mx_scanf(char *format, ...);
#define MAXCHAR 200

int main(void) {

	int condition, age, number, vol1, vol2, vol3;
	char name[MAXCHAR], name2[MAXCHAR];
	float height;
	printf("a:%p, nu:%p\n", &age, &number);
	while ((condition = mx_scanf("Nam%ne:%s%s\nAg%ne:%d\nNumber:%d%n\n", &vol3, name, name2, &vol1, &age, &number, &vol2)) >= 3) {
		printf("Name:%s\nSurename:%s\nAge:%d\nPhone number:%d\n", name, name2, age, number);
		printf("vol1:%d\tvol2:%d\tvol3:%d\n", vol1, vol2, vol3);
	}
	if (condition == -1)
		printf("An unexpected error, exiting\n");

	return 0;
}

int mx_scanf(char *format, ...) {

	int *pin, c, count, count_ch, i;
	float *pfn;
	char string[250], *psn, *p;
	va_list ap;
	int *pvn;
	count = i = count_ch = 0;
	
	va_start(ap, format);
	for (p = format; c != EOF && *p; ++p) {
		++count_ch;
		if (*p != '%')
			continue;
		++count;
		switch (*++p) {
			case 'd': case 'i':
				pin = va_arg(ap, int *);
				*pin = 0;
				while (isdigit(c = getchar())) {
					*pin = *pin * 10 + (c - '0');
					++count_ch;
				}
				if (!isspace(c) && c != EOF)
					return --count;
				break;
			case 'f':
				while (isdigit(c = getchar()) || c == '.') {
					string[i++] = c;
					++count_ch;
				}
				if (!isspace(c) && c != EOF)
					return --count;
				string[i] = '\0';
				pfn = va_arg(ap, float *);
				*pfn = atof(string);
				i = 0;
				break;
			case 's':
				psn = va_arg(ap, char *);
				while (isalnum(c = getchar())) {
					*psn++ = c;
					++count_ch;
				}
				if (!isspace(c) && c != EOF) 
					return --count;
				*psn = '\0';
				break;
			case 'n':
				pin = va_arg(ap, int *);
				*pin = count_ch;
				break;
			default:
				return count;
		}
	}
	return count;
}






