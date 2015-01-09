/*
 * conf.h
 * Created at: Nov 6, 2014
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

#ifndef _CONF_H_
#define _CONF_H_

#include <stdint.h>

typedef struct mg_server_s {
	char *server;
	char *icon;
	uint32_t online;
	uint32_t limit; /* Can set to (uint32_t)-1, and will ask upstream server for real information. */
	uint16_t port;
	/** Ping method:
	 *   0 => (default) Handled by minegate, return the number of online users connected with upstream.
	 *   1 => Handled by minegate, return the number of all online users connected to minegate.
	 *   2 => Pass request to upstream, let upstream handle the request.
	 */
	uint16_t pingMethod : 2;
	/** Custom Icon:
	 *   0 => (default) No, use global icon specified in config file (or fall back to default icon if not exist).
	 *   1 => Yes, specified in `this->icon'.
	 */
	uint16_t customIcon : 1;
} mg_server_t;

void mg_conf_init(void);
void mg_conf_reload(void);
void mg_free_server_t(mg_server_t *free);
mg_server_t *mg_config_get_server(const char *host, const uint16_t port);

#endif /* _CONF_H_ */
