#include <ctools/array.h>
#include "internal.h"


/**
 * IMPORTANT NOTE!
 * 
 * 
 * The array argument is the address of a NULL terminated array of pointers that when empty it's just NULL
 * 
 * void* array; <=> void*** array;
 * 
 * 
 * Therefore *array resolves to the array of pointers.
 * 
 * *array => void** array;
 * 
 * 
 * [Just in case it's still not clear]:
 * 
 * array(address) -> *array
 *                     = NULL (if empty)
 *                     or
 *                       [
 *                         - void*,
 *                         - void*,
 *                         - void*,
 *                         - ...
 *                         - NULL, (indicates the end)
 *                       ]
 * 
 * To keep things cleanish the `_c(array)` macro applies the (void***) cast
 * and the `__c(array)` macro applies the (void***) cast and resolves the address to get the array's starting point (data at that memory address).
 */

//:PRIVATE
#define _c(array) ((void***)array)
#define __c(array) (*_c(array))

//:PUBLIC
size_t array_length(void* array){
    void** t = __c(array);
    if(__c(array) == NULL){ return 0; }
    size_t cnt;
    for(cnt=0; __c(array)[cnt]!=NULL; cnt++);
    return cnt;
}
int array_push(void* array, void* item){
    if(item == NULL){ return 0; }
    register size_t memsize = array_length(array)+1;

    if(memins(array, sizeof(void*), memsize, 0, &item) == 0){ return 0; }

    if(memsize == 1){
        __c(array)[1] = NULL;
    }

    return 1;
}
int array_push_back(void* array, void* item){
    if(item == NULL){ return 0; }
    register size_t memsize = array_length(array)+1;

    if(memins(array, sizeof(void*), memsize, (memsize == 1)? 0 : memsize-2, &item) == 0){ return 0; }

    if(memsize == 1){
        __c(array)[1] = NULL;
    }

    return 1;
}
int array_insert(void* array, size_t index, void* item){
     if(item == NULL){ return 0; }
    register size_t memsize = array_length(array)+1;

    if(index > memsize-1){ return 0; }

    if(memins(array, sizeof(void*), memsize, index, &item) == 0){ return 0; }

    if(memsize == 1){
        __c(array)[1] = NULL;
    }

    return 1;
}
void* array_pop(void* array){
    if(__c(array) == NULL){ return NULL; }

    register size_t memsize = array_length(array)+1;
    void** tmp = NULL;

    void* item = __c(array)[0];

    if(memsize == 2){
        free(__c(array));
        __c(array) = NULL;
    }else if(memrem(array, sizeof(void*), memsize, 0) == 0){ return NULL; }

    return item;
}
void* array_pop_back(void* array){
    if(__c(array) == NULL){ return NULL; }

    register size_t memsize = array_length(array)+1;

    void* item = __c(array)[memsize-2];

    if(memsize == 2){
        free(__c(array));
        __c(array) = NULL;
    }else if(memrem(array, sizeof(void*), memsize, memsize-2) == 0){ return NULL; }

    return item;
}
void* array_remove(void* array, size_t index){
    if(__c(array) == NULL){ return NULL; }

    register size_t memsize = array_length(array)+1;

    if(index > memsize-1){ return NULL; }

    void* item = __c(array)[index];

    if(memsize == 2){
        free(__c(array));
        __c(array) = NULL;
    }else if(memrem(array, sizeof(void*), memsize, index) == 0){ return NULL; }

    return item;
}
void array_destroy(void* array, void (*destructor)(void*)){
    if(__c(array) == NULL){ return; }

    if(destructor != NULL){
        for(size_t i=0; __c(array)[i] != NULL; i++){
            destructor(__c(array)[i]);
        }
    }

    free(__c(array));
    __c(array) = NULL;
}
