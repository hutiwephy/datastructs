# Datastructs
Extended Data Structures and Functionality for the C language

This library aims to provide support for arrays, lists, dictionaries and much more to the C language. 

## Contents
- [Adding to a CMake Project](#adding-to-a-cmake-project)
- [Documentation](#documentation)
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
  - [Dictionary](#dict)
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
## Array
An array is a `NULL` terminated **array of pointers**, that when empty it's just `NULL`
<br>
<br><br>

<!-- array_length -->
### - <span id="array_length"></span>`size_t array_length(void* array)`
Dertermines the length of an array an returns, however it ignores the `NULL` terminator in order to assert the memory size of the array it is necessary to add 1 `sizeof(void*)`

**Parameters**:
- `void* array`: Address of an array

**Returns**
- `size_t`: Number of items in the array
<br>
<br><br>

<!-- array_push -->
### - <span id="array_push"></span>`int array_push(void* array, void* item)`
Insert an item to the start of the array

**Parameters**:
- `void* array`: Address of an array
- `void* item`: Pointer to add to list

**Returns**:
- `int`: Number of added items if zero then assume error
<br>
<br><br>

<!-- array_push_back -->
### - <span id="array_push_back"></span>`int array_push_back(void* array, void* item)`
Insert an item to the end of the array

**Parameters**:
- `void* array`: Address of an array
- `void* item`: Pointer to add to list

**Returns**:
- `int`: Number of added items if zero then assume error
<br>
<br><br>

<!-- array_insert -->
### - <span id="array_insert"></span>`int array_insert(void* array, size_t index, void* item)`
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
### - <span id="array_pop"></span>`void* array_pop(void* array);`
Remove an item from the start of the array

**Parameters**:
- `void* array`: Address of an array

**Returns**:
- `void*`: Item removed from the array (please free this memory)
<br>
<br><br>

<!-- array_pop_back -->
### - <span id="array_pop_back"></span>`void* array_pop_back(void* array);`
Remove an item from the end of the array

**Parameters**:
- `void* array`: Address of an array

**Returns**:
- `void*`: Item removed from the array (please free this memory)
<br>
<br><br>

<!-- array_remove -->
### - <span id="array_remove"></span>`void* array_remove(void* array, size_t index)`
Remove an item from the end of the array

**Parameters**:
- `void* array`: Address of an array
- `size_t index`: Index of the item to remove

**Returns**:
- `void*`: Item removed from the array (please free this memory)
<br>
<br><br>

<!-- array_destroy -->
### - <span id="array_destroy"></span>`void array_destroy(void* array, void (*destructor)(void*))`
Destroy an array and call a destructor for each item inside the array

**Parameters**:
- `void* array`: Address of an array
- `void (*destructor)(void*)`: function to free up the item's memory can be `NULL` (ex: `&free`)
<br>
<br><br>

## List
A List is any structure with a previous and next pointer in it's beginning

Example:
```c
typedef struct mystruct_st {
    struct mystruct_st* prev;
    struct mystruct_st* next;

    ...
} mystruct_t;
```
>**WARNING**: you are responsible for allocating and deallocating all of these these functions only provide generic [doubly linked list](https://en.wikipedia.org/wiki/Doubly_linked_list) operations.

<br>

<!-- list_push -->
### - <span id="list_push"></span>`int list_push(void* head, void* tail, void* item)`
Add an item to the start of the list

**Parameters**:
- `void* head`: address to the pointer of the first item in the list
- `void* tail`: address to the pointer of the last item in the list
- `void* item`: pointer to the item to be added

**Returns**:
- `int`: number of added items if 0 then assume error

**Example**:
```c
mystruct_t* head = NULL;
mystruct_t* tail = NULL;

...

int res = list_push(&head, &tail, item);
if(res == 0){
    /// Handle error
}
```
<br><br>

<!-- list_push -->
### - <span id="list_push_back"></span>`int list_push_back(void* head, void* tail, void* item)`
Add an item to the end of the list

**Parameters**:
- `void* head`: address to the pointer of the first item in the list
- `void* tail`: address to the pointer of the last item in the list
- `void* item`: pointer to the item to be added

**Returns**:
- `int`: number of added items if 0 then assume error

**Example**:
```c
mystruct_t* head = NULL;
mystruct_t* tail = NULL;

...

int res = list_push_back(&head, &tail, item);
if(res == 0){
    /// Handle error
}
```
<br><br>

<!-- list_pop -->
### - <span id="list_pop"></span>`int list_pop(void* head, void* tail)`
Remove the first item in a list

**Parameters**:
- `void* head`: address to the pointer of the first item in the list
- `void* tail`: address to the pointer of the last item in the list

**Returns**:
- `void*`: item that was removed

**Example**:
```c
mystruct_t* head = NULL;
mystruct_t* tail = NULL;

...

void* item = list_pop(&head, &tail);
if(item == NULL){
    /// Handle error or assume empty
}
free(item);
```
<br><br>

<!-- list_pop_back -->
### - <span id="list_pop_back"></span>`int list_pop_back(void* head, void* tail)`
Remove the last item in a list

**Parameters**:
- `void* head`: address to the pointer of the first item in the list
- `void* tail`: address to the pointer of the last item in the list

**Returns**:
- `void*`: item that was removed

**Example**:
```c
mystruct_t* head = NULL;
mystruct_t* tail = NULL;

...

void* item = list_pop_back(&head, &tail);
if(item == NULL){
    /// Handle error or assume empty
}
free(item);
```
<br><br>

<!-- list_insert -->
### - <span id="list_insert"></span>`int list_insert(void* head, void* tail, void* it, void* item)`
Add an item to a List before the iterator's location

**Parameters**:
- `void* head`: address to the pointer of the first item in the list
- `void* tail`: address to the pointer of the last item in the list
- `void* it`: iterator (pointer to a list item)
- `void* item`: pointer to the item to be added

**Returns**:
- `int`: number of added items if 0 then assume error
<br>
<br><br>

<!-- list_append -->
### - <span id="list_append"></span>`int list_append(void* head, void* tail, void* it, void* item)`
Add an item to a List after the iterator's location

**Parameters**:
- `void* head`: address to the pointer of the first item in the list
- `void* tail`: address to the pointer of the last item in the list
- `void* it`: iterator (pointer to a list item)
- `void* item`: pointer to the item to be added

**Returns**:
- `int`: number of added items if 0 then assume error
<br>
<br><br>

<!-- list_remove -->
### - <span id="list_remove"></span>`void* list_remove(void* head, void* tail, void* it)`
Add an item to a List after the iterator's location

**Parameters**:
- `void* head`: address to the pointer of the first item in the list
- `void* tail`: address to the pointer of the last item in the list
- `void* it`: iterator (pointer to a list item)

**Returns**:
- `void*`: item that was removed
<br>
<br><br>

<!-- list_remove -->
### - <span id="list_swap"></span>`void list_swap(void* head, void* tail, void* a, void* b)`
Switch the position of 2 items on a list

**Parameters**:
- `void* head`: address to the pointer of the first item in the list
- `void* tail`: address to the pointer of the last item in the list
- `void* a`: pointer to a list item
- `void* b`: pointer to a list item
<br>
<br><br>

## Dictionary
A Dictionary consists of a [doubly linked list](https://en.wikipedia.org/wiki/Doubly_linked_list) that pairs a string to a pointer to some user defined data.

Example:
```c
dict_t mydictionary = new_dict;

char* str = strdup("Hello, world!");
dict_set(&mydictionary, "greeting", str);

printf("Greetings: %s", dict_get(&mydictionary, "greeting"));

str = dict_set(&mydictionary, "greeting", DICT_DELETE);
free(str);
```

> **WARNING**: all items passed to the dictionary must be freed by the user

<br>

<!-- dict_isEmpty -->
### - <span id="dict_isEmpty"></span>`bool dict_isEmpty(dict_t* dict)`
Check if a dictionary is empty

**Parameters**:
- `dict_t* dict`: pointer to a dictionary

**Returns**:
- `bool`: true if empty otherwise false aka. 0
<br>
<br><br>

<!-- dict_set -->
### - <span id="dict_set"></span>`void* dict_set(dict_t* dict, char* key, void* value)`
Set a value to a key.<br>
If `value` is `NULL` or `DICT_DELETE` then this pair will be erased.<br>
The return value is all ways the old value or `NULL` if it is a new entry.

**Parameters**:
- `dict_t* dict`: pointer to a dictionary
- `char* key`: key to look for
- `void* value`: new value (`NULL` will result in deletition of the pair)

**Returns**:
- `void*`: old value (free this value)
<br>
<br><br>

<!-- dict_get -->
### - <span id="dict_get"></span>`void* dict_get(dict_t* dict, char* key)`
Get a value of a key.

**Parameters**:
- `dict_t* dict`: pointer to a dictionary
- `char* key`: key to look for

**Returns**:
- `void*`: value stored at the requested key or `NULL` if non-existing
<br>
<br><br>

<!-- dict_getKeys -->
### - <span id="dict_getKeys"></span>`char** dict_getKeys(dict_t* dict)`
Get all the keys in a dictionary.

**Parameters**:
- `dict_t* dict`: pointer to a dictionary

**Returns**:
- `char**`: `NULL` terminated array containing all keys in the dictionary.
<br>
<br><br>

<!-- dict_destroy -->
### - <span id="dict_destroy"></span>`void dict_destroy(dict_t* dict, void (*destructor)(void*))`
Destroy a dictionary and free all memory.

**Parameters**:
- `dict_t* dict`: pointer to a dictionary
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