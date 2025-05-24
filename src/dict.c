#include <ctools/array.h>
#include <ctools/list.h>
#include <ctools/dict.h>
#include "internal.h"


//:PRIVATE
typedef struct pair_st {
    struct pair_st* prev;
    struct pair_st* next;

    char* key;
} pair_t;
typedef pair_t* dict_it;
#define iskeyequal(a, b) (                        \
    (a) == (b) || /* allow usage of uintptr_t */  \
    strcmp((a), (b)) == 0                         \
)
#define _dict ((dict_t*)dict)
#define _pair ((pair_t*)pair)

//:PUBLIC
void* dict_set(void* dict, char* key, void* pair){
    if(dict == NULL){ return NULL; }

    dict_it tmp = dict_get(dict, key);
    if(pair == NULL){
        if(tmp == NULL){ return NULL; }

        // delete
        list_remove(dict, tmp);
        tmp->prev = NULL;
        tmp->next = NULL;
        return tmp;
    }else{
        // validate key
        if(!iskeyequal(key, _pair->key)){
            _pair->key = key;
        }

        if(tmp == NULL){
            // create new
            list_push_back(_dict, pair);
        }else{
            // swap
            list_swap(dict, tmp, pair);
        }
    }

    return tmp;
}
void* dict_get(void* dict, char* key){
    if(dict == NULL){ return NULL; }
    for(dict_it it = _dict->tail; it != NULL; it = it->prev){
        if(iskeyequal(key, it->key)){
            return it;
        }
    }
    return NULL;
}
char** dict_getKeys(void* dict){
    if(dict == NULL){ return NULL; }

    char** keys = NULL;
    for(dict_it it = _dict->head; it != NULL; it = it->next){
        array_push(&keys, it->key);
    }

    return keys;
}
