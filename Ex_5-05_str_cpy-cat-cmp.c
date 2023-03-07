/* Exercise 5-5. Write versions of the library funcitons "strcpy, strncat", and "strncmp", which operate on at most the first n characters of their argument strings. For example, "strncpy (s,t,n)" copies at most
 * "n" characters of "t" to "s". Full descriptions are in Appendix B. */

#include <stdio.h>

void xstrcpy (char *, char *, int);	// copy at most "n" characters of string "ct" to "s"; return "s". Pad with '\0''s if "ct" has fewer than "n" characters
char *xstrcat (char *, char *, int);	// concatenate at most "n" characters of string "ct" to end of string "s"; terminate "s" with '\0'; return "s"
int xstrcmp (char *, char *, int);	// compare at most "n" characters of string "cs" to string "ct", return <0 if "cs<ct", 0 if "cs==ct", or >0 if "cs>ct".

#define MAX 450

int main (void) {

	char array1[MAX] = "Mama Ci mowi, mowi Ci mama, zjedz tego wreszcie kurwaaaa karpia ";
	char array2[MAX] = "Ty powiedz nie, Ty powiedz PIERODL SIEE LALA LA LALALA ";
	char array3[MAX] = "Grudniowe noce, zimowe noce, Karol, Roxane po cipce gilgoczne... ";
	char array4[MAX] = "karpia ";
	char array5[MAX] = "Ty powiedz nie, Ty powaznie tak brzydko mowisz?";
	char array6[100];
	int int1, int2, int3;
	char *p1, *p2, *p3, *p4;
	int1 = xstrcmp (array2, array5, 5);
	int2 = xstrcmp (array2, array5, 35);
	xstrcpy (array6, array3, 14);
	printf("Copied: %s\n", array1);
	p1 = xstrcat (array1, array2, 50);
	p2 = xstrcat (array6, array3, 30);
	printf("\n----------------------ADVERTISMENT--------------\n-------------------END OF THE ADVERT-----------------------\n\n");
	printf("%s\n", p2);
	p3 = xstrcat (array6, array5, 52);
	printf("%s\n", p3);
	p4 = xstrcat (array6, array3, 52);
	printf("%s\n", p4);
	printf("Integer results: No.1:%d ---- No.2:%d\n", int1, int2);
	printf("%s\n%s\n%s\n", array1, array2, array6);
	//printf("%s\n%s\n%s\n%s\n", p1, p2, p3, p4);
	printf("\n----------------------ADVERTISMENT--------------\n-------------------END OF THE ADVERT-----------------------\n\n");
	char array10[MAX] = "In 1943 Konrad Hoffman Von Szlugenstern ";
	char array11[MAX] = "during the operation Kuttanossa ";
	char array12[MAX] = "had visited an undergrund strip club where ";
	char array13[MAX] = "he met your grandmother Alicja ";
	char *p11, *p12, *p13, *p14, *pp1, *pp2, *pp3, *pp4;
	/*p11 = xstrcat (array10, array11, 60);
	p12 = xstrcat (array12, array13, 60);
	p13 = xstrcat (array11, array12, 60);
	p14 = xstrcat (array10, array11, 60);
	printf("%s\n", p14);*/
	pp1 = xstrcat (array10, array11, 160);
	pp2 = xstrcat (array10, array12, 160);
	pp3 = xstrcat (array10, array13, 240);
	printf("%s\n%s\n%s\n", pp1, pp2, pp3);
	printf("\n\n%s\n", pp3);

	return 0;

}
char *xstrcat (char *s1, char *s2, int n) {
	
	char *pp1;
	pp1 = s1;	
	while (*s1++)
		;
	--s1;
	while ((*s1++ = *s2++) && (n > 0)) {		// You need to insert the assigment in parantheses because assigment has lower precendences than && operator
		--n;
	}
	if (n == 0) {
		--s1;
		*s1 = '\0';
	}
	return pp1;
}

void xstrcpy (char *s1, char *s2, int n) {


	while (*s1++ = *s2++ && n > 0) {
			--n;
	}
	if (n == 0) {
		--s1;
		*s1 = '\0';
	}
}

int xstrcmp (char *s1, char *s2, int n) {
	
	while (*s1++ == *s2++ && n > 0) {
		--n;
	}
	--s1;
	--s2;
	if (n == 0)
		return 0;
	else
		return (*s1 - *s2);
}
		
