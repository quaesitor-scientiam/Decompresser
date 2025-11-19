#include <stdint.h>
#include "librom.h"

#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

typedef struct {
	int size;
	uint8_t output[];
} Result;

Result* KOMAMI_decompressor(int offset, LIBROM* rom);
uint8_t read_byte(LIBROM* rom);

#endif

