/* Exercise 5-18. Make "dcl" recover from input errors. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};

void dcl (void);
void dirdcl (void);
void buffclear (void);

int gettoken (void);		
int tokentype;			/* type of last token */
char token[MAXTOKEN];		/* last token string */
char name[MAXTOKEN];		/* identifier name */
char datatype[MAXTOKEN];	/* data type = char, int, etc. */
char out[1000];

/* convert declaration to words */
int main (void) {

	while (gettoken() != EOF) {		/* 1st token on line --- */
		strcpy (datatype, token);	/* --- is the datatype */
		out[0] = '\0';
		dcl();				/* parse rest of line */
		if (tokentype == '\n' && datatype[0] != '\0' && name[0] != '\0')
			printf("%s: %s %s\n", name, out, datatype);
		else {
			token[0] = '\0';
			printf("---Syntax error, buffer is cleared automatically.\n");
			buffclear();
			out[0] = name[0] = datatype[0] = '\0';
		}
	}
	return 0;
}

/* dcl: parse a declarator */
void dcl (void) {

	int ns;

	for (ns = 0; gettoken() == '*'; )	/* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat (out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl (void) {

	int type;

	if (tokentype == '(') {		/* (*dcl) */
		dcl ();
		if (tokentype != ')')
			printf("---Bad syntax: missing \")\n");
	} 
	else if (tokentype == NAME)	/* variable name */
		strcpy (name, token);
	else
		printf("-x-error: expected name or (dcl)\n");
	
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat (out, " function returning");
		else {
			strcat (out, " array");
			strcat (out, token);
			strcat (out, " of");
		}
}

int getch (void);
void ungetch (int);

/* return next token */
int gettoken (void) {

	int c, getch (void);
	void ungetch (int);
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy (token, "()");
			return tokentype = PARENS;
		} else {
			ungetch (c);
			return tokentype = '(';
		}
	} 
	else if (c == '[') {
		*p++ = c;
		c = getch();
		if (isdigit(c))
			for (*p++ = c; isdigit(c = getch()) && c != ']'; )
			      	*p++ = c;	
		else if (isalpha(c)) 
			for (*p++ = c; isalnum(c = getch()) && c != ']'; )
				*p++ = c;

		if (c == ']') {
			*p++ = c;
			*p = '\0';
			return tokentype = BRACKETS;
		} 
		else {
			printf("---Lack of the right bracket \"]\".\n---Added automatically after \"%c\".\n", *(p-1));
			ungetch (c);
			*p++ = ']';
			*p = '\0';
			return tokentype = BRACKETS;
		}
	} 
	else if (isalpha(c)) {
		for (*p++ = c; (isalnum (c = getch())) && !isspace(c); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
        else if (c == '\n')
		return tokentype = '\n';	
	else 
		return tokentype = c;
}

#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

/* get a (possibly pushed-back) character */
int getch (void) {	

	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch (int c) {

	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else {
		if (c != EOF)
			buf[bufp++] = c;
		else
			buf[bufp++] = '\0';
	}
}

/* buffclear: removes all stored chars from the buffer */
void buffclear (void) {

	bufp = 0;
	buf[bufp] = '\0';
}

