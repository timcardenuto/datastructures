#ifndef _linkedlist_h
#define _linkedlist_h


/* struct defining doubly-linked list node */
typedef struct llnode_struct {
    void* data;                  // pointer to data in the node
    struct llnode_struct* prev;  // pointer to the previous node in the list
    struct llnode_struct* next;  // pointer to the next node in the list
} llnode;


/* struct defining the doubly-linked list */
typedef struct linkedlist_struct {
    int size;       // the size of the list, initialize to 0
    llnode* head;   // pointer to head of list
    llnode* tail;   // pointer to tail of list
    llnode* cur;    // pointer to current iterator item
} linkedlist;



/**********************************************************
* function prototypes
***********************************************************/

/**
 * Creates and initializes a linked list.
 * @return a pointer to a newly created linkedlist struct
 **/
linkedlist* create_linkedlist();

/**
 * Creates a new list node.
 * @param data - a pointer to the data to store in the list node
 * @return a pointer to a newly created linkedlist node
 **/
llnode* create_llnode(void* data);

/**
 * Frees the memory for the specified linkedlist node
 * @param node - a pointer to the node to be freed
 **/
void free_llnode(llnode* node);

/**
 * Frees the memory for a complete linked list
 * @param lst - a pointer to the linkedlist to be freed
 **/
void free_linkedlist(linkedlist* lst);

/**
 * Checks to see if the linkedlist is empty
 * @param lst - a pointer to the linkedlist to check
 * @return TRUE if empty, FALSE otherwise
 **/ 
int is_list_empty(linkedlist* lst);

/**
 * Removes all existing nodes from the linkedlist and
 * resets the state of the list
 * @param lst - a pointer to the linkedlist to clear
 **/
void clear_list(linkedlist* lst);

/**
 * Creates a new node for the input data and appends it to the list
 * @param lst - a pointer to the linkedlist to append the data
 * @param data - the data to append to the linkedlist
 **/
void append_list(linkedlist* lst, void* data);

/**
 * Creates a new node for the input data and prepends it to the list
 * @param lst - a pointer to the linkedlist to prepend the data
 * @param data - the data to prepend to the linkedlist
 **/
void prepend_list(linkedlist* lst, void* data);

/**
 * Removes the node from the head of the list and returns the data
 * contained within that node.
 * @param lst - a pointer to the linkedlist from which to remove the head
 * @return the data contained with the head node of the list, NULL if the
 *  list is empty.
 **/
void* remove_list_head(linkedlist* lst);

/**
 * Removes the node from the tail of the list and returns the data
 * contained within that node.
 * @param lst - a pointer to the linkedlist from which to remove the tail
 * @return the data contained with the tail node of the list, NULL if the
 *  list is empty.
 **/
void* remove_list_tail(linkedlist* lst);



/**********************************************************
* function prototypes for iterator portion of linkedlist
***********************************************************/

/**
 * Get the data item from the list node at the head of the list.  This function
 * should also be used to set the current iterator item to the head of the list.
 * @param lst - a pointer to the linkedlist from which to get the data
 * @return the data item at the head of the specified linkedlist, NULL if the 
 *  list is empty.
 **/
void* get_list_head(linkedlist* lst);

/**
 * Get the data item from the list node at the tail of the list.  This function
 * should also be used to set the current iterator item to the tail of the list.
 * @param lst - a pointer to the linkedlist from which to get the data
 * @return the data item at the tail of the specified linkedlist, NULL if the 
 *  list is empty.
 **/
void* get_list_tail(linkedlist* lst);

/**
 * Get the next data item in the list. First, advances the iterator variable
 * (cur) and then returns the data item from the new location in the list. 
 * NOTE: This function should only be used if the iterator variable is first 
 * initialized by calling get_list_head or get_list_tail.
 * @param lst - a pointer to the linkedlist from which to get the data
 * @return the data item at the next location of the specified linkedlist, NULL
 *  if the list is empty.
 **/
void* get_list_next(linkedlist* lst);

/**
 * Get the previous data item in the list. First, moves the iterator variable 
 * (cur) back one position and then returns the data item from the new location 
 * in the list. 
 * NOTE: This function should only be used if the iterator variable is first 
 * initialized by calling get_list_tail or get_list_head.
 * @param lst - a pointer to the linkedlist from which to get the data
 * @return the data item at the previous location of the specified linkedlist, NULL
 *  if the list is empty.
 **/
void* get_list_prev(linkedlist* lst);

/**
 * Deletes the item from the linked list that is currently selected with the
 * linked list iterator.
 * NOTE: This function should only be used if the iterator variable is first 
 * initialized by calling get_list_tail or get_list_head.
 * ANOTHER NOTE: This function currently sets the iterator variable back to NULL
 * meaning that it must be initialized again before using any of the iterator
 * traversal functions.
 * @param lst - a pointer to the linkedlist from which to delete the data
 * @return pointer to the data that was just deleted from the list
 **/
void* delete_list_current(linkedlist* lst);

/**
 * Creates a new node for the input data and inserts it into the list before 
 * the location of the current iterator variable (cur).
 * NOTE: This function should only be used if the iterator variable is first 
 * initialized 
 * by calling get_list_head or get_list_tail.
 * @param lst - a pointer to the linkedlist to insert the data
 * @param data - the data to insert into the linkedlist
 **/
void insert_node_before_cur(linkedlist* lst, void* data);

/**
 * Creates a new node for the input data and inserts it into the list after 
 * the location of the current iterator variable (cur).
 * NOTE: This function should only be used if the iterator variable is first 
 * initialized by calling get_list_head or get_list_tail.
 * @param lst - a pointer to the linkedlist to insert the data
 * @param data - the data to insert into the linkedlist
 **/
void insert_node_after_cur(linkedlist* lst, void* data);

/**
 * Print the data in each of the nodes of the linkedlist. 
 * IMPORTANT: This function is used for debugging and can assume
 * that all data stored in the linkedlist nodes are integers.
 * @param lst - a pointer to the linkedlist to print
 **/
void print_list(linkedlist* lst);


#endif
