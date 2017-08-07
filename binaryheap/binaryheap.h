#ifndef _binheap_h
#define _binheap_h


/* struct defining the heap */
typedef struct binheap_struct {
    int cur_size;   // the current size of the heap
    int max_size;   // the maximum size of the heap
    int* arr;       // an integer array in which to store keys
} binheap;


/**********************************************************
 * function prototypes
 ***********************************************************/

/**
 * Creates and initializes a binheap. 
 * @param max_size - the maximum number of keys that can be inserted into the binheap
 * @return a pointer to the newly created binheap
 **/
binheap* create_binheap(int max_size);

/**
 * Frees all the memory for the specified binheap
 * @param h - a pointer to the binheap to be freed
 **/
void free_binheap(binheap* h);

/**
 * Checks to see if the binheap is empty
 * @param h - a pointer to the binheap to check
 * @return 1 if empty, 0 otherwise
 **/ 
int is_heap_empty(binheap* h);

/**
 * Inserts a new key into the binary heap. Duplicate nodes ARE
 * allowed in the binheap.
 * @param h - a pointer to the binheap in which to insert the key
 * @param key - the key value to insert into the binheap
 * @return 1 if key was successfully inserted, 0 otherwise
 **/
int insert(binheap* h, int key);

/**
 * Percolates a node up the binary heap. A node is continually 
 * swapped with its parent if it is less than its parent
 * @param h - a pointer to the binheap with the node to percolate
 * @param node_idx - the array index of the node in the heap that 
 *        is to be percolated
 **/
void percolate_up(binheap* h, int node_idx);

/**
 * Percolates a node down the binary heap. A node is continually 
 * swapped with the lesser of its two children if the smaller of 
 * its two children has a key value less than that of the node
 * @param h - a pointer to the binheap with the node to percolate
 * @param node_idx - the array index of the node in the heap that 
 *        is to be percolated
 **/
void percolate_down(binheap* h, int node_idx);
                  
/**
 * Deletes the minimum element from the provided binheap (the root)
 * @param h - a pointer to the binheap from which to delete the minimum
 * @return the key values of the minimum element that was deleted. If 
 *         no node is deleted (the binheap is emepty) then return -1
 **/
int delete_min(binheap* h);

/**
 * Given a heap struct that is not necessarily in heap-order, this
 * function will heapify the input such that heap-order is restored.
 * @param h - a pointer to the binheap to heapify
 **/
void build_heap(binheap* h);

/**
 * Given a heap struct that is not necessarily in heap-order, this
 * function will perform a heap_sort.
 * @param h - a pointer to the binheap to sort
 **/
void heap_sort(binheap* h);

/**
 * Prints the contents of the binheap in level-order
 * @param h - a pointer to the binheap to print
 **/
void print_binheap(binheap* h);


#endif
