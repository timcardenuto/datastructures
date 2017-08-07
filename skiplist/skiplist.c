#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // contains INT_MAX constant
#include <math.h>
#include <time.h>
#include "utils.h"
#include "skiplist.h"

/**********************************************************
 * Functions for the skiplist
 ***********************************************************/

skiplist* create_skiplist(int max_levels, float prob) {
    skiplist* sl = myMalloc(sizeof(skiplist));
	sl->size = 0;
	sl->prob = prob;
	sl->max_levels = max_levels;
	sl->cur_levels = 0;
	sl->head = create_slnode(0, max_levels);
	sl->tail = NULL;	//what is max integer and why do I need a tail?
	return sl;
}



void free_skiplist(skiplist* slst) {
	clear_list(slst);
	free(slst);
}



slnode* create_slnode(int key, int num_levels) {
    slnode* node = myMalloc(sizeof(slnode));
	node->key = key;
	slnode** array = myMalloc(num_levels * sizeof(slnode));
	int i = 0;
	for (i = 0; i < num_levels; i++) {
		array[i] = NULL;
	}
	node->next = array;
	
	/////// Take this out for non-debug ///////
	node->levels = num_levels;
	//////////////////////////////////////////
	
	return node;
}



void free_slnode(slnode* node) {
    free(node->next);
	free(node);
}



int is_list_empty(skiplist* slst) {
    if (slst->size == 0) { return 1; }
	else { return 0; }
}



void clear_list(skiplist* slst) {
	while (slst->head->next[0] != NULL) {
		int dont_need = delete(slst, slst->head->next[0]->key);
	}
}



int generate_random_level(int max_levels, float prob) {
	int head = 0;
	int levels = 0;
	head = rand() % 2;
	while (head == 1 && levels < max_levels) {
		levels = levels + 1;
		head = rand() % 2;
	}
	return levels;
}



slnode* find(skiplist* slst, int key) {
    printf("Finding key %i\n", key);
	slnode* cur = slst->head;
	int level = slst->cur_levels;
	int i = 0;
	for (i = 0; i < slst->size; i++) {	
		if (level == 0 && (cur->next[level] == NULL || cur->next[level]->key > key)) {	//end of list or next is bigger, didn't find it
			printf("Key not found\n");
			printf("--------------------------------------\n");
			return NULL;
			
		} else if (cur->next[level] == NULL || cur->next[level]->key > key) { //but level > 0, decrease level and look again
			printf("Decrease level and search again\n");
			level = level - 1;
		
		} else if (cur->next[level]->key < key) {	//keep searching
			printf("Keep searching\n");
			cur = cur->next[level];
		
		} else if (cur->next[level]->key == key) {	//found it
			printf("Key %i found\n", key);
			printf("--------------------------------------\n");
			return cur->next[level];
		}
	}
	printf("Key not found\n");
	printf("--------------------------------------\n");
	return NULL;
}



void insert(skiplist* slst, int key) {
	printf("Inserting new key %i\n", key);
	int new_level = generate_random_level(slst->max_levels, .5);
	slnode* new_node = create_slnode(key, new_level);
	printf("New level %i\n", new_level);
	slnode** prev_array = myMalloc(new_level * sizeof(slnode));
	slnode* cur = slst->head;
	int level = slst->cur_levels;
	int done = 0;
	int j = new_level;
	for (j = new_level; j > level; j--) { //If new node will be highest add head nodes to array
		prev_array[j] = cur;
	}
	
	while (done == 0) {	
		if (level == 0 && (cur->next[level] == NULL || cur->next[level]->key > key)) {	//end of list or next is bigger, can't decrease insert here
			printf("End of list insert here\n");
			printf("Update pointers from previous nodes\n");
			int i = new_level;
			for (i = new_level; i > 0; i--) { //update pointers from previous nodes
				printf("Updating level %i\n", i);
				prev_array[i]->next[i] = new_node;
			}
			printf("Updating level 0\n");
			cur->next[level] = new_node; //For current node (level 0)
			
			if (slst->cur_levels < new_level) {
				printf("Update cur_levels to be %i\n", new_level);
				slst->cur_levels = new_level;
			}
			
			printf("Updating size to %i\n", slst->size + 1);
			slst->size = slst->size + 1;
			done = 1;
			
		} else if (cur->next[level] == NULL || cur->next[level]->key > key) { //but level > 0, decrease level and look again
			printf("Decrease level and search again\n");
			if (level <= new_level) {	//add cur node to top of array if it's within range of new node levels
				prev_array[level] = cur;
			}
			level = level - 1;
		
		} else if (cur->next[level]->key < key) {	//keep searching
			printf("Keep searching\n");
			cur = cur->next[level];
		
		} else if (cur->next[level]->key == key) {	//error bail
			printf("Duplicate Key\n");
			exit(1);
		}
	}
}



int delete(skiplist* slst, int key) {
	printf("Deleting key %i\n", key);
	int level = slst->cur_levels;
	slnode* cur = slst->head;
		
	while (TRUE) {	
		if (level == 0 && (cur->next[level] == NULL || cur->next[level]->key > key)) {	//end of list or next is bigger, can't decrease no key
			printf("Key does not exist, delete failed\n");
			return 0;
			
		} else if (cur->next[level] == NULL || cur->next[level]->key > key) { //but level > 0, decrease level and look again
			printf("Decrease level and search again\n");
			level = level - 1;
		
		} else if (cur->next[level]->key < key) {	//keep searching
			printf("Keep searching\n");
			cur = cur->next[level];
		
		} else if (cur->next[level]->key == key && level != 0) {	//found it, update pointer and keep going
			slnode* tmp = cur->next[level]->next[level];
			cur->next[level] = tmp;
			level = level - 1;
			
		} else if (cur->next[level]->key == key && level == 0) {	//done, delete key
			printf("Done updating pointers\n");
			slnode* dead_node =  cur->next[level];
			slnode* tmp = cur->next[level]->next[level];
			cur->next[level] = tmp;
			free_slnode(dead_node);	//all pointers should have been updated by jumping the undesired node
			printf("Key deleted\n");
			return 1;
		}
	}
}



void print_list(skiplist* slst) {
	printf("Printing List\n");
	if (slst->size != 0) {
		slnode* cur = slst->head;
		
		while (cur->next[0] != NULL) {
			printf("%i", cur->next[0]->key);
			
			/////// Take this out for non-debug ///////
			int i = 0;
			for (i = 0; i < cur->next[0]->levels; i++) {
				printf("[]");
			}
			//////////////////////////////////////////
			
			printf("\n");
			cur = cur->next[0];
		}
		printf("--------------------------------------\n");
		
	} else {
		printf("Empty skiplist------------------------\n");
	}
}


/**********************************************************
 * The following main function is for debugging this 
 * skiplist.  Supply the DEBUG flag to to compiler to 
 * compile a skiplist containing this main function.
 ***********************************************************/
#ifdef DEBUG_SKIPLIST
int main(void) {
    printf("====================\n");
    printf("Debugging Skiplist\n");
    printf("====================\n");
	
	/* NOTE
		I added a parameter to the slnode to store the number of levels generated
		for each node. This is only used when printing the list so you can see it
		visually. I was gonna take it out but it looks nice so don't count it against
		me it doesn't impact the code anywhere else.:)
	*/
	
    srand(time(NULL));
    
    skiplist* slst = create_skiplist(16, 0.5);
	print_list(slst);  // should print an empty list
    
    insert(slst, 1);
	print_list(slst);
	
	insert(slst, 3);
	print_list(slst);
	
	insert(slst, 5);
	print_list(slst);
	
	insert(slst, 6);
	print_list(slst);
	
	insert(slst, 8);
	print_list(slst);
	
	insert(slst, 10);
	print_list(slst);
	
	insert(slst, 13);
	print_list(slst);
	
	slnode* n = find(slst, 6);
		
	slnode* n2 = find(slst, 20);	//doesn't exist, make sure doesn't break

	int who = delete(slst, 1);		//first node
	print_list(slst);
	
	int what = delete(slst, 6);		//middle node
	print_list(slst);
	
	int where = delete(slst, 13);	//last node
	print_list(slst);
	
	int when = delete(slst, 20);	//doesn't exist, make sure doesn't break
	print_list(slst);
	
    free_skiplist(slst);
	print_list(slst);	//empty list
	
    return 0;
}
#endif
