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
int save_data(struct data *sd, FILE *db);
int flush_line(FILE *db);
void new_item(int taskornote, int *wastask, struct data *sd, char *str);
#endif // SAVELOAD_H
