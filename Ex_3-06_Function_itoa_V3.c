/* Exercise 3-6. write a version of "itoa" that accepts three arguments instead of two. The third argument is a minimum field width; the converted number must be padded with blanks on the left if necessary to make it wide enough. */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXLEN 13
#define COUNT 8
#define MAXCHAR 1000

void itoa (int n, char s[], int w);
void reverse (char s[]);

int main() {

	int i, number[] = {15, -15, 6, -6, 1983, -1983, INT_MIN, INT_MAX};
	char s[MAXLEN];

	for (i = 0; i < COUNT; i++)
	{
		itoa(number[i], s, 11);
		printf("%s\n", s);
	}
	exit(0);
}
void itoa (int n, char s[], int width) {
    
	int i, sign;
    
   	 if ((sign = n) < 0)
        	n = -n;
	 i = 0;
         do {
        	s[i++] = n % 10 + '0';
    	} while ((n /= 10) > 0);
    	if (sign < 0)
        	s[i++] = '-';
    
    	while (i < width )    /*  Only addition to original function  */
        	s[i++] = ' ';
    
    	s[i] = '\0';
    	reverse(s);
}

void reverse (char s[]) {

	int i, j, c;
	for (i = 0, j = strlen (s) - 1; i < j; i++, j--) {
	       c = s[i];
	       s[i] = s[j];
	       s[j]= c;
	}
}



