/* Exercise 5-9. Rewrite the routines day_of_year and month_day with pointers instead of indexing. */

#include <stdio.h>
int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);


static int tab[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static int tab2[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static int *daytab[] = {tab, tab2};

/* day_of_year: set day of year from month & day */
int day_of_year (int year, int month, int day) {

	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	 if (day < 1 || month < 1 || month > 12 || (month == 2 && leap && day > 29) || (month == 2 && !leap && day > 28) || \
	     ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || (!(month == 4 || month == 6 || month == 9 || month == 11) && day > 31))
		return 0;
	
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day: set month, day from day of year */
void month_day (int year, int yearday, int *pmonth, int *pday) {
	
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	if (yearday < 1 || (leap && yearday > 366) || (!leap && yearday > 365))
    {
        *pmonth = *pday = 0;
        return; // invalid input
    }

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

/* My pointers in main hadn't got (probably) defined memory therfore it hadn't work!*/
int main () {

	int day, month, ydy, a,b,c,d,e,f,g;
	day = 12;
	month = 7;
	ydy = 69;
	
	a = day_of_year (1666, 12, 4);
	month_day (2023, ydy, &month, &day);
	printf("Day of 4th Dec 1666 - %d\n2023, 69 day - month:%d day:%d\n", a, month, day);

	return 0;
}


	
