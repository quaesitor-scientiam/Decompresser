
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "decompressor.h"
#include "librom.h"


void decompress(char* rom_path, char* decompressed_path, char* codec) {
	struct librom rom = initialize_rom(rom_path, 'L');
	if (rom.size == 0) {
		return;
	}
	Result* result = KOMAMI_decompressor(0, &rom ); // Pass address of rom

	//for (int i = 0; i < result->size; i++) {
	//	printf("%02x ", ((unsigned char*)result->output)[i]);
	//}

	// TODO: Write output to decompressed_path and free output
	FILE* pFile = fopen(decompressed_path, "wb");
	if (pFile) {
		fwrite(&result->output, result->size, 1, pFile);
		fclose(pFile);
	}
}


Result* KOMAMI_decompressor(int offset, struct librom* rom) {
	rom->cursor = offset;
	rom->data += offset;
	
	// Allocate Result buffer (assume decompressed data won't exceed rom.size * 2)
	Result *result = malloc(sizeof(Result) * rom->size * 2 * sizeof(uint8_t));
	if (!result) {
		printf("Error: Failed to allocate output buffer.\n");
		return NULL;
	}
	
	result->size = 0;
	while (1) {
		uint8_t byte = read_byte(rom);
		if (byte == 0xFF) {
			break;
		}

		if (byte <= 0x80) {
			uint8_t _readed = read_byte(rom);
			for (int i = 0; i < byte; i++) {
				result->output[result->size] = _readed;
				result->size++;
			}
		} else {
			for (int i = 0; i < (byte - 0x80); i++) {
				result->output[result->size] = read_byte(rom);
				result->size++;
			}
		}
	}
	return result;
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