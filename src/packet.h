/*
 * packet.h
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

#ifndef _PACKET_H_
#define _PACKET_H_

#include "mem.h"

typedef struct mg_packet_s {
	uint16_t id; /* packet_id */
	uint16_t size; /* packet size */
	void *buff; /* packet buffers, linked list */
} mg_packet_t;

mg_packet_t *mg_parse_pkt(mg_mem_t *buff) {
	mg_memstate_t state = mg_mem_snapshot(buff);
}

#endif /* _PACKET_H_ */
