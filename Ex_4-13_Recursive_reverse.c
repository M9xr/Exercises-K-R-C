/* Exercise 4-13. Write a recursice version of the function "reverse(s)", which reverses the string s in place. */
#include <stdio.h>

void reverse (char s[]);

int main (void) {

	char s[] = "K jak Kajak";
	char s2[] = "Kamil Slimak";
	reverse (s);
	reverse (s2);
	printf("%s\n%s\n", s, s2);
}

/*void reverse (char s[]) {

	static int i,j;
	if (s[i] != '\0') {
		i++;
		reverse (s);
	}
	i = i - 1;
	s[j] = s[i];
	++j;

}
*/
/*
void reverse(char s[])
{
    static int i,j;

    if (s[i]) {
        int c = s[i++];
        reverse(s);
        s[j++] = c;
    }

    if (i==j)
        i=0,j=0;
}
*/
void reverse(char s[])
{
    static int i = 0, n;
    int c = s[i];
    if (c) {
	printf("Getttherefast\n");
        i++;
        reverse(s);
        s[n-i] = c;
        i--;
	printf("i=%d\tn=%d\n",i,n);

    } else {
        n = i;
	printf("HereIcome\n");
    }
}
