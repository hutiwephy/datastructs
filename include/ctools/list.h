#pragma once


typedef struct list_st {
    void* head;
    void* tail;
} list_t;

#define list_push(list, item) list_insert(list, (list)->head, item)
#define list_push_back(list, item) list_append(list, (list)->tail, item)
#define list_pop(list) list_remove(list, (list)->head)
#define list_pop_back(list) list_remove(list, (list)->tail)
int list_insert(void* list, void* it, void* item);
int list_append(void* list, void* it, void* item);
void* list_remove(void* list, void* it);
void list_swap(void* list, void* a, void* b);
