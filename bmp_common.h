#ifndef _DOT_MATRIX_FONT_TO_BMP_H
#define _DOT_MATRIX_FONT_TO_BMP_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct bmp_file_header {
	uint8_t magic[2];
	uint32_t file_size; /* byte */
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t offset;
} __attribute__ ((packed)) bmp_file_header_t;

typedef struct dib_header { /* BITMAPINFOHEADER */
	uint32_t dib_header_size;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bits_per_pix;
	uint32_t compression;
	uint32_t image_size; /* byte */
	uint32_t x_pix_per_meter;
	uint32_t y_pix_per_meter;
	uint32_t colors_in_colortable;
	uint32_t important_color_count;
} __attribute__ ((packed)) dib_header_t;

typedef struct bmp_file {
	bmp_file_header_t bmp_h;
	dib_header_t dib_h;
	uint8_t *pdata;
} __attribute__ ((packed)) bmp_file_t;

void set_header(bmp_file_t *pbmp_f, uint32_t width, uint32_t height, uint16_t bits_per_pix);
void get_header(const bmp_file_t *pbmp_f, bmp_file_header_t *bmp_header, dib_header_t *dib_header);

#endif
