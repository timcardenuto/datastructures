#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable.h"
#include "linkedlist.h"
#include "utils.h"


/**********************************************************
 * Functions for the binheap
 ***********************************************************/

hashtable* create_hashtable(int capacity) {
    hashtable* ht = myMalloc(sizeof(hashtable));
	ht->capacity = capacity;
	ht->size = 0;
	linkedlist** t = myCalloc(capacity, sizeof(linkedlist)); //Allocates memory capacity memory blocks for linked lists
	int i = 0;
	for(i = 0; i < capacity; i++) { //creates a linked list in each block of memory
		t[i] = create_linkedlist();
	}
	ht->table = t;
	return ht;
}



void free_hashtable(hashtable* h) {
	if (h->table == NULL) {
		fprintf(stderr, "Attempted NULL hashtable access\n");
		exit(1);
	} else {
		int i = 0;
		for(i = 0; i < h->capacity; i++) {
			free_linkedlist(h->table[i]);
		}
		free(h);
	}
}



int is_hashtable_empty(hashtable* h) {
   	if (h->table == NULL) {
		fprintf(stderr, "Attempted NULL hashtable access\n");
		exit(1);
	} else if (h->size == 0) {
		return 1;
	} else {
		return 0;
	}
}



double get_load_factor(hashtable* h) {
   	if (h->table == NULL) {
		fprintf(stderr, "Attempted NULL hashtable access\n");
		exit(1);
	} else {
		return (double)h->size / h->capacity;
	}
}



unsigned int hash(char* str, int capacity) {
    unsigned int hashcode = 0;
    while (*str != '\0') {
        // printf("%c", *str); // uncomment for debugging
        hashcode = *str + (hashcode << 5) - hashcode;
        str++;
    }
    // printf(" - hashcode=%i\n", (hashcode % capacity));  // uncomment for debugging
    return hashcode % capacity;
}



int find(hashtable* h, char* str) {
	if (h->table == NULL) {
		fprintf(stderr, "Attempted NULL hashtable access\n");
		exit(1);
	} else {
		int i = 0;
		for(i = 0; i < h->capacity; i++) {
			llnode* tmp = h->table[i]->cur;
			char* string = get_list_head(h->table[i]);
			while (string != NULL) {
				if (!strcmp(string, str)) {
					printf("Found %s\n", string);
					h->table[i]->cur = tmp;
					return 1;
				}
				string = get_list_next(h->table[i]);
			}
			h->table[i]->cur = tmp;
		}
		printf("%s not in Hashtable\n", str);
		return 0;
	}
}



int insert(hashtable* h, char* str) {
	if (h->table == NULL) {
		fprintf(stderr, "Attempted NULL hashtable access\n");
		exit(1);
	} else {
		int index = hash(str, h->capacity);
		printf("Index: %i\n",index);
		
		//Search linked list for str
		llnode* tmp = h->table[index]->cur;
		void* string = get_list_head(h->table[index]);
		
		while (string != NULL) {
			if (!strcmp(string, str)) {
				printf("Duplicate string found ------------\n");
				h->table[index]->cur = tmp;
				return 0;
			}
			h->size = h->size + 1;
			string = get_list_next(h->table[index]);
		}
		h->table[index]->cur = tmp;
		h->size = h->size + 1;
		//If str not already inserted, then add it
		append_list(h->table[index], str);
		printf("Insert success ------------\n");
		return 1;
	}
}



int delete(hashtable* h, char* str) {
   if (h->table == NULL) {
		fprintf(stderr, "Attempted NULL hashtable access\n");
		exit(1);
	} else {
		int i = 0;
		for(i = 0; i < h->capacity; i++) {
			llnode* tmp = h->table[i]->cur;
			char* string = get_list_head(h->table[i]);
			while (string != NULL) {
				if (!strcmp(string, str)) {
					printf("Deleting %s\n", string);
					remove_list_head(h->table[i]);
					h->size = h->size - 1;
					h->table[i]->cur = tmp;
					return 1;
				}
				string = get_list_next(h->table[i]);
			}
			h->table[i]->cur = tmp;
		}
		printf("%s not in Hashtable\n", str);
		return 0;
	}
}



void print_hashtable(hashtable* h) {
	int i = 0;
	for(i = 0; i < h->capacity; i++) {
		//Search linked list for strings
		llnode* tmp = h->table[i]->cur;
		char* string = get_list_head(h->table[i]);
		while (string != NULL) {
			printf("String in bucket %i: %s\n", i, string);
			string = get_list_next(h->table[i]);
		}
		h->table[i]->cur = tmp;
	}		
}



/**********************************************************
 * The following main function is for debugging this 
 * hash table.  Supply the DEBUG flag to to compiler to 
 * compile a binheap containing this main function.
 ***********************************************************/
#ifdef DEBUG_HASHTABLE
int main(void) {
    printf("=====================\n");
    printf("Debugging Hash Table\n");
    printf("=====================\n");
    
    ////////////////////////////////////////////
    // Test a few insertions
    ////////////////////////////////////////////
    hashtable* h = create_hashtable(31);
	printf("Created Hash!\n");
    char* s1 = "Elephant";
    char* s2 = "Monkey";
    char* s3 = "Zebra";
    char* s4 = "Screeching Giraffe";
    char* s5 = "Donkey";
    char* s6 = "Badger";
    char* s7 = "Snake";
    char* s8 = "Tortoise";
    char* s9 = "Squid";
    char* s10 = "Whale";
    char* s11 = "Octopus";
    char* s12 = "Electric Eel";
    char* s13 = "Mountain Goat";
    char* s14 = "Lion";
    char* s15 = "Mountain Llama";
    char* s16 = "Sea Monkey";
    char* s17 = "Narwhal";
    char* s18 = "Flying Platypus";
    char* s19 = "Stealth Rhinoceros";
    char* s20 = "Magical Liger";
    char* s21 = "Bear";
    int success;
    
    printf("Inserting %s\n", s1);
    success = insert(h, s1);
    assert(success == 1);
    
    printf("Inserting %s\n", s2);
    success = insert(h, s2);
    assert(success == 1);

    printf("Inserting %s\n", s3);
    success = insert(h, s3);
    assert(success == 1);

    printf("Inserting %s\n", s4);
    success = insert(h, s4);
    assert(success == 1);

    printf("Inserting %s\n", s5);
    success = insert(h, s5);
    assert(success == 1);
    
    printf("Inserting %s\n", s6);
    success = insert(h, s6);
    assert(success == 1);    

    printf("Inserting %s\n", s7);
    success = insert(h, s7);
    assert(success == 1);   

    printf("Inserting %s\n", s8);
    success = insert(h, s8);
    assert(success == 1);

    printf("Inserting %s\n", s9);
    success = insert(h, s9);
    assert(success == 1);
    
    printf("Inserting %s\n", s10);
    success = insert(h, s10);
    assert(success == 1);
    
    printf("Inserting %s\n", s11);
    success = insert(h, s11);
    assert(success == 1);
    
    printf("Inserting %s\n", s12);
    success = insert(h, s12);
    assert(success == 1);

    printf("Inserting %s\n", s13);
    success = insert(h, s13);
    assert(success == 1);
    
    printf("Inserting %s\n", s14);
    success = insert(h, s14);
    assert(success == 1);

    printf("Inserting %s\n", s15);
    success = insert(h, s15);
    assert(success == 1);

    printf("Inserting %s\n", s16);
    success = insert(h, s16);
    assert(success == 1);
    
    printf("Inserting %s\n", s17);
    success = insert(h, s17);
    assert(success == 1);
    
    printf("Inserting %s\n", s18);
    success = insert(h, s18);
    assert(success == 1);
    
    printf("Inserting %s\n", s19);
    success = insert(h, s19);
    assert(success == 1);
    
    printf("Inserting %s\n", s20);
    success = insert(h, s20);
    assert(success == 1);

	printf("Size: %i\n", h->size);
    printf("\nLoad Factor = %lf\n", get_load_factor(h)); 
    
    
    
    ////////////////////////////////////////////
    // The following insertion should fail
    ////////////////////////////////////////////
    printf("\n");
    printf("Inserting %s again\n", s1);
    success = insert(h, s1);
    assert(success == 0);
    printf("\n");

    ////////////////////////////////////////////
    // Print the Hash table
    ////////////////////////////////////////////
    print_hashtable(h);
    
    ////////////////////////////////////////////
    // Test some find operations
    ////////////////////////////////////////////
    printf("\n");
    printf("Finding %s\n", s8);
    success = find(h, s8);
    assert(success == 1);

    printf("Finding %s\n", s20);
    success = find(h, s20);
    assert(success == 1);

    printf("Finding %s\n", s21);
    success = find(h, s21);
    assert(success == 0);


    ////////////////////////////////////////////
    // Test the delete operation
    ////////////////////////////////////////////
    printf("\n");
    printf("Deleting %s\n", s21);
    success = delete(h, s21);
    assert(success == 0);

    printf("Deleting %s\n", s18);
    success = delete(h, s18);
    assert(success == 1);
    
    printf("Deleting %s\n", s8);
    success = delete(h, s8);
    assert(success == 1);
        
    printf("Deleting %s\n", s5);
    success = delete(h, s5);
    assert(success == 1);
    
    
    printf("\nLoad Factor = %lf\n", get_load_factor(h)); 
    
    ////////////////////////////////////////////
    // Print the Hash table
    ////////////////////////////////////////////
    print_hashtable(h);
    
    printf("\n");
    free_hashtable(h);
        
    return 0;
}
#endif
