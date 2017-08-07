#ifndef _skiplist_h
#define _skiplist_h


/* struct defining a skiplist node */
typedef struct skiplist_node_struct {
    int key;                            // node stores a single integer
    struct skiplist_node_struct** next; // pointer to an array of next pointers
	
	/////// Take this out for non-debug ///////
	int levels;
	//////////////////////////////////////////

} slnode;


typedef struct skiplist_struct {
    int size;        // number of nodes currently in the skiplist (not counting
    float prob;      // probability with which to add new levels (0.5 for coin flip)
    int max_levels;  // maximum number of levels for this skiplist, Pugh suggests 16 for lists up to 65,536 nodes
    int cur_levels;  // current number of levels in this skiplist, cur_levels <= max_levels
    slnode* head;    // head of the skiplist; it contains no data; should be maximum height
    slnode* tail;    // tail node should contain the maximum possible integer (INT_MAX), need only be 1 level
} skiplist;


/**********************************************************
 * function prototypes
 ***********************************************************/

/**
 * Creates and initializes a skiplist. 
 * @param max_levels - the maximum number of levels to allow for this skiplist
 * @param prob - probability with which to add new levels (0.5 for coin flip)
 * @return a pointer to the newly created skiplist
 **/
skiplist* create_skiplist(int max_levels, float prob);

/**
 * Frees ALL the memory for the specified skiplist
 * @param slst - a pointer to the skiplist to be freed
 **/
void free_skiplist(skiplist* slst);

/**
 * Creates and initializes a skiplist node
 * @param key - the key to store in this skiplist node
 * @param num_levels - the number of levels for this node
 * @return a pointer to the newly created skiplist node
 **/
slnode* create_slnode(int key, int num_levels);

/**
 * Frees ALL the memory for the specified skiplist node
 * @param node - a pointer to the skiplist node to be freed
 **/
void free_slnode(slnode* node);

/**
 * Checks to see if the skiplist is empty
 * @param slst - a pointer to the skiplist to check
 * @return 1 if empty, 0 otherwise
 **/ 
int is_list_empty(skiplist* slst);

/**
 * Removes all existing nodes from the skiplist
 * @param slst - a pointer to the skiplist to clear
 **/
void clear_list(skiplist* slst);

/**
 * Ramdomly generates the level of a new skip list node.
 * Levels begin at 0 (not at 1 like in Pugh's paper).
 * @return an integer value between 0 and max_levels-1
 **/
int generate_random_level(int max_levels, float prob);

/**
 * Searches a skiplist for a node containing the specified key.
 * @param slst - a pointer to the skiplist to search
 * @param key - the key value for which to search in the skiplist
 * @return the skiplist node that contains the specified key, NULL
 *         if the key is not found int the skiplist
 **/
slnode* find(skiplist* slst, int key);

/**
 * Creates a new skiplist node with the specified key, and inserts it
 * into the specified skiplist.  
 **************************************************************
 * DO NOT allow duplicate keys.  If a user tries to insert a 
 * duplicate key, print an error to stderr and terminate the 
 **************************************************************
 * program with a call to 'exit'.
 * @param slst - a pointer to the skiplist into which the new skiplist 
 *               node should be inserted
 * @param key - the key value to store in the new skiplist node
 **/
void insert(skiplist* slst, int key);

/**
 * Searches for and deletes the skiplist node with the specified
 * key from the specified skiplist.  If the node is successfully
 * deleted, then this function returns TRUE (i.e. 1).  If a node
 * with the specified key does not exist in the skiplist, then 
 * this function returns FALSE (i.e. 0) to indicate that the node
 * was not deleted.
 * @param slst - a pointer to the skiplist from which to delete the
 *               skiplist node with the specified key
 * @param key - the key value to search for and delete
 * @return TRUE if the a skiplist node with the key is found and 
 *         deleted.  FALSE if no skiplist node is found with the 
 *         specified key.
 **/
int delete(skiplist* slst, int key);

/**
 * Prints the contents of the skiplist, in order, from
 * head to tail
 * @param slst - a pointer to the skiplist to print
 **/
void print_list(skiplist* slst);


#endif
