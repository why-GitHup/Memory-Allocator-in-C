// This code is meant to be compiled in Linux (Docker)
#ifdef _WIN32
    #pragma message("Warning: This code requires Linux environment")
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "avl.h"

#define BLOCK_SIZE sizeof(Block)

static Block *free_list = NULL;

Block* request_space(size_t size){
    Block *block;
    void *request;
    
    // Request space for Block metadata + actual data
    request = sbrk(BLOCK_SIZE + size);
    
    if(request == (void*) -1){
        return NULL; // sbrk failed
    }
    
    block = request;
    block->size = size;
    block->is_free = 0;
    block->left = NULL;
    block->right = NULL;
    block->height = 1;
    
    return block;
}


void* mem_alloc(size_t size){
    // Search for a free block that fits using AVL tree
    Block* found = avl_find_best_fit(free_list, size);
    if(found){
        found->is_free = 0;
        return (void*)(found + 1);
    }

    // No suitable block found - request more space
    Block *block = request_space(size);
    
    if(!block){
        return NULL;  // Out of memory
    }
    
    // Insert the new block into AVL tree
    free_list = avl_insert(free_list, block);
    return (void*)(block + 1);
}


void mem_free(void* ptr){
    if(!ptr) return;
    
    Block *block = (Block*)ptr - 1;
    block->is_free = 1;

    
}

int main(){

    return 0;
}