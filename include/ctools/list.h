#pragma once


typedef struct list_st {
    struct list_st* prev;
    struct list_st* next;

    void* data;
} list_t;
typedef list_t* list_it;

#define list_push(head, tail, item) list_insert(head, tail, *head, item)
#define list_push_back(head, tail, item) list_append(head, tail, *tail, item)
#define list_pop(head, tail) list_remove(head, tail, *head)
#define list_pop_back(head, tail) list_remove(head, tail, *tail)
int list_insert(void* head, void* tail, void* it, void* item);
int list_append(void* head, void* tail, void* it, void* item);
void* list_remove(void* head, void* tail, void* it);
void list_swap(void* head, void* tail, void* a, void* b);
