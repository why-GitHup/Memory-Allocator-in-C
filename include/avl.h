#ifndef AVL_H
#define AVL_H

#include <stddef.h>

typedef struct Block {
    size_t size;
    int is_free;
    struct Block* left;
    struct Block* right;
    int height;
} Block;

// Get height of a node
int avl_height(Block* node);

// Get balance factor of a node
int avl_get_balance(Block* node);

// Rotate right (for left-left case)
Block* avl_rotate_right(Block* y);

// Rotate left (for right-right case)
Block* avl_rotate_left(Block* x);

// Insert a block into the AVL tree
Block* avl_insert(Block* root, Block* block);

Block* avl_remove_block(Block* root, Block* block);
// Find the best fit block (in-order traversal for smallest sufficient block)
Block* avl_find_best_fit(Block* root, size_t size);

int max(int a, int b);

#endif // AVL_H
