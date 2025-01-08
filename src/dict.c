#include <ctools/array.h>
#include <ctools/list.h>
#include <ctools/dict.h>
#include "internal.h"


//:PRIVATE
#define _head (&(dict->head))
#define _tail (&(dict->tail))
#define _pair ((pair_t*)pair)
void* dict_splice(dict_t* dict, dict_it it){
    list_remove(dict, it);
    void* tmp = it->value;
    free(it->key);
    free(it);
    return tmp;
}
pair_t* dict_getPair(dict_t* dict, char* key){
    for(dict_it it = dict->head; it != NULL; it = it->next){
        if(strcmp(it->key, key) == 0){ return it; }
    }
    return NULL;
}

//:PUBLIC
void* dict_set(dict_t* dict, char* key, void* value){
    dict_it it = dict_getPair(dict, key);

    // If value is NULL then delete entry
    if(value == NULL){
        if(it == NULL){ return NULL; }
        
        return dict_splice(dict, it);
    }

    // If entry not existant then create a new one
    if(it == NULL){
        it = calloc(1, sizeof(pair_t));
        if(it == NULL){ return NULL; }

        it->key = strdup(key);

        list_push(dict, it);
    }

    // Swap the value and return the old one
    void* tmp = it->value;
    it->value = value;
    return tmp;
}
void* dict_get(dict_t* dict, char* key){
    dict_it it = dict_getPair(dict, key);
    return (it == NULL)? NULL : it->value;
}
char** dict_getKeys(dict_t* dict){
    if(dict == NULL){ return NULL; }

    char** keys = NULL;
    for(dict_it it = dict->head; it != NULL; it = it->next){
        array_push(&keys, it->key);
    }

    return keys;
}
void dict_destroy(dict_t* dict, void (*destructor)(void*)){
    if(dict == NULL){ return; }

    dict_it it = dict->head;

    while(it != NULL){
        dict_it tmp = it->next;
        
        if(destructor != NULL){
            destructor(it->value);
        }
        free(it->key);
        free(it);
        it = tmp;
    }

    dict->head = NULL;
    dict->tail = NULL;
}
