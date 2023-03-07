/* Exercise 5-11. Modify the program "entab" and "detab" (written as exercises in Chapter 1) to accept a list of tab stop as arguments.
 * Use the default tab settings if there are no arguments. */
/* Exercuse 5-12. Extend "entab" and "detab" to accept the shorthand "entab -m +n" to mean tab stops every n columns, starting at column m.
 * Choose convenient (for the user) default behaviour. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHAR 2000
#define TRUE 1
#define FALSE 0

int soptional (int argc, char *argv[], int *m, int *n);

int main (int argc, char *argv[]) {

	

}

int soptional (int argc, char *argv[], int *sw, int *sh) {

        int val = 0, c;
        char set = set2 ='Y';
        while (--argc > 0) { 
			c = **(++argv);
			if ((c == '-' && (set = ++(**argv)) == 'm')
                        	 ||
			   (c == '+' && (set2 = ++(**argv)) == 'n'))
                        }
			else {
				printf("Improper value/s, exiting\n");
				return -1;
			}

                         if (isdigit (c = *++argv[0])) {
                                        printf("Digit found!\n");
                                        val = atoi (*argv);
                                        if (val > 1 && val < 250 && set == 'm') {
                                                *sw = val;
                                                }
                                        else if (val > (1 + *sw) && val < MAXCHARS && set == 'n') {
                                                *sh = val;
                                                }
                                        else  {
                                                printf("Wrong value for %s\n", set == 'm' ? "width" : "height");
                                                return -1;
                                                }
                        }
                        else {
                                printf("Error: No proper value for %s\n", set == 'm' ? "width" : "height");
                                return -1;
                                }
                }
        return 1;
}


