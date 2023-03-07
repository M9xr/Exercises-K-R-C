/* Exercise 2-5. Write the function any (s1,s2), which returns the first location in a string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk does the same job but returns a pointer to the location.) */
#include <stdio.h>
#define MAXCHAR 250

void any (char s1[], char s2[]);

int main (void) {

	int  c, i;
	char s1[MAXCHAR];
	char s2[MAXCHAR];

	printf("Write the first string: ");
	while ((c = getchar()) != EOF && c != '\0' && c != '\n') {
		s1[i] = c;
		++i; }
	s1[i] = '\0';
	i = 0;
	printf("Write the second string: ");
	while ((c = getchar()) != EOF && c != '\0' && c != '\n') {
		s2[i] = c;
		++i; }
	s2[i] = '\0';
	
	any (s1, s2);
}
void any (char s1[], char s2[]) {

	int i, j, coordinate, end;
	i = j = end = 0;
	while (s1[i] != '\0' && end != 1) {
		for (j = 0; j < MAXCHAR && end != 1; ++j) {
			if (s2[j] == s1[i]) {
				coordinate = i; 
				end = 1; }
			else if (s2[j] == '\0') {
				++i;
				j = -1; }
			else {
				coordinate = -1; }
			}
	}
	if (s1[i] == '\0') {
		printf("The string s1 contains no char from string 2\n"); }		
	else if (coordinate >= 0) {
		printf("The localization of the character (%c) in string 1, which is also present in the string s2 is: %d\n", s1[coordinate], coordinate + 1); }
	else {
		printf("The string s1 contains no character from the string s2\n"); }
}
	


