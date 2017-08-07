#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "binheap.h"
#include "utils.h"

#define PARENT(i) i/2
#define LCHILD(i) 2*i
#define RCHILD(i) 2*i+1

/**********************************************************
 * Functions for the binheap
 ***********************************************************/

binheap* create_binheap(int max_size) {
    binheap* bh = myMalloc(sizeof(binheap));
	bh->max_size = max_size;
	bh->cur_size = 0;
	int* array = myMalloc(max_size * sizeof(int));
	bh->arr = array;
	return bh;
}



void free_binheap(binheap* h) {
    free(h);
}



int is_heap_empty(binheap* h) {
    if (h->cur_size == 0) {
		return 1;
	} else {
		return 0;
	}
}



int insert(binheap* h, int key) {
	if (h->cur_size != h->max_size) {
		h->cur_size = h->cur_size + 1;
		h->arr[h->cur_size] = key;
		percolate_up(h, h->cur_size);
		return 1;
	} else {
		return 0;
	}
}



void percolate_up(binheap* h, int node_idx) {
	int key = h->arr[node_idx];
	while (node_idx/2 != 0 && key < h->arr[node_idx/2]) {	//while key is less than parent...
		h->arr[node_idx] = h->arr[node_idx/2]; //copy parent to the child node
		node_idx = node_idx/2;		//update index to be parent node
	}
	h->arr[node_idx] = key;	//copy key to the final node
}



void percolate_down(binheap* h, int node_idx) {
	int key = h->arr[node_idx];	//store key to percolate
	int small_child = 0;
	
	if (node_idx*2 > h->cur_size) { //if left child doesn't exist
		small_child = node_idx;	//no canidate
	} else if (((node_idx*2 + 1) > h->cur_size) || (h->arr[node_idx*2] < h->arr[node_idx*2 + 1])) { //if left child is only child or is smaller than right child
		small_child = node_idx*2;	//left child is swap canidate
	} else {
		small_child = node_idx*2 + 1;	//right child is swap canidate
	}
	
	while (key > h->arr[small_child] && small_child != 1) {	//while key is larger than smallest child...
		h->arr[node_idx] = h->arr[small_child]; //copy small child to parent node
		node_idx = small_child;		//update index to be small child node
	
		if (node_idx*2 > h->cur_size) { //find new small child
			break;
		} else if (((node_idx*2 + 1) > h->cur_size) || (h->arr[node_idx*2] < h->arr[node_idx*2 + 1])) {
			small_child = node_idx*2;
		} else {
			small_child = node_idx*2 + 1;
		}
	}
	h->arr[node_idx] = key;	//copy key to the final node
}



int delete_min(binheap* h) {
    if (is_heap_empty(h)) {
		return -1;
	} else {
		int root = h->arr[1];
		h->arr[1] = h->arr[h->cur_size];	//so the last key is percolated down from root
		h->cur_size = h->cur_size - 1;
		percolate_down(h, 1);	
		h->arr[h->cur_size + 1] = 0;
		return root;
	}	
}



void build_heap(binheap* h) {
	printf("Building Heap\n");
	int size = h->cur_size;
	int i = size / 2;
	for (i = (size / 2); i > 0; i--) {
		percolate_down(h, i);
	}
}



void heap_sort(binheap* h) {
	build_heap(h);
	printf("Sorting Heap\n");
	int size = h->cur_size;
	int i = size;	
	for (i = size; i > 0; i--) {
		int root = delete_min(h);
		h->arr[i] = root;
	}
	h->cur_size = size;
}



void print_binheap(binheap* h) {
    	int i = 1;
	for (i = 1; i < (h->cur_size + 1); i++) {
		printf("%i\n", h->arr[i]);
	}
	printf("-------------------------------------\n");
}


/**********************************************************
 * The following main function is for debugging this 
 * binheap.  Supply the DEBUG flag to to compiler to 
 * compile a binheap containing this main function.
 ***********************************************************/
#ifdef DEBUG_BINARYHEAP
int main(void) {
    printf("=====================\n");
    printf("Debugging Binary Heap\n");
    printf("=====================\n");
    
    ////////////////////////////////////////////
    // Test a few insertions
    ////////////////////////////////////////////
    binheap* h = create_binheap(100);
    assert(is_heap_empty(h) == TRUE);
    print_binheap(h);
	
    insert(h, 55);
    assert(is_heap_empty(h) == FALSE);
    assert(h->cur_size == 1);
    print_binheap(h);
    
    insert(h, 44);
    assert(is_heap_empty(h) == FALSE);
    assert(h->cur_size == 2);
    print_binheap(h);
	
    insert(h, 0);
    assert(is_heap_empty(h) == FALSE);
    assert(h->cur_size == 3);
    print_binheap(h);
    
    insert(h, 66);
    assert(is_heap_empty(h) == FALSE);
    assert(h->cur_size == 4);
    print_binheap(h);
    
    insert(h, 10);
    assert(is_heap_empty(h) == FALSE);
    assert(h->cur_size == 5);
    print_binheap(h);
    ////////////////////////////////////////////
    ////////////////////////////////////////////
    
    
    ////////////////////////////////////////////
    // Test a few deletions
    ////////////////////////////////////////////
    int deleted_val = delete_min(h);
    assert(h->cur_size == 4);
    assert(deleted_val == 0);
    print_binheap(h);
    
    deleted_val = delete_min(h);
    assert(h->cur_size == 3);
    assert(deleted_val == 10);
    print_binheap(h);    
    
    deleted_val = delete_min(h);
    assert(h->cur_size == 2);
    assert(deleted_val == 44);
    print_binheap(h);
	
    deleted_val = delete_min(h);
    assert(h->cur_size == 1);
    assert(deleted_val == 55);
    print_binheap(h);

    deleted_val = delete_min(h);
    assert(h->cur_size == 0);
    assert(deleted_val == 66);
    print_binheap(h);
    
    deleted_val = delete_min(h);
    assert(h->cur_size == 0);
    assert(deleted_val == -1);
    print_binheap(h);
    
    free_binheap(h);
    ////////////////////////////////////////////
    ////////////////////////////////////////////

    
    ////////////////////////////////////////////
    // Test the build_heap function
    ////////////////////////////////////////////
    h = create_binheap(100);
    
    // For debugging, just insert the elements directly
    // into the array prior to calling build_heap
    h->arr[1] = 17;
    h->arr[2] = 22;
    h->arr[3] = 19;
    h->arr[4] = 55;
    h->arr[5] = 7;
    h->arr[6] = 43;
    h->arr[7] = 14;
    h->arr[8] = 97;
    h->arr[9] = 63;
    h->arr[10] = 61;
    h->arr[11] = 3;
    h->arr[12] = 2;
    h->arr[13] = 1;
    h->arr[14] = 13;
    h->arr[15] = 27;
    h->arr[16] = 37;
    h->arr[17] = 9;
    h->arr[18] = 0;
    h->cur_size = 18;
    
    build_heap(h);

    // Verify that the build_heap function
    // operates as expected
    assert(h->arr[1] == 0);
    assert(h->arr[2] == 3);
    assert(h->arr[3] == 1);
    assert(h->arr[4] == 9);
    assert(h->arr[5] == 7);
    assert(h->arr[6] == 2);
    assert(h->arr[7] == 13);
    assert(h->arr[8] == 22);
    assert(h->arr[9] == 55);
    assert(h->arr[10] == 61);
    assert(h->arr[11] == 17);
    assert(h->arr[12] == 19);
    assert(h->arr[13] == 43);
    assert(h->arr[14] == 14);
    assert(h->arr[15] == 27);
    assert(h->arr[16] == 37);
    assert(h->arr[17] == 97);
    assert(h->arr[18] == 63);
	
    free_binheap(h);
    ////////////////////////////////////////////
    // Done testing build_heap function
    ////////////////////////////////////////////
    
    
    ////////////////////////////////////////////
    // Test the heap_sort function
    ////////////////////////////////////////////
    h = create_binheap(100);
    
    // For debugging, just insert the elements directly
    // into the array prior to calling heap_sort
    // this is the same array from the test above
    h->arr[1] = 17;
    h->arr[2] = 22;
    h->arr[3] = 19;
    h->arr[4] = 55;
    h->arr[5] = 7;
    h->arr[6] = 43;
    h->arr[7] = 14;
    h->arr[8] = 97;
    h->arr[9] = 63;
    h->arr[10] = 61;
    h->arr[11] = 3;
    h->arr[12] = 2;
    h->arr[13] = 1;
    h->arr[14] = 13;
    h->arr[15] = 27;
    h->arr[16] = 37;
    h->arr[17] = 9;
    h->arr[18] = 0;
    h->cur_size = 18;
	
    heap_sort(h);
    
    // Verify that the build_heap function
    // operates as expected
    assert(h->arr[1] == 97);
    assert(h->arr[2] == 63);
    assert(h->arr[3] == 61);
    assert(h->arr[4] == 55);
    assert(h->arr[5] == 43);
    assert(h->arr[6] == 37);
    assert(h->arr[7] == 27);
    assert(h->arr[8] == 22);
    assert(h->arr[9] == 19);
    assert(h->arr[10] == 17);
    assert(h->arr[11] == 14);
    assert(h->arr[12] == 13);    
    assert(h->arr[13] == 9);
    assert(h->arr[14] == 7);
    assert(h->arr[15] == 3);
    assert(h->arr[16] == 2);
    assert(h->arr[17] == 1);
    assert(h->arr[18] == 0);

    free_binheap(h);
    ////////////////////////////////////////////
    // Done testing heap_sort function
    ////////////////////////////////////////////

    
    return 0;
}
#endif
