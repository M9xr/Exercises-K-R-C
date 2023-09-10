/* Exercise 5-08. There is no error checking in "day_of_year" or "month_day". Remedy this defect. */

#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {

	int i, leap;
        
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	if ((month < 1 || month > 12) || (day < 1 || day > 31) || (day > 30 && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)) || \
                        (leap && month == 2 && day > 29) || (!leap && month == 2 && day > 28))
                return -1;
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day: set month and day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {

	int i, leap;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	if (yearday < 1 || (leap && yearday > 366) || (!leap && yearday > 365))
        	return;

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

int main(void) {

	int yearday1, month1, year1, yearday2, month2, year2, day1;
	

	yearday1 = day_of_year(2000, 6, 6);
       	month_day(2023, 122, &month1, &day1);
	if (yearday1 < 0) {
		printf("Error, wrong values\n");
		return -1;
	}
	printf("year day of 06/06/2000 is:%d\nfor 122th day of 2023 year the month is:%d, and the day is:%d\n", yearday1, month1, day1);

	return 0;
}	

	
