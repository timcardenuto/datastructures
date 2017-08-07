#ifndef _hashtable_h
#define _hashtable_h

#include "linkedlist.h"


/* struct defining the hashtable */
// The capacity should be a prime number close to the desired capacity
typedef struct hashtable_struct {
    int capacity;       // the number of buckets in our hashtable
    int size;           // the number of elements currently in the table
    linkedlist** table; // an integer array in which to store keys
} hashtable;


/**********************************************************
 * function prototypes
 ***********************************************************/

/**
 * Creates and initializes a hashtable.
 * @param capacity - the size of the array for this hashtable
 * @return a pointer to the newly created hashtable
 **/
hashtable* create_hashtable(int capacity);

/**
 * Frees all the memory for the specified hashtable
 * @param h - a pointer to the hashtable to be freed
 **/
void free_hashtable(hashtable* h);

/**
 * Checks to see if the hashtable is empty. 
 * If a NULL hashtable is passed to this function, 
 * program prints an error and exits.
 * @param h - a pointer to the hashtable to check
 * @return 1 if empty, 0 otherwise
 **/ 
int is_hashtable_empty(hashtable* h);

/**
 * Computes the load factor for the hashtable. The
 * load factor for a hashtable with chaining is equal
 * to n/m where n is the number of elements in the hash
 * table and m is the number of hash table buckets. This
 * means that the load factor for a hash table with chaining
 * can be > 1.  The load factor for this type of hash table
 * indicates the number of elements we might expect to 
 * see in a bucket of the hash table.
 * If a NULL hashtable is passed to this function, 
 * program prints an error and exits.
 * @param h - a pointer to the hashtable for which to compute
 *            the load factor
 * @return the load factor of the input hashtable
 **/ 
double get_load_factor(hashtable* h);

/**
 * Computes the hashcode for a string that is to be 
 * inserted into the hashtable.
 * @param str - the string for which to compute a hascode
 * @param capacity - the capacity of the hashtable
 * @return an unsigned integer representing the bucket into
 *         which the input string should be stored
 **/ 
unsigned int hash(char* str, int capacity);

/**
 * Searches the hashtable for a specified string
 * If a NULL hashtable is passed to this function, 
 * program prints an error and exits.
 * @param h - a pointer to the hashtable to search
 * @param str - the string to find in the hashtable
 * @return 1 if search string is found, 
 *         0 otherwise (if str didn't exist in hashtable)
 **/ 
int find(hashtable* h, char* str);

/**
 * Inserts a character string into a hashtable. This hashtable
 * uses chaining to handle all collisions. Do not allow the 
 * same string to be inserted multiple times. See return values
 * below.
 * If a NULL hashtable is passed to this function, 
 * program prints an error and exits.
 * @param h - a pointer to the hashtable to insert data into
 * @param str - the string to insert into the hashtable
 * @return 1 if search string is successfully inserted, 
 *         0 otherwise (if str already existed)
 **/ 
int insert(hashtable* h, char* str);

/**
 * Searches the hashtable for a specified string and 
 * deletes it if found.
 * If a NULL hashtable is passed to this function, 
 * program prints an error and exits.
 * @param h - a pointer to the hashtable from which to 
 *            delete the string
 * @param str - the string to delete from the hashtable
 * @return 1 if search string deleted successfully
 *         0 otherwise (if str didn't exist in hashtable)
 **/ 
int delete(hashtable* h, char* str);

/**
 * Prints the contents of the hashtable
 * @param h - a pointer to the hashtable to print
 **/
void print_hashtable(hashtable* h);

#endif
