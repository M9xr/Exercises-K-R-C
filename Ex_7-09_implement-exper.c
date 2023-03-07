/* Exercise 7-9. Functions like "isupper" can be implemented to save space or to save time. Explore both possibilities */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define xisupper(c) ((c >= 'A' && c <= 'Z') ? 1 : 0)
int zisupper(int);

int main(int argc, char *argv[]) {

	int c, set, cond; 
	long upper_letters = 0, other_letters = 0;
	FILE *fp;
	
	if (argc < 2) {
		printf("Error. Ussage: ./ex-7-09 -d file1 file2...\n");
		return -1;
	}

	if (strcmp("-d", argv[1]) == 0) {
		++argv;
		set = 2;
	}
	else
		set = 1;

	while ((fp = fopen(*++argv, "r")) != NULL) {
		if (set == 1) {
			while ((c = getc(fp)) != EOF) {
				if ((cond = zisupper(c)) == 1)
					++upper_letters;
				else
					++other_letters;
				}
			}
		else {
			while ((c = getc(fp)) != EOF) {
				if ((cond = xisupper(c)) == 1)
					++upper_letters;
				else
					++other_letters;
			}
		}
		fclose(fp);
	}
	if (set == 1)
		printf("Function version:\n");
	else
		printf("Define version::\n");
	printf("Upper letters:%ld\tOthers:%ld\n", upper_letters, other_letters);
	return 0;
}
	
int zisupper(int c) {

	if (c >= 'A' && c <= 'Z')
		return 1;
	return 0;
}


