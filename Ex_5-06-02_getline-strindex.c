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
	
	int n = 0, index;
	char array1[MAX], array3[MAX];
/*	n = xgetline(array1, MAX-1);
	printf("%s\nlength:%d\n", array1, n);
*/
	char array2[MAX] = "read a line into s, return length "
			   "converts s to integer "
			   "converts n to characters in s"
			   "return index of t in s, -1 if none\n"
			   "reverse the order\n"
			   "Unix system\n"
			   "Linux Philosophy\n";
	n = xgetline(array3, MAX-1);
	index = xstrindex (array2, array3);
	if (index >= 0) {
		printf("Index:%d\n", index);
		printf("%s\n", array2+index);
	}
	else 
		printf("Provided phrase doesn't exists\n");

	return 0;
}

/* strindex: return index of t in s, -1 if none */
int xstrindex (char *s, char *t) {

	int i, j, control;
	i = j = control = 0;
	char *back;
	back = t;

	while (*s) {
		++control;
		if (*s == *t) {
			++j;
			++i;
			while (*s++ == *t++) {
				++i;
				++j;
				if (*t == '\0') {
				//	printf("Control:%d\nValue of i:%d value of j:%d\n", control, i, j);
					return j-i;
				}
			}
		}
		if (*s != *t) {
			t = back;
			i = 0;
			++s;
			++j;
		}
		if (*s == '\0') {
			//printf("Control:%d\n", control);
			return -1;
		}
	}
	printf("Error: Critical error\n");
	return -2;
}
/* getline: getline into s, return length */
int xgetline (char *s, int lim) {
	
	int c, i;
	i = 0;
	while ((c = getchar()) != EOF && c != '\n' && --lim > 0) {
		*s++ = c;
		++i;
	}
	*s = '\0';
	return i;

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








