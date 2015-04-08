/* Save/load functions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "saveload.h"
#include "list.h"

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
		save_data(&savedata, db);
	else
		puts("Couldn't open file");
	
	return 0;
}


// refactor function, this is wider than hidamari's faces
int save_data(struct data *sd, FILE *db)
{
	static size_t cmpsz = strlen(typeNote[0]); // All three strings are strlen 9
	static char subbuff[cmpsz + 1];
	signed char c;
	int count = 1;
	int wastask = 0;
	while ((c = fgetc(db)) != EOF) {
		subbuf[count] = c;
		if (count == cmpsz) {
			subbuf[cmpsz] = '\0';
			for (int i = 0; typeNote[i] != NULL; ++i) {
				if (strcmp(subbuf, typeNote[i]) == 0) {
					// lastnode was task and had date string
					if (wastask && i == 1) {
						sd->tail->str; // save str date
						wastask = 0;
					}
					
					// line has task
					if (i == 0) {
						insert_item(list, sd, 1, str);
						wastask = 1;
					}
					if (i == 2) {
						insert_item(list, sd, 2, str);
						wastask = 0;
					}
					
					// start reading from this allocating mem until new-line
					// create node based on i (i == 0 -> create task,
					// i == 1 -> check if after i was 0, add date on last node. i == 2, create note.
				} else {
					// read until '\n'
					if (!flush_line(db)) {
						// exit loop and function, we reached end of file
						
					}
				}
			}
			count = 1;
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
