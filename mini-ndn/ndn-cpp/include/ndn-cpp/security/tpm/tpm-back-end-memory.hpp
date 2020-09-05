/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (C) 2017-2018 Regents of the University of California.
 * @author: Jeff Thompson <jefft0@remap.ucla.edu>
 * @author: From ndn-cxx security https://github.com/named-data/ndn-cxx/blob/master/src/security/tpm/back-end-mem.hpp
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

#ifndef NDN_TPM_BACK_END_MEMORY_HPP
#define NDN_TPM_BACK_END_MEMORY_HPP

#include <map>
#include "tpm-back-end.hpp"

namespace ndn {

class TpmPrivateKey;

/**
 * TpmBackEndMemory extends TpmBackEnd to implement a TPM back-end using
 * in-memory storage.
 */
class TpmBackEndMemory : public TpmBackEnd {
public:
  TpmBackEndMemory();

  static std::string
  getScheme() { return "tpm-memory"; }

private:
  /**
   * Check if the key with name keyName exists in the TPM.
   * @param keyName The name of the key.
   * @return True if the key exists.
   */
  virtual bool
  doHasKey(const Name& keyName) const;

  /**
   * Get the handle of the key with name keyName.
   * @param keyName The name of the key.
   * @return The handle of the key, or null if the key does not exist.
   */
  virtual ptr_lib::shared_ptr<TpmKeyHandle>
  doGetKeyHandle(const Name& keyName) const;

  /**
   * Create a key for identityName according to params. The created key is
   * named as: /<identityName>/[keyId]/KEY . The key name is set in the returned
   * TpmKeyHandle.
   * @param identityName The name if the identity.
   * @param params The KeyParams for creating the key.
   * @return The handle of the created key.
   * @throws TpmBackEnd::Error if the key cannot be created.
   */
  virtual ptr_lib::shared_ptr<TpmKeyHandle>
  doCreateKey(const Name& identityName, const KeyParams& params);

  /**
   * Delete the key with name keyName. If the key doesn't exist, do nothing.
   * @param keyName The name of the key to delete.
   * @throws TpmBackEnd::Error if the deletion fails.
   */
  virtual void
  doDeleteKey(const Name& keyName);

  /**
   * Get the encoded private key with name keyName in PKCS #8 format, possibly
   * password-encrypted.
   * @param keyName The name of the key in the TPM.
   * @param password The password for encrypting the private key. If the
   * password is supplied, use it to return a PKCS #8 EncryptedPrivateKeyInfo.
   * If the password is null, return an unencrypted PKCS #8 PrivateKeyInfo.
   * @param passwordLength The length of the password. If password is null, this
   * is ignored.
   * @return The encoded private key.
   * @throws TpmBackEnd::Error if the key does not exist or if the key cannot be
   * exported, e.g., insufficient privileges.
   */
  virtual Blob
  doExportKey(const Name& keyName, const uint8_t* password, size_t passwordLength);

  /**
   * Import an encoded private key with name keyName in PKCS #8 format, possibly
   * password-encrypted.
   * @param keyName The name of the key to use in the TPM.
   * @param pkcs8 The input byte array. If the password is supplied, this is a
   * PKCS #8 EncryptedPrivateKeyInfo. If the password is null, this is an
   * unencrypted PKCS #8 PrivateKeyInfo.
   * @param pkcs8Length The length of the input byte array.
   * @param password The password for decrypting the private key. If the
   * password is supplied, use it to decrypt the PKCS #8 EncryptedPrivateKeyInfo.
   * If the password is null, import an unencrypted PKCS #8 PrivateKeyInfo.
   * @param passwordLength The length of the password. If password is null, this
   * is ignored.
   * @throws TpmBackEnd::Error for an error importing the key.
   */
  virtual void
  doImportKey
    (const Name& keyName, const uint8_t* pkcs8, size_t pkcs8Length,
     const uint8_t* password, size_t passwordLength);

  // Disable the copy constructor and assignment operator.
  TpmBackEndMemory(const TpmBackEndMemory& other);
  TpmBackEndMemory& operator=(const TpmBackEndMemory& other);

  std::map<Name, ptr_lib::shared_ptr<TpmPrivateKey>> keys_;
};

}

#endif
