/**********************************************************
 * Author: James Moscola
 ***********************************************************/

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
    llnode* node = myMalloc(sizeof(llnode));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}



void free_llnode(llnode* node) {
    if (node == NULL)  return;
    free(node);
}



void free_linkedlist(linkedlist* lst) {
    if (lst == NULL)  return;
    clear_list(lst);
    free(lst);
}



int is_list_empty(linkedlist* lst) {
    return (lst->size == 0);
}



void clear_list(linkedlist* lst) {
    while (remove_list_head(lst)) { /* no body */ }
}



void append_list(linkedlist* lst, void* data) {
    llnode* node = create_llnode(data);
    
    if (lst->size == 0) {
        lst->head = lst->tail = node;
    } else {
        node->prev = lst->tail;
        lst->tail->next = node;
        lst->tail = node;
    }
    lst->size++;
}



void prepend_list(linkedlist* lst, void* data) {
    llnode* node = create_llnode(data);
    
    if (lst->size == 0) {
        lst->head = lst->tail = node;
    } else {
        node->next = lst->head;
        lst->head->prev = node;
        lst->head = node;
    }
    lst->size++;
}



void* remove_list_head(linkedlist* lst) {
    if (lst->size == 0) {
        return NULL;
    } else {
        llnode* node = lst->head;
        void* data = node->data;
        lst->head = lst->head->next;
        if (lst->head != NULL) {    // check to see if last node was
            lst->head->prev = NULL; // just removed
        }
        lst->size--;
        free_llnode(node);
        return data;
    }
}



void* remove_list_tail(linkedlist* lst) {
    if (lst->size == 0) {
        return NULL;
    } else {
        llnode* node = lst->tail;
        void* data = node->data;
        lst->tail = lst->tail->prev;
        if (lst->tail != NULL) {    // check to see if last node was
            lst->tail->next = NULL; // just removed
        }
        lst->size--;
        free_llnode(node);
        return data;
    }
}



/**********************************************************
 * Functions for the iterator portion of the linkedlist
 ***********************************************************/

void* get_list_head(linkedlist* lst) {
    if (lst == NULL || lst->size == 0) {
        return NULL;
    } else {
        lst->cur = lst->head;
        return lst->head->data;
    }
}



void* get_list_tail(linkedlist* lst) {
    if (lst == NULL || lst->size == 0) {
        return NULL;
    } else {
        lst->cur = lst->tail;
        return lst->tail->data;
    }
}



/* must initialize lst->cur first */
void* get_list_next(linkedlist* lst) {
    if (lst->cur == NULL) { // check to see if cur has been initialized
        fprintf(stderr, "Iterator has not been initialized\n");
        exit(EXIT_FAILURE);
    } else if (lst->cur->next == NULL) {
        return NULL;
    } else {
        lst->cur = lst->cur->next;
        return lst->cur->data;
    }
}



/* must initialize lst->cur first */
void* get_list_prev(linkedlist* lst) {
    if (lst->cur == NULL) { // check to see if cur has been initialized
        fprintf(stderr, "Iterator has not been initialized\n");
        exit(EXIT_FAILURE);
    } else if (lst->cur->prev == NULL) {
        return NULL;
    } else {
        lst->cur = lst->cur->prev;
        return lst->cur->data;
    }
}



/* must initialize lst->cur first */
/* must re-initialize lst->cur after calling this function */
void* delete_list_current(linkedlist* lst) {
    if (lst->cur == NULL) { // check to see if cur has been initialized
        fprintf(stderr, "Iterator has not been initialized\n");
        exit(EXIT_FAILURE);
    }

    void* data = lst->cur->data;
    
    // head of list
    if (lst->cur->prev == NULL) {
        lst->head = lst->cur->next;
    } else {
        lst->cur->prev->next = lst->cur->next;
    }
    
    // tail of list
    if (lst->cur->next == NULL) { 
        lst->tail = lst->cur->prev;
    } else {
        lst->cur->next->prev = lst->cur->prev;
    }

    free_llnode(lst->cur);
    lst->cur = NULL;
    lst->size--;
    return data;
}



/* must initialize lst->cur first */
void insert_node_before_cur(linkedlist* lst, void* data) {
    if (lst->cur == NULL) { // check to see if cur has been initialized
        fprintf(stderr, "Iterator has not been initialized\n");
        exit(EXIT_FAILURE);
    } else if (lst->cur->prev == NULL) {
        prepend_list(lst, data);
    } else { 
        llnode* node = create_llnode(data);
        lst->cur->prev->next = node;
        node->prev = lst->cur->prev;
        node->next = lst->cur;
        lst->cur->prev = node;
        lst->size++;
    }
}



/* must initialize lst->cur first */
void insert_node_after_cur(linkedlist* lst, void* data) {
    if (lst->cur == NULL) { // check to see if cur has been initialized
        fprintf(stderr, "Iterator has not been initialized\n");
        exit(EXIT_FAILURE);
    } else if (lst->cur->next == NULL) {
        append_list(lst, data);
    } else {
        llnode* node = create_llnode(data);
        lst->cur->next->prev = node;
        node->next = lst->cur->next;
        node->prev = lst->cur;
        lst->cur->next = node;
        lst->size++;
    }
}



void print_list(linkedlist* lst) {
    llnode* tmp = lst->cur; // save the current state of the iterator
    
//    printf("List: ");
    void* data = get_list_head(lst);
    while (data != NULL) {
        printf("%s -> ", (char*)data);
        data = get_list_next(lst);
    }
    printf("NULL");
    lst->cur = tmp;  // restore the state of the iterator
}



/**********************************************************
 * The following main function is for debugging this 
 * linkedlist.  Supply the DEBUG flag to to compiler to 
 * compile a linkedlist containing this main function.
 ***********************************************************/
#ifdef DEBUG
int main(void) {
    printf("====================\n");
    printf("Debugging linkedlist\n");
    printf("====================\n");
   
    linkedlist* l = create_linkedlist(); // create the linkedlist
    char* s1 = "Hello";
    char* s2 = "World";
    append_list(l, s1);
    append_list(l, s2);
    print_list(l);
    
    printf("Freeing linkedlist\n");
    free_linkedlist(l);  // free list

    printf("\n");

    return 0;
}
#endif

