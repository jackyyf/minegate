/*
 * packet.c
 * Created at: Nov 9, 2014
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

#include <stdlib.h>
#include <string.h>

#include "packet.h"

int32_t mg_read_varint(mg_mem_t *mem) {
	/* Each byte provides 7 bits, so there are at most 5 bytes. */
	mg_memstate_t state = mg_mem_snapshot(mem);
	int32_t ret = 0;
	int i;
	for(i = 0; i < 5; ++ i) {
		int32_t cur = mg_mem_getchar(mem);
		if (cur < 0) {
			mg_mem_rollback(mem, state);
			return -1;
		}
		ret = (ret << 7) | (cur & 0x7F);
		if (!(cur & 0x80)) break;
	}
	return ret;
}
int64_t mg_read_varlong(mg_mem_t *mem) {
	/* Each byte provides 7 bits, so there are at most 9 bytes. */
	mg_memstate_t state = mg_mem_snapshot(mem);
	int64_t ret = 0;
	int i;
	for(i = 0; i < 9; ++ i) {
		int32_t cur = mg_mem_getchar(mem);
		if (cur < 0) {
			mg_mem_rollback(mem, state);
			return -1;
		}
		ret = (ret << 7) | (cur & 0x7F);
		if (!(cur & 0x80)) break;
	}
}

mg_packet_t *mg_parse_pkt(mg_mem_t *buff) {
	mg_memstate_t state = mg_mem_snapshot(buff);
	/* Step 1: Read packet size. */
	int32_t size = mg_read_varint(buff);
	/* Make sure there are enough data for packet body. */
	if (mg_mem_hasmore(buff, size) != size) {
		mg_mem_rollback(buff, state);
		return NULL;
	}
}
