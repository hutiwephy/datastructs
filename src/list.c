#include <ctools/list.h>
#include "internal.h"


//:PRIVATE
typedef struct listnode_st {
    struct listnode_st* prev;
    struct listnode_st* next;
} listnode_t;
#define _cht(node) ((listnode_t**)node) // Cast head and tail
#define __cht(node) (*_cht(node))
#define _cit(node) ((listnode_t*)node)  // Cast iterator and node
// Aliases for improved readability
#define _head __cht(head)
#define _tail __cht(tail)
#define _it _cit(it)
#define _item _cit(item)
#define _a _cit(a)
#define _b _cit(b)

//:PUBLIC
int list_insert(void* head, void* tail, void* it, void* item){
    if(_head == NULL){
        _head = item;
        _tail = item;
    }else if(it == NULL){
        _tail->next = item;
        _item->prev = _tail;
        _tail = item;
    }else{
        _item->next = _it;
        _item->prev = _it->prev;
        _it->prev = _item;

        if(_it == _head){ _head = _item; }
    }

    return 1;
}
int list_append(void* head, void* tail, void* it, void* item){
    if(_head == NULL){
        _head = _item;
        _tail = _item;
    }else if(_it == NULL){
        _head->prev = _item;
        _item->next = _head;
        _head = _item;
    }else{
        _item->prev = _it;
        _item->next = _it->next;
        _it->next = _item;

        if(_it == _tail){ _tail = _item; }
    }

    return 1;
}
void* list_remove(void* head, void* tail, void* it){
    register listnode_t* it_prev = _it->prev;

    if(_it == _head){
        _head = _it->next;
    }
    if(_it == _tail){
        _tail = _it->prev;
    }
    _it->prev = _it->next;
    _it->next = it_prev;

    return _it;
}
void list_swap(void* head, void* tail, void* a, void* b){
    register listnode_t* a_prev = _a->prev;
    register listnode_t* a_next = _a->next;
    _a->prev = _b->prev;
    _a->next = _b->next;
    _b->prev = a_prev;
    _b->next = a_next;

    if(a == _head){
        _head = b;
        if(b == _tail){
            _tail = a;
        }
    }else if(a == _tail){
        _tail = b;
        if(b == _head){
            _head = a;
        }
    }else if(b == _head){
        _head = a;
    }else if(b == _tail){
        _tail = a;
    }
}
