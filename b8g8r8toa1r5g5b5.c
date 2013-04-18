#include "bmp_common.h"
#include "b8g8r8toa1r5g5b5.h"
#include "bmp_io.h"
#include "debug_log.h"

#ifndef MAX_8_BIT
#define MAX_8_BIT	256
#endif

#ifndef MAX_5_BIT
#define MAX_5_BIT	32
#endif

#if 0
inline uint16_t pix_b8g8r8_to_a1r5g5b5(uint32_t pix24, int alpha)
{
	uint16_t pix16 = 0;
	// uint8_t old, new;

	/* ALPHA */
	if (alpha)
		pix16 |= (1 << 0);
	/* R */
	// old = pix24 & 0xff;
	// new = old * MAX_5_BIT / MAX_8_BIT;
	// new = (pix24 & 0xff) * MAX_5_BIT / MAX_8_BIT;
	pix16 |= (((pix24 & 0xff) * MAX_5_BIT / MAX_8_BIT) << 1);
	/* G */
	// old = (pix24 & 0xff00) >> 8;
	// new = old * MAX_5_BIT / MAX_8_BIT;
	// new = ((pix24 & 0xff00) >> 8) * MAX_5_BIT / MAX_8_BIT;
	pix16 |= ((((pix24 & 0xff00) >> 8) * MAX_5_BIT / MAX_8_BIT) << 6);
	/* B */
	// old = (pix24 & 0xff0000) >> 16;
	// new = old * MAX_5_BIT / MAX_8_BIT;
	// new = ((pix24 & 0xff0000) >> 16) * MAX_5_BIT / MAX_8_BIT;
	pix16 |= ((((pix24 & 0xff0000) >> 16) * MAX_5_BIT / MAX_8_BIT) << 11);
	return pix16;
}
#else
uint16_t pix_b8g8r8_to_a1r5g5b5(uint32_t pix24, int alpha)
{
	uint16_t pix16 = 0;
	uint8_t old, new;

	/* ALPHA */
	if (alpha)
		pix16 |= (1 << 15);
	/* R */
	old = pix24 & 0xff;
	new = old * MAX_5_BIT / MAX_8_BIT;
	pix16 |= (new << 0);
	/* G */
	old = (pix24 & 0xff00) >> 8;
	new = old * MAX_5_BIT / MAX_8_BIT;
	pix16 |= (new << 5);
	/* B */
	old = (pix24 & 0xff0000) >> 16;
	new = old * MAX_5_BIT / MAX_8_BIT;
	pix16 |= (new<< 10);
	return pix16;
}
#endif

int main(int argc, char **argv)
{
	uint16_t pix16;
	uint32_t pix24;
	FILE *in = stdin;
	bmp_file_t bmp24;
	bmp_file_t bmp16;
	int size;
	int i;

	memset(&bmp24, 0, sizeof(bmp24));
	memset(&bmp16, 0, sizeof(bmp16));
	read_and_alloc_one_bmp(in, &bmp24);

	set_header(&bmp16, bmp24.dib_h.width, bmp24.dib_h.height, 16);
	bmp16.pdata = malloc(bmp16.dib_h.image_size);
	size = bmp24.dib_h.width * bmp24.dib_h.height;
	for (i = 0; i < size; i++) {
		pix24 = *((uint32_t *)(bmp24.pdata + i * 3));
		pix16 = pix_b8g8r8_to_a1r5g5b5(pix24, 1);
		*((uint16_t *)(bmp16.pdata + i * 2)) = pix16;
	}
	output_bmp(stdout, &bmp16);
	free(bmp24.pdata);
	free(bmp16.pdata);
	return 0;
}
