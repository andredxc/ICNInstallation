/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
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

#include "../../c/security/rsa-public-key.h"
#include <ndn-cpp/lite/security/rsa-public-key-lite.hpp>

#if NDN_CPP_HAVE_LIBCRYPTO

namespace ndn {

RsaPublicKeyLite::RsaPublicKeyLite()
{
  ndn_RsaPublicKey_initialize(this);
}

RsaPublicKeyLite::~RsaPublicKeyLite()
{
  ndn_RsaPublicKey_finalize(this);
}

ndn_Error
RsaPublicKeyLite::decode
  (const uint8_t* publicKeyDer, size_t publicKeyDerLength)
{
  return ndn_RsaPublicKey_decode(this, publicKeyDer, publicKeyDerLength);
}

ndn_Error
RsaPublicKeyLite::encode(uint8_t* encoding, size_t& encodingLength) const
{
  return ndn_RsaPublicKey_encode(this, encoding, &encodingLength);
}

bool
RsaPublicKeyLite::verifyWithSha256
  (const uint8_t* signature, size_t signatureLength, const uint8_t* data,
   size_t dataLength) const
{
  return ndn_RsaPublicKey_verifyWithSha256
    (this, signature, signatureLength, data, dataLength) != 0;
}

ndn_Error
RsaPublicKeyLite::verifySha256WithRsaSignature
  (const uint8_t *signature, size_t signatureLength, const uint8_t *data,
   size_t dataLength, const uint8_t *publicKeyDer, size_t publicKeyDerLength,
   bool &verified)
{
  int intResult;
  ndn_Error status = ndn_verifySha256WithRsaSignature
    (signature, signatureLength, data, dataLength, publicKeyDer,
     publicKeyDerLength, &intResult);
  verified = (intResult != 0);
  return status;
}

ndn_Error
RsaPublicKeyLite::encrypt
  (const uint8_t* plainData, size_t plainDataLength,
   ndn_EncryptAlgorithmType algorithmType, uint8_t* encryptedData,
   size_t& encryptedDataLength) const
{
  return ndn_RsaPublicKey_encrypt
    (this, plainData, plainDataLength, algorithmType, encryptedData,
     &encryptedDataLength);
}

}

#endif // NDN_CPP_HAVE_LIBCRYPTO
