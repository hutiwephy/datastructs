#pragma once

#include <stddef.h>

/**
 * @brief Insert an item at a specified position in raw array
 * 
 * @param memory Address of an array
 * @param itemsize Size of items in array
 * @param length Array length
 * @param index Position to insert item
 * @param item Chunk to copy onto memory
 * @return Number of added items if zero then assume error
 */
int memins(void** memory, size_t itemsize, size_t length, size_t index, void* item);

/**
 * @brief Remove an item at a specified position in raw array
 * 
 * @note all memory related to the item must be freed by your code
 * 
 * @param memory Address of an array
 * @param itemsize Size of items in array
 * @param length Array length
 * @param index Position of item to remove
 * @return Number of removed items if zero then assume error
 */
int memrem(void** memory, size_t itemsize, size_t length, size_t index);

/**
 * @brief Dertermines the length of an array an returns, however it ignores the NULL terminator in order to assert the memory size of the array it is necessary to add 1 sizeof(void*)
 * 
 * @param array Address of an array
 * @return size_t Number of items in the array
 */
size_t array_length(void* array);

/**
 * @brief Insert an item to the start of the array
 * 
 * @param array Address of an array
 * @param item Pointer to add to list
 * @return Number of added items if zero then assume error
 */
int array_push(void* array, void* item);

/**
 * @brief Insert an item to the end of the array
 * 
 * @param array Address of an array
 * @param item Pointer to add to list
 * @return Number of added items if zero then assume error
 */
int array_push_back(void* array, void* item);

/**
 * @brief Insert an item to a specified index in the array
 * 
 * @param array Address of an array
 * @param index Index to insert new item
 * @param item Pointer to add to list
 * @return Number of added items if zero then assume error
 */
int array_insert(void* array, size_t index, void* item);

/**
 * @brief Remove an item from the start of the array
 * 
 * @param array Address of an array
 * @return Item removed from the array (please free this memory)
 */
void* array_pop(void* array);

/**
 * @brief Remove an item from the end of the array
 * 
 * @param array Address of an array
 * @return Item removed from the array (please free this memory)
 */
void* array_pop_back(void* array);

/**
 * @brief Remove an item from the end of the array
 * 
 * @param array Address of an array
 * @param index Index of the item to remove
 * @return Item removed from the array (please free this memory)
 */
void* array_remove(void* array, size_t index);

/**
 * @brief Destroy an array and call a destructor for each item inside the array
 * 
 * @param array Address of an array
 * @param destructor function to free up the item's memory can be `NULL` (ex: `&free`)
 */
void array_destroy(void* array, void (*destructor)(void*));
