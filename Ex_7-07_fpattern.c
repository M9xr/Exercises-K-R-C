/* Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its input from set of named files or, if no files are named as arguments, from standard input.
 * Should the file by printed when a matching line is found? */
/* -Yes. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int igetline(char *, int);
int getstr(FILE *, char *, int);

#define MAXCHARS 234

int main(int argc, char *argv[]) {

	long lineno = 0;
	int c, except = 0, number = 0, found = 0;
	char line[MAXCHARS];
	char *prog = argv[0];

	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
				case 'x':
					except = 1;
					break;
				case 'n':
					number = 1;
					break;
				default:
					fprintf(stderr, "%s: illegal option %c\n", prog+10, c);
					exit(1);
			}
	if (argc == 0) {
		fprintf(stderr, "%s: Usage: \"fpattern -x -n pattern\", exiting.\n", prog+10);
		exit(1);
	}
	else if (argc == 1) {
		while ((igetline(line, MAXCHARS)) > 0) {
			lineno++;
			printf("\n");
			if ((strstr(line, *argv) != NULL) != except) {
				if (number)
					printf("%ld:", lineno);
				printf("%s", line);
				found++;
			}
		}
	}
	else {
		FILE *fp;
		char *pattern = *argv;
		int print;
		
		while (--argc > 0) {
			lineno = 0;
			print = 0;
			if ((fp = fopen(*++argv, "r")) == NULL)
				fprintf(stderr,"\n%s: can't open %s\n", prog+10, *argv);
			else {
				while (getstr(fp, line, MAXCHARS) != -1) {
					++lineno;
					if ((strstr(line, pattern) != NULL) != except) {
						if (print == 0) {
							printf("\n\n\t--------%s:--------\n", *argv);
							print = 1;
						}
						if (number)
							printf("%ld:  ", lineno);
						printf("%s\n", line);
						found++;
					}
				}
				fclose(fp);
			}
		}
	}
	printf("\nTotal found:%d\n", found);
	exit(0);
}

/* getline: read a line, return length */
int igetline(char *line, int max) {

	if(fgets(line, max, stdin) == NULL)
		return 0;
	else
		return strlen(line);
}
	
int getstr(FILE *ifp, char *s, int lim) {

	while ((*s = getc(ifp)) != '\n' && *s != EOF && --lim >0)
		++s;
	if (*s != EOF) {
		if (*s == '\n')
			*s = '\0';
		else 
			*++s = '\0';
		return 0;
	}
	return -1;
}

