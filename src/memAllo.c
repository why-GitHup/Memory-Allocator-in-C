// This code is meant to be compiled in Linux (Docker)
#ifdef _WIN32
    #pragma message("Warning: This code requires Linux environment")
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../include/avl.h"
#include <pthread.h>

#define BLOCK_SIZE sizeof(Block)

// Static mutex for thread safety
static pthread_mutex_t mem_mutex = PTHREAD_MUTEX_INITIALIZER;

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

    void* result = NULL;
    pthread_mutex_lock(&mem_mutex);
    // Search for a free block that fits using AVL tree
    Block* found = avl_find_best_fit(free_list, size);
    if(found){
        found->is_free = 0;
        result = (void*)(found + 1);
    } else {
        // No suitable block found - request more space
        Block *block = request_space(size);
        if(!block){
            pthread_mutex_unlock(&mem_mutex);
            return NULL;  // Out of memory
        }
        // Insert the new block into AVL tree
        free_list = avl_insert(free_list, block);
        result = (void*)(block + 1);
    }
    pthread_mutex_unlock(&mem_mutex);
    return result;
}


void mem_free(void* ptr){
    if(!ptr) return;
    pthread_mutex_lock(&mem_mutex);
    Block *block = (Block*)ptr - 1;
    block->is_free = 1;
    pthread_mutex_unlock(&mem_mutex);
}

int main(){

    return 0;
}