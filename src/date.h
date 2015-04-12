#ifndef DATE_H
#define DATE_H

/* correct_length_date
 * Description: Checks if the string length is < 7 ("mar 12"), and
 *              > 4 ("mar 1").
 * Parameters: Pointer to string.
 * Returns: True if length is correct, false otherwise.
 **/
int correct_length_date(char *str);

/* in_alphabet
 * Description: Checks if characters begining str upto until are alphabet
 *              characters.
 * Parameters: Pointer to string, numbers of characters to be checked.
 * Returns: True if those characters are letters, false otherwise.
 **/
int in_alphabet(const char * restrict str, size_t until);

/* are_digit
 * Description: Check if the characters from str + adv position upto
 *              quantity are digits.
 * Parameters: Pointer to string, adv the number of characters to advance
 *             str before checking, and quantity the number of characters to
 *             check if are digit.
 * Returns: True if are digits, false otherwise.
 **/
int are_digit(const char * restrict str, size_t adv, size_t quantity);

/* is_month
 * Description: Checks if the string has a month substring.
 * Parameters: Pointer to string, sz size of month (should be 3).
 * Returns: An int specifying the month found (1 for January, 2 for
 *          February, ...), false otherwise.
 **/
int is_month(const char * restrict str, size_t sz);

/* date_is_valid
 * Description: Wrapper for in_alphabet, are_digit, and is_month functions.
 * Parameters: Pointer to string.
 * Returns: True if date is valid, false otherwise.
 **/
int date_is_valid(char *str);

/* fur_val (further_validation)
 * Description: Wacky hacky function to validate strange cases of date like:
 *              "decc10", "dec 0", "dec 1o", "dec 01".
 * Warning: Even though in the function we're indexing to a fixed position,
 *          this is safe because this function is only executed if validate_date
 *          returns true, thanks to short circuit evaluation of operator && in
 *          date_is_valid function.
 * Parameters: Pointer to string.
 * Returns: True if valid date, false otherwise.
 **/
int fur_val(const char * restrict str);

/* day_in_range
 * Description: Check if day range is valid, (> 0 && < 32).
 * Parameters: Pointer to string.
 * Returns: True if day is in range, false otherwise.
 **/
int day_in_range(char *str);

/* isdigitchar
 + Description: Similar to isdigit(), but instead of returning true or false
 *              returns the corresponding int value.
 * Parameters: Char.
 * Returns: int.
 **/
int isdigitchar(char c);

/* get_date
 * Description: Calls ctime to get current date.
 * Parameters: Nothing.
 * Returns: Nothing.
 */
void get_date(void);

/* pdate
 * Description: Puts date in the form "MMM DD" on the global currentdate, and make it a string.
 * Parameters: Pointer to date obtained from ctime.
 * Returns: Nothing.
 */
void pdate(const char *date);

/* istoday
 * Description: Compares today's date and the string given.
 * Parameters: Pointer to date string.
 * Returns: True if compare was success, false otherwise.
 **/
int istoday(const char *date);
#endif // -> DATE_H
