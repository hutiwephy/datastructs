#pragma once

#include <ctools/list.h>


typedef struct dict_st {
    void* head;
    void* tail;
} dict_t;
#define new_dict (dict_t){NULL, NULL}
#define DICT_DELETE NULL

/**
 * @brief Set a value to a key.
 * If value is `NULL` or `DICT_DELETE` then this pair will be erased.
 * The return value is all ways the old pair structure or `NULL` if it is a new or non existent entry.
 * 
 * @warning if the passed `key` value is not equal to the `pair->key` value then strcpy will be used
 * @note the key can be a `uintptr_t` value as the matching function will check if the pointer values are equal first and then it will do strcmp (this may trigger some error)
 * 
 * @param dict pointer to a dictionary compatible structure
 * @param key key to look for
 * @param pair pair to replace old one
 * @return old pair value (free this value)
 */
void* dict_set(void* dict, char* key, void* pair);

/**
 * @brief Get a pair of a key.
 * 
 * @param dict pointer to a dictionary compatible structure
 * @param key key to look for
 * @return pair stored at the requested key or NULL if non-existing
 */
void* dict_get(void* dict, char* key);

/**
 * @brief Get all the keys in a dictionary.
 * 
 * @param dict pointer to a dictionary
 * @return NULL terminated array containing all keys in the dictionary. (use free when no longer needed)
 */
char** dict_getKeys(void* dict);

/**
 * @brief Destroy a dictionary and free all memory.
 * 
 * @param dict pointer to a dictionary
 * @param destructor function to free up the pair's memory can be NULL (ex: &free)
 */
#define dict_destroy(dict, destructor) list_destroy(dict, destructor)
