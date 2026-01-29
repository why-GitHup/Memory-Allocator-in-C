#include <stdio.h>
#include "../include/LL.h"
#include "../include/memAllo.h"

int main() {
    listNode *head = NULL;
    printf("Testing custom mem_alloc with linked list...\n");

    // Add nodes at head
    for (int i = 0; i < 5; ++i) {
        listNode *node = createNode(i);
        if (!node) {
            printf("Failed to allocate node %d\n", i);
            return 1;
        }
        add_at_head(&head, node);
    }

    // Add nodes at tail
    for (int i = 5; i < 10; ++i) {
        listNode *node = createNode(i);
        if (!node) {
            printf("Failed to allocate node %d\n", i);
            return 1;
        }
        add_at_tail(&head, node);
    }

    // Print list
    printf("Linked list contents: ");
    listNode *curr = head;
    while (curr) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");

    // Free list
    free_list(&head);
    if (head == NULL) {
        printf("List successfully freed.\n");
    } else {
        printf("List not freed properly!\n");
    }
    return 0;
}
