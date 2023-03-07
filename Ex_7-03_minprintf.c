/* Exercise 7-3. Revise "minprintf" to handle more of the other facilities of "printf" */

#include <stdio.h>
#include <stdarg.h>

int minprintf(char *format, ...);

int main(void) {
	
	int volume, value1, value2, value11;
	char string1[] = "Each call of \"va_arg\" returns one argument and steps \"ap\" to the next %% %";

	volume = minprintf("Cotton, for your dick and anus %g %c %u%d\n%s %n %g %f  - %%'\nThe ptr adress:%p%d\nOCTAL:%o\thexa:%x\tHEXA:%X\n\n", 429.1245, 112, -5, 17, string1, &value1, 2.4, -0.7724, &value1, 99, 735, 1489, 11835);
	minprintf("Volume at \"n\" is :%d The whole volume is:%d\n", value1, volume);

	return 0;
}

/* minprintf: minimal printf with variable argument list */
int minprintf(char *fmt, ...) {

	va_list ap;	/* point to each unnamed arg in turn */
	char *p, *sval;
	int ival, count = 0, *pin;
	unsigned int *pinx, uival;
	double dval;
	void *ptr;
	unsigned char uchar;

	va_start(ap, fmt);	/* make ap point to 1st unnamed arg */
	for (p = fmt; *p; ++p) {
		++count;
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		++count;
		switch (*++p) {
			case 'd': case 'i':
				ival = va_arg(ap, int);
				count += printf("%d", ival);
				break;
			case 'f':
				dval = va_arg(ap, double);
				count += printf("%f", dval);
				break;
			case 'g': case 'G':
				dval = va_arg(ap, double);
				count += printf("%g", dval);
				break;
			case 'e': case 'E':
				dval = va_arg(ap, double);
				count += printf("%e", dval);
				break;
			case 'u':
				uival = va_arg(ap, unsigned int);
				count += printf("%u", uival);
				break;
			case 'c':
				uchar = va_arg(ap, int);
				count += printf("%c", uchar);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++) {
					putchar(*sval);
					++count;
				}
				break;
			case 'x':
				ival = va_arg(ap, unsigned int);
				count += printf("%x", ival);
				break;
			case 'X':
				ival = (int)va_arg(ap, unsigned int);
				count += printf("%X", ival);
				break;
			case 'o':
				ival = va_arg(ap, int);
				count += printf("%o", ival);
				break;
			case 'p':
				ptr = va_arg(ap, void *);
				printf("%p", ptr);
				break;
			case 'n':
				pin = va_arg(ap, int *);
				*pin = count;
				break;
			case ' ': case '\0': case '%':
				putchar(*--p);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap);	/* clean up when done */
	return count;
}
