
#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

typedef enum {
    STR2INT_SUCCESS,
    STR2INT_OVERFLOW,
    STR2INT_UNDERFLOW,
    STR2INT_INCONVERTIBLE
} str2int_errno;

#define true 1
#define false 0

#ifndef __STDC_VERSION__ 
    #define __STDC_VERSION__ 0
#endif // !__STDC_VERSION__

#if __STDC_VERSION__ == 199901L
    #define C99  1
#else 
    #define C99  0
#endif

size_t readAllBytesFromFile(char* filename, char** output, int zeroTerminate);
int fileExists(const char* filename);

#endif
