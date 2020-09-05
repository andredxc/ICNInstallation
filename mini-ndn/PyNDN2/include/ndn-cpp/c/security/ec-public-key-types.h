/**
 * Copyright (C) 2016-2018 Regents of the University of California.
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

#ifndef NDN_EC_PUBLIC_KEY_TYPES_H
#define NDN_EC_PUBLIC_KEY_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

struct ec_key_st;

/**
 * A struct ndn_EcPublicKey holds a decoded EC public key for use in crypto
 * operations.
 */
struct ndn_EcPublicKey {
  struct ec_key_st *publicKey;
};

#ifdef __cplusplus
}
#endif

#endif
