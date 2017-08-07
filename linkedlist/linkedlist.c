#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "linkedlist.h"


/**********************************************************
 * Functions for the linkedlist
 ***********************************************************/
linkedlist* create_linkedlist() {
    linkedlist* l = myMalloc(sizeof(linkedlist));
    l->size = 0;
    l->head = NULL;
    l->tail = NULL;
    l->cur  = NULL;
    return l;
}



llnode* create_llnode(void* data) {
    llnode* n = myMalloc(sizeof(llnode));
	n->data = data;
	n->prev = NULL;
	n->next = NULL;
    return n;
}



void free_llnode(llnode* node) {
    free(node);   
}



void free_linkedlist(linkedlist* lst) {
    if (lst->size > 0) {
		int i;
		int s = lst->size;
		for(i = 1; i < s; i++) {
			lst->tail = lst->tail->prev;	//move tail back
			free_llnode(lst->tail->next);	//free the unneeded node
			lst->size = lst->size - 1;
		}
		free_llnode(lst->head);
		lst->size = lst->size - 1;
	}
	free(lst);
}



int is_list_empty(linkedlist* lst) {
    if(lst->size == 0) {
		return 1;
	} else {
		return 0;
	}
}



void clear_list(linkedlist* lst) {
    int i;
	int s = lst->size;
    for(i = 1; i < s; i++) {
		lst->tail = lst->tail->prev;	//move tail back
		free_llnode(lst->tail->next);	//free the unneeded node
		lst->size = lst->size - 1;
	}
	free_llnode(lst->head);
	lst->size = lst->size - 1;
}



void append_list(linkedlist* lst, void* data) {
    llnode* new_node = create_llnode(data);
	if (lst->size == 0) {
		lst->tail = new_node;
		lst->head = new_node;
	} else {
		new_node->prev = lst->tail;
		lst->tail->next = new_node;
		lst->tail = new_node;
	}
	lst->size = lst->size + 1;
}



void prepend_list(linkedlist* lst, void* data) {
    llnode* new_node = create_llnode(data);
	if (lst->size == 0) {
		lst->tail = new_node;
		lst->head = new_node;
	} else {
		new_node->next = lst->head;
		lst->head->prev = new_node;
		lst->head = new_node;
	}
	lst->size = lst->size + 1;
}



void* remove_list_head(linkedlist* lst) {
    if (lst->size == 0) {
		return NULL;
	} else {
		llnode* temp = lst->head;
		lst->head = lst->head->next;	//move head pointer
		lst->head->prev = NULL;
		free(lst->head->prev);		//free location head was pointing to
		lst->size = lst->size - 1;	//decrease size
		return temp->data;
	}
}



void* remove_list_tail(linkedlist* lst) {
    if (lst->size == 0) {
		return NULL;
	} else {
		llnode* temp = lst->tail;
		lst->tail = lst->tail->prev;	//move tail pointer
		free(lst->tail->next);		//free location tail was pointing to
		lst->size = lst->size - 1;	//decrease size
		return temp->data;
	}
}



/**********************************************************
 * Functions for the iterator portion of the linkedlist
 ***********************************************************/

void* get_list_head(linkedlist* lst) {
    if (lst->size == 0) {
		return NULL;
	} else {
		lst->cur = lst->head;
		return lst->cur->data;
	}
}



void* get_list_tail(linkedlist* lst) {
    if (lst->size == 0) {
		return NULL;
	} else {
		lst->cur = lst->tail;
		return lst->cur->data;
	}
}



void* get_list_next(linkedlist* lst) {
   if (lst->size == 0 || lst->cur == NULL || lst->cur == lst->tail) {
		return NULL;
	} else {
		lst->cur = lst->cur->next;
		return lst->cur->data;
	}
}



void* get_list_prev(linkedlist* lst) {
   if (lst->size == 0 || lst->cur == NULL || lst->cur == lst->head) {
		return NULL;
	} else {
		lst->cur = lst->cur->prev;
		return lst->cur->data;
	}
}



void insert_node_before_cur(linkedlist* lst, void* data) {
	llnode* new_node = create_llnode(data);
	if (lst->size == 0 || lst->cur == NULL) {
		lst->head = new_node;
		lst->tail = new_node;
	} else {
		new_node->prev = lst->cur->prev;
		new_node->next = lst->cur;
		new_node->prev->next = new_node;
		lst->cur->prev = new_node;
		if (lst->cur == lst->head) {	//If cur and head are at same node...
			lst->head = new_node;		//...update head
		}
		lst->size = lst->size + 1;
	}
}



void insert_node_after_cur(linkedlist* lst, void* data) {
	llnode* new_node = create_llnode(data);
	if (lst->size == 0 || lst->cur == NULL) {
		lst->head = new_node;
		lst->tail = new_node;	
	} else {
		new_node->next = lst->cur->next;
		new_node->prev = lst->cur;
		new_node->next->prev = new_node;
		lst->cur->next = new_node;
		if (lst->cur == lst->tail) {	//If cur and tail are at same node...
			lst->tail = new_node;		//...update tail
		}
		lst->size = lst->size + 1;
	}
}



/**
 * IMPORTANT: This function is used for debugging and can assume
 * that all data stored in the linkedlist nodes are integers.
 **/
void print_list(linkedlist* lst) {
    llnode* tmp = lst->cur; // save the current state of the iterator
    
    printf("List: ");
    void* data = get_list_head(lst);
    while (data != NULL) {
        printf("%i -> ", *(int*)data);
        data = get_list_next(lst);
    }
    printf("NULL \n\n");
    lst->cur = tmp;  // restore the state of the iterator
}



/**********************************************************
 * The following main function is for debugging this 
 * linkedlist.  Supply the DEBUG flag to to compiler to 
 * compile a linkedlist containing this main function.
 ***********************************************************/
#ifdef DEBUG_LINKEDLIST
int main(void) {
    printf("====================\n");
    printf("Debugging linkedlist\n");
    printf("====================\n");
    
    linkedlist* l = create_linkedlist(); // create the linkedlist

	int i1 = 1;  // create some integers to store in the list
    int i2 = 2;
    int i3 = 3;
    int i4 = 4;
    int i5 = 5;
    int i6 = 6;
    void* i1p = (void*)&i1; // create pointers to those integers
    void* i2p = (void*)&i2;
    void* i3p = (void*)&i3;
    void* i4p = (void*)&i4;
    void* i5p = (void*)&i5;
    void* i6p = (void*)&i6;    
    
    print_list(l);           // list should be empty
    
    printf("Appending %i\n", *(int*)i1p);
    append_list(l, i1p);     // append item to list
    print_list(l);
    
    printf("Appending %i\n", *(int*)i2p);
    append_list(l, i2p);     // append item to list
    print_list(l);
    
    printf("Appending %i\n", *(int*)i3p);
    append_list(l, i3p);     // append item to list
    print_list(l);
    
    printf("\n");
    printf("The current size is %i\n", l->size);
    printf("The current head is %i\n", *(int*)l->head->data);
    printf("The current tail is %i\n", *(int*)l->tail->data);
    printf("\n");
    
    printf("Removed head node %i\n", *(int*)remove_list_head(l));
    printf("Size after removing head = %i\n", l->size);
    printf("\n");
    
    printf("Prepending %i\n", *(int*)i4p);
    prepend_list(l, i4p);     // prepend item to list
    print_list(l);
    
    printf("Initializing iterator with get_list_head\n");
    get_list_head(l);
    printf("Current node is %i\n", *(int*)l->cur->data);
    printf("\n");
    
    printf("Moving to next node with get_list_next\n");
    get_list_next(l);
    printf("Current node is %i\n", *(int*)l->cur->data);
    printf("\n");	
	
    printf("Inserting node %i before current node\n", *(int*)i5p);
    insert_node_before_cur(l, i5p); // insert item into list
    print_list(l);
	
	printf("Inserting node %i after current node\n", *(int*)i6p);
    insert_node_after_cur(l, i6p);  // insert item into list
    print_list(l);
    

    
    printf("The current size is %i\n", l->size);
    printf("The current head is %i\n", *(int*)l->head->data);
    printf("The current tail is %i\n", *(int*)l->tail->data);
    printf("\n");
    
    printf("Freeing linkedlist\n");
    clear_list(l);
    printf("The current size is %i\n", l->size);
    print_list(l);
    printf("\n");
	free_linkedlist(l);
    
    return 0;
}
#endif

