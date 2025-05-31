#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctools/list.h>
#include <ctools/dict.h>


enum json_parsererrors {
    JSON_PE_UNKNOWN = 0x80000000,
    JSON_PE_MEMORY,
    JSON_PE_STRINGLEN,
    JSON_PE_EXPECTEDTRUE,
    JSON_PE_EXPECTEDFALSE,
    JSON_PE_EXPECTEDNULL,
    JSON_PE_INVALIDCHAR,
    JSON_PE_INVALIDESCAPE,
    JSON_PE_UNICODEUNSUPPORTED,
    JSON_PE_UNEXPECTEDCHAR,
    JSON_PE_EXPECTEDPAIR,
};

enum json_datatype {
    JSON_NULL   = 0,
    JSON_OBJECT = 8,
    JSON_ARRAY  = 4,
    JSON_STRING = 1,
    JSON_NUMBER = 2,
    JSON_BOOL   = 3,
};

typedef struct json_value_st {
    union {
        dict_t object;
        list_t array;
        char* string;
        double number;
        bool boolean;
    } data;
    int type;
} json_value_t;

typedef struct json_pair_st {
    struct json_pair_st* prev;
    struct json_pair_st* next;

    char* key;
    json_value_t value;
} json_pair_t;

typedef struct json_item_st {
    struct json_item_st* prev;
    struct json_item_st* next;

    json_value_t value;
} json_item_t;

#define json_t json_value_t

/**
 * @brief Returns a JSON Object iterator
 * 
 * @param json JSON Value of type object
 */
#define json_getObjectIt(json) ((json_pair_t*)((json->type != JSON_OBJECT)? NULL : json->data.object.head))

/**
 * @brief Returns a JSON Array iterator
 * 
 * @param json JSON Value of type array
 */
#define json_getArrayIt(json) ((json_item_t*)((json->type != JSON_ARRAY)? NULL : json->data.array.head))

/**
 * @brief creates a blank JSON Value
 * 
 * @return pointer to JSON Value
 */
json_t* json_create();

/**
 * @brief Parse a String into a JSON Value
 * 
 * @param str String to parse
 * @return JSON Value
 */
json_t* json_parse(const char* str);

/**
 * @brief Turn a JSON Value back into a string
 * 
 * @param json JSON Value
 * @param ident set this to a value above 0 to enable pretty print
 * @return char* 
 */
char* json_stringify(json_t* json, int ident);


/**
 * @brief Access a Object key value
 * 
 * @param json JSON Object
 * @param key Key to look for
 * @return JSON Value
 */
json_t* json_getValueByKey(json_t* json, char* key);

/**
 * @brief Access an Array key value
 * 
 * @param json JSON Array
 * @param index Index to access
 * @return JSON Value
 */
json_t* json_getValueByIndex(json_t* json, size_t index);

/**
 * @brief Delete a Object key value
 * 
 * @param json JSON Object
 * @param key Key to look for
 * @return 0 on success
 */
int json_deleteByKey(json_t* json, char* key);

/**
 * @brief Delete a Array key value
 * 
 * @param json JSON Array
 * @param index Index to access
 * @return 0 on success
 */
int json_deleteByIndex(json_t* json, size_t index);

/**
 * @brief Adds a null entry to an Object
 * 
 * @param json JSON Object
 * @param key Key to create
 * @return JSON Value created
 */
json_t* json_addEntry(json_t* json, char* key);

/**
 * @brief Adds a null entry to an Array
 * 
 * @param json JSON Array
 * @return JSON Value created
 */
json_t* json_addItem(json_t* json);

#define json_isDefined(json) (json != NULL)
#define json_isNull(json) (json->type == JSON_NULL)
#define json_isObject(json) (json->type == JSON_OBJECT)
#define json_isArray(json) (json->type == JSON_ARRAY)
#define json_isString(json) (json->type == JSON_STRING)
#define json_isNumber(json) (json->type == JSON_NUMBER)
#define json_isBool(json) (json->type == JSON_BOOL)

#define json_getString(json) (json->data.string)
#define json_getNumber(json) (json->data.number)
#define json_getBool(json) (json->data.boolean)

//:PRIVATE (don't use)
int json_set_(json_t* json, int type, uintptr_t value);

/**
 * @brief Changes a JSON Value
 * 
 * @param json JSON Value
 * @param type type to set
 * @param value value to store
 * @return 0 on success
 */
#define json_set(json, type, value) json_set_(json, type, (uintptr_t)value)

/**
 * @brief Destroy a JSON Value
 * 
 * @param json JSON Value
 */
void json_destroy(json_t* json);

/**
 * @brief Get the last Parser error
 * 
 * @param message Error string
 * @param index Error location (by character index)
 * @return Error code
 */
int json_getParserError(char** message, size_t* index);
