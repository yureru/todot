#ifndef LIST_H
#define LIST_H
struct node {
	unsigned ton; // 1 == task, 2 == note
	char *str;
	char *date;
	struct node *next;
};

/* Save/load header */
struct data {
	unsigned taskqt, noteqt;
	struct node *head;
	struct node *tail;
	//unsigned flines;
};
void initdata(struct node *item, struct data *savedata);
void initnode(struct node *item);

/* initinfo
 * Description: Used to initialize savedata structure.
 * Parameters: Poiner to savedata struct
 * Returns: Nothing.
 */
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
void insert_item(struct node *item, struct data *savedata, int taskornote, char *str);

/* print_data
 * Description: Prints the strings of nodes, used to debug currently.
 * Parameters: Pointer to savedata struct.
 * Returns: Nothing.
 */
void print_data(struct data *savedata);

/* delete_list
 * Description: Deallocates message strings, and nodes of the list.
 * Parameters: Pointer to savedata struct.
 * Returns: Nothing.
 **/
void delete_list(struct data *savedata);
// Refactor this 4, DRY
void print_task_for_today(const struct data *savedata);
/*void print_note_windex(const struct data *savedata);
void print_task_windex(const struct data *savedata);
void print_task_note_windex(const struct data *savedata);*/

// Refactoring
void apply(const struct data *savedata,
		const char *(*fn)(const struct node *curr, size_t id),
		unsigned comp);
const char *print_note_windex(const struct node *curr, size_t id);
const char *print_task_windex(const struct node *curr, size_t id);
const char *print_task_note_windex(const struct node *curr, size_t id);


void delete_item(struct data *savedata, size_t id, int taskornote);
struct node *del_itm(struct node *item, int taskornote);
int item_exists(size_t id, const struct node **curr, const struct node **prev);

#endif
