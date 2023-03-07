#include <stdio.h>
#define MAXCHAR 1000
void tss (int num);
void escape (char s[], char t[]);
int main (void) {

	char s[MAXCHAR], t[MAXCHAR];
	int c, i, nb;
	
	for (i = 0; i < MAXCHAR; i++) {
		s[i] = t[i] = 0; }
	nb = 0;
	printf("Write the first text: ");
		while ((c = getchar()) != EOF && nb < (MAXCHAR/2)){
			s[nb] = c;
			++nb; }
	getchar(c) == 'C';	
	nb = c = 0;
	printf("\nWrite the second text: "); 
		while ((c = getchar()) != EOF){
			t[nb] = c; tss(2);
			++nb; tss(3); }
	tss(1);
	escape(s, t);
}

void escape (char s[], char t[]) {
	
	int c, i;
	
	i = c = 0;
	while (s[i] != '\0')
		++i;
	while (t[c] != '\0') {
	       	switch (c) {
                case '\t':
		       	c = '\\';
			s[i] = c;
			++i;
			c = 't';
			s[i] = c;
			++i;
			break;
		case '\n':
			c = '\\';
			s[i] = c;
			++i;
			s[i] = c;
			++i;
			break;
		default :
			s[i] = c;
			++i;
			break; }
	}
	printf("The final string is: %s", s);
	printf("\n\n");
}	
			
void tss (int num) {
	printf("Test%d", num); 
}
		   		  
		


