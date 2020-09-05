# -*- Mode:python; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
#
# Copyright (C) 2014-2018 Regents of the University of California.
# Author: Jeff Thompson <jefft0@remap.ucla.edu>
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
This module defines the Sha256WithRsaSignature class which extends Signature and
holds the signature bits and other info representing a SHA256-with-RSA signature
in a data packet.
"""

from pyndn.signature import Signature
from pyndn.util.change_counter import ChangeCounter
from pyndn.util.blob import Blob
from pyndn.key_locator import KeyLocator
from pyndn.validity_period import ValidityPeriod

class Sha256WithRsaSignature(Signature):
    """
    Create a new Sha256WithRsaSignature object, possibly copying values from
    another object.

    :param value: (optional) If value is a Sha256WithRsaSignature, copy its
      values.  If value is omitted, the keyLocator is the default with
      unspecified values and the signature is unspecified.
    :type value: Sha256WithRsaSignature
    """
    def __init__(self, value = None):
        if value == None:
            self._keyLocator = ChangeCounter(KeyLocator())
            self._validityPeriod = ChangeCounter(ValidityPeriod())
            self._signature = Blob()
        elif isinstance(value, Sha256WithRsaSignature):
            # Copy its values.
            self._keyLocator = ChangeCounter(KeyLocator(value.getKeyLocator()))
            self._validityPeriod = ChangeCounter(ValidityPeriod(value.getValidityPeriod()))
            self._signature = value._signature
        else:
            raise RuntimeError(
              "Unrecognized type for Sha256WithRsaSignature constructor: " +
              str(type(value)))

        self._changeCount = 0

    def clone(self):
        """
        Create a new Sha256WithRsaSignature which is a copy of this object.

        :return: A new object which is a copy of this object.
        :rtype: Sha256WithRsaSignature
        """
        return Sha256WithRsaSignature(self)

    def getKeyLocator(self):
        """
        Get the key locator.

        :return: The key locator.
        :rtype: KeyLocator
        """
        return self._keyLocator.get()

    def getValidityPeriod(self):
        """
        Get the validity period.

        :return: The validity period.
        :rtype: ValidityPeriod
        """
        return self._validityPeriod.get()

    def getSignature(self):
        """
        Get the data packet's signature bytes.

        :return: The signature bytes as a Blob, which maybe isNull().
        :rtype: Blob
        """
        return self._signature

    def setKeyLocator(self, keyLocator):
        """
        Set the key locator to a copy of the given keyLocator.

        :param KeyLocator keyLocator: The KeyLocator to copy.
        """
        self._keyLocator.set(KeyLocator(keyLocator))
        self._changeCount += 1

    def setValidityPeriod(self, validityPeriod):
        """
        Set the validity period to a copy of the given ValidityPeriod.

        :param ValidityPeriod validityPeriod: The ValidityPeriod which is copied.
        """
        self._validityPeriod.set(ValidityPeriod(validityPeriod))
        self._changeCount += 1

    def setSignature(self, signature):
        """
        Set the signature bytes to the given value.

        :param signature: The array with the signature bytes. If signature is
          not a Blob, then create a new Blob to copy the bytes (otherwise
          take another pointer to the same Blob).
        :type signature: A Blob or an array type with int elements
        """
        self._signature = (signature if isinstance(signature, Blob)
                           else Blob(signature))
        self._changeCount += 1

    def clear(self):
        self._keyLocator.get().clear()
        self._signature = Blob()
        self._changeCount += 1

    def getChangeCount(self):
        """
        Get the change count, which is incremented each time this object
        (or a child object) is changed.

        :return: The change count.
        :rtype: int
        """
        # Make sure each of the checkChanged is called.
        changed = self._keyLocator.checkChanged()
        changed = self._validityPeriod.checkChanged() or changed
        if changed:
            # A child object has changed, so update the change count.
            self._changeCount += 1

        return self._changeCount

    # Create managed properties for read/write properties of the class for more pythonic syntax.
    keyLocator = property(getKeyLocator, setKeyLocator)
    signature = property(getSignature, setSignature)
