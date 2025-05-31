#include <ctools/json.h>
#include "internal.h"


/**
 * Dear future code reviewers, aka. me,
 * 
 * My deepest apologies...
 * 
 * Sincerely,
 * hutiwephy
 */

//:PRIVATE
static char* errors[] = {
    "Unknown error",
    "Failed to allocate memory",
    "Insufficient string length",
    "Expected \"true\"",
    "Expected \"false\"",
    "Expected \"null\"",
    "Invalid character",
    "Invalid escape sequence",
    "Unicode is unsupported",
    "Unexpected character",
    "Expected \":\"",
};
static struct parsererror {
    int code;
    size_t idx;
} error = {0};

int pvalue(json_t* value, char* str, size_t* i, size_t str_len);
int pstring(char** value, char* str, size_t* i, size_t str_len);

int pskipws(char* str, size_t* i, size_t str_len){
    while(*i<str_len){
        switch(str[*i]){
            case ' ':
            case '\n':
            case '\r':
            case '\t':
                if(++(*i) >= str_len){ return JSON_PE_STRINGLEN; }
                break;
            default:
                return 0;
        }
    }
    return 0;
}
int pobject(dict_t* value, char* str, size_t* i, size_t str_len){
    int err = 0;
    if(++(*i) >= str_len){ err = JSON_PE_STRINGLEN; goto end; }

    while(*i<str_len){
        if((err = pskipws(str, i, str_len)) != 0){ goto end; }
        switch(str[*i]){
            case '}':
                goto end;
            
            case '"':
                object_pair:
                {
                    json_pair_t* entry = malloc(sizeof(json_pair_t));
                    if(entry == NULL){ err = JSON_PE_MEMORY; goto end; }
                    memset(entry, 0, sizeof(json_pair_t));
                    
                    if((err = pstring(&(entry->key), str, i, str_len)) != 0){
                        free(entry);
                        goto end;
                    }

                    // overwrite exception! 
                    // RFC8259 allows duplicate entries, but behaviour is undefined therefore I pick overwrite
                    json_pair_destroy((json_pair_t*)dict_set(value, entry->key, entry));

                    if(++(*i) >= str_len){ err = JSON_PE_STRINGLEN; goto end; }
                    if((err = pskipws(str, i, str_len)) != 0){ goto end; }
                    if(str[*i] != ':'){
                        err = JSON_PE_EXPECTEDPAIR;
                        goto end;
                    }
                    if(++(*i) >= str_len){ err = JSON_PE_STRINGLEN; goto end; }
                    if((err = pskipws(str, i, str_len)) != 0){ goto end; }
                    if((err = pvalue(&(entry->value), str, i, str_len)) != 0){
                        goto end;
                    }
                    if(++(*i) >= str_len){ err = JSON_PE_STRINGLEN; goto end; }
                    if((err = pskipws(str, i, str_len)) != 0){ goto end; }
                    switch(str[*i]){
                        case ',':
                            if(++(*i) >= str_len){ err = JSON_PE_STRINGLEN; goto end; }
                            if((err = pskipws(str, i, str_len)) != 0){ goto end; }
                            if(str[*i] != '"'){
                                err = JSON_PE_UNEXPECTEDCHAR;
                                goto end;
                            }
                            goto object_pair;
                            break;
                        case '}':
                            goto end;
                        default:
                            err = JSON_PE_UNEXPECTEDCHAR;
                            goto end;
                    }
                    break;
                }
            default:
                err = JSON_PE_UNEXPECTEDCHAR;
                goto end;
        }
    }

    end:
    return err;
}
int parray(list_t* value, char* str, size_t* i, size_t str_len){
    int err = 0;
    if(++(*i) >= str_len){ err = JSON_PE_STRINGLEN; goto end; }

    while(*i<str_len){
        switch(str[*i]){
            case ']':
                goto end;
            default:
                array_item:
                {
                    json_item_t* item = malloc(sizeof(json_item_t));
                    if(item == NULL){ err = JSON_PE_MEMORY; goto end; }
                    memset(item, 0, sizeof(json_item_t));

                    list_push_back(value, item);

                    if((err = pvalue(&(item->value), str, i, str_len)) != 0){
                        goto end;
                    }
                    if(++(*i) >= str_len){ err = JSON_PE_STRINGLEN; goto end; }
                    if((err = pskipws(str, i, str_len)) != 0){ goto end; }
                    switch(str[*i]){
                        case ',':
                            if(++(*i) >= str_len){ err = JSON_PE_STRINGLEN; goto end; }
                            if((err = pskipws(str, i, str_len)) != 0){ goto end; }
                            if(str[*i] == ']'){
                                err = JSON_PE_UNEXPECTEDCHAR;
                                goto end;
                            }
                            goto array_item;
                            break;
                        case ']':
                            goto end;
                        default:
                            err = JSON_PE_UNEXPECTEDCHAR;
                            goto end;
                    }
                }
        }
    }

    end:
    return err;
}
int pstring(char** value, char* str, size_t* i, size_t str_len){
    int err = 0;
    if(++(*i) >= str_len){ err = JSON_PE_STRINGLEN; goto end; }

    size_t j = 0;
    size_t mlen = CHUNK_SIZE;
    *value = malloc(mlen);
    if(*value == NULL){ err = JSON_PE_MEMORY; goto end; }

    while(*i<str_len){
        register char ch = 0;

        switch(str[*i]){
            case '"':
                goto end;
            case '\\':
                if(++(*i) >= str_len){ err = JSON_PE_STRINGLEN; goto end; }
                switch(str[*i]){
                    case '\"':
                        // quotation mark
                        ch = '\"';
                        break;
                    case '\\':
                        // reserse solidus
                        ch = '\\';
                        break;
                    case '/':
                        // solidus
                        ch = '/';
                        break;
                    case 'b':
                        // backspace
                        ch = '\b';
                        break;
                    case 'f':
                        // formfeed
                        ch = '\f';
                        break;
                    case 'n':
                        // newline
                        ch = '\n';
                        break;
                    case 'r':
                        // carriage return
                        ch = '\r';
                        break;
                    case 't':
                        // horizontal tab
                        ch = '\t';
                        break;
                    case 'u':
                        // unicode (4 hex digits)
                        err = JSON_PE_UNICODEUNSUPPORTED;
                        goto end;
                    default:
                        err = JSON_PE_INVALIDESCAPE;
                        goto end;
                }
                break;
            case '\b':
            case '\n':
            case '\r':
            case '\t':
                err = JSON_PE_INVALIDCHAR;
                goto end;
            default:
                // regular char
                ch = str[*i];
                break;
        }

        // save current char
        (*value)[j] = ch;
        
        // get next char
        if(++(*i) >= str_len){ err = JSON_PE_STRINGLEN; goto end; }

        // goto next char position and resize if needed
        if(++j >= mlen){
            mlen += CHUNK_SIZE;
            *value = realloc(*value, mlen);
            if(*value == NULL){ err = JSON_PE_MEMORY; goto end; }
        }
    }
    
    end:
    if(err == 0){
        if(++j >= mlen){
            mlen += CHUNK_SIZE;
            *value = realloc(*value, mlen);
            if(*value == NULL){ err = JSON_PE_MEMORY; goto end; }
        }
        (*value)[j-1] = 0;
        mlen = strlen(*value) + 1;

        *value = realloc(*value, mlen);
        if(*value == NULL){ return JSON_PE_MEMORY; }
    }else if(err != JSON_PE_MEMORY){
        free(*value);
    }
    return err;
}
int pnumber(double* value, char* str, size_t* i, size_t str_len){
    int err = 0;
    char* start = &(str[*i]);
    char* end = NULL;

    *value = strtod(start, &end);

    *i += end-start-1;
    return 0;
}
int pother(json_t* value, char* str, size_t* i, size_t str_len){
    switch(str[*i]){
        case 't':
            if(*i+3 >= str_len){ return JSON_PE_STRINGLEN; }
            if(
                str[++(*i)] == 'r' &&
                str[++(*i)] == 'u' &&
                str[++(*i)] == 'e'
            ){
                // true
                value->type = JSON_BOOL;
                value->data.boolean = true;
                return 0;
            }

            // error
            return JSON_PE_EXPECTEDTRUE;
        case 'f':
            if(*i+4 >= str_len){ return JSON_PE_STRINGLEN; }
            if(
                str[++(*i)] == 'a' &&
                str[++(*i)] == 'l' &&
                str[++(*i)] == 's' &&
                str[++(*i)] == 'e'
            ){
                // false
                value->type = JSON_BOOL;
                value->data.boolean = false;
                return 0;
            }

            return JSON_PE_EXPECTEDFALSE;
        case 'n':
            if(*i+3 >= str_len){ return JSON_PE_STRINGLEN; }
            if(
                str[++(*i)] == 'u' &&
                str[++(*i)] == 'l' &&
                str[++(*i)] == 'l'
            ){
                // null
                value->type = JSON_NULL;
                return 0;
            }

            return JSON_PE_EXPECTEDNULL;
        default:
            // number
            value->type = JSON_NUMBER;
            return pnumber(&(value->data.number), str, i, str_len);
    }
}
int pvalue(json_t* value, char* str, size_t* i, size_t str_len){
    if(pskipws(str, i, str_len) != 0){ return JSON_PE_STRINGLEN; }

    switch(str[*i]){
        case '{':
            value->type = JSON_OBJECT;
            return pobject(&(value->data.object), str, i, str_len);
        case '[':
            value->type = JSON_ARRAY;
            return parray(&(value->data.array), str, i, str_len);
        case '"':
            value->type = JSON_STRING;
            return pstring(&(value->data.string), str, i, str_len);
        default:
            return pother(value, str, i, str_len);
    }
}

//:PUBLIC
json_t* json_parse(const char* str){
    if(str == NULL){ return NULL; }
    
    json_t* root = malloc(sizeof(json_t));
    if(root == NULL){ return NULL; }
    memset(root, 0, sizeof(json_t));

    size_t str_length = strlen(str);
    size_t i = 0;
    int err = 0;
    if((err = pvalue(root, (char*)str, &i, str_length)) != 0){
        // error
        error.code = err;
        error.idx = i;
        return NULL;
    }

    return root;
}
int json_getParserError(char** message, size_t* index){
    if(error.code != 0){
        if(message != NULL){
            *message = errors[error.code & 0x7fffffff];
        }
        if(index != NULL){
            *index = error.idx;
        }
    }

    return error.code;
}
