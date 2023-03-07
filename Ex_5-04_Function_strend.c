/* Exercise 5-4. Write a function "strend (s,t)", which return 1 if the string "t" occurs at the end of the string "s", and zero otherwise. */

#include <stdio.h>

#define MAXCHAR 1000

int strend (char *, char *);
int main (void) {

	char s1[MAXCHAR] = "Jak to mowia kto nie ma w glowie, ten ma w dupie";
	char s2[MAXCHAR] = "Kto rano wstaje, temu chuja daje";
	char s3[MAXCHAR] = "w dupie";
	char s4[MAXCHAR] = "chuja daje";
	char xs1[] = "Jaraj to gowno";
	char xs2[] = "Greta";
	char xs3[] = " Tararara Greta";
	char xs4[] = "gowno";
	int r1,r2,r3,r4;
	int jupos1,jupos2,jupos3,jupos4,jupos5, i;

	jupos1 = strend (s1, s4);
	jupos2 = strend (s1, s3);
	jupos3 = strend (s2, s3);
	jupos4 = strend (s2, s4);
	jupos5 = strend (s3, s4);

	printf("%d %d %d %d %d\n", jupos1, jupos2,jupos3,jupos4,jupos5);
	
	r1 = strend (xs1, xs3);
	r2 = strend (xs2, &xs3[10]);
	r3 = strend (xs1, xs4);
	r4 = strend (xs3, xs2);

	printf("%d %d %d %d\n", r1, r2, r3, r4);
	
	
	return 0;
}

/* strend: return 1 if the string "t" occurs at the end of the string "s", and zero otherwise */
int strend (char *s, char *t) {
	int n,m,p;
	n = m = p = 0;
	while (*s++ != '\0')
		++n;
	while (*t++ != '\0')
		++m;
	p = n - m;
	if (p < 0)
		return 0;
	
	s -= m;
	t -= m;
	while (*s == *t) {
		++s;
		++t;
	}
	--s;
	--t;
	if (*t == '\0' && *s == '\0')
		return 1;
	else
		return 0;

}
