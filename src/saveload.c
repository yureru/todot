/* Save/load functions */
#include <stdio.h>
#include <stdlib.h>

#include "saveload.h"
#include "list.h"

const char *DB_FILE = "./src/db.txt";

const char *typeNote[] = {"[task] = ", "[date] = ", "[note] = "};

struct node *list;
struct data savedata;

int load_data(struct node *list, struct data *sd)
{
	initdata(list, sd);
	return 0;
}
