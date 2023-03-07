/* Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercise with pointers instead of array indexing. Good possibilities include "getline" (Chapter 1 and 4),"atoi, itoa" and their variants (Chapter 2, 3, and 4),        "reverse" (Chapter 3), and "strindex" and "getop" (Chapter 4). */

#include <stdio.h>
#include <ctype.h>

int xgetline (char *, int);		// read a line into s, return length 
int xatoi (char *);			// converts s to integer
void xitoa (int n, char *);		// converts n to characters in s
double xatof (char *);			// convert string s to double
int xstrindex (char *, char *);		// return index of t in s, -1 if none
int getop (char *);			// get next character or numeric operand
void reverse (char *);			// reverse the order

#define MAX 500

// Itoa + atoi - first
// Strindex - second
// And for a dessert, getline + atof + getop in Calculator.

int main (void) {
	
	int val, val2;
	double val3, val4;
	char array1[MAX] = "1234", array2[MAX] = "798214", array3[MAX], array4[MAX], array5[MAX] = "214.666", array6[MAX] = "88.44";
	val = xatoi(array1);
	val2 = xatoi(array2);
	printf("Xatoi1: %d\t\tXatoi2: %d\n\n", val, val2);
	xitoa (val2, array3);
	xitoa (val, array4);
	printf("Xitoa1: %s\t\tXaitoa2: %s\n\n", array3, array4);
	val3 = xatof (array5);
	val4 = xatof (array6);
	printf("Xatof1: %g\t\tXatof2: %g\n", val3, val4);



	return 0;
}

/* itoa: convert n to character in s */
void xitoa (int n, char *s) {

	char *p1;
	p1 = s;
	do {
		*s++ = n % 10 + '0';
	} while ((n /= 10) > 0); 
	*s = '\0';
	reverse (p1);
	
}

/* atoi: convert s to intger */
int xatoi (char *s) {
	
	int val = 0;

	while (*s) 
		val = ((val * 10) + (*s++ - '0'));	// '0' is necessary because otherwise it would had been treated as value of machine code 
	return val;
}

/* atof: convert s to double */
double xatof (char *s) {
	
	double val, base, val2;
	base = 0.1; 
	val = val2 = 0.0;

	while (*s && *s != '.') {
		val = ((val * 10) + (*s++ - '0'));	// '0' is necessary because otherwise it would had been treated as value of machine code 
	}
	if (*s == '.') {
		++s;
		while (*s) {
			val2 = val2 + base * (*s++ - '0');	// There is also the quirk with machine code. "  -'0'  " makes sure that expression is treated as decimal value.
			base *= 0.1;
		}
	}
	return val + val2;
}

/* reverse: reverse the order of values in the array */
void reverse (char *s) {
	
	char *p1, temp;
	p1 = s;
	int n, j;
	n = j = 0;

	while (*s++)
		++n;
	s -= 2;
	while (j < (n/2)) {
		temp = *s;
		*s-- = *p1;
		*p1++ = temp;
		++j;
	}	
}	








