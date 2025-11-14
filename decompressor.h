#include <stdint.h>
#include "librom.h"

#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

typedef struct {
	int size;
	uint8_t output[];
} Result;

const char COMPRESSIOM_TYPES[] = {
	'0', // No compression
	'1', // RLE Konami
	'2', // RLE Bakutoshu
	'3', // LZSS
	'4', // Huffman
	'5'  // Custom / Other
};

Result* KOMAMI_decompressor(int offset, LIBROM* rom);
uint8_t read_byte(LIBROM* rom);

#endif

