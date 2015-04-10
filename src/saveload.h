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

int load_data(struct node *list, struct data *sd);
int load_list_f(struct data *sd, FILE *db);
int flush_line_f(FILE *db);
void new_item(int taskornote, int *wastask, struct data *sd, char *str);
void save_data_f(struct data *sd, const char **tn);
#endif // SAVELOAD_H
