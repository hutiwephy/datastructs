#pragma once

#include <stdint.h>


typedef struct pair_st {
    struct pair_st* prev;
    struct pair_st* next;

    char* key;
    void* value;
} pair_t;

typedef pair_t* dict_it;

typedef struct dict_st {
    pair_t* head;
    pair_t* tail;
} dict_t;
#define new_dict (dict_t){NULL, NULL}
#define DICT_DELETE NULL

#define dict_isEmpty(dict) (dict->head == NULL)
void* dict_set(dict_t* dict, char* key, void* value);
void* dict_get(dict_t* dict, char* key);
char** dict_getKeys(dict_t* dict);
void dict_destroy(dict_t* dict, void (*destructor)(void*));
