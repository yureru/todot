#ifndef READIN_H
#define READIN_H
#include <stdio.h>
/* gets_unl
 * Description: Calls readstdin.
 * Parameters: Nothing. (DELETING ALL ARGS FOR gets_unl()
 * Returns: Pointer to string.
 **/
char *gets_unl(void);

/* readstdin
 * Description: Gets a string of unkown length from stdin.
 * Parameters: Nothing.
 * Returns: Pointer to null terminated string, or NULL if couldn't allocate memory.
 **/
char *readstdin(void);

/* want_date
 * Description: Gets input when asked if date is wanted to be added.
 * Parameters: Nothing.
 * Returns: true if input was "y" or "Y", false otherwise.
 **/
int want_date(void);

/* is_null
 * Description: Returns true if pointer given is NULL, false otherwise.
 * Parameters: Pointer to char.
 * Returns: size_t.
 **/
size_t is_null(char *ptr);

/* gets_unl_f
 * Description: Same behaviour as gets_unl(), but reads from a file instead of stdin.
 * Parameters: Correctly opened file that must be readable.
 * Returns: Pointer to null terminated string.
 **/
char *gets_unl_f(FILE *db);
#endif // -> READIN_H
