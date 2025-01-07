#pragma once

#include <stddef.h>


int memins(void** memory, size_t itemsize, size_t length, size_t index, void* item);
int memrem(void** memory, size_t itemsize, size_t length, size_t index);

size_t array_length(void* array);
int array_push(void* array, void* item);
int array_push_back(void* array, void* item);
int array_insert(void* array, size_t index, void* item);
void* array_pop(void* array);
void* array_pop_back(void* array);
void* array_remove(void* array, size_t index);
void array_destroy(void* array, void (*destructor)(void*));
