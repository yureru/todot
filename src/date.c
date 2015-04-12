/* Functions related to date */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "date.h"
#include "commands.h"

// Global external variables, getted from commands.c
extern const char *months[];
extern const unsigned monthqt;

// Globals
char currentdate[7]; // Today's date in form "MMM DD", plus NUL that's why 7 size.

/* A date to be valid needs to be "mar 3" "mar 29" so str > 4 && str < 7  */
// dec 111
int correct_length_date(char *str)
{
	validate_cmd(str);
	size_t sz = strlen(str);
	if (sz < 5 || sz > 6)
		return 0;
	return 1;
}

int in_alphabet(const char * restrict str, size_t until)
{
	size_t cnt = 0;
	for (size_t i = 0; str[i] != '\0' && i < until; ++i, ++cnt)
		if (!isalpha(str[i]))
			break;
	if (cnt == until)
		return 1;
	return 0;
}

int are_digit(const char * restrict str, size_t adv, size_t quantity)
{
	for (size_t i = 0; i < adv && str != '\0'; ++i, ++str)
		;
	size_t cnt = 0;
#ifdef DEBUG
	printf("str is: '%s'\n", str);
#endif
	for (size_t i = 0; str[i] != '\0' && i < quantity; ++i, ++cnt)
		if (!isdigit(str[i]))
			break;
	if (cnt)
		return 1;
	return 0;
}

int is_month(const char * restrict str, size_t sz)
{
	for (size_t i = 0; i < monthqt; ++i)
		if (!strncmp(str, months[i], sz))
			return i + 1;
	return 0;
}

int date_is_valid(char *str)
{
	// New approach, functions needs to be called only if the before one was returned true
	return correct_length_date(str) && in_alphabet(str, 3) && are_digit(str, 4, 2) &&
		is_month(str, 3) && day_in_range(str);
}

int fur_val(const char * restrict str)
{
	if (str[3] != ' ')
		return 0;
	if (str[4] == '0')
		return 0;
	if (str[5] != '\0' && !isdigit(str[5]))
		return 0;
	return 1;
}

int day_in_range(char *str/*, size_t number*/)
{
	// error at power * 10, day 11 is 59
	str += 4; // Safe since short-circuit evaluation on call
	int day = 0;
	int qt = 0; // Number of digits (max is 2)
	for (int i = 0; str[i] != '\0'; ++i)
		++qt;
	if (qt == 1) {
		day = isdigitchar(*str);
	} else {
		day = isdigitchar(*str) * 10;
		//day += str[1];
		day += isdigitchar(str[1]);
	}
	if (day > 0 && day < 32)
		return 1;
	return 0;
}

int isdigitchar(char c)
{
	switch (c) {
		case '0':
			return 0;
		break;
		case '1':
			return 1;
		break;
		case '2':
			return 2;
		break;
		case '3':
			return 3;
		break;
		case '4':
			return 4;
		break;
		case '5':
			return 5;
		break;
		case '6':
			return 6;
		break;
		case '7':
			return 7;
		break;
		case '8':
			return 8;
		break;
		case '9':
			return 9;
		break;
		default:
			return 0;
		break;
	}
	return 0; // muh warnings
}

void get_date(void)
{
	time_t rawtime;
	time(&rawtime);
	pdate(ctime(&rawtime));
#ifdef DEBUG
	printf("Date is: %s\n", currentdate);
#endif
}

void pdate(const char *date)
{
	strncpy(currentdate, date + 4, 6); /* date + 4 since date is "Wed Feb 14", therefore
	                               it would start at "Feb 14", and 6 because "Feb 14" size is 6*/
	if (currentdate[4] == '0') {
		currentdate[4] = currentdate[5];
		currentdate[5] = '\0';
	} else {
		currentdate[6] = '\0';
	}
	validate_cmd(currentdate);
}

int istoday(const char *date)
{
	if (strcmp(date, currentdate) == 0)
		return 1;
	return 0;
}
