#pragma once


typedef void (*destructor_t)(void*);
typedef struct dict_st {
    void* head;
    void* tail;
} dict_t;
#define new_dict (dict_t){NULL, NULL}
#define DICT_DELETE NULL

#define dict_isEmpty(dict) (dict->head == NULL)
void* dict_set(void* dict, char* key, void* pair);
void* dict_get(void* dict, char* key);
char** dict_getKeys(void* dict);
void dict_destroy(void* dict, void (*destructor)(void*));
