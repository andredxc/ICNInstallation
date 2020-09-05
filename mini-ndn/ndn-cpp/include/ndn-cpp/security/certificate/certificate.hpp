/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (C) 2013-2018 Regents of the University of California.
 * @author: Yingdi Yu <yingdi@cs.ucla.edu>
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

#ifndef NDN_CERTIFICATE_HPP
#define NDN_CERTIFICATE_HPP

#include "../../data.hpp"
#include "../../common.hpp"
#include "../../sha256-with-rsa-signature.hpp"

#include "certificate-subject-description.hpp"
#include "certificate-extension.hpp"
#include "public-key.hpp"

namespace ndn {

typedef std::vector<CertificateSubjectDescription> SubjectDescriptionList;
typedef std::vector<CertificateExtension> ExtensionList;

class Certificate : public Data {
public:
  /**
   * The default constructor.
   */
  Certificate();

  /**
   * Create a Certificate from the content in the data packet.
   * @param data The data packet with the content to decode.
   */
  Certificate(const Data& data);

  /**
   * The virtual destructor.
   */
  virtual
  ~Certificate();

  /**
   * Encode the contents of the certificate in DER format and set the Content
   * and MetaInfo fields.
   */
  void
  encode();

  /**
   * Override to call the base class wireDecode then populate the certificate
   * fields.
   * @param input The input byte array to be decoded as an immutable Blob.
   * @param wireFormat A WireFormat object used to decode the input. If omitted,
   * use WireFormat getDefaultWireFormat().
   */
  virtual void
  wireDecode
    (const Blob& input,
     WireFormat& wireFormat = *WireFormat::getDefaultWireFormat());

  /**
   * Add a subject description.
   * @param description The description to be added.
   */
  void
  addSubjectDescription(const CertificateSubjectDescription& description) { subjectDescriptionList_.push_back(description); }

  const SubjectDescriptionList&
  getSubjectDescriptionList() const { return subjectDescriptionList_; }

  SubjectDescriptionList&
  getSubjectDescriptionList() { return subjectDescriptionList_; }

  /**
   * Add a certificate extension.
   * @param extension the extension to be added
   */
  void
  addExtension(const CertificateExtension& extension) { extensionList_.push_back(extension); }

  const ExtensionList&
  getExtensionList() const { return extensionList_; }

  ExtensionList&
  getExtensionList() { return extensionList_; }

  void
  setNotBefore(const MillisecondsSince1970& notBefore) { notBefore_ = notBefore; }

  MillisecondsSince1970&
  getNotBefore() { return notBefore_; }

  const MillisecondsSince1970&
  getNotBefore() const { return notBefore_; }

  void
  setNotAfter(const MillisecondsSince1970& notAfter) { notAfter_ = notAfter; }

  MillisecondsSince1970&
  getNotAfter() { return notAfter_; }

  const MillisecondsSince1970&
  getNotAfter() const { return notAfter_; }

  void
  setPublicKeyInfo(const PublicKey& key) { key_ = key; }

  PublicKey&
  getPublicKeyInfo() { return key_; }

  const PublicKey&
  getPublicKeyInfo() const { return key_; }

  /**
   * Get the public key DER encoding.
   * @return The DER encoding Blob.
   * @throws runtime_error if the public key is not set.
   */
  const Blob&
  getPublicKeyDer() const;

  /**
   * Check if the certificate is valid.
   * @return True if the current time is earlier than notBefore.
   */
  bool
  isTooEarly() const;

  /**
   * Check if the certificate is valid.
   * @return True if the current time is later than notAfter.
   */
  bool
  isTooLate() const;

  bool
  isInValidityPeriod(MillisecondsSince1970 time) const
  {
    // Debug: Generalize this from Sha256WithRsaSignature.
    return dynamic_cast<const Sha256WithRsaSignature *>
      (getSignature())->getValidityPeriod().isValid(time);
  }

  void
  printCertificate(std::ostream& os) const;

  void
  printCertificate() const;

protected:
  void
  decode();

  SubjectDescriptionList subjectDescriptionList_;
  MillisecondsSince1970 notBefore_;
  MillisecondsSince1970 notAfter_;
  PublicKey key_;
  ExtensionList extensionList_;

private:
  ptr_lib::shared_ptr<DerNode>
  toDer();
};

}

#endif
