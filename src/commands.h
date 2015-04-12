#ifndef COMMANDS_H
#define COMMANDS_H
#include "list.h"
/* Protoypes */
/* get_command
 * Description: Ask for a command.
 * Parameters: None yet ??
 * Returns: ??
 **/
int get_command(void);

/* validate_cmd
 * Description: Converts the string to lower case and deletes the first
 *              new-line character.
 * Parameters: Pointer to null terminated string.
 * Returns: Nothing
 **/
void validate_cmd(char *str);

/* search_cmd
 * Description: Search a command from the given string and cmd array.
 * Parameters: Pointer to null terminated string.
 * Returns: Zero if command wasn't found, and positive specifying the
 *          command that was found (from 1 to cmdqt).
 **/
int search_cmd(const char * restrict str);


/* operation
 * Description: Selects which command perform.
 * Parameters: Opcode, pointer to struct data.
 * Returns: Nothing.
 **/
void operation(int op, struct data *savedata);

// Ask input based on option
void ask_input(unsigned op);

/* id2delete
 * Description: Gets number used to delete an id. This number needs to be < 8,
 *              can't start with 0, and can't have - + characters.
 * Parameters: Nothing.
 * Returns: int, the id.
 **/
int id2delete(void);

/* strisnum
 * Description: Checks if given string is valid number (e.g: doesn't contain
 *              characters different to digits.)
 * Parameters: Pointer to string.
 * Returns: True if number is correct, false otherwise.
 **/
int strisnum(const char *str, size_t sz);

/* propernum
 * Description: Checks if first digit is not '0'.
 * Parameters: Pointer to string.
 * Returns: True or false.
 **/
int propernum(const char *str);

/* str2num
 * Description: Converts str to int of a maximum maxdgt digits. (e.g: "321" to 321).
 * Parameters: Pointer to string, and maxdgt (strlen of string). -Warning-: Don't pass
 *             a dirty string (not contains only digits) and a string that is too long
 *             because it would overflow the integer, pass string of 7 length at max. 
 *
 **/
int str2num(const char *str, size_t maxdgt);

#endif // -> COMMANDS_H
