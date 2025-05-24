#include "internal.h"


#define _memory ((uint8_t*)(*memory))
#define _tmp ((uint8_t*)(tmp))

int memins(void** memory, size_t itemsize, size_t length, size_t index, void* item){
    if(memory == NULL){ return 0; }

    // allocate new memory with 1 more item
    void* tmp = malloc((length+1)*itemsize);
    if(tmp == NULL){ return 0; }

    // if old memory is not NULL then copy to new memory but jump index position
    if(*memory != NULL){
        memcpy(_tmp, _memory, index*itemsize); // copy everything until index

        memcpy(
            _tmp+((index+1)*itemsize),  // begin placing at index+1
            _memory+((index)*itemsize), // begin copying from index position
            ((length-index))*itemsize   // copy everything after index
        );

        free(*memory);
    }

    memcpy(_tmp+(index*itemsize), item, itemsize);

    *memory = tmp;
    return 1;
}
int memrem(void** memory, size_t itemsize, size_t length, size_t index){
    if(memory == NULL || *memory == NULL){ return 0; }

    // allocate new memory with 1 less item
    void* tmp = malloc((length-1)*itemsize);
    if(tmp == NULL){ return 0; }

    // copy everything before index
    memcpy(tmp, *memory, index*itemsize);
    // copy everything after index
    memcpy(_tmp+(index*itemsize), _memory+((index+1)*itemsize), (length-(index+1))*itemsize);

    // set old memory equal to new memory
    free(*memory);
    *memory = tmp;

    return 1;
}

void* memcatcpy(void* a, size_t a_size, void* b, size_t b_size){
    if(a == NULL && b == NULL){ return NULL; }

    void* tmp = malloc(a_size + b_size);
    if(tmp == NULL){ return NULL; }

    memcpy(tmp, a, a_size);
    memcpy(_tmp+a_size, b, b_size);

    return tmp;
}

char* strcatcpy(char* a, char* b){
    if(b == NULL){ return NULL; }

    size_t a_size = (a == NULL)? 0 : strlen(a);
    size_t b_size = strlen(b);

    return memcatcpy(a, a_size, b, b_size+1);
}
