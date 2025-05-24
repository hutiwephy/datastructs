#pragma once

#include <stdio.h>
#include <stdarg.h>

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)

#define CTOOLS_ASPRINTF

#ifdef __cplusplus
extern "C"
{
#endif

int vasprintf(char** strp, const char* fmt, va_list ap);
int asprintf(char** strp, const char* fmt, ...);

#ifdef __cplusplus
}
#endif
#endif
