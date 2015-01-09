/*
 * mem.c
 * Created at: Jan 8, 2015
 * 
 * minegate
 * Copyright (C) 2015 Yifu Yu<root@jackyyf.com>
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

#include "mem.h"
#include "macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mg_mem_t *mg_malloc(size_t size) {
	mg_mem_t *ret = (mg_mem_t *)malloc(sizeof(mg_mem_t));
	if (ret == NULL)
		return NULL;
	ret->data = malloc(size);
	if (ret->data == NULL) {
		free(ret);
		return NULL;
	}
	ret->ptr = ret->data;
	ret->size = size;
	return ret;
}

mg_mem_t *mg_calloc(size_t num, size_t size) {
	mg_mem_t *ret = (mg_mem_t *)malloc(sizeof(mg_mem_t));
	if (ret == NULL)
		return NULL;
	ret->data = calloc(num, size);
	if (ret->data == NULL) {
		free(ret);
		return NULL;
	}
	ret->ptr = ret->data;
	ret->size = num * size;
	return ret;
}

void mg_free(mg_mem_t *mem) {
	if (mg_likely(mem != NULL)) {
		if (mg_likely(mem->data != NULL))
			free(mem->data);
		free(mem);
	}
}

/**
 * Return corresponding char if there is one, or EOF when no more memory is available now.
 */

int32_t mg_mem_getchar(mg_mem_t *mem) {
	if (mg_likely(mg_mem_hasmore(mem, 1))) {
		return (int32_t)(*(uint8_t *)(mem->ptr++));
	}
	return EOF;
}

int32_t mg_mem_putchar(mg_mem_t *mem, int32_t ch) {
	if (mg_likely(mg_mem_hasmore(mem, 1))) {
		return (*(uint8_t *)(mem->ptr++)) = (ch & 0xFF);
	}
	return EOF;
}

size_t mg_mem_hasmore(mg_mem_t *mem, size_t size) {
	return size < mem->data + mem->size - mem->ptr ? size : mem->data + mem->size - mem->ptr;
}

size_t mg_mem_read(mg_mem_t *from, size_t size, void *to) {
	size_t lft = mg_mem_hasmore(from, size);
	memcpy(to, from->ptr, lft);
	from->ptr += lft;
	return lft;
}
size_t mg_mem_copy(mg_mem_t *from, size_t size, mg_mem_t *to) {
	size_t cap = minuptr(mg_mem_hasmore(from, size), mg_mem_hasmore(to, size));
	memcpy(to->ptr, from->ptr, cap);
	to->ptr += cap;
	from->ptr += cap;
	return cap;
}
size_t mg_mem_write(mg_mem_t *to, size_t length, void *from) {
	size_t lft = mg_mem_hasmore(to, length);
	memcpy(from, to->ptr, lft);
	to->ptr += lft;
	return lft;
}

/* The following two state only saves pointer state. */

mg_memstate_t mg_mem_snapshot(mg_mem_t *mem) {
	return mem->ptr;
}
int32_t mg_mem_rollback(mg_mem_t *mem, mg_memstate_t state) {
	if (mg_likely(mem->data <= state && state <= mem->data + mem->size)) {
		mem->ptr = state;
		return 0;
	}
	return -1;
}

size_t mg_mem_getoffset(mg_mem_t *mem) {
	return mem->ptr - mem->data;
}
size_t mg_mem_setoffset(mg_mem_t *mem, size_t offset) {
	if (mg_rarely(offset > mem->size))
		offset = mem->size;
	mem->ptr = mem->data + offset;
	return offset;
}
size_t mg_mem_addoffset(mg_mem_t *mem, ptrdiff_t diff) {
	mem->ptr += diff;
	if (diff > 0) {
		if (mem->ptr > mem->data + mem->size)
			mem->ptr = mem->data + mem->size;
	} else {
		if (mem->ptr < mem->data)
			mem->ptr = mem->data;
	}
	return mem->ptr - mem->data;
}
