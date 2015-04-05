#ifndef SAVELOAD_H
#define SAVELOAD_H
#include "list.h"
/* File text has the form:
[task]text of the task
[task]yes this is another task
[date]Jun 18
[note]this is a note :^)

*/

int load_data(struct node *list, struct data *sd);

#endif // SAVELOAD_H
