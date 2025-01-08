#include <ctools/list.h>
#include "internal.h"


//:PRIVATE
typedef struct listnode_st {
    struct listnode_st* prev;
    struct listnode_st* next;
} listnode_t;
typedef struct listheader_st {
    listnode_t* head;
    listnode_t* tail;
} listheader_t;

// Aliases for improved readability
#define _list ((listheader_t*)(list))
#define _head ((listnode_t*)(_list->head))
#define _tail ((listnode_t*)(_list->tail))
#define __head ((_list->head))  // Bypass "error: lvalue required as left operand of assignment"
#define __tail ((_list->tail))  // Bypass "error: lvalue required as left operand of assignment"
#define _it   ((listnode_t*)(it))
#define _item ((listnode_t*)(item))
#define _a    ((listnode_t*)(a))
#define _b    ((listnode_t*)(b))

//:PUBLIC
int list_insert(void* list, void* it, void* item){
    if(_head == NULL){
        __head = item;
        __tail = item;
    }else if(it == NULL){
        _tail->next = item;
        _item->prev = _tail;
        __tail = item;
    }else{
        _item->next = _it;
        _item->prev = _it->prev;
        _it->prev = _item;

        if(_it == _head){ __head = _item; }
    }

    return 1;
}
int list_append(void* list, void* it, void* item){
    if(_head == NULL){
        __head = _item;
        __tail = _item;
    }else if(_it == NULL){
        _head->prev = _item;
        _item->next = _head;
        __head = _item;
    }else{
        _item->prev = _it;
        _item->next = _it->next;
        _it->next = _item;

        if(_it == _tail){ __tail = _item; }
    }

    return 1;
}
void* list_remove(void* list, void* it){
    register listnode_t* it_prev = _it->prev;

    if(_it == _head){
        __head = _it->next;
    }
    if(_it == _tail){
        __tail = _it->prev;
    }
    _it->prev = _it->next;
    _it->next = it_prev;

    return _it;
}
void list_swap(void* list, void* a, void* b){
    register listnode_t* a_prev = _a->prev;
    register listnode_t* a_next = _a->next;
    _a->prev = _b->prev;
    _a->next = _b->next;
    _b->prev = a_prev;
    _b->next = a_next;

    if(a == _head){
        __head = b;
        if(b == _tail){
            __tail = a;
        }
    }else if(a == _tail){
        __tail = b;
        if(b == _head){
            __head = a;
        }
    }else if(b == _head){
        __head = a;
    }else if(b == _tail){
        __tail = a;
    }
}
