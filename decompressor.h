#include <stdint.h>

#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

const char COMPRESSIOM_TYPES[] = {
	'0', // No compression
	'1', // RLE Konami
	'2', // RLE Bakutoshu
	'3', // LZSS
	'4', // Huffman
	'5'  // Custom / Other
};

void KOMAMI_decompressor(int offset, struct librom rom);
uint8_t read_byte(struct librom* rom);

#endif

