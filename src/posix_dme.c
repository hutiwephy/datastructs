#include <stdlib.h>
#include <posix_dme.h>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/*
#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif
*/

#ifdef __ALLOC_H_MEMSTREAM
FILE* fmemopen(void* buf, size_t size, const char* mode){}
FILE* open_memstream(char** ptr, size_t* sizeloc){}
FILE* open_wmemstream(wchar_t** ptr, size_t* sizeloc){}
#endif

#ifdef __ALLOC_H_DYNSPRINTF
int asprintf(char** strp, const char* fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    int result = vasprintf(strp, fmt, ap);
    va_end(ap);

    return result;
}
int aswprintf(wchar_t** strp, const wchar_t* fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    int result = vaswprintf(strp, fmt, ap);
    va_end(ap);

    return result;
}
int vasprintf(char** strp, const char* fmt, va_list arg){
    if(strp == NULL){ return -1; }
    *strp = NULL;

    va_list ap2;
    va_copy(ap2, arg);

    int length = vsnprintf(NULL, 0, fmt, ap2);
    va_end(ap2);

    if(length < 0){ return -1; }

    *strp = (char*)malloc(length+sizeof(char));
    if(*strp == NULL){ return -1; }

    if(vsnprintf(*strp, length, fmt, arg) != length){
        free(*strp);
        return -1;
    }

    return length;
}
int vaswprintf(wchar_t** strp, const wchar_t* fmt, va_list arg){
    if(strp == NULL){ return -1; }
    *strp = NULL;

    va_list ap2;
    va_copy(ap2, arg);

    int length = vsnwprintf(NULL, 0, fmt, ap2);
    va_end(ap2);

    if(length < 0){ return -1; }

    *strp = (wchar_t*)malloc(length+sizeof(wchar_t));
    if(*strp == NULL){ return -1; }

    if(vsnwprintf(*strp, length, fmt, arg) != length){
        free(*strp);
        return -1;
    }

    return length;
}
#endif

#ifdef __ALLOC_H_DELIMITEDREAD
ssize_t getline(char** lineptr, size_t* n, FILE* stream){
    return getdelim(lineptr, n, '\n', stream);
}
ssize_t getwline(wchar_t** lineptr, size_t* n, FILE* stream){
    return getwdelim(lineptr, n, '\n', stream);
}
ssize_t getdelim(char** lineptr, size_t* n, int delimiter, FILE* stream){
    if(stream == NULL || lineptr == NULL || n == NULL){ return -1; }

    if(*lineptr == NULL){ *n = 0; }

    char ch;
    size_t m = *n;

    while(!feof(stream)){
        ch = fgetc(stream);

        // Realloc if need more size (account for NULL terminator)
        if(((*n)+1) >= m){
            m += BUFSIZ*sizeof(char);

            *lineptr = realloc(*lineptr, m);
            if(*lineptr == NULL){ return -1; }
        }

        // Push new char
        (*lineptr)[(*n)++] = ch;

        // Quit if read "delimiter" char
        if(ch == delimiter){ break; }
    }

    // Add NULL terminator
    *lineptr[*n] = 0;

    // Adjust size to fit string
    *lineptr = realloc(*lineptr, (++(*n))*sizeof(char));
    if(*lineptr == NULL){ return -1; }

    return *n-1;
}
ssize_t getwdelim(wchar_t** lineptr, size_t* n, wint_t delimiter, FILE* stream){
    if(stream == NULL || lineptr == NULL || n == NULL){ return -1; }

    if(*lineptr == NULL){ *n = 0; }

    wchar_t ch;
    size_t m = *n;

    while(!feof(stream)){
        ch = fgetwc(stream);

        // Realloc if need more size (account for NULL terminator)
        if(((*n)+1) >= m){
            m += BUFSIZ*sizeof(wchar_t);
            
            *lineptr = realloc(*lineptr, m);
            if(*lineptr == NULL){ return -1; }
        }

        // Push new char
        (*lineptr)[(*n)++] = ch;

        // Quit if read "delimiter" char
        if(ch == delimiter){ break; }
    }

    // Add NULL terminator
    *lineptr[*n] = 0;

    // Adjust size to fit string
    *lineptr = realloc(*lineptr, (++(*n))*sizeof(wchar_t));
    if(*lineptr == NULL){ return -1; }

    return *n-1;
}
#endif
