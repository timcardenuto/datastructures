#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "aatree.h"

/**********************************************************
 * Functions for the bintree
 ***********************************************************/

AAnode* create_AAnode(int key) {
    AAnode* n = myMalloc(sizeof(AAnode));
	n->key = key;
	n->level = 1;
	n->left = NULL;
	n->right = NULL;
    return n;
}



void free_AAnode(AAnode* node) {
	free(node);
}



void AAmake_empty(AAnode* node) {
	if (node == NULL) {
	} else if (node->left != NULL) {
		AAmake_empty(node->left);
		if (node->right != NULL) {
			AAmake_empty(node->right);
		}
		free_AAnode(node);
	} else if (node->right != NULL) {
		AAmake_empty(node->right);
		if (node->left != NULL) {
			AAmake_empty(node->left);
		}
		free_AAnode(node);
	} else {
		free_AAnode(node);
	}
}



AAnode* AAinsert_node(AAnode* node, int key) {
	AAnode* tmp = node;
	if (node == NULL) {
		node = create_AAnode(key);
	} else {
		if (node->key == key) {
			fprintf (stderr, "Error: identical key\n" );
			exit(1);
		} else if (node->key > key) {
			node->left = AAinsert_node(node->left, key);
		} else if (node->key < key) {
			node->right = AAinsert_node(node->right, key);	
		}
		
		if (tmp->left != NULL) {
			if (tmp->level == tmp->left->level) {
				node = AAskew(tmp);
			}
			if (node->right->right != NULL) {
				if (node->level == node->right->right->level) {
					node = AAsplit(node);
				}
			}
		} else if ((tmp->right != NULL) && (tmp->right->right != NULL)) {
			
			if ((tmp->level == tmp->right->level) && (tmp->level == tmp->right->right->level)) {
				node = AAsplit(tmp);
			}
		}
	}
	return node;
}



AAnode* AAskew(AAnode* node) {
	AAnode* tmp = node->left;
	if (node->left->right == NULL) {
		node->left = NULL;
	} else {
		node->left = node->left->right;	
	}
	tmp->right = node;
	return tmp;
}



AAnode* AAsplit(AAnode* node) {
    AAnode* tmp = node->right;
	if (node->right->left != NULL) {
		node->right = node->right->left;
	} else {
		node->right = NULL;
	}
	tmp->left = node;
	tmp->level = tmp->level + 1;
	return tmp;
}



AAnode* AAsuccessor(AAnode* node) {
	AAnode* successor = node;
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



AAnode* AApredecessor(AAnode* node) {
	AAnode* predecessor = node;
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



AAnode* AAremove(AAnode* node, int key) {
    if (node == NULL) {
	} else if (node->key == key) {
		if (node->left == NULL && node->right == NULL) {
			free_AAnode(node);
			node = NULL;
		} else if (node->left == NULL) {
            AAnode* right_child = node->right;
            free_AAnode(node);
            node = right_child;
        } else if (node->right == NULL) {
            AAnode* left_child = node->left;
            free_AAnode(node);
            node = left_child;
        } else {	
            AAnode* succ = AAsuccessor(node);
            node->key = succ->key;
            node->right = AAremove(node->right, succ->key);
		}
	} else if (node->key < key) {
		node->right = AAremove(node->right, key);
	} else if (node->key > key) {
		node->left = AAremove(node->left, key);
	}
	
	if (node != NULL) {
		if (node->left != NULL) {
			if (node->level > node->left->level + 1) {
				node->level = node->level - 1;
				node->right->level = node->level;
				node->right = AAskew(node->right);
				node->right->right = AAskew(node->right->right);
				node = AAsplit(node);
				node->right = AAsplit(node->right);
			} else if (node->right == NULL) {
				node->level = node->level - 1;
				node = AAskew(node);
				node->right = AAskew(node->right);
				node = AAsplit(node);
			} else if (node->level > node->right->level + 1) {
				node->level = node->level - 1;
				node = AAskew(node);
			}
		} else if (node->left == NULL && node->right != NULL) {
			node->level = node->level - 1;
		}
	}
	return node;
}



int AAfind(AAnode* node, int key) {
	AAnode* tmp = node;
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



AAnode* AAmin_node(AAnode* node) {
	AAnode* tmp = node;
	while (1) {
		if (tmp->left == NULL) {
			return tmp;
		} else if (tmp->left->key < tmp->key) {
			tmp = tmp->left;
		}
	}
}



AAnode* AAmax_node(AAnode* node) {
	AAnode* tmp = node;
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

void AAprint_preorder(AAnode* node) {
	if (node == NULL) {
		printf("Tree is NULL\n");
	} else {
		printf("%i  %i\n", node->key, node->level);
		if(node->left != NULL) {
			AAprint_preorder(node->left);
			if (node->right != NULL) {
				AAprint_preorder(node->right);
			}
		} else if (node->right != NULL) {
			AAprint_preorder(node->right);
		}
	}
}



void AAprint_postorder(AAnode* node) {
	if (node == NULL) {
		printf("Tree is NULL");
	} else if(node->left != NULL) {
		AAprint_postorder(node->left);
		if (node->right != NULL) {
			AAprint_postorder(node->right);
		}
		printf("%i\n", node->key);
	} else if (node->right != NULL) {
		AAprint_postorder(node->right);
		printf("%i\n", node->key);
	} else {
		printf("%i\n", node->key);
	}
}



void AAprint_inorder(AAnode* node) {
	if (node == NULL) {
		printf("Tree is NULL");
	} else if (node->left != NULL) {
		AAprint_inorder(node->left);
		printf("%i\n", node->key);
		if (node->right != NULL) {
			AAprint_inorder(node->right);
		}
	} else if (node->left == NULL && node->right != NULL) {
		printf("%i\n", node->key);
		AAprint_inorder(node->right);
	} else if (node->left == NULL && node->right == NULL) {
		printf("%i\n", node->key);
	}
}



/**********************************************************
 * The following main function is for debugging this 
 * binary tree.  Supply the DEBUG flag to to compiler to 
 * compile a bintree containing this main function.
 ***********************************************************/
#ifdef DEBUG_AATREE
int main(void) {
    printf("====================\n");
    printf("Debugging Binary Tree\n");
    printf("====================\n");

    AAnode* AAroot = NULL;
    AAroot = AAinsert_node(AAroot, 4);
    AAroot = AAinsert_node(AAroot, 10);
    AAroot = AAinsert_node(AAroot, 2);
    AAroot = AAinsert_node(AAroot, 6);
    AAroot = AAinsert_node(AAroot, 12);
    AAroot = AAinsert_node(AAroot, 3);
    AAroot = AAinsert_node(AAroot, 1);
    AAroot = AAinsert_node(AAroot, 8);
    AAroot = AAinsert_node(AAroot, 13);
    AAroot = AAinsert_node(AAroot, 11);
    AAroot = AAinsert_node(AAroot, 5);
    AAroot = AAinsert_node(AAroot, 9);
    AAroot = AAinsert_node(AAroot, 7);
	
    int min_val = AAmin_node(AAroot)->key;
    printf("Minimum value is %i\n", min_val);

    int max_val = AAmax_node(AAroot)->key;
    printf("Maximum value is %i\n", max_val);

    printf("Does 7 exist?  %i\n", AAfind(AAroot, 7));
    printf("Does 12 exist?  %i\n", AAfind(AAroot, 12));
    printf("Does 55 exist?  %i\n", AAfind(AAroot, 55));
	
    printf("Printing Pre-Order Traversal\n");
    AAprint_preorder(AAroot);
    printf("\n");
    
    printf("Removing a leaf node (node 1)\n");
    AAroot = AAremove(AAroot, 1);
    printf("Printing Pre-Order Traversal\n");
    AAprint_preorder(AAroot);
    printf("\n");

    printf("Removing a leaf node (node 5)\n");
    AAroot = AAremove(AAroot, 5);
    printf("Printing Pre-Order Traversal\n");
    AAprint_preorder(AAroot);
    printf("\n");
    
    printf("Removing a node with two children (node 10)\n");
    AAroot = AAremove(AAroot, 10);
    printf("Printing Pre-Order Traversal\n");
    AAprint_preorder(AAroot);
    printf("\n");

    printf("Printing Post-Order Traversal\n");
    AAprint_postorder(AAroot);
    printf("\n");
    
    printf("Printing In-Order Traversal\n");
    AAprint_inorder(AAroot);
    printf("\n");

    printf("Freeing bintree\n");
    AAmake_empty(AAroot);
    printf("\n");
	AAprint_preorder(AAroot);
    return 0;
}
#endif
