#ifndef MEMALLO_H
#define MEMALLO_H

#include <stddef.h>
#include "avl.h"

// Request space from the system using sbrk
Block* request_space(size_t size);

// Allocate memory of given size
void* mem_alloc(size_t size);

// Free allocated memory
void mem_free(void* ptr);

#endif // MEMALLO_H
