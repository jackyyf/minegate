/*
 * base64.c
 * Created at: Nov 4, 2014
 * 
 * minegate
 * Copyright (C) 2014 Yifu Yu<root@jackyyf.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "base64.h"

#include <stdint.h>
#include <string.h>

const static char char_table[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', '0', '1', '2', '3',
		'4', '5', '6', '7', '8', '9', '+', '/',
};

const static char padding = '=';
const static long padding_length[] = {0, 2, 1};

void base64_encode(const char *input, const size_t size_in,
				   char *buff, size_t *buffsize) {
	size_t expect_size = 4 * ((size_in + 2) / 3);
	uint32_t bits24;
	long buff_idx, full_chunk = size_in / 3, chunk_idx, i;
	for (buff_idx = 0, chunk_idx = 0; chunk_idx < full_chunk; ++ chunk_idx ) {
		bits24 = ((uint32_t)input[0] << 16) | ((uint32_t)input[1] << 8) | (uint32_t)input[2];
		input += 3;
		for(i = 3; i >= 0; -- i) {
			if (buff_idx >= *buffsize) return; /* no more data can be stored. */
			buff[buff_idx ++] = char_table[(bits24 >> (i * 6)) & 0x3F];
		}
	}
	if (size_in % 3 == 0) return; /* No more data to process */
	for (chunk_idx = full_chunk * 3, i = 0, bits24 = 0; chunk_idx < size_in; ++ chunk_idx, ++ i) {
		bits24 |= ((uint32_t)input[i]) << ((2 - i) << 3);
	}
	static char tmp[4];
	for(i = 0; i < 4; ++ i)
		tmp[i] = char_table[((bits24 >> ((3 - i) * 6)) & 0x3F)];
	for(i = 0; i < padding_length[size_in % 3]; ++ i) {
		tmp[3 - i] = padding;
	}
	for(i = 0; i < 4; ++ i) {
		if (buff_idx >= *buffsize) return;
		buff[buff_idx ++] = tmp[i];
	}
	*buffsize = buff_idx;
}

/**
 * Note: this base64_decode is not in strict mode, i.e., if valid characters in input is
 * not a multiple of 4, padding('=') will be added to the very last of the input. Also,
 * all invalid character will be ignored.
 */

const static uint8_t char_map[] = {
 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233,	/* 0x0f */
 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233,	/* 0x1f */
 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233,  62, 233, 233, 233,  63,	/* 0x2f */
  52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 233, 233, 233, 233, 233, 233,	/* 0x3f */
 233,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,	/* 0x4f */
  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25, 233, 233, 233, 233, 233,	/* 0x5f */
 233,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,	/* 0x6f */
  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51, 233, 233, 233, 233, 233,	/* 0x7f */
 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233,	/* 0x8f */
 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233,	/* 0x9f */
 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233,	/* 0xaf */
 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233,	/* 0xbf */
 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233,	/* 0xcf */
 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233,	/* 0xdf */
 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233,	/* 0xef */
 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233,	/* 0xff */
};

void base64_decode(const char *input, const size_t size_in,
				   char *buff, size_t *buffsize) {
	uint32_t bits24 = 0;
	long b64c = 0, buff_idx = 0;
	int i, j;
	for(i = 0; i < size_in; ++ i) {
		if (char_map[input[i]] == 233) continue; /* Invalid char */
		++ b64c; bits24 = (bits24 << 6) | char_map[input[i]];
		if (b64c == 4) { /* read 4 base64 character, convert to 3 bytes */
			for(j = 2; j >= 0; -- j) {
				if (buff_idx >= *buffsize) return;
				buff[buff_idx ++] = (char)((bits24 >> (j << 3)) /* j * 8 */ & 0xFF);
			}
			b64c = 0; bits24 = 0;
		}
	}
	switch(b64c) {
		case 0:
			/* 0 bits => 0 bytes */
			break;
		case 1:
			/* 6 bits => 0 bytes*/
			break;
		case 2:
			/* 12 bits => 1 byte, LSB is meaningless */
			if (buff_idx >= *buffsize) return;
			buff[buff_idx ++] = (char)((bits24 >> 4) & 0xFF);
			break;
		case 3:
			/* 18 bits => 2 byte, LSB is meaning less */
			if (buff_idx >= *buffsize) return;
			buff[buff_idx ++] = (char)((bits24 >> 10) & 0xFF);
			if (buff_idx >= *buffsize) return;
			buff[buff_idx ++] = (char)((bits24 >> 2) & 0xFF);
			break;
	}
	*buffsize = buff_idx;
}
