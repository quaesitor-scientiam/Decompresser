#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "utils.h"


size_t readAllBytesFromFile(char* filename, char** output, int zeroTerminate) {
    FILE* fileptr;
    errno_t err;
    long filelen;
    int error = false;

    #if C99
        fileptr = fopen(filename, "rb");
        if (fileptr == NULL) {
            error = true;
        }
    #else
        err = fopen_s(&fileptr, filename, "rb");
        if (err != 0) {
            error = true;
        }
    #endif

    if (error) {
        printf("Error: Can't find file \"");
        printf("%s", filename);
        printf("\".\n");
        return -1;
    }

    fseek(fileptr, 0, SEEK_END);
    filelen = ftell(fileptr) + zeroTerminate;
    rewind(fileptr);

    // Save errno before malloc, restore after if needed
    int saved_errno = errno;
    char* result = (char*)malloc(filelen * sizeof(char));
    if (result == NULL) {
        printf("Error: Couldn't allocate memory for reading file data.\n");
        return -1;
    }
    errno = saved_errno;

    fread(result, filelen, 1, fileptr);
    fclose(fileptr);

    for (int i = filelen - zeroTerminate; i < filelen; i++) {
        result[i] = 0;
    }

    *output = result;
    return filelen;
}

int fileExists(const char* filename) {
    FILE* file;
#if defined(__GNUC__) || defined(__GNUG__) || defined(C99)
    file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
#else
    errno_t error = fopen_s(&file, filename, "r");
    if (error == 0) {
        fclose(file);
        return 1;
    }
#endif
    return 0;
}

const char* compression_name(compressionTypes ctype) {
    switch (ctype) {
        CTYPE_ENUM(CTYPE_ENUM_STRING)
    default: assert(!"Unknown compression type");
    }
}

const char* const type_names[] = {
    #define X(x) [x] = #x,
        CTYPE_ENUM(X)
    #undef X
};

compressionTypes compressionType_from_string(const char* str) {
    CTYPE_ENUM(CTYPE_ENUM_FROM_STRING)
        assert(!"Unknown compression type string");
}
