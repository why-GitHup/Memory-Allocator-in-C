#include "../include/avl.h"
#include <stddef.h>

// Helper function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Get height of a node
int avl_height(Block* node) {
    return node ? node->height : 0;
}

// Get balance factor of a node
int avl_get_balance(Block* node) {
    return node ? avl_height(node->left) - avl_height(node->right) : 0;
}

// Right rotation (for left-left case)
Block* avl_rotate_right(Block* y) {
    Block* x = y->left;
    Block* T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = max(avl_height(y->left), avl_height(y->right)) + 1;
    x->height = max(avl_height(x->left), avl_height(x->right)) + 1;
    
    return x; // New root
}

// Left rotation (for right-right case)
Block* avl_rotate_left(Block* x) {
    Block* y = x->right;
    Block* T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    // Update heights
    x->height = max(avl_height(x->left), avl_height(x->right)) + 1;
    y->height = max(avl_height(y->left), avl_height(y->right)) + 1;
    
    return y; // New root
}

// Insert a block into the AVL tree
Block* avl_insert(Block* root, Block* block) {
    if (!block) return root;
    
    // 1. Perform normal BST insertion
    if (root == NULL) {
        block->left = NULL;
        block->right = NULL;
        block->height = 1;
        return block;
    }
    
    if (block->size < root->size) {
        root->left = avl_insert(root->left, block);
    } else if (block->size > root->size) {
        root->right = avl_insert(root->right, block);
    } else {
        // Duplicate size - insert to the right to allow multiple blocks of same size
        root->right = avl_insert(root->right, block);
    }
    
    // 2. Update height of this ancestor node
    root->height = 1 + max(avl_height(root->left), avl_height(root->right));
    
    // 3. Get the balance factor
    int balance = avl_get_balance(root);
    
    // 4. If unbalanced, there are 4 cases:
    
    // Left-Left case
    if (balance > 1 && block->size < root->left->size) {
        return avl_rotate_right(root);
    }
    
    // Right-Right case
    if (balance < -1 && block->size > root->right->size) {
        return avl_rotate_left(root);
    }
    
    // Left-Right case
    if (balance > 1 && block->size > root->left->size) {
        root->left = avl_rotate_left(root->left);
        return avl_rotate_right(root);
    }
    
    // Right-Left case
    if (balance < -1 && block->size < root->right->size) {
        root->right = avl_rotate_right(root->right);
        return avl_rotate_left(root);
    }
    
    return root;
}
Block* minValueNode(Block* node) {
    Block* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}
Block* avl_remove_block(Block* root, Block* block){
   if(root == NULL) return root;

   if(block->size < root->size){
    root->left = avl_remove_block(root->left, block);
   }
   if(block->size > root->size){
    root->right = avl_remove_block(root->right, block);
   }
   else{
        if((root->left == NULL) || (root->right == NULL)){
            Block* temp = root->left ? root->left : root->right;

            if(temp == NULL){
                temp = root;
                root = NULL;
            }
            else{
                *root = *temp;
            }
            
        }else{
            Block* temp = minValueNode(root->right);

            root->size = temp->size;

            root->right = avl_remove_block(root->right, temp);
        }
   }

   if(root == NULL){
        return root;
   }
   root->height = 1 + max(avl_height(root->left), avl_height(root->right));

    
    int balance = avl_get_balance(root);

    // If unbalanced, there are 4 cases:

    // Left Left Case
    if (balance > 1 && avl_get_balance(root->left) >= 0)
        return avl_rotate_right(root);

    // Left Right Case
    if (balance > 1 && avl_get_balance(root->left) < 0) {
        root->left = avl_rotate_left(root->left);
        return avl_rotate_right(root);
    }

    // Right Right Case
    if (balance < -1 && avl_get_balance(root->right) <= 0)
        return avl_rotate_left(root);

    // Right Left Case
    if (balance < -1 && avl_get_balance(root->right) > 0) {
        root->right = avl_rotate_right(root->right);
        return avl_rotate_left(root);
    }

    return root;

}

// Find the best fit block (in-order traversal for smallest sufficient block)
Block* avl_find_best_fit(Block* root, size_t size) {
    if (root == NULL) return NULL;
    
    // Search left subtree first (smaller sizes)
    Block* result = avl_find_best_fit(root->left, size);
    if (result != NULL) {
        return result;
    }
    
    // Check current node
    if (root->size >= size && root->is_free == 1) {
        return root;
    }
    
    // Search right subtree (larger sizes)
    return avl_find_best_fit(root->right, size);
}
