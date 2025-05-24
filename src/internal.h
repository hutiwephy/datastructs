#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <asprintf.h>

#define CHUNK_SIZE 512

#ifdef json_t
struct json_pair_st;
typedef struct json_pair_st json_pair_t;

struct json_item_st;
typedef struct json_item_st json_item_t;

void json_pair_destroy(json_pair_t* pair);
void json_item_destroy(json_item_t* item);
#define json_value_destroy json_destroy
void json_wipe(json_t* json);
#endif

void* memcatcpy(void* a, size_t a_size, void* b, size_t b_size);
char* strcatcpy(char* a, char* b);
