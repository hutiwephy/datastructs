#ifndef __STDC_ALLOC_LIB__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// Compliance level
#ifdef _WIN32
#define __STDC_ALLOC_LIB__ ((long)0)
#endif

// Memory streaming
#ifdef _WIN32
//#define __ALLOC_H_MEMSTREAM
//FILE* fmemopen(void* buf, size_t size, const char* mode);
//FILE* open_memstream(char** ptr, size_t* sizeloc);
//FILE* open_wmemstream(wchar_t** ptr, size_t* sizeloc);
#endif

// Dynamic sprintf
#if !(defined __linux__ || defined BSD)
#define __ALLOC_H_DYNSPRINTF
int asprintf(char** strp, const char* fmt, ...);
int aswprintf(wchar_t** strp, const wchar_t* fmt, ...);
int vasprintf(char** strp, const char* fmt, va_list arg);
int vaswprintf(wchar_t** strp, const wchar_t* fmt, va_list arg);
#endif

// Delimited read
#ifdef _WIN32
#define __ALLOC_H_DELIMITEDREAD
ssize_t getline(char** lineptr, size_t* n, FILE* stream);
ssize_t getwline(wchar_t** lineptr, size_t* n, FILE* stream);
ssize_t getdelim(char** lineptr, size_t* n, int delimiter, FILE* stream);
ssize_t getwdelim(wchar_t** lineptr, size_t* n, wint_t delimiter, FILE* stream);
#endif

#ifdef __cplusplus
}
#endif
#endif