/* Exercise 4-8. Suppose that there will never be more than one character of pushback. Modify "getch" and "ungetch" accordingly. */
/* Exercise 4-9. Our "getch" and "ungetch" do not handle a pushed-back "EOF" correctly. Decide what their properties ought to be if an "EOF" is pushed back, then implement your design. */

#include <stdio.h>
#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getch (void);
void ungetch (int c);

int main () {

	signed char s[100];
	int c, i, j, h;
	for (i = 0, j = 19; i < j; ++i) 
		s[i] = getch();
	ungetch ('\0');
	ungetch (EOF);
	printf("i=%d j=%d s[i]=%c", i, j, s[i-1]);
	printf("\nTHERE IS 2L\n");
	s[j] = getch();
	s[j+1] = getch();
	printf("%hhn\n", s);
	s[i] = getch();
	s[i+1] = getch();
	printf("Dupxo\n%hhn\n",s);
	s[j] = getch();
	s[j+1] = getch();
	printf("22Dupxo\n%hhn\n",s);
	
	return 0;

}
int getch(void)
{
	if (bufp > 0) {
		--bufp;
		return buf[0];
	}
	else
		return getchar();
}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("error: stack is full, can't execute ungetch()\n");
	else if (bufp < BUFSIZE && c != EOF) {
		buf[bufp] = c;
		++bufp;
	}
	else if (c == EOF) {
		buf[bufp] = '\0'; 
		++bufp;}

	printf("uno=%c\n", c);
}


