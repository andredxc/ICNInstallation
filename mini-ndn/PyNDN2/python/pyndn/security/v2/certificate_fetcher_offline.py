# -*- Mode:python; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
#
# Copyright (C) 2018 Regents of the University of California.
# Author: Jeff Thompson <jefft0@remap.ucla.edu>
# Author: From ndn-cxx security https://github.com/named-data/ndn-cxx/blob/master/src/security/v2/certificate-fetcher-offline.hpp
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
This module defines the CertificateFetcherOffline class which extends
CertificateFetcher to implement a fetcher that does not fetch certificates
(always offline).
"""

from pyndn.security.v2.validation_error import ValidationError
from pyndn.security.v2.certificate_fetcher import CertificateFetcher

class CertificateFetcherOffline(CertificateFetcher):
    def __init__(self):
        super(CertificateFetcherOffline, self).__init__()

    def _doFetch(self, certificateRequest, state, continueValidation):
        """
        :type certificateRequest: CertificateRequest
        :type state: TValidationState
        :type continueValidation: function object
        """
        state.fail(ValidationError
          (ValidationError.CANNOT_RETRIEVE_CERTIFICATE,
           "Cannot fetch certificate " +
           certificateRequest._interest.getName().toUri() + " in offline mode"))
