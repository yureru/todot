/* Linked list */
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "date.h"

// Globals
int fitem = 1; // True if the list is empty, false if contains element(s).

void initdata(struct data *savedata)
{
	initinfo(savedata);
}

void initnode(struct node *item)
{
	item->ton  = 0;
	item->str  = NULL;
	item->date  = NULL;
	item->next = NULL;
}

void initinfo(struct data *savedata)
{
	savedata->taskqt = 0;
	savedata->noteqt = 0;
	savedata->head   = NULL;
	savedata->tail   = NULL;
}

struct node *create_item(void)
{
	struct node *newnode = NULL;
	if ((newnode = malloc(sizeof(struct node))) == NULL) {
		printf("Error: malloc failed at allocating node"
			" on %s function\n", __func__);
		exit(EXIT_FAILURE);
	}
	// Initialize 
	initnode(newnode);
	return newnode;
}

// New definition that is FIFO
void insert_item(struct data *savedata, int taskornote, char *str)
{
	struct node *new = create_item();
	new->ton = taskornote;
	new->str = str;
	new->next = NULL;
	// Global fitem used to determine if list is empty
	if (fitem) {
		savedata->head = new;
		savedata->tail = new;
		fitem = 0;
	} else {
		savedata->tail->next = new;
		savedata->tail = new;
	}
}

void print_data(struct data *savedata)
{
	struct node *curr = savedata->head;
	while (curr != NULL) {
#ifdef DEBUG
		printf("String is: %s\n", curr->str);
		if (curr->ton == 1 && curr->date != NULL)
			printf("Date is: %s\n", curr->date);
#endif
		curr = curr->next;
	}
	
}

void delete_list(struct data *savedata)
{
	struct node *nextp = savedata->head;
	for (struct node *curr = nextp;
		curr != NULL;
		curr = nextp) {
		nextp = curr->next;
		free(curr->str);
		free(curr);
	}
	savedata->head = NULL;
	savedata->tail = NULL;
}

void apply(const struct data *savedata,
		const char *(*fn)(const struct node *curr, size_t id),
		unsigned comp)
{
	const unsigned print_all = 3;
	struct node *curr = savedata->head;
	int items = 0;
	for (size_t i = 1; curr != NULL; ++i, curr = curr->next) {
		if (comp == print_all || curr->ton == comp) {
			(*fn)(curr, i);
			++items;
		}
	}
	if (items == 0)
		printf("%s\n", (*fn)(curr, 0)); // Use fn string returned.
}

const char *print_note_windex(const struct node *curr, size_t id)
{
	static const char *msg = "There's no notes currently";
	if (id != 0)
		printf("[id %d] %s\n", id, curr->str);
	return msg;
}

const char *print_task_windex(const struct node *curr, size_t id)
{
	static const char *msg = "There's no tasks currently";
	if (id != 0)
		printf("[id %d] %s\n", id, curr->str);
	return msg;
}

const char *print_task_note_windex(const struct node *curr, size_t id)
{
	static const char *msg = "There's no tasks or notes currently";
	if (id != 0)
		printf("[id %d] %s\n", id, curr->str);
	return msg;
}

void print_task_for_today(const struct data *savedata)
{
	struct node *curr = savedata->head;
	int today_task = 0;
	while (curr != NULL) {
		if (curr->ton == 1 && curr->date != NULL) {
			if (istoday(curr->date)) {
				printf("Task: %s\n", curr->str);
				today_task = 1;
			}
		}
		curr = curr->next;
	}
	if (!today_task)
		puts("There's no tasks with today's date");
	
}

void delete_item(struct data *savedata, size_t id, int taskornote)
{
#ifdef DEBUG
	printf("#id: %u, ton: %d\n", id, taskornote);
#endif
	struct node *curr = savedata->head; // Current
	struct node *prev = NULL; // Before
	struct node *next = NULL; // After
	if (!item_exists(id,(const struct node **) &curr, (const struct node **) &prev)) {
		puts("Item doesn't exists");
		return;
	}

	// Item exists
	if ((unsigned)taskornote != curr->ton) { // Cast to get rid of warning
			puts("Type of task or note doesn't match");
			return;
	}
	if (prev != NULL) { // Item is no the first one
#ifdef DEBUG
		printf("taskornote is: %u\ncurr->ton is: %u", taskornote, curr->ton);
#endif
		if (curr->next == NULL) {
			curr = del_itm(curr, taskornote);
			prev->next = next;
			savedata->tail = prev;
		} else {
			next = curr->next;
			curr = del_itm(curr, taskornote);
			prev->next = next;
		}
		return;
	}
	
	// If item to delete is the first one
	if (curr->next == NULL) {
		// Item to delete is the first and the only one in list
		curr = del_itm(curr, taskornote);
		savedata->head = NULL;
		savedata->tail = NULL;
		fitem = 1;
	} else {
		// Item to delete is the first one but theres more items in the list
		 next = curr->next;
		 curr = del_itm(curr, taskornote);
		 savedata->head = next;
	}
}

struct node *del_itm(struct node *item, int taskornote)
{
	if (taskornote == 1)
		free(item->date);
	
	free(item->str);
	free(item);
	return NULL;
}

int item_exists(size_t id, const struct node **curr, const struct node **prev)
{
	size_t i;
	for (i = 1; *curr != NULL && i < id; ++i) {
		*prev = *curr;
		*curr = (*curr)->next;
	}
	if (*curr != NULL && i == id)
		return 1;
	return 0;
}

void apply_f(const struct data *savedata, FILE *db, const char **tn)
{
	for (struct node *curr = savedata->head;
		curr != NULL;
		curr = curr->next) {
		if (curr->ton == 1) {
			fprintf(db, "%s%s\n", tn[0], curr->str);
			if (curr->date != NULL)
				fprintf(db, "%s%s\n", tn[1], curr->date);
		}
		if (curr->ton == 2)
			fprintf(db, "%s%s\n", tn[2], curr->str);
	}
}
