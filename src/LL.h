
#ifndef LL
#define LL

typedef struct listNode{
    int value;
    struct listNode* next;

}listNode;

listNode* createNode(int value);
void add_at_head(listNode** head, listNode* load);
void add_at_tail(listNode** head, listNode* load);
void free_list(listNode** head);




#endif