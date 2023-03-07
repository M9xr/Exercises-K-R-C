/* Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in the strings s1 into the equivalent complete list abc..xyz in s2. Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing "-" is taken literally. */
#include <stdio.h>
#define MAXCHAR 2500
void expand (char s1[]);
int main (void) {

	int c, i;
	char s1[MAXCHAR];
	i = 0;
	while ((c = getchar()) != EOF) {
		s1[i] = c;
		++i; }
	expand (s1);
	printf("\n");
}

void expand (char s1[MAXCHAR]) {

	int c, i, j, differ, set, m, b, e;
	char s2[MAXCHAR];
	j = 0;
	set = 3;
	for (i = 0; s1[i] != '\0'; ++i) {
		b = s1[i];
		m = s1[i+1];
		e = s1[i+2];
		if (m == '-' && (e - b > 0) && ((b >= 'A' && e <= 'z') || (b >= '0' && e <= '9')) && !(((b || e) > 'Z') && ((b || e) < 'a'))){ 
			for (differ = 0; differ <= (e - b); ++differ, j++) {
			      s2[j] = b + differ; } 
			      i = i + 2;
			      set = 0;}
		else {
			s2[j] = s1[i];
			++j;
	       		++set; }
	}
	printf("%s", s2);
}
