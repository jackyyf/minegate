/*
 * mem.h
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

#ifndef _MEM_H_
#define _MEM_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct mg_mem_s {
	void *data;
	void *ptr; /* Warning: READ and WRITE operations shared the same ptr variable. */
	size_t size;
} mg_mem_t;

typedef void* mg_memstate_t;

mg_mem_t *mg_malloc(size_t size);
mg_mem_t *mg_calloc(size_t num, size_t size);
void mg_free(mg_mem_t *mem);

/**
 * Return corresponding char if there is one, or EOF when no more memory is available now.
 */
int32_t mg_mem_getchar(mg_mem_t *mem);
int32_t mg_mem_putchar(mg_mem_t *mem, int32_t ch);

size_t mg_mem_hasmore(mg_mem_t *mem, size_t size);
size_t mg_mem_read(mg_mem_t *src, size_t size, void *dest);
size_t mg_mem_copy(mg_mem_t *src, size_t size, mg_mem_t *dest);
size_t mg_mem_write(mg_mem_t *dest, size_t length, void *src);

size_t mg_mem_getoffset(mg_mem_t *mem);
size_t mg_mem_setoffset(mg_mem_t *mem, size_t offset);
size_t mg_mem_addoffset(mg_mem_t *mem, ptrdiff_t diff);

/* The following two state only saves pointer state. */

mg_memstate_t mg_mem_snapshot(mg_mem_t *mem);
int32_t mg_mem_rollback(mg_mem_t *mem, mg_memstate_t state);

#endif /* _MEM_H_ */
