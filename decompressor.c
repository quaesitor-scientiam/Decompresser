#include "librom.h"
#include <stdio.h>
#include <stdint.h>


void decompress(char* rom_path, char* decompressed_path, char* codec) {
	struct librom rom = initialize_rom(rom_path, 'L');
	if (rom.size == 0) {
		return;
	}
	//for compression in 0 to rom.size {
	//	// Decompression logic based on codec
	//	// This is a placeholder for actual decompression code
	//}
	KOMAMI_decompressor(0, rom);
}


void KOMAMI_decompressor(int offset, struct librom rom) {
	// Decompression logic for Konami RLE
	rom.cursor = offset;
	rom.data += offset;
	uint8_t byte = read_byte(&rom);

};

uint8_t read_byte(struct librom* rom) {
	if (rom->cursor >= rom->size) {
		printf("Error: Attempted to read beyond end of ROM data.\n");
		return 0;
	}
	return (uint8_t)rom->data[rom->cursor++];
}

//unsigned char* decompress_rle_konami(unsigned char* data, int data_len, int* decompressed_len) {
//    unsigned char* decompressed = malloc(data_len * sizeof(unsigned char)); // Allocate memory
//    int i = 0, j = 0;
//
//    while (i < data_len) {
//        unsigned char byte = data[i];
//        if (byte == 0xFF) {
//            unsigned char repeat = data[i + 1];
//            unsigned char value = data[i + 2];
//            for (int k = 0; k < repeat; ++k) {
//                decompressed[j++] = value;
//            }
//            i += 3;
//        } else {
//            decompressed[j++] = byte;
//            i++;
//        }
//    }
//
//    *decompressed_len = j;
//    return decompressed;
//}

//int decompress_rle_bakutoshu(void) {
//	char buffer[BUFSIZ];
//    int c;
//    int i;
//    size_t count_members;
//    size_t count_repeats;
//
//    while ((c = getchar()) != EOF && !feof(stdin)) {
//            count_repeats = c & 0x1F;
//            count_members = (c & 0xE0) >> 5;
//
//            if (count_members == 5) {
//                    break;
//            } else if (count_members == 0) {
//                    for (i = 0; i <= count_repeats; i++) {
//                            putchar(getchar());
//                    }
//            } else {
//                    count_members = (count_members >= 3) ? (count_members + 1) : count_members;
//                    fread(buffer, 1, count_members, stdin);
//
//                    for (i = 0; i <= count_repeats; i++) {
//                            fwrite(buffer, 1, count_members, stdout);
//                    }
//            }
//    }
//
//    return 0;
//}


int main(int argc, char** argv) {
	if (argc < 4) {
		printf("Usage: %s <rom_path> <decompressed_path> <codec>\n", argv[0]);
		return 1;
	}
	char* rom_path = argv[1];
	char* decompressed_path = argv[2];
	char* codec = argv[3];
	decompress(rom_path, decompressed_path, codec);
	return 0;
}