/*
 * macros.h
 * Created at: Jan 9, 2015
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

#ifndef _MACROS_H_
#define _MACROS_H_

#ifdef __GNUC__ /* We are using GCC, use its branch predict macro */
#define mg_likely(x) __builtin_expect(!!(x), 1)
#define mg_rarely(x) __builtin_expect(!!(x), 0)
#else /* Not GCC, use it as-is. */
#define mg_likely(x) (x)
#define mg_rarely(x) (x)
#endif /* __GNUC__ */

#include <stdint.h>

#define _min(a, b) ((a) < (b) ? (a) : (b))
#define _max(a, b) ((a) < (b) ? (a) : (b))

static inline int8_t max8(int8_t a, int8_t b) { return _max(a, b); }
static inline uint8_t maxu8(uint8_t a, uint8_t b) { return _max(a, b); }
static inline int16_t max16(int16_t a, int16_t b) { return _max(a, b); }
static inline uint16_t maxu16(uint16_t a, uint16_t b) { return _max(a, b); }
static inline int32_t max32(int32_t a, int32_t b) { return _max(a, b); }
static inline uint32_t maxu32(uint32_t a, uint32_t b) { return _max(a, b); }
static inline int64_t max64(int64_t a, int64_t b) { return _max(a, b); }
static inline uint64_t maxu64(uint64_t a, uint64_t b) { return _max(a, b); }
static inline intptr_t maxptr(intptr_t a, intptr_t b) { return _max(a, b); }
static inline uintptr_t maxuptr(uintptr_t a, uintptr_t b) { return _max(a, b); }

static inline int8_t min8(int8_t a, int8_t b) { return _min(a, b); }
static inline uint8_t minu8(uint8_t a, uint8_t b) { return _min(a, b); }
static inline int16_t min16(int16_t a, int16_t b) { return _min(a, b); }
static inline uint16_t minu16(uint16_t a, uint16_t b) { return _min(a, b); }
static inline int32_t min32(int32_t a, int32_t b) { return _min(a, b); }
static inline uint32_t minu32(uint32_t a, uint32_t b) { return _min(a, b); }
static inline int64_t min64(int64_t a, int64_t b) { return _min(a, b); }
static inline uint64_t minu64(uint64_t a, uint64_t b) { return _min(a, b); }
static inline intptr_t minptr(intptr_t a, intptr_t b) { return _min(a, b); }
static inline uintptr_t minuptr(uintptr_t a, uintptr_t b) { return _min(a, b); }

#undef _min
#undef _max

#endif /* _MACROS_H_ */
