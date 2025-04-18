# Datastructs
Extended Data Structures and Functionality for the C language

This library aims to provide support for arrays, lists, dictionaries and much more to the C language. 

## Contents
- [Adding to a CMake Project](#adding-to-a-cmake-project)
- [Documentation](#documentation)
  - [memins](#memins)
  - [memrem](#memrem)
  - [Array](#array)
    - [length](#array_length)
    - [push](#array_push)
    - [push_back](#array_push_back)
    - [insert](#array_insert)
    - [pop](#array_pop)
    - [pop_back](#array_pop_back)
    - [remove](#array_remove)
    - [destroy](#array_destroy)
  - [List](#list)
    - [push](#list_push)
    - [push_back](#list_push_back)
    - [pop](#list_pop)
    - [pop_back](#list_pop_back)
    - [insert](#list_insert)
    - [append](#list_append)
    - [remove](#list_remove)
    - [swap](#list_swap)
  - [Dictionary](#dictionary)
    - [isEmpty](#dict_isEmpty)
    - [set](#dict_set)
    - [get](#dict_get)
    - [getKeys](#dict_getKeys)
    - [destroy](#dict_destroy)
- [License](#license)


## Adding to a CMake Project
In the `CMakeLists.txt` before the targets add:
```cmake
include(FetchContent)

FetchContent_Declare(
    CTOOLS_DATASTRUCTS
    GIT_REPOSITORY https://github.com/hutiwephy/datastructs.git
    GIT_TAG master
)
FetchContent_MakeAvailable(CTOOLS_DATASTRUCTS)
```
and after the target declaration add:
```cmake
target_link_libraries(your_target CTOOLS::datastructs)
```

## Documentation
<!-- Add Introduction here -->
## Memory
Complementary memory operations found on the array header.
<br>
<br><br>

<!-- memins -->
### <span id="memins"></span>`int memins(void** memory, size_t itemsize, size_t length, size_t index, void* item)`
Insert an item at a specified position in raw array

**Parameters**:
- `void** memory`: Address of an array
- `size_t itemsize`: Size of items in array
- `size_t length`: Array length
- `size_t index`: Position to insert item
- `void* item`: Chunk to copy onto memory

**Returns**:
- `int`: Number of added items if zero then assume error
<br>
<br><br>

<!-- memins -->
### <span id="memrem"></span>`int memrem(void** memory, size_t itemsize, size_t length, size_t index)`
Remove an item at a specified position in raw array
> NOTE: all memory related to the item must be freed by your code

**Parameters**:
- `void** memory`: Address of an array
- `size_t itemsize`: Size of items in array
- `size_t length`: Array length
- `size_t index`: Position of item to remove

**Returns**:
- `int`: Number of removed items if zero then assume error
<br>
<br><br>

## Array
An array is a `NULL` terminated **array of pointers**, that when empty it's just `NULL`
<br>
<br><br>

<!-- array_length -->
### <span id="array_length"></span>`size_t array_length(void* array)`
Dertermines the length of an array an returns, however it ignores the `NULL` terminator in order to assert the memory size of the array it is necessary to add 1 `sizeof(void*)`

**Parameters**:
- `void* array`: Address of an array

**Returns**
- `size_t`: Number of items in the array
<br>
<br><br>

<!-- array_push -->
### <span id="array_push"></span>`int array_push(void* array, void* item)`
Insert an item to the start of the array

**Parameters**:
- `void* array`: Address of an array
- `void* item`: Pointer to add to list

**Returns**:
- `int`: Number of added items if zero then assume error
<br>
<br><br>

<!-- array_push_back -->
### <span id="array_push_back"></span>`int array_push_back(void* array, void* item)`
Insert an item to the end of the array

**Parameters**:
- `void* array`: Address of an array
- `void* item`: Pointer to add to list

**Returns**:
- `int`: Number of added items if zero then assume error
<br>
<br><br>

<!-- array_insert -->
### <span id="array_insert"></span>`int array_insert(void* array, size_t index, void* item)`
Insert an item to a specified index in the array

**Parameters**:
- `void* array`: Address of an array
- `size_t index`: Index to insert new item
- `void* item`: Pointer to add to list

**Returns**:
- `int`: Number of added items if zero then assume error
<br>
<br><br>

<!-- array_pop -->
### <span id="array_pop"></span>`void* array_pop(void* array);`
Remove an item from the start of the array

**Parameters**:
- `void* array`: Address of an array

**Returns**:
- `void*`: Item removed from the array (please free this memory)
<br>
<br><br>

<!-- array_pop_back -->
### <span id="array_pop_back"></span>`void* array_pop_back(void* array);`
Remove an item from the end of the array

**Parameters**:
- `void* array`: Address of an array

**Returns**:
- `void*`: Item removed from the array (please free this memory)
<br>
<br><br>

<!-- array_remove -->
### <span id="array_remove"></span>`void* array_remove(void* array, size_t index)`
Remove an item from the end of the array

**Parameters**:
- `void* array`: Address of an array
- `size_t index`: Index of the item to remove

**Returns**:
- `void*`: Item removed from the array (please free this memory)
<br>
<br><br>

<!-- array_destroy -->
### <span id="array_destroy"></span>`void array_destroy(void* array, void (*destructor)(void*))`
Destroy an array and call a destructor for each item inside the array

**Parameters**:
- `void* array`: Address of an array
- `void (*destructor)(void*)`: function to free up the item's memory can be `NULL` (ex: `&free`)
<br>
<br><br>

## List
A List is any structure with a head and a tail in its beginning its nodes also need a previous and next pointer in it's beginning

Example:
```c
typedef struct mylistnode_st {
    struct mylistnode_st* prev;
    struct mylistnode_st* next;

    ...
} mylistnode_t;

typedef struct mylist_st {
    mylistnode_t* head;
    mylistnode_t* tail;

    ...
} mylist_t;

```
>**WARNING**: you are responsible for allocating and deallocating all of these these functions only provide generic [doubly linked list](https://en.wikipedia.org/wiki/Doubly_linked_list) operations.

<br>

<!-- list_push -->
### <span id="list_push"></span>`int list_push(void* list, void* item)`
Add an item to the start of the list

**Parameters**:
- `void* list`: address to a struct containing the head and tail pointers in it's start
- `void* item`: pointer to the item to be added

**Returns**:
- `int`: number of added items if 0 then assume error

**Example**:
```c
mylist_t list = (mylist_t){NULL, NULL};

...

int res = list_push(&list, item);
if(res == 0){
    /// Handle error
}
```
<br><br>

<!-- list_push -->
### <span id="list_push_back"></span>`int list_push_back(void* list, void* item)`
Add an item to the end of the list

**Parameters**:
- `void* list`: address to a struct containing the head and tail pointers in it's start
- `void* item`: pointer to the item to be added

**Returns**:
- `int`: number of added items if 0 then assume error

**Example**:
```c
mylist_t list = (mylist_t){NULL, NULL};

...

int res = list_push_back(&list, item);
if(res == 0){
    /// Handle error
}
```
<br><br>

<!-- list_pop -->
### <span id="list_pop"></span>`int list_pop(void* list)`
Remove the first item in a list

**Parameters**:
- `void* list`: address to a struct containing the head and tail pointers in it's start

**Returns**:
- `void*`: item that was removed

**Example**:
```c
mylist_t list = (mylist_t){NULL, NULL};

...

void* item = list_pop(&list);
if(item == NULL){
    /// Handle error or assume empty
}
free(item);
```
<br><br>

<!-- list_pop_back -->
### <span id="list_pop_back"></span>`int list_pop_back(void* list)`
Remove the last item in a list

**Parameters**:
- `void* list`: address to a struct containing the head and tail pointers in it's start

**Returns**:
- `void*`: item that was removed

**Example**:
```c
mylist_t list = (mylist_t){NULL, NULL};

...

void* item = list_pop_back(&list);
if(item == NULL){
    /// Handle error or assume empty
}
free(item);
```
<br><br>

<!-- list_insert -->
### <span id="list_insert"></span>`int list_insert(void* list, void* it, void* item)`
Add an item to a List before the iterator's location

**Parameters**:
- `void* list`: address to a struct containing the head and tail pointers in it's start
- `void* it`: iterator (pointer to a list item)
- `void* item`: pointer to the item to be added

**Returns**:
- `int`: number of added items if 0 then assume error
<br>
<br><br>

<!-- list_append -->
### <span id="list_append"></span>`int list_append(void* list, void* it, void* item)`
Add an item to a List after the iterator's location

**Parameters**:
- `void* list`: address to a struct containing the head and tail pointers in it's start
- `void* it`: iterator (pointer to a list item)
- `void* item`: pointer to the item to be added

**Returns**:
- `int`: number of added items if 0 then assume error
<br>
<br><br>

<!-- list_remove -->
### <span id="list_remove"></span>`void* list_remove(void* list, void* it)`
Add an item to a List after the iterator's location

**Parameters**:
- `void* list`: address to a struct containing the head and tail pointers in it's start
- `void* it`: iterator (pointer to a list item)

**Returns**:
- `void*`: item that was removed
<br>
<br><br>

<!-- list_remove -->
### <span id="list_swap"></span>`void list_swap(void* list, void* a, void* b)`
Switch the position of 2 items on a list

**Parameters**:
- `void* list`: address to a struct containing the head and tail pointers in it's start
- `void* a`: pointer to a list item
- `void* b`: pointer to a list item
<br>
<br><br>

## Dictionary
A Dictionary consists of a [doubly linked list](https://en.wikipedia.org/wiki/Doubly_linked_list) that contains pairs, each pair as a key and some data.

The suported key formats are `char*` and `uintptr_t`.

These methods only provide common operations and you are responsible for any memory allocation.

A valid Dictionary structure must be similar to (a default one is provided as `dict_t`):
```c
typedef struct dict_st {
    struct mypair_st* head;
    struct mypair_st* tail;

    ...
} dict_t;
```
while a valid Pair structure must be:
```c
typedef struct pair_st {
    struct pair_st* prev;
    struct pair_st* next;

    char* key;
    ...
} pair_t;
```

Example:
```c
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
```

> **WARNING**: all items passed to the dictionary must be freed by the user

<br>

<!-- dict_isEmpty -->
### <span id="dict_isEmpty"></span>`bool dict_isEmpty(void* dict)`
Check if a dictionary is empty

**Parameters**:
- `void* dict`: pointer to a dictionary

**Returns**:
- `bool`: true if empty otherwise false aka. 0
<br>
<br><br>

<!-- dict_set -->
### <span id="dict_set"></span>`void* dict_set(void* dict, char* key, void* value)`
Set a value to a key.<br>
If `value` is `NULL` or `DICT_DELETE` then this pair will be erased.<br>
The return value is all ways the old value or `NULL` if it is a new or non existent entry.

**Parameters**:
- `void* dict`: pointer to a dictionary
- `char* key`: key to look for
- `void* value`: new value (`NULL` will result in the removal of the pair)

**Returns**:
- `void*`: old value (free this value)
<br>
<br><br>

<!-- dict_get -->
### <span id="dict_get"></span>`void* dict_get(void* dict, char* key)`
Get a pair of a key.

**Parameters**:
- `void* dict`: pointer to a dictionary
- `char* key`: key to look for

**Returns**:
- `void*`: pair stored at the requested key or `NULL` if non-existing
<br>
<br><br>

<!-- dict_getKeys -->
### <span id="dict_getKeys"></span>`char** dict_getKeys(void* dict)`
Get all the keys in a dictionary.

**Parameters**:
- `void* dict`: pointer to a dictionary

**Returns**:
- `char**`: `NULL` terminated array containing all keys in the dictionary. (use free when no longer needed)
<br>
<br><br>

<!-- dict_destroy -->
### <span id="dict_destroy"></span>`void dict_destroy(void* dict, void (*destructor)(void*))`
Destroy a dictionary and free all memory.

**Parameters**:
- `void* dict`: pointer to a dictionary
- `void (*destructor)(void*)`: function to free up the item's memory can be `NULL` (ex: `&free`)
<br>
<br><br>

## License
```

   Copyright 2024 hutiwephy

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

```
