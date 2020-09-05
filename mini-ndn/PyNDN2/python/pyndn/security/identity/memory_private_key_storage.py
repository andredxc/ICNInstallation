# -*- Mode:python; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
#
# Copyright (C) 2014-2018 Regents of the University of California.
# Author: Jeff Thompson <jefft0@remap.ucla.edu>
# From ndn-cxx security by Yingdi Yu <yingdi@cs.ucla.edu>.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# A copy of the GNU Lesser General Public License is in the file COPYING.

"""
This module defines the MemoryPrivateKeyStorage class which extends
PrivateKeyStorage to implement private key storage in memory.
"""

from pyndn.util.blob import Blob
from pyndn.security.security_types import DigestAlgorithm
from pyndn.security.security_types import KeyClass
from pyndn.security.security_types import KeyType
from pyndn.security.security_exception import SecurityException
from pyndn.security.certificate.public_key import PublicKey
from pyndn.security.tpm.tpm_private_key import TpmPrivateKey
from pyndn.security.identity.private_key_storage import PrivateKeyStorage

class MemoryPrivateKeyStorage(PrivateKeyStorage):
    def __init__(self):
        super(MemoryPrivateKeyStorage, self).__init__()
        # The key is the keyName.toUri(). The value is security.certificate.PublicKey.
        self._publicKeyStore = {}
        # The key is the keyName.toUri(). The value is TpmPrivateKey.
        self._privateKeyStore = {}

    def setPublicKeyForKeyName(self, keyName, keyType, publicKeyDer):
        """
        Set the public key for the keyName.

        :param Name keyName: The key name.
        :param keyType: The KeyType, such as KeyType.RSA.
        :type keyType: an int from KeyType
        :param publicKeyDer: The public key DER byte array.
        :type publicKeyDer: str, or an array type with int elements which is
          converted to str
        """
        self._publicKeyStore[keyName.toUri()] = PublicKey(
          Blob(publicKeyDer, True))

    def setPrivateKeyForKeyName(self, keyName, keyType, privateKeyDer):
        """
        Set the private key for the keyName.

        :param Name keyName: The key name.
        :param keyType: The KeyType, such as KeyType.RSA.
        :type keyType: an int from KeyType
        :param privateKeyDer: The private key DER byte array.
        :type privateKeyDer: str, or an array type with int elements which is
          converted to str
        """
        privateKey = TpmPrivateKey()
        try:
            privateKey.loadPkcs8(privateKeyDer, keyType)
        except Exception as ex:
            raise SecurityException("Error in loadPkcs8: " + str(ex))
        self._privateKeyStore[keyName.toUri()] = privateKey

    def setKeyPairForKeyName(
          self, keyName, keyType, publicKeyDer, privateKeyDer = None):
        """
        Set the public and private key for the keyName.

        :param Name keyName: The key name.
        :param keyType: The KeyType, such as KeyType.RSA.
        :type keyType: an int from KeyType
        :param publicKeyDer: The public key DER byte array.
        :type publicKeyDer: str, or an array type with int elements which is
          converted to str
        :param privateKeyDer: The private key DER byte array.
        :type privateKeyDer: str, or an array type with int elements which is
          converted to str
        """
        if not type(keyType) is int:
            # Using the deprecated form setKeyPairForKeyName(keyName, publicKeyDer, privateKeyDer).
            # Shift arguments.
            privateKeyDer = publicKeyDer
            publicKeyDer = keyType
            keyType = KeyType.RSA

        self.setPublicKeyForKeyName(keyName, keyType, publicKeyDer)
        self.setPrivateKeyForKeyName(keyName, keyType, privateKeyDer)

    def generateKeyPair(self, keyName, params):
        """
        Generate a pair of asymmetric keys.

        :param Name keyName: The name of the key pair.
        :param KeyParams params: The parameters of the key.
        """
        privateKey = None
        try:
            privateKey = TpmPrivateKey.generatePrivateKey(params)
        except Exception as ex:
            raise SecurityException("Error in generatePrivateKey: " + str(ex))

        publicKeyDer = None
        try:
            publicKeyDer = privateKey.derivePublicKey()
        except Exception as ex:
            raise SecurityException("Error in derivePublicKey: " + str(ex))

        self._privateKeyStore[keyName.toUri()] = privateKey
        self._publicKeyStore[keyName.toUri()] = PublicKey(publicKeyDer)

    def deleteKeyPair(self, keyName):
        """
        Delete a pair of asymmetric keys. If the key doesn't exist, do nothing.

        :param Name keyName: The name of the key pair.
        """
        keyUri = keyName.toUri()

        try:
            del self._publicKeyStore[keyUri]
        except KeyError:
            pass

        try:
            del self._privateKeyStore[keyUri]
        except KeyError:
            pass

    def getPublicKey(self, keyName):
        """
        Get the public key with the keyName.

        :param Name keyName: The name of public key.
        :return: The public key.
        :rtype: PublicKey
        """
        keyUri = keyName.toUri()
        if not (keyUri in self._publicKeyStore):
            raise SecurityException(
              "MemoryPrivateKeyStorage: Cannot find public key " +
              keyName.toUri())

        return self._publicKeyStore[keyUri]

    def sign(self, data, keyName, digestAlgorithm = DigestAlgorithm.SHA256):
        """
        Fetch the private key for keyName and sign the data, returning a
        signature Blob.

        :param data: The input byte buffer to sign.
        :type data: an array which implements the buffer protocol
        :param Name keyName: The name of the signing key.
        :param digestAlgorithm: (optional) the digest algorithm. If omitted,
          use DigestAlgorithm.SHA256.
        :type digestAlgorithm: int from DigestAlgorithm
        :return: The signature Blob.
        :rtype: Blob
        :raises SecurityException: if can't find the private key with keyName.
        """
        # Find the private key.
        keyUri = keyName.toUri()
        if not keyUri in self._privateKeyStore:
            raise SecurityException(
              "MemoryPrivateKeyStorage: Cannot find private key " + keyUri)
        privateKey = self._privateKeyStore[keyUri]

        try:
            return privateKey.sign(Blob(data, False).toBytes(), digestAlgorithm)
        except Exception as ex:
            raise SecurityException("Error in sign: " + str(ex))

    def doesKeyExist(self, keyName, keyClass):
        """
        Check if a particular key exists.

        :param Name keyName: The name of the key.
        :param keyClass: The class of the key, e.g. KeyClass.PUBLIC,
           KeyClass.PRIVATE, or KeyClass.SYMMETRIC.
        :type keyClass: int from KeyClass
        :return: True if the key exists, otherwise false.
        :rtype: bool
        """
        keyUri = keyName.toUri()
        if keyClass == KeyClass.PUBLIC:
          return keyUri in self._publicKeyStore
        elif keyClass == KeyClass.PRIVATE:
          return keyUri in self._privateKeyStore
        else:
          # KeyClass.SYMMETRIC not implemented yet.
          return False
