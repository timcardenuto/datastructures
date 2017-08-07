#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/**
 * Attempts to allocate memory. If memory allocation fails, the
 * program terminates. This function is handy as it handles all 
 * of the error checking that is required each time a user calls
 * 'malloc'. 
 * @param size - the number of bytes requested to be allocated
 * @return a pointer to the allocated memory if allocation is 
 *  successful.
 **/
void* myMalloc(size_t size) {
    void *ptr;
    if ((ptr = malloc(size)) == NULL) {
        fprintf(stderr, "Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}


/**
 * Attempts to allocate and clear memory. If memory allocation 
 * fails, the program terminates. This function is handy as it 
 * handles all of the error checking that is required each time 
 * a user calls 'calloc'. 
 * @param count - the number of objects to store in memory
 * @param size - the size, in bytes, of each object to be stored
 * @return a pointer to the allocated memory if allocation is 
 *  successful.
 **/

void* myCalloc(size_t count, size_t size) {
    void *ptr;
    if ((ptr = calloc(count, size)) == NULL) {
        fprintf(stderr, "Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}