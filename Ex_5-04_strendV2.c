/* Exercise 5-4. Write the function "strend (s,t)", which returns 1 if the string "t" occurs at the end of the string s, and zero otherwise. */

#include <stdio.h>

int xstrend (char *, char *);

int main (void) {

	char *p1, *p2, *p3, *p5;
	int val1, val2, val3, val4, val5, val6, val7, val8, val9;
	char array1[] = "Ach neodym ";
	char array2[] = "Tudizez fosfor";
	p3 = "fosfor";
	p5 = "fosfor";
	char p4[] = "fosfor";
	char p6[] = "fosfor";

	p1 = array1;
	p2 = array2;

	val1 = xstrend (p1, array2);
	val2 = xstrend (p2, p3);
	val3 = xstrend (p2, p4);
	val4 = xstrend (p3, p4);
	val5 = xstrend (p6, p4);
	//val6 = xstrend (p3, p5);
	//val7 = xstrend (p5, p6);
	//val8 = xstrend (p6, p3);
	printf("Val:%d\t The string t %s at the end of the string s\n", val1, (val1 == 1 ? "occurs" : "doesn't occur"));
	printf("Val:%d\t The string t %s at the end of the string s\n", val2, (val2 == 1 ? "occurs" : "doesn't occur"));
	printf("Val:%d\t The string t %s at the end of the string s\n", val3, (val3 == 1 ? "occurs" : "doesn't occur"));
	printf("Val:%d\t The string t %s at the end of the string s\n", val4, (val4 == 1 ? "occurs" : "doesn't occur"));
	printf("Val:%d\t The string t %s at the end of the string s\n", val5, (val5 == 1 ? "occurs" : "doesn't occur"));
	//printf("Val:%d\t The string t %s at the end of the string s\n", val6, (val6 == 1 ? "occurs" : "doesn't occur"));
	//printf("Val:%d\t The string t %s at the end of the string s\n", val7, (val7 == 1 ? "occurs" : "doesn't occur"));
	//printf("Val:%d\t The string t %s at the end of the string s\n", val8, (val8 == 1 ? "occurs" : "doesn't occur"));

	return 0;
}

int xstrend (char *s, char *t) {

	int l1, l2;
	l1 = l2 = 1;

	while (*s++)
		++l1;
	while (*t++)
		++l2;
	
	if (l2 > l1)
		return 0;
	s -= l2;
	t -= l2;
	while (*s++ == *t++)
		;
	--s;
	--t;
	if (*s == '\0') {
		s -= l1;
		t -= l2;
		printf("%s <----> %s\n", s, t);
		return 1;
	}
	else
		return 0;

}
