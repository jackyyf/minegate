/*
 * ping.h
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

#ifndef _PING_H_
#define _PING_H_

#include <stdint.h>

typedef struct mg_ping_handle_s {
	char *host;
	uint16_t port;
	uint16_t protocol; /* Protocol version, assume less than 65535 */
} mg_ping_handle_t;

mg_ping_handle_t *mg_init_ping();

#endif /* _PING_H_ */
