#include <ctools/json.h>
#include "internal.h"


//:PRIVATE
void json_pair_destroy(json_pair_t* pair){
    if(pair == NULL){ return; }

    free(pair->key);

    switch(pair->value.type){
        case JSON_OBJECT:
            dict_destroy(&(pair->value.data.object), (destructor_t)&json_pair_destroy);
        case JSON_ARRAY:
            list_destroy(&(pair->value.data.array), (destructor_t)&json_item_destroy);
        case JSON_STRING:
            free(pair->value.data.string);
        default:
            free(pair);
            break;
    }
}
void json_item_destroy(json_item_t* item){
    if(item == NULL){ return; }

    switch(item->value.type){
        case JSON_OBJECT:
            dict_destroy(&(item->value.data.object), (destructor_t)&json_pair_destroy);
        case JSON_ARRAY:
            list_destroy(&(item->value.data.array), (destructor_t)&json_item_destroy);
        case JSON_STRING:
            free(item->value.data.string);
        default:
            free(item);
            break;
    }
}

void json_wipe(json_t* json){
    if(json == NULL){ return; }

    switch(json->type){
        case JSON_OBJECT:
            dict_destroy(&(json->data.object), (destructor_t)&json_pair_destroy);
        case JSON_ARRAY:
            list_destroy(&(json->data.array), (destructor_t)&json_item_destroy);
        case JSON_STRING:
            free(json->data.string);
        default:
            json->type = JSON_NULL;
            break;
    }
}

//:PUBLIC
void json_destroy(json_t* json){
    json_wipe(json);

    if(json != NULL){ free(json); }
}
