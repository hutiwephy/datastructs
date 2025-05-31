#include <ctools/json.h>
#include "internal.h"


//:PRIVATE
typedef struct json_strbuildstate_st {
	char* str;
    int ident;
    int depth;
} json_strbuildstate_t;
int json_strbuildstate_write(json_strbuildstate_t* state, const char* format, ...){
    char* tmp_va = NULL;

    va_list args;
    va_start(args, format);
    int len = vasprintf(&tmp_va, format, args);
    va_end(args);
    if(len == -1 || tmp_va == NULL){
        if(state->str != NULL){
            free(state->str);
        }
        state->str = NULL;
        return -1;
    }

    char* tmp_str = strcatcpy(state->str, tmp_va);
    if(state->str != NULL){
        free(state->str);
    }
    if(tmp_str == NULL){
        free(tmp_va);
        state->str = NULL;
        return -1;
    }
    state->str = tmp_str;
    return 0;
}
int json_strbuildstate_newline(json_strbuildstate_t* state){
    if(state->ident <= 0){ return 0; }
    size_t len = (state->depth * state->ident) + 2;
    char* tmp = malloc(len);
    if(tmp == NULL){ return -1; }
    
    memset(tmp, ' ', len);
    tmp[0] = '\n';
    tmp[len-1] = 0;

    char* str2 = strcatcpy(state->str, tmp);
    if(str2 == NULL){ return -1; }

    free(state->str);
    state->str = str2;
    return 0;
}

char* json_str2string(char* value){
    if(value == NULL){ return NULL; }

    // determine size
    size_t len = 0;
    for(size_t i=0; value[i] != 0; i++){
        switch(value[i]){
            case '\"':
            case '\\':
            case '/':
            case '\b':
            case '\f':
            case '\n':
            case '\r':
            case '\t':
                len += 2;
                break;
            
            default:
                // not a control character and not delete
                if(value[i] >= 32 && value[i] != 127){
                    len++;
                }
                break;
        }
    }

    // create string
    char* tmp = malloc(len+1);
    if(tmp == NULL){ return NULL; }

    char esc = 0;

    size_t j=0;
    for(size_t i=0; value[i] != 0; i++){
        switch(value[i]){
            case '\"':
                esc = '\"';
            case '\\':
                esc = '\\';
            case '/':
                esc = '/';
            case '\b':
                esc = 'b';
            case '\f':
                esc = 'f';
            case '\n':
                esc = 'n';
            case '\r':
                esc = 'r';
            case '\t':
                esc = 't';

                tmp[j++] = '\\';
                tmp[j++] = esc;
                break;
            
            default:
                // not a control character and not delete
                if(value[i] >= 32 && value[i] != 127){
                    tmp[j++] = value[i];
                }
                break;
        }
    }
    tmp[j] = 0;

    if(j != len){
        free(tmp);
        return NULL;
    }
    return tmp;
}

int json_value_stringify(json_value_t* value, json_strbuildstate_t* state);

#define pair ((json_pair_t*)it)
int json_object_stringify(dict_t* value, json_strbuildstate_t* state){
    if(list_isEmpty(value)){
        if(json_strbuildstate_write(state, "{}") != 0){ return -1; }
    }else{
        if(json_strbuildstate_write(state, "{") != 0){ return -1; }
        state->depth++;

        for(list_it it = value->head; it != NULL; it = it->next){
            if(json_strbuildstate_newline(state) != 0){ return -1; }
            
            char* key = json_str2string(pair->key);
            if(key == NULL){ return -1; }

            if(json_strbuildstate_write(state, (state->ident == 0)? "\"%s\":" : "\"%s\": ", key) != 0){ return -1; }
            free(key);

            if(json_value_stringify(&(pair->value), state) != 0){ return -1; }
            if(it->next != NULL){
                if(json_strbuildstate_write(state, ",") != 0){ return -1; }
            }
        }

        state->depth--;
        if(json_strbuildstate_newline(state) != 0){ return -1; }
        if(json_strbuildstate_write(state, "}") != 0){ return -1; }
    }
    return 0;
}

#define item ((json_item_t*)it)
int json_array_stringify(list_t* value, json_strbuildstate_t* state){
    if(list_isEmpty(value)){
        if(json_strbuildstate_write(state, "[]") != 0){ return -1; }
    }else{
        if(json_strbuildstate_write(state, "[") != 0){ return -1; }
        state->depth++;

        for(list_it it = value->head; it != NULL; it = it->next){
            if(json_strbuildstate_newline(state) != 0){ return -1; }
            
            if(json_value_stringify(&(item->value), state) != 0){ return -1; }
            if(it->next != NULL){
                if(json_strbuildstate_write(state, ",") != 0){ return -1; }
            }
        }

        state->depth--;
        if(json_strbuildstate_newline(state) != 0){ return -1; }
        if(json_strbuildstate_write(state, "]") != 0){ return -1; }
    }
    return 0;
}

int json_value_stringify(json_value_t* value, json_strbuildstate_t* state){
    switch(value->type){
        case JSON_OBJECT:
            return json_object_stringify(&(value->data.object), state);
        case JSON_ARRAY:
            return json_array_stringify(&(value->data.array), state);
        case JSON_STRING:
            {
                char* tmp = json_str2string(value->data.string);
                if(tmp == NULL){ return -1; }
                int err = json_strbuildstate_write(state, "\"%s\"", tmp);
                free(tmp);
                return err;
            }
        case JSON_NUMBER:
            return json_strbuildstate_write(state, "%.15g", value->data.number);
        case JSON_BOOL:
            return json_strbuildstate_write(state, (value->data.boolean)? "true" : "false");
        case JSON_NULL:
            return json_strbuildstate_write(state, "null");
        default:
            return -1;
    }   
}

//:PUBLIC
char* json_stringify(json_t* json, int ident){
    if(json == NULL){ return NULL; }
    int err = 0;
    
    json_strbuildstate_t state = {
        .str = NULL,
        .depth = 0,
        .ident = ident
    };
    if((err = json_value_stringify(json, &state)) != 0){
        if(state.str != NULL){ free(state.str); }
        return NULL;
    }

    return state.str;
}
