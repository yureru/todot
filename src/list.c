/* Linked list */
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "date.h"

// Globals
int fitem = 1; // True if the list is empty, false if contains element(s).

/* Functions that are needed to implement a linked list:
 * Wrappers: create_note, create_task
 * insert(); Used to insert a node, Ok
 * create_item(); Used to create a node (structure), Ok
 * delete_list(); Used to delete and deallocate nodes and node's members, Ok needs to deallocate date strings.
 *
 */
//void initstructs(struct node *item, struct data *savedata)
void initdata(struct node *item, struct data *savedata)
{
	/*item->ton  = 0;
	item->str  = NULL;
	item->str  = NULL;
	item->next = NULL;
	
	savedata->taskqt = 0;
	savedata->noteqt = 0;
	savedata->todo   = NULL;*/
	/*initnode(item);*/
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
void insert_item(struct node *item, struct data *savedata, int taskornote, char *str)
{
	struct node *new = create_item();
	new->ton = taskornote;
	new->str = str;
	new->next = NULL;
	// Global used to determine if list is empty
	/*fitem = 1; // If first item of list, make savedata point to*/
	if (fitem) {
		savedata->head = new;
		savedata->tail = new;
		fitem = 0;
	} else {
		savedata->tail->next = new;
		savedata->tail = new;
		/*
		savedata->tail = new;
		savedata->tail->next = NULL;*/
	}
	
	
}

// Old definition that is FILO
/*
void insert_item(struct node *item, struct data *savedata, int taskornote, char *str)
{

	struct node *new = create_item();
	new->str = str;
	new->next = savedata->todo;
	savedata->todo = new;
	//avedata->todo = create_item(); // Create new item and since it's the head, assign to todo
	//initnode(&savedata->todo); // Init new head node
}*/

void print_data(struct data *savedata)
{
	struct node *curr = savedata->head;
	while (curr != NULL) {
		//printf("String is: %s\n", savedata->todo->str); BUG
		//curr = savedata->todo->next; BUG
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
	/*const static char msgs*[] = {"There's no tasks currently",
				"There's no notes currently",
				"There's no tasks or notes currently"};*/
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
	if (id != 0) {
		printf("[id %d] %s\n", id, curr->str);
		/*++(*itms);*/
	}
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

/*const char *print_task_for_today(const struct node *curr, size_t id)
{
	static const char *msg = "There's no tasks with today's date";
	if (id != 0 && curr->date != NULL)
		if (istoday(curr->date))
			printf("Task: %s\n", curr->str);
	return msg;
}*/

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

/*void print_note_windex(const struct data *savedata)
{
	struct node *curr = savedata->head;
	size_t items = 0;
	for (size_t i = 1; curr != NULL; ++i, curr = curr->next) {
		if (curr->ton == 2) {
			printf("[id %d] %s\n", i, curr->str);
			++items;
		}
	}
	if (items == 0) // Didn't loop once
		puts("There's no notes currently");
}*/

/*void print_task_windex(const struct data *savedata)
{
	struct node *curr = savedata->head;
	size_t items = 0;
	for (size_t i = 1; curr != NULL; ++i, curr = curr->next) {
		if (curr->ton == 1) {
			printf("[id %d] %s\n", i, curr->str);
			++items;
		}
	}
	if (items == 0) // Didn't loop once
		puts("There's no tasks currently");
}*/

/*void print_task_note_windex(const struct data *savedata)
{
	struct node *curr = savedata->head;
	size_t items = 0;
	for (size_t i = 1; curr != NULL; ++i, curr = curr->next) {
		printf("[id %d] %s\n", i, curr->str);
		++items;
	}
	if (items == 0) // Didn't loop once
		puts("There's no tasks or notes currently");
}*/

void delete_item(struct data *savedata, size_t id, int taskornote)
{
	/* Challenges found:
	 * What if the list only has one item and we want to delete it, how can we insert a new
	 * item so it can be the head and and tail, because fitem only does it one time.
	 *
	 * What if the item to be deleted is the last one (and no the first one), delete it,
	 * and make the previous item point to null.
	 *
	 */
	/* To see if an item with id given exists, we must iterate through the list, incrementing
	 * a var inside the loop, if this var is the same as the id and the current item is
	 * not NULL then the item exists and we can delete it.
	 *
	 * 
	 *
	 */
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
	// [head] -> [next] -> [tail]
	if ((unsigned)taskornote != curr->ton) { // Cast to get rid of warning
			puts("Type of task or note doesn't match");
			return;
	}
	if (prev != NULL) { // Item is no the first one
#ifdef DEBUG
		printf("taskornote is: %u\ncurr->ton is: %u", taskornote, curr->ton);
#endif
		/*
		 * Deleting tail and is not first item:
		 * If curr->next is NULL, curr is tail. Therefore we need to do prev->next = NULL and savedata->tail = NULL
		 *
		 * Deleting somewhere middle item:
		 * next = curr->next;
		 * delete curr
		 * make prev point next.
		 *
		 *
		 *
		 *
		 **/
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
		// Check how to deal with insert_item.
		curr = del_itm(curr, taskornote);
		savedata->head = NULL;
		savedata->tail = NULL;
		fitem = 1;
	} else {
		// Item to delete is the first one but theres more items in the list
		/* next = cur->next;
		 * delete curr
		 * savedata->head = next;
		 *
		 *
		 **/
		 next = curr->next;
		 curr = del_itm(curr, taskornote);
		 savedata->head = next;
	}
	// We still have to manage when there's only one item in the list!
	/*for (size_t i = 1;
		curr != NULL && i < id;
		++i, curr = curr->next) {
		bef = curr;
	}*/
	/* Bugs founded:
	 * -> If we have 1 item list or 2 item list (havem't checked further), e.g: two notes added
	 * and we try to delete a task in a range id, it doesn't prints "Type of task or note doesn't match".
	 * -> If we command to delete a given note it doesn't delete it.
	 * -> If we command to delete a given task it delete its, but we cannot add more notes/tasks.
	 */
	
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
		/*if (i != 1)
			*prev = *curr;*/
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

/* Visualization of linked list
 * List:
 * node3 -> node2 -> node1 -> NULL;
 * savedata->todo == node3
 *
 * savedata->todo == NULL
 * node1 is created and assigned node1->next with the value of savedata->todo == NULL
 * savedata is updated to point to node1: savedata->todo == node1
 * node2 iscreated and assigned node2->next with the value of savedata->todo == node1
 * savedata is updated to point to node2: savedata->todo == node2
 * 
 *
 **/
