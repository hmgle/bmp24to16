#include <stdio.h>
#include "debug_log.h"
#include "bmp_common.h"

void 
set_header(bmp_file_t *pbmp_f, 
	   uint32_t width, 
	   uint32_t height, 
	   uint16_t bits_per_pix)
{
	uint32_t rowsize;

	pbmp_f->bmp_h.magic[0] = 'B';
	pbmp_f->bmp_h.magic[1] = 'M';
	pbmp_f->bmp_h.offset = sizeof(bmp_file_header_t) + sizeof(dib_header_t);
	pbmp_f->dib_h.dib_header_size = sizeof(dib_header_t);
	pbmp_f->dib_h.width = width;
	pbmp_f->dib_h.height = height;
	pbmp_f->dib_h.planes = 1;
	pbmp_f->dib_h.bits_per_pix = bits_per_pix;
	pbmp_f->dib_h.compression = 0;
	rowsize = (bits_per_pix * width + 31) / 32 * 4; /* 4字节对齐 */
	pbmp_f->dib_h.image_size = rowsize * height;
	pbmp_f->dib_h.x_pix_per_meter = 0;
	pbmp_f->dib_h.y_pix_per_meter = 0;
	pbmp_f->dib_h.colors_in_colortable = 0;
	pbmp_f->dib_h.important_color_count = 0;
	pbmp_f->bmp_h.file_size = pbmp_f->bmp_h.offset + pbmp_f->dib_h.image_size;
}

void 
get_header(const bmp_file_t *pbmp_f, bmp_file_header_t *bmp_header, dib_header_t *dib_header)
{
	bmp_header->magic[0] = pbmp_f->bmp_h.magic[0];
	bmp_header->magic[1] = pbmp_f->bmp_h.magic[1];
	bmp_header->file_size = pbmp_f->bmp_h.file_size;
	bmp_header->reserved1 = pbmp_f->bmp_h.reserved1;
	bmp_header->reserved2 = pbmp_f->bmp_h.reserved2;
	bmp_header->offset = pbmp_f->bmp_h.offset;

	dib_header->dib_header_size = pbmp_f->dib_h.dib_header_size;
}
