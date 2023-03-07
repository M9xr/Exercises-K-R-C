/* Exercise 1-14. Write program to print a histogram of the frequencies of different characters in its input */

#include <stdio.h>

#define TRUE  1
#define FALSE 0

int main(void) {

	int c, i;
	int ndigit[67];
	int difference = '!';	// The first "normal" character"
	int difference_middle = 'a' - 'Z';	// upper cases aren't followed by lowers immediately
	int difference_within = 'z' - 'a';

 
	for (i = 0; i < 67; ++i)
		ndigit[i] = 0;
	
	while ((c = getchar()) && c != EOF) {
		if (c >= '!' && c < 'a') {
			if ((ndigit[c - difference]) < 100) {
				++ndigit[c -= difference];
			}
		}
		if (c >= 'a' && c <= 'z') {
			if ((ndigit[c - (difference + ('a' - 'A'))]) < 100)
				++ndigit[c -= (difference + ('a' - 'A'))];
		}
		if (c > 'z' && c <= '~') {
			if ((ndigit[c - (('a' - 'A') + difference - 6)]) < 100)
				++ndigit[c -= (('a' - 'A') + difference - 6)];

		}
	}

	int super_horiz, minor_vert, char_vert, length, set, nchar_vert;
	super_horiz = 100;
	minor_vert = 0;

	int tower[100];
	for (set = 100; set > 0; set--) {
		tower[set] = 0; }
	
	//ndigit[0] = 0;
	while (super_horiz > 0) {
		printf ("%d\t\b\b|.", super_horiz);
		
		for (minor_vert == 0; minor_vert <= 200; minor_vert++) {		 
			length = (minor_vert / 3);

			if (ndigit[length] > 0 && ndigit[length] == super_horiz) {
				       printf("/x\\");
			       	       tower[length] = length;
				       if (ndigit[length] > 0 && length == 0)
					       tower[length] = ndigit[length];
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
		printf("\t|");

	int rest, nchar;
	minor_vert = 200;
	nchar = 0;
	while (minor_vert > 0) {
		if (nchar < ('a' - difference))
			printf("%c |", nchar + difference);
		else 
			printf("%c |", nchar + difference + ('a' - 'A') - ('a' - 'Z' - 1));
		++nchar;
	       	minor_vert = minor_vert - 3; 
	}

	char x_axis[] = {"Characters"};
	printf ("%150s", x_axis);
	printf("\n");

}
