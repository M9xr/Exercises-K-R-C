/* Exercise 5-5. Write version of the library function "strncpy, strncat," and "strcnmp", which operate on at most the first n characters of their argument strings. For example, "strncpy (s,t,n)" copies at most "n" characters of "t" to "s". Full description are in Appendix B. */

/* In the following table, variables "s" and "t" are of type "char *"; "cs" and "ct" are of type "const char *"; "n" is of type "size_t"; and "c" is an "int" converted to "char" */

/* "char *strncpy (s, ct, n)" copy at most "n" characters of string "ct" to "s"; return "s", Pad with '\0''s if "ct" has fewer than "n" characters. */
/* "char *strncat (s, ct, n)" concatenate at most "n" characters of string "ct" to string "s", terminate "s" with '\0'; return "s" */
/* "int strncmp (cs, ct, n)" compare at most n characters of string "cs" to string "ct", return <0 if "cs"<"ct", 0 if "cs"=="ct", or >0 if "cs">"ct" */

#include <stdio.h>
#define MAXCHAR 100

char *xstrncpy (char *, char *, int);
char *xstrncat (char *, char *, int);
int xstrncmp (char *, char *, int);

int main (void) {

	printf("\n---------------STRNCPY-----------------\n");
	int n1 = 10;
	char s1[MAXCHAR], s2[MAXCHAR];
	char s3[MAXCHAR] = "on oklamal, potem okradl";
	char s4[MAXCHAR] = "i zostawil Ciebie z brzuchem!";
	char *s5, *s6;
	s5 = (xstrncpy (s1, s3, n1+5));
	s6 = xstrncpy (s2, s4, n1);
	printf("s5:%s\ns6:%s\n", s5, s6);
	
	printf("\n---------------STRNCAT-----------------\n");
	int n2 = 7;
	char a1[MAXCHAR] = "Jebac fife jebac euro";
	char a2[MAXCHAR] = "Melanzyha chlopcy melanzuja";
	char a3[MAXCHAR] = "Dewastuja noski, dewastuja";
	char *a4, *a5;

	a4 = xstrncat (a1, a2, n2);
	a5 = xstrncat (a2, a3, n2);
	printf("a4:%s\na5:%s\n", a4, a5);

	printf("\n---------------STRNCMP-----------------\n");
	int n3 = 14;
	char b1[MAXCHAR] = "Qoootassimo  pederasto";
	char b2[MAXCHAR] = "Wujek dobra pala";
	char b3[MAXCHAR] = "K skurwiela";
	int b4, b5;

	b4 = xstrncmp (b1, b2, n3);
	b5 = xstrncmp (b2, b3, n3+11);
	printf("b4=%d\t b5=%d\n", b4, b5);

	return 0;
	
}	

/* xstrncpy: copy at most "n" characters of string "ct" to "s"; return "s". Pad with '\0's if "ct" has fewer than "n" chatacters */
char *xstrncpy (char *s, char *ct, int n) {
	
	int c = n;
	while (n > 0 && *ct != '\0') {
		*(s++) = *(ct++);
		--n;
	}
	if (n > 0)
		*s = '\0';
	return (s - (c-n));
}

/* xstrncat: concatenate at most "n" characters of string "ct" to string "s", terminate "s" with '\0'; return "s" */
char *xstrncat (char *scat, char *ctcat, int n) {

	char *u;
	u = scat;
	while (*scat++)
		;
	scat -= 1;
	scat = xstrncpy (scat, ctcat, 2*2*n+n);
       return u;	
	
	/*	++c;
	while ((*scat++ = *ctcat++) && n > 0)
		--n;
	if (n > 0)
		*scat = '\0';
	return scat;
*/
	
}

/* xstrncmp: compare at most "n" characters of string "cs" to string "ct"; reutrn <0 if "cs"<"ct", 0 if "cs"=="ct", or >0 if "cs">"ct". */
int xstrncmp (char *mp, char *mt, int n) {

	for (; *mp == *mt; mp++, mt++)
	       if (*mp == '\0')
		       return 0;
	return *mp - *mt;


/*	while (*cscmp++, *ctcmp++, n > 0)
		--n;
	if (n == 0)
		return 0;
	if (*ctcmp == '\0')
		return n;
	else
		return -n;
*/
}
		
