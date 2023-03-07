/* Exercise 1-13. Write a program to print a histogram of the lengths of words in its input.
 * It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging. */
// My first program which I was and am really proud of. ~"04.09.2022 04:13" 
#include <stdio.h>

#define TRUE  1
#define FALSE 0
int main () {

	int c, i, len, rexi;
	int ndigit[67];
	len = 0;

	for (i = 0; i < 67; ++i)
		ndigit[i] = 0;
	
	while ((c = getchar()) && c != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			++ndigit[len]; 
			len = 0; }
		else {
			++len; }
	}

	int super_horiz, minor_vert, char_vert, length, set, nchar_vert;
	super_horiz = 100;
	minor_vert = 0;

	int tower[100];
	for (set = 100; set > 0; set--) {
		tower[set] = 0; }
	
	ndigit[0] = 0;
	while (super_horiz > 0) {
		printf ("%d\t\b\b|", super_horiz);
		
		for (minor_vert == 0; minor_vert <= 200; minor_vert++) {		 
			length = (minor_vert / 3);

			if (ndigit[length] > 0 && ndigit[length] == super_horiz) {
				       printf("/x\\");
			       	       tower[length] = length;
				       minor_vert = minor_vert + 2; } 	

			else if (tower[(length)] > 0 && tower[(length)] < 80) {
				printf("|x:");
		       		minor_vert = minor_vert + 2;}
			else {
				printf("."); }
			}

			minor_vert = 0;
			--super_horiz;
			printf("\n");
		} 
		printf("\t");

	int rest, nchar;
	minor_vert = 200;
	nchar = 0;
	while (minor_vert > 0) {
		if (nchar <= 9) {
			printf(" %d|", nchar);
			++nchar;
	       		minor_vert = minor_vert - 3; }
		else {					
			printf("%d|", nchar);
			++nchar; 
			minor_vert = minor_vert - 3; } 
	}

	char x_axis[] = {"Amount of characters"};
	printf ("%150s", x_axis);
	printf("\n");
	
	printf ("The amount of words with the length from 1 to 20\n\n");
	for (i = 1; i < 67; ++i)
		if (ndigit[i] > 0) {
			printf ("There are %d of words that cointain %d chars \n\n", ndigit[i], i); } 
	}
