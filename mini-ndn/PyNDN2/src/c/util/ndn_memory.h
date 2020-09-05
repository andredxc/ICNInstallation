/**
 * Copyright (C) 2013-2018 Regents of the University of California.
 * @author: Jeff Thompson <jefft0@remap.ucla.edu>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version, with the additional exemption that
 * compiling, linking, and/or using OpenSSL is allowed.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * A copy of the GNU Lesser General Public License is in the file COPYING.
 */

/*
 * Based on NDN_CPP_HAVE_MEMCMP, NDN_CPP_HAVE_MEMCPY and NDN_CPP_HAVE_MEMSET in
 * ndn-cpp-config.h, use the library version or a local implementation of
 * memcmp, memcpy and memset.
 */

#ifndef NDN_MEMORY_H
#define NDN_MEMORY_H

#include <ndn-cpp/c/common.h>

#ifdef __cplusplus
extern "C" {
#endif

#if NDN_CPP_HAVE_MEMCMP

#if NDN_CPP_HAVE_MEMORY_H
#include <memory.h>
#else
#include <string.h>
#endif
/**
 * Use the library version of memcmp.
 */
static __inline int ndn_memcmp(const uint8_t *buf1, const uint8_t *buf2, size_t len)
{
  if (len == 0)
    // Allow buf1 or buf2 to be null.
    return 0;
  else
    return memcmp(buf1, buf2, len);
}
#else
/**
 * Use a local implementation of memcmp instead of the library version.
 */
int ndn_memcmp(const uint8_t *buf1, const uint8_t *buf2, size_t len);
#endif

#if NDN_CPP_HAVE_MEMCPY

#if NDN_CPP_HAVE_MEMORY_H
#include <memory.h>
#else
#include <string.h>
#endif
/**
 * Use the library version of memcpy.
 */
static __inline void ndn_memcpy(uint8_t *dest, const uint8_t *src, size_t len)
{
  // If len == 0, allow dest or src to be null.
  if (len > 0)
    memcpy(dest, src, len);
}
#else
/**
 * Use a local implementation of memcpy instead of the library version.
 */
void ndn_memcpy(uint8_t *dest, const uint8_t *src, size_t len);
#endif

#if NDN_CPP_HAVE_MEMSET

#if NDN_CPP_HAVE_MEMORY_H
#include <memory.h>
#else
#include <string.h>
#endif
/**
 * Use the library version of memset.
 */
static __inline void ndn_memset(uint8_t *dest, int val, size_t len)
{
  // If len == 0, allow dest to be null.
  if (len > 0)
    memset(dest, val, len);
}
#else
/**
 * Use a local implementation of memset instead of the library version.
 */
void ndn_memset(uint8_t *dest, int val, size_t len);
#endif

#ifdef __cplusplus
}
#endif

#endif

