#include <ctools/json.h>
#include "internal.h"


//:PRIVATE
json_pair_t* json_getByKey(json_t* json, char* key){
    if(
        json == NULL ||
        json->type != JSON_OBJECT ||
        key == NULL
    ){
        return NULL;
    }

    json_pair_t* tmp = dict_get(&(json->data.object), key);
    if(tmp == NULL){ return NULL; }

    return tmp;
}
#define item ((json_item_t*)it)
json_item_t* json_getByIndex(json_t* json, size_t index){
    if(
        json == NULL ||
        json->type != JSON_ARRAY
    ){
        return NULL;
    }

    size_t i, j;
    list_it it;
    for(
        // Init
        i = 0,
        j = index,
        it = json->data.array.head;
        // Cond
        it != NULL &&
        j != 0;
        // Iterate
        it = it->next,
        j--,
        i++
    );

    if(i != j){ return NULL; }

    return item;
}

//:PUBLIC
json_t* json_getValueByKey(json_t* json, char* key){
    json_pair_t* tmp = json_getByKey(json, key);
    if(tmp == NULL){ return NULL; }

    return &(tmp->value);
}
json_t* json_getValueByIndex(json_t* json, size_t index){
    json_item_t* tmp = json_getByIndex(json, index);
    if(tmp == NULL){ return NULL; }

    return &(tmp->value);
}
int json_deleteByKey(json_t* json, char* key){
    json_pair_t* tmp = json_getByKey(json, key);
    if(tmp == NULL){ return -1; }

    list_remove(&(json->data.object), tmp);
    json_pair_destroy(tmp);

    return 0;
}
int json_deleteByIndex(json_t* json, size_t index){
    json_item_t* tmp = json_getByIndex(json, index);
    if(tmp == NULL){ return -1; }

    list_remove(&(json->data.array), tmp);
    json_item_destroy(tmp);

    return 0;
}

json_t* json_addEntry(json_t* json, char* key){
    if(
        json == NULL ||
        json->type != JSON_OBJECT ||
        key == NULL
    ){
        return NULL;
    }

    json_pair_t* tmp = dict_get(&(json->data.object), key);
    if(tmp != NULL){ return NULL; }

    tmp = malloc(sizeof(json_pair_t));
    if(tmp == NULL){ return NULL; }

    memset(tmp, 0, sizeof(json_pair_t));
    tmp->key = strdup(key);
    if(tmp->key == NULL){
        free(tmp);
        return NULL;
    }
    list_push_back(&(json->data.object), tmp);

    return &(tmp->value);
}
json_t* json_addItem(json_t* json){
    if(
        json == NULL ||
        json->type != JSON_ARRAY
    ){
        return NULL;
    }

    json_item_t* tmp = malloc(sizeof(json_item_t));
    if(tmp == NULL){ return NULL; }

    memset(tmp, 0, sizeof(json_item_t));
    list_push_back(&(json->data.array), tmp);

    return &(tmp->value);
}
/*
int json_set(json_t* json, json_t value){
    if(json == NULL){ return -1; }
    
    json_wipe(json);
    memcpy(json, &value, sizeof(json_t));
    return 0;
}
*/
int json_set_(json_t* json, int type, uintptr_t value){
    if(json == NULL){ return -1; }
    
    json_wipe(json);
    json_value_t tmp = {0};
    tmp.type = type;
    tmp.data.string = (char*)value;
    memcpy(json, &tmp, sizeof(json_t));
    return 0;
}

json_t* json_create(){
    json_t* tmp = malloc(sizeof(json_t));
    if(tmp == NULL){ return NULL; }

    memset(tmp, 0, sizeof(json_t));
    return tmp;
}
