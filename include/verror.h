#ifndef VERROR_H
#define VERROR_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void verror(const char* format, ...);

#define RED           "\x1b[31;1m"
#define END_OF_RED "\x1b[39;49m\n" 

#define VERROR(...) do                                              \
    {                                                               \
        fprintf(stderr, RED "ERROR:%s (%d)\n", __FILE__, __LINE__); \
        verror(__VA_ARGS__);                                        \
        fprintf(stderr, END_OF_RED);                                \
    } while (0)

#define VERROR_MEM VERROR("memory allocation failure")
                                                    
#endif