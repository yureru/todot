#ifndef SAVELOAD_H
#define SAVELOAD_H
#include <stdio.h>
#include "list.h"

/* File text has the form:
[task]text of the task
[task]yes this is another task
[date]Jun 18
[note]this is a note :^)
*/

/* load_data
 * Description: Opens a file, if sucess calls load_list_f() and fclose().
 * Parameters: Pointer to struct data.
 * Returns: int.
 **/
int load_data(struct data *sd);

/* load_list_f
 * Description: Reads a file, checking if the line begins with any of TypeNote
 *              array, if so calls new_item to create a note or task based of
 *              matching of TypeNote comparing, and assign the string to the new
 *              node. A date could be after a task, this is assigned on the next
 *              iteration.
 * Parameters: Pointer to struct data.
 * Returns: int.
 **/
int load_list_f(struct data *sd, FILE *db);

/* flush_line_f
 * Description: Discards line until '\n' or EOF. Currently unused.
 * Parameters: Pointer to opened file.
 * Returns: Zero if reached EOF, true otherwise.
 **/
int flush_line_f(FILE *db);

/* new_item
 * Description: Creates a task or note, or assign the date to the last task
 *              created (tail).
 * Parameters: Task or note id, wastask if the last item read was task,
 *             pointer to struct data, pointer to allocated string.
 * Returns: Nothing.
 **/
void new_item(int taskornote, int *wastask, struct data *sd, char *str);

/* save_data_f
 * Description: Opens a file, and calls apply_f() to save the data to file.
 * Parameters: Pointer to struct data, double pointer to string (typeNote).
 * Returns: Nothing.
 **/
void save_data_f(struct data *sd, const char **tn);
#endif // SAVELOAD_H
