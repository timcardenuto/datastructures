#ifndef _aatree_h
#define _aatree_h


/* struct defining AA tree node */
typedef struct AAnode_struct {
    int key;                      // node stores a single integer
    int level;                    // the level of a node in the AA tree
    struct AAnode_struct* left;   // pointer to the left child of this node
    struct AAnode_struct* right;  // pointer to the right child of this node
} AAnode;


/**********************************************************
 * function prototypes
 ***********************************************************/


/**
 * Creates a new tree node with the specified key
 * @param key - the integer to store in the AA tree node
 * @return a pointer to a newly created AA tree node
 **/
AAnode* create_AAnode(int key);

/**
 * Frees the memory for the specified AAnode
 * @param node - a pointer to the node to be freed
 **/
void free_AAnode(AAnode* node);

/**
 * Removes all the nodes from the subtree rooted at node
 * @param node - the root of the subtree to make empty
 **/
void AAmake_empty(AAnode* node);

/**
 * Creates a new node for the input key and adds it to the AA tree 
 * in the appropriate location.
 * DO NOT allow duplicate keys.  If a user tries to insert a 
 * duplicate key, print an error to stderr and terminate the 
 * program with a call to 'exit'.
 * @param node - the root of the subtree in which to insert the key
 * @param key - the key to insert into the tree
 * @return a pointer to the new subtree root
 **/
AAnode* AAinsert_node(AAnode* node, int key);

/**
 * Performs a skew operation on the input node
 * @param node - the node on which to perform the skew operation
 * @return the new root of the subtree after the skew operation is performed
 **/
AAnode* AAskew(AAnode* node);

/**
 * Performs a split operation on the input node
 * @param node - the node on which to perform the split operation
 * @return the new root of the subtree after the split operation is performed
 **/
AAnode* AAsplit(AAnode* node);

/**
 * Find the successor of a given node (if it exists).
 * @param node - the node for which to find the successor
 * @return the successor node if it exists, NULL otherwise
 **/
AAnode* AAsuccessor(AAnode* node);

/**
 * Find the predecessor of a given node (if it exists).
 * @param node - the node for which to find the predecessor
 * @return the predecessor node if it exists, NULL otherwise
 **/
AAnode* AApredecessor(AAnode* node);

/**
 * Removes the node with the specified key from the AA tree
 * (if it exists)
 * @param node - the root of the subtree from which the key is to be deleted
 * @param key - the key to delete (if it exists)
 * @return a pointer to the new subtree root
 **/
AAnode* AAremove(AAnode* node, int key);

/**
 * Searches for the specified key in the subtree rooted at node
 * @param node - the root of the subtree to search for the key
 * @param key - the key to search for in the tree
 * @return 1 if the node is found, 0 otherwise
 **/
int AAfind(AAnode* node, int key);

/**
 * Finds the minimum key value stored in the specified tree
 * @param node - the root of the subtree in which to search for the min value
 * @return the node containing the minimum integer key stored in the tree
 **/
AAnode*  AAmin_node(AAnode* node);

/**
 * Finds the maximum key value stored in the specified tree
 * @param node - the root of the subtree in which to search for the max value
 * @return the node containing the maximum integer key stored in the tree
 **/
AAnode* AAmax_node(AAnode* node);

/**
 * Prints the key values stored in the specified AA tree as they
 * are visited in a preorder traversal
 * @param bt - a pointer to the AA tree to traverse and print
 **/
void AAprint_preorder(AAnode* node);

/**
 * Prints the key values stored in the specified AA tree as they
 * are visited in a postorder traversal
 * @param bt - a pointer to the AA tree to traverse and print
 **/
void AAprint_postorder(AAnode* node);

/**
 * Prints the key values stored in the specified AA tree as they
 * are visited in an inorder traversal
 * @param bt - a pointer to the AA tree to traverse and print
 **/
void AAprint_inorder(AAnode* node);


#endif
