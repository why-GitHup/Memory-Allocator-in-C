#include <stdio.h>
#include "memAllo.h"
#include "LL.h"

listNode* createNode(int value){
    listNode* n = mem_alloc(sizeof(listNode));
    if(!n) return NULL;

    n->next = NULL;
    n->value = value;
    
    return n;
}
void add_at_head(listNode** head, listNode* load){
    if(!load) return;
    if(!*head) *head = load;
    listNode* temp = *head;
    load->next = temp;
    *head = load;
}
void add_at_tail(listNode **head, listNode *load){
    if(!load || !head) return;
    if(!*head) { *head = load; return; }

    listNode* temp = *head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = load;
}

void free_list(listNode** head){
    listNode* temp = *head;
    listNode* next;
    while(temp != NULL){
        next = temp->next;
        mem_free(temp);
        temp = next;
    }
    *head = NULL;
}

