#pragma once


typedef void (*destructor_t)(void*);
typedef struct list_st {
    void* head;
    void* tail;
} list_t;
typedef struct list_item_st {
    struct list_item_st* prev;
    struct list_item_st* next;
} list_item_t;
typedef struct list_item_st* list_it;

/**
 * @brief Check if a list is empty
 * 
 * @param list address to a struct containing the head and tail pointers in it's start
 * @return true if empty
 */
#define list_isEmpty(list) (list->head == NULL)

/**
 * @brief Add an item to the start of the list
 * 
 * @param list address to a struct containing the head and tail pointers in it's start
 * @param item pointer to the item to be added
 * @return number of added items if 0 then assume error
 */
#define list_push(list, item) list_insert(list, (list)->head, item)

/**
 * @brief Add an item to the end of the list
 * 
 * @param list address to a struct containing the head and tail pointers in it's start
 * @param item pointer to the item to be added
 * @return number of added items if 0 then assume error
 */
#define list_push_back(list, item) list_append(list, (list)->tail, item)

/**
 * @brief Remove the first item in a list
 * 
 * @param list address to a struct containing the head and tail pointers in it's start
 * @return item that was removed
 */
#define list_pop(list) list_remove(list, (list)->head)

/**
 * @brief Remove the last item in a list
 * 
 * @param list address to a struct containing the head and tail pointers in it's start
 * @return item that was removed
 */
#define list_pop_back(list) list_remove(list, (list)->tail)

/**
 * @brief Add an item to a List before the iterator's location
 * 
 * @param list address to a struct containing the head and tail pointers in it's start
 * @param it iterator (pointer to a list item)
 * @param item pointer to the item to be added
 * @return number of added items if 0 then assume error
 */
int list_insert(void* list, void* it, void* item);

/**
 * @brief Add an item to a List after the iterator's location
 * 
 * @param list address to a struct containing the head and tail pointers in it's start
 * @param it iterator (pointer to a list item)
 * @param item pointer to the item to be added
 * @return number of added items if 0 then assume error
 */
int list_append(void* list, void* it, void* item);

/**
 * @brief Remove the item in a List pointed by the iterator
 * 
 * @param list address to a struct containing the head and tail pointers in it's start
 * @param it iterator (pointer to a list item)
 * @return item that was removed
 */
void* list_remove(void* list, void* it);

/**
 * @brief Switch the position of 2 items on a list
 * 
 * @param list address to a struct containing the head and tail pointers in it's start
 * @param a pointer to a list item
 * @param b pointer to a list item
 */
void list_swap(void* list, void* a, void* b);

/**
 * @brief Destroy an array and call a destructor for each item inside the array
 * 
 * @param list address to a struct containing the head and tail pointers in it's start
 * @param destructor function to free up the item's memory can be `NULL` (ex: `&free`)
 */
void list_destroy(void* list, void (*destructor)(void*));
