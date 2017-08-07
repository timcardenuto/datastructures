#ifndef _bintree_h
#define _bintree_h


/* struct defining bintree node */
typedef struct btnode_struct {
    int key;                      // node stores a single integer
    struct btnode_struct* left;   // pointer to the left child of this node
    struct btnode_struct* right;  // pointer to the right child of this node
} btnode;


/**********************************************************
 * function prototypes
 ***********************************************************/


/**
 * Creates a new tree node with the specified key
 * @param key - the integer to store in the bintree node
 * @return a pointer to a newly created bintree node
 **/
btnode* create_btnode(int key);

/**
 * Frees the memory for the specified btnode
 * @param node - a pointer to the node to be freed
 **/
void free_btnode(btnode* node);

/**
 * Removes all the nodes from the subtree rooted at node
 * @param node - the root of the subtree to make empty
 **/
void bt_make_empty(btnode* node);

/**
 * Creates a new node for the input key and adds it to the binary
 * search tree in the appropriate location.
 * DO NOT allow duplicate keys.  If a user tries to insert a 
 * duplicate key, print an error to stderr and terminate the 
 * program with a call to 'exit'.
 * @param node - the root of the subtree in which to insert the key
 * @param key - the key to insert into the tree
 * @return a pointer to the new subtree root
 **/
btnode* bt_insert_node(btnode* node, int key);

/**
 * Find the successor of a given node (if it exists).
 * @param node - the node for which to find the successor
 * @return the successor node if it exists, NULL otherwise
 **/
btnode* bt_successor(btnode* node);

/**
 * Find the predecessor of a given node (if it exists).
 * @param node - the node for which to find the predecessor
 * @return the predecessor node if it exists, NULL otherwise
 **/
btnode* bt_predecessor(btnode* node);

/**
 * Removes the node with the specified key from the binary tree 
 * (if it exists)
 * @param node - the root of the subtree from which the key is to be deleted
 * @param key - the key to delete (if it exists)
 * @return a pointer to the new subtree root
 **/
btnode* bt_remove(btnode* node, int key);

/**
 * Searches for the specified key in the subtree rooted at node
 * @param node - the root of the subtree to search for the key
 * @param key - the key to search for in the tree
 * @return 1 if the node is found, 0 otherwise
 **/
int bt_find(btnode* node, int key);

/**
 * Finds the minimum key value stored in the specified tree
 * @param node - the root of the subtree in which to search for the min value
 * @return the node containing the minimum integer key stored in the tree
 **/
btnode*  bt_min_node(btnode* node);

/**
 * Finds the maximum key value stored in the specified tree
 * @param node - the root of the subtree in which to search for the max value
 * @return the node containing the maximum integer key stored in the tree
 **/
btnode* bt_max_node(btnode* node);

/**
 * Prints the key values stored in the specified bintree as they
 * are visited in a preorder traversal
 * @param bt - a pointer to the bintree to traverse and print
 **/
void bt_print_preorder(btnode* node);

/**
 * Prints the key values stored in the specified bintree as they
 * are visited in a postorder traversal
 * @param bt - a pointer to the bintree to traverse and print
 **/
void bt_print_postorder(btnode* node);

/**
 * Prints the key values stored in the specified bintree as they
 * are visited in an inorder traversal
 * @param bt - a pointer to the bintree to traverse and print
 **/
void bt_print_inorder(btnode* node);


#endif
