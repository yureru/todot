/* Save/load functions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "saveload.h"
#include "list.h"
#include "readin.h"

const char *DB_FILE = "./src/db.txt";

const char *typeNote[] = {"[task] = ", "[date] = ", "[note] = ", NULL};

struct node *list;
struct data savedata;

int load_data(struct node *list, struct data *sd)
{
	initdata(list, sd);
	// load file
	FILE *db = NULL;
	db = fopen(DB_FILE, "r");
	if (db != NULL)
		save_data(sd, db);//save_data(&savedata, db);
	else
		puts("Couldn't open file");
	
	return 0;
}


// refactor function, this is wider than hidamari's faces
int save_data(struct data *sd, FILE *db)
{
	size_t cmpsz = strlen(typeNote[0]); // All three strings are strlen 9
	char subbuff[cmpsz + 1];
	signed char c;
	size_t count = 0;
	int wastask = 0;
	while ((c = fgetc(db)) != EOF) {
		subbuff[count++] = c;
		if (count == cmpsz) {
			subbuff[cmpsz] = '\0';
			char *str = gets_unl_f(db);
			for (int i = 0; typeNote[i] != NULL; ++i)
				if (strcmp(subbuff, typeNote[i]) == 0)
					new_item(i, &wastask, sd, str);
			count = 0;
		}
	}
	return 0; // edit
}

int flush_line(FILE *db)
{
	int i;
	while ((i = fgetc(db)) != '\n' && i != EOF)
		; // EMPTY BODY
	if (i == EOF)
		return 0;
	return 1;
}

void new_item(int taskornote, int *wastask, struct data *sd, char *str)
{
	// lastnode was task and had date string
	if (*wastask && taskornote == 1) {
		sd->tail->date = str; // save str date
		*wastask = 0;
	} else if (taskornote == 1){
		free(str); // Date was found after a note, discard it
		*wastask = 0;
	}
	if (taskornote == 0) {
		insert_item(list, sd, 1, str);
		*wastask = 1;
	}
	if (taskornote == 2) {
		insert_item(list, sd, 2, str);
		*wastask = 0;
	}
}
