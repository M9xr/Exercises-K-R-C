/* Exercise 2-4. Write an alternative version of squeeze (s1,s2) that deletes each character in s1 that matches any character in the string s2. */

#include <stdio.h>
#define MAXCHAR 250
#define END 1
#define NOEND 0
void test (int naplet);
void squeeze (char s1[], char s2[]);

int main (void) {

char s1[MAXCHAR]; 
char s2[MAXCHAR];
int set = NOEND;
int i, c = 0;

printf("Write the first string: \n");
	while(set != END && (c = getchar()) != EOF) {
		if (c == '\0' || c == '\n') {
			s1[i] = '\0'; test(101);
			set = END; }
		else { //if (c != '\0' && c != '\n') {
			s1[i] = c; test(102);
	       		++i; }
		}
printf("\nWrite the second string: \n");

	i = 0;
	set = NOEND;
	while (set != END && (c = getchar()) != EOF) {
		if (c == '\0' || c =='\n') {
			s2[i] = '\0';test(103);
			set = END; }
		else {
			s2[i] = c;test(104);
	       		++i; }
		}
	printf("\n\nChecking the strings:\n\nString N1:%s\n\nString N2:%s\n\n", s1, s2);
	squeeze (s1, s2);
	printf("\n\n");



}
/* Delete each character in s1 that matches any character in s2. */

void squeeze (char s1[], char s2[]) {

	int i, j, k;
	char str1[MAXCHAR];
	
	i = j = k = 0;
	while (s1[i] != '\0') {
	        for (j = 0; j < MAXCHAR && s1[i] != '\0'; ++j) {
	 	      if (s2[j] == s1[i]) {
			      test(2); printf(" i%d:j%d ", i, j); 
			      ++i; 
		     	      j = -1; }  
		      else if (s2[j] == '\0') {
			      test(3); printf(" i%d:j%d ", i, j);
			      str1[k] = s1[i];
			      ++i;
			      ++k;
			      j = -1; }
		      else if (s2[j] != s1[i]) {
			       test(4); printf(" i%d:j%d", i, j); }
		      } 	
		}
	str1[k] = '\0';
	printf("\n\nString 1: %s\n\nString 2: %s\n\n", str1, s2); 
}

void test(int rzerze) {
	printf("\tT%d", rzerze); 
}
