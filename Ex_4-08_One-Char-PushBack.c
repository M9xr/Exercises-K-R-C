/* Exercise 4-8. Suppose that there will never be more than one character of pushback. Modify "getch" and "ungetch" accordingly. */

#include <stdio.h>
#define BUFSIZE 1

char buf[BUFSIZE];
int bufp = 0;

int getch (void);
void ungetch (int c);

int main () {

	printf("size:%d\n", bufp);
	int i, g;
	char s[] = "Not Cool Exercise!";
	printf("size:%d\n", bufp);

		


}
int getch(void)
{
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("error: stack is full, can't execute ungetch()\n");
	else
		buf[bufp++] = c;
}


