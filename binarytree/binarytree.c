#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "binarytree.h"

/**********************************************************
 * Functions for the bintree
 ***********************************************************/

btnode* create_btnode(int key) {
    btnode* n = myMalloc(sizeof(btnode));
	n->key = key;
	n->left = NULL;
	n->right = NULL;
    return n;
}



void free_btnode(btnode* node) {
    free(node);
}



void bt_make_empty(btnode* node) {
	if (node == NULL) {
	} else if (node->left != NULL) {
		bt_make_empty(node->left);
		if (node->right != NULL) {
			bt_make_empty(node->right);
		}
		free_btnode(node);
	} else if (node->right != NULL) {
		bt_make_empty(node->right);
		if (node->left != NULL) {
			bt_make_empty(node->left);
		}
		free_btnode(node);
	} else {
		free_btnode(node);
	}
}



btnode* bt_insert_node(btnode* node, int key) {
	if (node == NULL) {
		node = create_btnode(key);
	} else if (node->key == key) {
		fprintf (stderr, "Error reading file\n" );
		exit(1);
	} else if (key < node->key && node->left != NULL) {
		btnode* tmp = bt_insert_node(node->left, key);
	} else if (key > node->key && node->right != NULL) {
		btnode* tmp = bt_insert_node(node->right, key);
	} else if (key < node->key && node->left == NULL) {
		node->left = create_btnode(key);
	} else if (key > node->key && node->right == NULL) {
		node->right = create_btnode(key);
	}
	return node;
}



btnode* bt_successor(btnode* node) {
	btnode* successor = node;
	if (node->right == NULL) {
		successor =  NULL;
	} else {
		successor = node->right;
		while (successor->left != NULL){
			successor = successor->left;
		}
	}
    return successor;
}



btnode* bt_predecessor(btnode* node) {
	btnode* predecessor = node;
    if (node->left == NULL) {
		predecessor =  NULL;
	} else {
		predecessor = node->left;
		while (predecessor->right != NULL){
			predecessor = predecessor->right;
		}
	}
    return predecessor;
}



btnode* bt_remove(btnode* node, int key) {
	if (node == NULL) {
		return NULL;
	} else if (node->key == key) {	//if found then return successor
		if (node->left == NULL && node->right == NULL) {
			free_btnode(node);
			return NULL;
		} else if (node->left != NULL && node->right != NULL) {	//two children
			btnode* successor = NULL;
			btnode* parent = NULL;
			if (node->right != NULL) {
				successor = node->right;
				parent = successor;
				while (successor->left != NULL){
					parent = successor;
					successor = successor->left;
				}
			}
			node->key = successor->key;
			parent->left = bt_remove(successor, successor->key);
			return node;
		} else {		//1 child
			btnode* successor = bt_successor(node);
			node->key = successor->key;
			node->left = NULL;
			node->right = NULL;
			free_btnode(successor);
			return node;
		}
	} else if (node->key < key && node->right != NULL) {
		node->right = bt_remove(node->right, key);
		return node;
	} else if (node->key > key && node->left != NULL) {
		node->left = bt_remove(node->left, key);
		return node;
	}
}



int bt_find(btnode* node, int key) {
	btnode* tmp = node;
    while (1) {
		if (tmp->key == key) {
			return 1;
		} else if (tmp->key < key && tmp->right != NULL) {
			tmp = tmp->right;
		} else if (tmp->key > key && tmp->left != NULL) {
			tmp = tmp->left;
		} else {
			return 0;
		}
	}
}



btnode* bt_min_node(btnode* node) {
	btnode* tmp = node;
	while (1) {
		if (tmp->left == NULL) {
			return tmp;
		} else if (tmp->left->key < tmp->key) {
			tmp = tmp->left;
		}
	}
}



btnode* bt_max_node(btnode* node) {
	btnode* tmp = node;
	while (1) {
		if (tmp->right == NULL) {
			return tmp;
		} else if (tmp->right->key > tmp->key) {
			tmp = tmp->right;
		}
	}
}



/**********************************************************
 * Functions for printing the bintree using various
 * traversal methods
 ***********************************************************/


void bt_print_preorder(btnode* node) { 
	if (node == NULL) {
		printf("Tree is NULL\n");
	} else {
		printf("%i\n", node->key);
		if(node->left != NULL) {
			bt_print_preorder(node->left);
			if (node->right != NULL) {
				bt_print_preorder(node->right);
			}
		} else if (node->right != NULL) {
			bt_print_preorder(node->right);
		}
	}
}



void bt_print_postorder(btnode* node) {
	if (node == NULL) {
		printf("Tree is NULL");
	} else if(node->left != NULL) {
		bt_print_postorder(node->left);
		if (node->right != NULL) {
			bt_print_postorder(node->right);
		}
		printf("%i\n", node->key);
	} else if (node->right != NULL) {
		bt_print_postorder(node->right);
		printf("%i\n", node->key);
	} else {
		printf("%i\n", node->key);
	}
}



void bt_print_inorder(btnode* node) {
    if (node == NULL) {
		printf("Tree is NULL");
	} else if (node->left != NULL) {
		bt_print_inorder(node->left);
		printf("%i\n", node->key);
		if (node->right != NULL) {
			bt_print_inorder(node->right);
		}
	} else if (node->left == NULL && node->right != NULL) {
		printf("%i\n", node->key);
		bt_print_inorder(node->right);
	} else if (node->left == NULL && node->right == NULL) {
		printf("%i\n", node->key);
	}
}



/**********************************************************
 * The following main function is for debugging this 
 * binary tree.  Supply the DEBUG flag to to compiler to 
 * compile a bintree containing this main function.
 ***********************************************************/
#ifdef DEBUG_BINARYTREE
int main(void) {
    printf("====================\n");
    printf("Debugging Binary Tree\n");
    printf("====================\n");

    btnode* bt_root = NULL;
    bt_root = bt_insert_node(bt_root, 7);
	printf("node 7 inserted\n");
    bt_root = bt_insert_node(bt_root, 5);
	printf("node 5 inserted\n");
    bt_root = bt_insert_node(bt_root, 10);
	printf("node 10 inserted\n");
    bt_root = bt_insert_node(bt_root, 2);
	printf("node 2 inserted\n");
    bt_root = bt_insert_node(bt_root, 6);
	printf("node 6 inserted\n");
    bt_root = bt_insert_node(bt_root, 3);
	printf("node 3 inserted\n");
    bt_root = bt_insert_node(bt_root, 8);
	printf("node 8 inserted\n");
    bt_root = bt_insert_node(bt_root, 9);
	printf("node 9 inserted\n\n");
    
    int min_val = bt_min_node(bt_root)->key;
    printf("Minimum value is %i\n", min_val);
    
    int max_val = bt_max_node(bt_root)->key;
    printf("Maximum value is %i\n", max_val);
    
    printf("Does 9 exist?  %i\n", bt_find(bt_root, 9));
    printf("Does 12 exist?  %i\n", bt_find(bt_root, 12));

    printf("Printing Pre-Order Traversal\n");
    bt_print_preorder(bt_root);
    printf("\n");
    
    printf("Printing Post-Order Traversal\n");
    bt_print_postorder(bt_root);
    printf("\n");
    
    printf("Printing In-Order Traversal\n");
    bt_print_inorder(bt_root);
    printf("\n");


    printf("Removing a leaf node (node 9)\n");
    bt_remove(bt_root, 9);
    printf("Printing Pre-Order Traversal\n");
    bt_print_preorder(bt_root);
    printf("\n");

	
    printf("Removing a node with 1 child (node 2)\n");
    bt_remove(bt_root, 2);
    printf("Printing Pre-Order Traversal\n");
    bt_print_preorder(bt_root);
    printf("\n");


    printf("Removing a node with 2 children (node 7)\n");
    bt_remove(bt_root, 7);
    printf("Printing Pre-Order Traversal\n");
    bt_print_preorder(bt_root);
    printf("\n");

	
    printf("Freeing bintree\n");
    bt_make_empty(bt_root);
    printf("\n");
    
	
    return 0;
}
#endif
