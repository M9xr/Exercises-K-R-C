/* Exercise 1-24. Write a program to check a C program for rudimentary syntax errors like unmatched parentheses, bracktes and braces.
 * Don't forget about quotes, both single and double, escape sequences, and comments. (This program is hard if you do it in full generality.) */

#include <stdio.h>

#define MAXCHARS 30000
#define MAXCHAR 1000

int syntax_checker(char s[]);
int xgetline(char s[], int lim);
void cat_strings(char s[], char t[]);

int main(void) {

	char buffer[MAXCHARS];
	char line[MAXCHAR];
	int len, condition;

	while ((len = xgetline(line, MAXCHAR)) > 0)
		cat_strings(buffer, line);
	if ((condition = syntax_checker(buffer)) != 0) 
		printf("There are %d bugs in the program.\n", condition);
	else
		printf("Syntax-chcker: Program have no major bug.\nIf you cannot compile the program, make sure that it doesn't try to read areas of the memory it shouldn't.\n");
	
	return 0;
}

#define TRUE  	1
#define FALSE 	0
#define OPEN  	11
#define CLOSED  10

/* rudimentary syntax error checker */
/* take C program as a string, return number of bugs */
int syntax_checker(char s[]) {

	/* variables for syntax checker */
	int comment = FALSE;		/* whether a comment is open  */
	int brackets = 0;		/* number of open brackets */
	int state_brackets = CLOSED;	/* whether brackets are open or closed */
	int last_brackets = 0;		/* line number of the last opened bracket */
	int braces = 0;			/* number of open braces */
	int state_braces = CLOSED;	/* whether braces are open or closed */
	int last_braces = 0;		/* line number of the last opened brace */
	int q_single = 0;		/* number of open single quotes */
	int q_double = FALSE;		/* whether double quotes are open*/
	int escape = 0;			/* number of bad escape sequences */
	int parens = 0;			/* number of open parens */
	int state_parens = CLOSED;	/* whether parens are open or closed */
	int last_parens = 0;		/* line number of the last opened parens */
	int line = 0;			/* line number */
	int bugs = 0;			/* number of bugs found in a program */
	int last = 0;			/* starting position of the line */
	int error = FALSE;  		/* state of error: if there is no error, state is FALSE; */
	int i, cond;
	i = cond = 0;
	
	while (s[i] != '\0') {
		if (s[i] == '\n') {
			printf("%3d| ", ++line);
			while (last <= i) {
				printf("%c", s[last]);
				++last;
			}
		}
		if (s[i] == '(') {
			++parens;
			state_parens = OPEN;
			last_parens = line+1;
		}
		if (s[i] == ')') {
			--parens;
			state_parens = CLOSED;
		}
		if (s[i] == '{') {
			++braces;
			state_braces = OPEN;
			last_braces = line+1;
		}
		if (s[i] == '}') {
			if (--braces < 0) {
				printf("*** Error: Closing braces don't have pair. Line:%d\n", line+1);
				++bugs;
				++braces;
			}
			state_braces = CLOSED;
		}
		if (s[i] == '[') {
			++brackets;
			state_brackets = OPEN;
			last_brackets = line+1;
		}
		if (s[i] == ']') {
			if (--brackets < 0) {
				printf("*** Error: Closing brackets don't have pair. Line:%d\n", line+1);
				++bugs;
				++brackets;
			}
			state_brackets = CLOSED;
		}
		if (s[i] == '"') {
			++i;
			while (s[i] != '"' && s[i] != EOF)
				++i;
			if (s[i] != '"') {
				printf("*** Error: Double quote is not closed. Line:%d\n", line+1);
				++bugs;
			}
			
		}
		if (s[i] == '\'') {
			++i;
			if (s[i] == '\\') {
				++i;
				if (s[i] != 'n' && s[i] != 't' && s[i] != 'b' && s[i] != '\'' && s[i] != '\\' && s[i] != '0' && s[i] != 'v') {
					printf("*** Error: Bad escape sequence. Line:%d\n", line+1);
					++bugs;
				}
			}
			++i;
			if (s[i] != '\''){
				printf("*** Error:%c invalid single quote usage. Line:%d\n", s[i],line+1);
				++bugs;
				}
		}
		if (s[i] == '/') {
			++i;
			if (s[i] == '/') {
				while (s[i] != '\n' && s[i] != EOF)
					++i;
				--i;
			}
			else if (s[i] == '*') {
				cond = TRUE;
				while (cond != FALSE && s[i] != EOF) {
					++i;
					if (s[i] == '\n') {
						printf("%3d| ", ++line);
						while (last <= i) {
							printf("%c", s[last]);
							++last;
							}
						}	
					if (s[i] == '*') {
						++i;
						if (s[i] == '/') {
							cond = FALSE;
						}
					}
				}
				if (cond == TRUE) {
					printf("*** Error: Comment is not closed. Line:%d\n", line);
					++bugs;
				}
			}
		}
			++i;
	}

	if (state_parens == OPEN) {
		printf("*** Error: Parens aren't closed. Line:%d\n", last_parens);
		++bugs;
	}
	if (state_braces == OPEN) {
		printf("*** Error: Braces aren't closed. Line:%d\n", last_braces);
		++bugs;
	}
	if (state_brackets == OPEN) {
		printf("*** Error: Brackets aren't closed. Line:%d\n", last_brackets);
		++bugs;
	}
	printf("\n");
	return bugs;
}


/* xgeltine: get a line into string s, return length of the line */
int xgetline(char s[], int lim) {

        int c, i;
        for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
                s[i] = c;
        if (c == '\n') {
                s[i] = c;
                ++i;
        }
        s[i] = '\0';
        return i;
}

/* cat_strings: concatenate t to end of s; s must be big enough */
void cat_strings(char s[], char t[]) {

        int i, j;

        i = j = 0;
        while (s[i] != '\0')    /* find end of s */
                i++;
        while ((s[i++] = t[j++]) != '\0') /* copy t */
                ;
}

