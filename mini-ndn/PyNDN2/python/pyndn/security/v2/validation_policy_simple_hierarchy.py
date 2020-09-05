# -*- Mode:python; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
#
# Copyright (C) 2018 Regents of the University of California.
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
This module defines the ValidationPolicySimpleHierarchy class which extends
ValidationPolicy to implement a Validation policy for a simple hierarchical
trust model.
"""

from pyndn.interest import Interest
from pyndn.security.v2.certificate_request import CertificateRequest
from pyndn.security.v2.validation_error import ValidationError
from pyndn.security.v2.validation_policy import ValidationPolicy

class ValidationPolicySimpleHierarchy(ValidationPolicy):
    def __init__(self):
        super(ValidationPolicySimpleHierarchy, self).__init__()

    def checkPolicy(self, dataOrInterest, state, continueValidation):
        """
        :param dataOrInterest:
        :type dataOrInterest: Data or Interest
        :param ValidationState state:
        :param continueValidation:
        :type continueValidation: function object
        """
        keyLocatorName = ValidationPolicy.getKeyLocatorName(dataOrInterest, state)
        if state.isOutcomeFailed():
            # Already called state.fail().
            return

        if keyLocatorName.getPrefix(-2).isPrefixOf(dataOrInterest.getName()):
            continueValidation(CertificateRequest(Interest(keyLocatorName)), state)
        else:
            state.fail(ValidationError(ValidationError.INVALID_KEY_LOCATOR,
              "Signing policy violation for " + dataOrInterest.getName().toUri() +
              " by " + keyLocatorName.toUri()))
