/* Functions to get/validate commands */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commands.h"
#include "readin.h"
#include "saveload.h"
#include "list.h"
#include "date.h"

#define BUF_SIZE 20 // Size of input buffer


const char *cmd[] = {"add note", "add task", "delete note", "delete task",
			"help", "?", "print all", "print notes", "print tasks",
			"todo", "quit"};
const unsigned cmdqt = 11; // Number of strings in cmd global variable

const char *options[] = {"Enter cmd: ", "Enter note: ", "Enter task: ",
			"Enter id of note: ", "Enter id of task: ",
			"Want to add date to do this task (y/n): ",
			"Enter month and day (example: Jun 15): "};
			
const char *months[] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug",
			"sep", "oct", "nov", "dec"};
const unsigned monthqt = 12; // Number of months, should be obvious

extern struct node *list;
extern struct data savedata;
		
int get_command(void)
{
	static int init = 1;
	if (init) { // Execute only once
		load_data(list, &savedata);
		get_date();
		init = 0;
	}
		
	static char buf[BUF_SIZE];
	//printf("Enter cmd: ");
	ask_input(0);
	fgets(buf, BUF_SIZE, stdin);
	validate_cmd(buf);
	int indexcmd = 0;
	if ((indexcmd = search_cmd(buf))) {
		operation(indexcmd, list, &savedata);
	} else {
		puts("Unknown command, enter ? or help");
	}
	/* Used for testing */
	if (buf[0] == 'q') {
		//get_date();
		print_data(&savedata);
		delete_list(&savedata);
		return 0;
	}
		
	/*
	if (date_is_valid(buf))
		printf("%s, is a valid date\n", buf);
	else
		printf("%s, is not a valid date\n", buf);
	return 1;*/
	return 1;
}

void validate_cmd(char *str)
{
	for (size_t i = 0; str[i] != '\0'; ++i) {
		str[i] = tolower(str[i]);
		if (str[i] == '\n')
			str[i] = '\0';
	}
}

int search_cmd(const char * restrict str)
{
	for (size_t i = 0; i < cmdqt; ++i)
		if (!strcmp(str, cmd[i]))
			return i + 1; // Should return + 1
	return 0;
}


void operation(int op, struct node *item, struct data *savedata) // CHANGE NAME savedata, HIDES GLOBAL
{
	/*op -= 1; // scale to index*/
	/*if (op > -1 && op < 11)
		printf("%s", options[op]);
	else*/
	int id;
	switch (op) {
		case 1:
			// Add note
			ask_input(op);
			//printf("%s", options[op]);
			insert_item(item, savedata, 2, gets_unl(op));
		break;
		case 2:
			// Add task
			ask_input(op);
			insert_item(item, savedata, 1, gets_unl(op));
			ask_input(5); // Want add date?
			if (want_date()) {
				ask_input(6);
				char *date = gets_unl(op);
				if (date_is_valid(date)) {
					savedata->tail->date = date;
				} else {
					free(date);
				}
			}
		break;
		case 3:
			// Delete note
			ask_input(op);
			id = id2delete();
			if (id == -1) {
				printf("Invalid id\n");
				break;
			}
			delete_item(savedata, id, 2);
		break;
		case 4:
			// Delete task
			ask_input(op);
			id = id2delete();
			if (id == -1) {
				printf("Invalid id\n");
				break;
			}
			delete_item(savedata, id, 1);
		break;
		case 5:
		case 6:
		/* FALL THROUGH */
			// Help
		break;
		case 7:
			// Print all
			//print_task_note_windex(savedata);
			apply(savedata, print_task_note_windex, 3);
		break;
		case 8:
			// Print notes
			//print_note_windex(savedata);
			apply(savedata, print_note_windex, 2);
		break;
		case 9:
			// Print tasks
			//print_task_windex(savedata);
			apply(savedata, print_note_windex, 1);
		break;
		case 10:
			// Todo
			print_task_for_today(savedata);
		break;
		case 11:
			// Quit
		break;
		default:
		break;
	}
	
}

void ask_input(unsigned op)
{
	printf("%s", options[op]);
}

// Ask item to delete, if not valid enter returns -1, otherwise the id from 1 to int_max
/*
 * Ask for number of 7 digits max, that is valid:
 * Valid means: It's not negative, it's not zero, it doesn't start with 0 (e.g: 019), it doesn't contains
 * alphabetic characters (e.g: 12e32).
*/
int id2delete(void)
{
	char *num = gets_unl(0);
	size_t sz = strlen(num);
	// Guards
	if (sz < 1 || sz > 7)
		return -1;
	if (!strisnum(num, sz))
		return -1;
	if (!propernum(num))
		return -1;
	int id = str2num(num, sz);
	free(num);
	return id;
}
int strisnum(const char *str, size_t sz)
{
	for (size_t i = 0; i < sz; ++i)
		if (!isdigit(str[i]))
			return 0;
	return 1;
}

int propernum(const char *str)
{
	if (str[0] == '0')
		return 0;
	return 1;
}

int str2num(const char *str, size_t maxdgt)
{
	size_t cpymd = maxdgt;
	size_t pow = 1;
	while (cpymd) {
		pow *= 10;
		--cpymd;
	}

	pow /= 10; // Divide by ten since we started with pow = 1
	int num = 0;
	for (size_t i = 0; i < maxdgt; ++i) {
		switch (str[i]) {
			case '1':
				num += pow * 1;
			break;
			case '2':
				num += pow * 2;
			break;
			case '3':
				num += pow * 3;
			break;
			case '4':
				num += pow * 4;
			break;
			case '5':
				num += pow * 5;
			break;
			case '6':
				num += pow * 6;
			break;
			case '7':
				num += pow * 7;
			break;
			case '8':
				num += pow * 8;
			break;
			case '9':
				num += pow * 9;
			break;
			default: // Here catchs '0'
			break;
		}
		pow /= 10;
	}
	return num;
}
