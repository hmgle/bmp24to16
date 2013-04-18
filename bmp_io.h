#ifndef _BMP_IO_H
#define _BMP_IO_H

#include <stdio.h>
#include "bmp_common.h"

int read_and_alloc_one_bmp(FILE *fp, bmp_file_t *ptrbmp);
void free_bmp(bmp_file_t *ptrbmp);
int output_bmp(FILE *fp, bmp_file_t *ptrbmp);

#endif
