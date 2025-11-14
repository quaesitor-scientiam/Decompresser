#ifndef LIB_ROM_H
#define LIB_ROM_H

#include <stdint.h>

typedef struct librom {
	char* filename;
	char* data;
	size_t size;
	char endian; // 'L' for little-endian, 'B' for big-endian
	int cursor;
} LIBROM;

// Global instance of librom
extern struct LIBROM rom;

LIBROM initialize_rom(char* filename, char endian);

#endif
