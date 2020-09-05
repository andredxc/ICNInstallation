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

#include "crypto.h"

#ifdef ARDUINO

ndn_Error
ndn_generateRandomBytes(uint8_t *buffer, size_t bufferLength)
{
  // Assume the application has already initialized it, e.g.:
  // randomSeed(analogRead(0));
  size_t i;
  for (i = 0; i < bufferLength; ++i)
    buffer[i] = random(0, 256);

  return NDN_ERROR_success;
}

#elif NDN_CPP_HAVE_LIBCRYPTO

#include <openssl/ssl.h>
#include <openssl/rand.h>
#include "../security/ec-public-key.h"
#include "../security/rsa-public-key.h"
#include "ndn_memory.h"

static int CURVE_OID_224[] = { OBJ_secp224r1 };
static int CURVE_OID_256[] = { OBJ_X9_62_prime256v1 };
static int CURVE_OID_384[] = { OBJ_secp384r1 };
static int CURVE_OID_521[] = { OBJ_secp521r1 };

struct ndn_EcKeyInfo EC_KEY_INFO[] = {
  { 224, NID_secp224r1, CURVE_OID_224, sizeof(CURVE_OID_224) / sizeof(CURVE_OID_224[0]) },
  { 256, NID_X9_62_prime256v1, CURVE_OID_256, sizeof(CURVE_OID_256) / sizeof(CURVE_OID_256[0]) },
  { 384, NID_secp384r1, CURVE_OID_384, sizeof(CURVE_OID_384) / sizeof(CURVE_OID_384[0]) },
  { 521, NID_secp521r1, CURVE_OID_521, sizeof(CURVE_OID_521) / sizeof(CURVE_OID_521[0]) }
};

void
ndn_digestSha256(const uint8_t *data, size_t dataLength, uint8_t *digest)
{
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, data, dataLength);
  SHA256_Final(digest, &sha256);
}

ndn_Error
ndn_generateRandomBytes(uint8_t *buffer, size_t bufferLength)
{
  RAND_bytes(buffer, (int)bufferLength);
  return NDN_ERROR_success;
}

void
ndn_computeHmacWithSha256
  (const uint8_t *key, size_t keyLength, const uint8_t *data, size_t dataLength,
   uint8_t *digest)
{
  HMAC(EVP_sha256(), key, keyLength, data, dataLength, digest, 0);
}

int
ndn_verifyHmacWithSha256Signature
  (const uint8_t *key, size_t keyLength, const uint8_t *signature,
   size_t signatureLength, const uint8_t *data, size_t dataLength)
{
  uint8_t dataDigest[ndn_SHA256_DIGEST_SIZE];
  ndn_computeHmacWithSha256(key, keyLength, data, dataLength, dataDigest);

  // Use constant-time CRYPTO_memcmp to avoid timing attacks.
  return signatureLength == ndn_SHA256_DIGEST_SIZE && CRYPTO_memcmp
    (signature, dataDigest, ndn_SHA256_DIGEST_SIZE) == 0;
}

int
ndn_verifyDigestSha256Signature
  (const uint8_t *signature, size_t signatureLength, const uint8_t *data,
   size_t dataLength)
{
  uint8_t dataDigest[ndn_SHA256_DIGEST_SIZE];
  ndn_digestSha256(data, dataLength, dataDigest);

  return signatureLength == ndn_SHA256_DIGEST_SIZE && CRYPTO_memcmp
    (signature, dataDigest, ndn_SHA256_DIGEST_SIZE) == 0;
}

size_t
ndn_getEcKeyInfoCount() { return sizeof(EC_KEY_INFO) / sizeof(EC_KEY_INFO[0]); }

const struct ndn_EcKeyInfo *
ndn_getEcKeyInfo(int i) { return EC_KEY_INFO + i; }

#else

#include <stdlib.h>
#include "time.h"
// Use the openssl code in contrib.
#include "../../../contrib/openssl/sha.h"
#include "ndn_memory.h"

void
ndn_digestSha256(const uint8_t *data, size_t dataLength, uint8_t *digest)
{
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, data, dataLength);
  SHA256_Final(digest, &sha256);
}

static int didRandomSeed = 0;
ndn_Error
ndn_generateRandomBytes(uint8_t *buffer, size_t bufferLength)
{
  // NOTE: This is not cryptographically strong.
  size_t i;
  if (!didRandomSeed) {
    uint64_t milliseconds = (uint64_t)ndn_getNowMilliseconds();
    srand((int)milliseconds);
    didRandomSeed = 1;
  }

  for (i = 0; i < bufferLength; ++i)
    buffer[i] = (uint8_t)rand();

  return NDN_ERROR_success;
}

int
ndn_verifyDigestSha256Signature
  (const uint8_t *signature, size_t signatureLength, const uint8_t *data,
   size_t dataLength)
{
  uint8_t dataDigest[ndn_SHA256_DIGEST_SIZE];
  ndn_digestSha256(data, dataLength, dataDigest);

  return signatureLength == ndn_SHA256_DIGEST_SIZE && ndn_memcmp
    (signature, dataDigest, ndn_SHA256_DIGEST_SIZE) == 0;
}

size_t
ndn_getEcKeyInfoCount() { return 0; }

const struct ndn_EcKeyInfo *
ndn_getEcKeyInfo(int i) { return 0; }

#endif
