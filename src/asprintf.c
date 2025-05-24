#include <stdlib.h>
#include <asprintf.h>


#ifdef CTOOLS_ASPRINTF

/*
#if _MSC_VER < 1800
#undef va_copy
#define va_copy(dst, src) (dst = src)
#endif
*/

int vasprintf(char** pstr, const char* fmt, va_list ap){
    if(pstr == NULL){ return -1; }
    *pstr = NULL;

    va_list ap2;
    va_copy(ap2, ap);

    int length = _vscprintf(fmt, ap2);
    va_end(ap2);

    if(length < 0){ return -1; }

    *pstr = (char*)malloc(length+1);
    if(*pstr == NULL){ return -1; }

    if(vsnprintf_s(*pstr, length+1, length, fmt, ap) != length){
        free(*pstr);
        return -1;
    }

    return length;
}

int asprintf(char** pstr, const char* fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    int result = vasprintf(pstr, fmt, ap);
    va_end(ap);

    return result;
}

#endif
