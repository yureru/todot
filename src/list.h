#ifndef LIST_H
#define LIST_H
struct node {
	unsigned ton; // 1 == task, 2 == note
	char *str;
	char *date;
	struct node *next;
};

struct data {
	unsigned taskqt, noteqt;
	struct node *head;
	struct node *tail;
};

/* initdata
 * Description: Calls initnode.
 * Parameters: Pointer to struct data.
 * Returns: Nothing.
 **/
void initdata(struct data *savedata);

/* initnode
 * Description: Initializes node to cero (pointers to null, integers to 0).
 * Parameters: Pointer to node.
 * Returns: Nothing.
 **/
void initnode(struct node *item);

/* initinfo
 * Description: Used to initialize savedata structure.
 * Parameters: Poiner to savedata struct
 * Returns: Nothing.
 **/
void initinfo(struct data *savedata);

/* create_item
 * Description: Allocates a node, exit failure if malloc can't allocate mem.
 * Parameters: Nothing.
 * Returns: Nothing.
 **/
struct node *create_item(void);

/* insert_item
 * Description: Calls create_item and inserts this item into the list at the end (tail).
 * Parameters: Pointer to item (unused), savedata struct, selector between task or note,
 *             pointer to malloc allocated string (message), and date string.
 * Returns: Nothing.
 **/
void insert_item(struct data *savedata, int taskornote, char *str);

/* print_data
 * Description: Prints the strings of nodes, used to debug currently.
 * Parameters: Pointer to savedata struct.
 * Returns: Nothing.
 **/
void print_data(struct data *savedata);

/* delete_list
 * Description: Deallocates message strings, and nodes of the list.
 * Parameters: Pointer to savedata struct.
 * Returns: Nothing.
 **/
void delete_list(struct data *savedata);

/* apply
 * Description: Traverse the list, callig the function pointer. If there's no
 *              items in the list, prints the string returned from the
 *              pointer to function.
 * Parameters: Pointer to struct data, Pointer to function that returns a const string,
 *             and has two parameters: pointer to current node, and id of item.
 * Returns: Nothing.
 **/
void apply(const struct data *savedata,
		const char *(*fn)(const struct node *curr, size_t id),
		unsigned comp);

/* print_note_windex
 * Description: Prints the current note string and the id.
 * Parameters:  Pointer to current node and the id of item.
 * Returns: Pointer to string.
 **/
const char *print_note_windex(const struct node *curr, size_t id);

/* print_task_windex
 * Description: Prints the current task string and the id.
 * Parameters:  Pointer to current node and the id of item.
 * Returns: Pointer to string.
 **/
const char *print_task_windex(const struct node *curr, size_t id);

/* print_task_note_windex
 * Description: Prints all the notes and tasks with index.
 * Parameters:  Pointer to current node and the id of item.
 * Returns: Pointer to string.
 **/
const char *print_task_note_windex(const struct node *curr, size_t id);

/* print_task_for_today
 * Description: Traverses the list, if there's a task with today's date, prints it.
 *              Uses istoday() to determine that.
 * Parameters: Pointer to struct data.
 * Returns: Nothing.
 **/
void print_task_for_today(const struct data *savedata);

/* delete_item
 * Description: Deletes the item of the list at given id, and checks if that item
 *              matchs with taskornote == curr->ton. If the item doens't exists or
 *              it doesn't match does nothing. Sets global fitem if the item deleted
 *              was the only one in the list.
 * Parameters: pointer to struct data, id of item, taskornote.
 * Returns: Nothing.
 **/
void delete_item(struct data *savedata, size_t id, int taskornote);

/* del_itm
 * Description: Free() the string of the node and the date if it's task and has date.
 * Parameters: Pointer to the node, taskornote.
 * Returns: Pointer NULL.
 **/
struct node *del_itm(struct node *item, int taskornote);

/* item_exists
 * Description: Checks if given id item exists, and gets the previous node at this
 *              item with **prev.
 * Parameters: id to be searched, double pointer to node, double pointer to prev node.
 * Returns: True if item exists, false otherwise.
 **/
int item_exists(size_t id, const struct node **curr, const struct node **prev);

/* apply_f
 * Description: Saves the data on the file, properly formatted.
 * Parameters: Pointer to struct data, opened file (with "w"), and double pointer to
 *             char tn which is typeNote global.
 * Returns: Nothing.
 **/
void apply_f(const struct data *savedata, FILE *db, const char **tn);

#endif
