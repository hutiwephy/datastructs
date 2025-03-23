#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctools/dict.h>

int main(int argc, char* argv[]){
    
    typedef struct mypair_st {
        struct mypair_st* prev;
        struct mypair_st* next;
    
        char* key;
        char* value;
    } mypair_t;
    dict_t mydictionary = new_dict;
    
    // Create a new entry
    mypair_t* entry = malloc(sizeof(mypair_t));
    *entry = (mypair_t){NULL, NULL, strdup("greeting"), strdup("Hello, world!")};
    
    // Add to dictionary
    dict_set(&mydictionary, "greeting", entry);
    
    // Read from dictionary
    printf("Greetings: %s", ((mypair_t*)dict_get(&mydictionary, "greeting"))->value);
    
    // Delete from dictionary
    entry = dict_set(&mydictionary, "greeting", DICT_DELETE);
    
    // Destroy entry
    free(entry->key);
    free(entry->value);
    free(entry);

    getchar();
    return 0;
}
