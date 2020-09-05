/**
 * Copyright (C) 2014-2018 Regents of the University of California.
 * @author: Jeff Thompson <jefft0@remap.ucla.edu>
 * From PyNDN unit-tests by Adeola Bannis.
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

#include "gtest/gtest.h"
#include <algorithm>
#include <sstream>
#include <ndn-cpp/security/certificate/certificate.hpp>
#include <ndn-cpp/security/identity/memory-identity-storage.hpp>
#include <ndn-cpp/security/identity/memory-private-key-storage.hpp>
#include <ndn-cpp/security/identity/identity-manager.hpp>
#include "../../src/encoding/der/der-node.hpp"

using namespace std;
using namespace ndn;

typedef DerNode::DerSequence DerSequence;
typedef DerNode::DerOctetString DerOctetString;
typedef DerNode::DerInteger DerInteger;

static const uint8_t PUBLIC_KEY[] = {
0x30, 0x81, 0x9d, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
0x01, 0x05, 0x00, 0x03, 0x81, 0x8b, 0x00, 0x30, 0x81, 0x87, 0x02, 0x81, 0x81, 0x00, 0x9e,
0x06, 0x3e, 0x47, 0x85, 0xb2, 0x34, 0x37, 0xaa, 0x85, 0x47, 0xac, 0x03, 0x24, 0x83, 0xb5,
0x9c, 0xa8, 0x05, 0x3a, 0x24, 0x1e, 0xeb, 0x89, 0x01, 0xbb, 0xe9, 0x9b, 0xb2, 0xc3, 0x22,
0xac, 0x68, 0xe3, 0xf0, 0x6c, 0x02, 0xce, 0x68, 0xa6, 0xc4, 0xd0, 0xa7, 0x06, 0x90, 0x9c,
0xaa, 0x1b, 0x08, 0x1d, 0x8b, 0x43, 0x9a, 0x33, 0x67, 0x44, 0x6d, 0x21, 0xa3, 0x1b, 0x88,
0x9a, 0x97, 0x5e, 0x59, 0xc4, 0x15, 0x0b, 0xd9, 0x2c, 0xbd, 0x51, 0x07, 0x61, 0x82, 0xad,
0xc1, 0xb8, 0xd7, 0xbf, 0x9b, 0xcf, 0x7d, 0x24, 0xc2, 0x63, 0xf3, 0x97, 0x17, 0xeb, 0xfe,
0x62, 0x25, 0xba, 0x5b, 0x4d, 0x8a, 0xc2, 0x7a, 0xbd, 0x43, 0x8a, 0x8f, 0xb8, 0xf2, 0xf1,
0xc5, 0x6a, 0x30, 0xd3, 0x50, 0x8c, 0xc8, 0x9a, 0xdf, 0xef, 0xed, 0x35, 0xe7, 0x7a, 0x62,
0xea, 0x76, 0x7c, 0xbb, 0x08, 0x26, 0xc7, 0x02, 0x01, 0x11
};

static const char* TEST_OID = "2.5.4.41";

static const char* CERT_STRING = "Certificate name:\n\
  /test/KEY/ksk-1457560485494/ID-CERT/%FD%00%00%01S%80H%E1%F3\n\
Validity:\n\
  NotBefore: 20131226T232254.000000\n\
  NotAfter: 20131226T232254.000000\n\
Subject Description:\n\
  2.5.4.41: TEST NAME\n\
Public key bits:\n\
MIGdMA0GCSqGSIb3DQEBAQUAA4GLADCBhwKBgQCeBj5HhbI0N6qFR6wDJIO1nKgF\n\
OiQe64kBu+mbssMirGjj8GwCzmimxNCnBpCcqhsIHYtDmjNnRG0hoxuImpdeWcQV\n\
C9ksvVEHYYKtwbjXv5vPfSTCY/OXF+v+YiW6W02Kwnq9Q4qPuPLxxWow01CMyJrf\n\
7+0153pi6nZ8uwgmxwIBEQ==\n";

static const uint8_t REAL_CERT[] = {
0x30, 0x82, 0x01, 0x63, 0x30, 0x22, 0x18, 0x0f, 0x32, 0x30, 0x31, 0x33, 0x31, 0x31, 0x30,
0x31, 0x31, 0x37, 0x31, 0x31, 0x32, 0x32, 0x5a, 0x18, 0x0f, 0x32, 0x30, 0x31, 0x34, 0x31,
0x31, 0x30, 0x31, 0x31, 0x37, 0x31, 0x31, 0x32, 0x32, 0x5a, 0x30, 0x19, 0x30, 0x17, 0x06,
0x03, 0x55, 0x04, 0x29, 0x13, 0x10, 0x4e, 0x44, 0x4e, 0x20, 0x54, 0x65, 0x73, 0x74, 0x62,
0x65, 0x64, 0x20, 0x52, 0x6f, 0x6f, 0x74, 0x30, 0x82, 0x01, 0x20, 0x30, 0x0d, 0x06, 0x09,
0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0d,
0x00, 0x30, 0x82, 0x01, 0x08, 0x02, 0x82, 0x01, 0x01, 0x00, 0xd3, 0xac, 0x7e, 0x7a, 0x5c,
0x33, 0x58, 0x21, 0xda, 0xe0, 0x8d, 0xdb, 0xca, 0xb6, 0x02, 0x30, 0x02, 0x15, 0xc5, 0x0a,
0x51, 0x54, 0xbb, 0x8e, 0x5e, 0x9d, 0x21, 0xf8, 0x14, 0xbe, 0xe4, 0x63, 0x60, 0x31, 0x53,
0xe2, 0xef, 0xee, 0x34, 0xa3, 0x8c, 0xd2, 0x24, 0x6f, 0xa4, 0x89, 0x4f, 0x02, 0x20, 0x7d,
0x66, 0xb6, 0x3f, 0x11, 0x40, 0x0c, 0xc1, 0x5f, 0xd8, 0x45, 0x23, 0x95, 0x40, 0xc8, 0xe0,
0xbc, 0x9d, 0x2f, 0x03, 0xf1, 0x83, 0x9f, 0x07, 0x0b, 0x76, 0xc9, 0x10, 0xd9, 0x3e, 0x0b,
0x75, 0x13, 0x93, 0xe9, 0xc9, 0x85, 0x01, 0x88, 0x36, 0x2e, 0xab, 0xfc, 0xe6, 0x24, 0x32,
0xfc, 0xc6, 0x3c, 0x40, 0x97, 0x1a, 0xcc, 0xcd, 0x53, 0xaa, 0x0f, 0xfb, 0xa3, 0xfe, 0xf9,
0x24, 0x70, 0x13, 0x3f, 0x4f, 0x5b, 0x7d, 0x43, 0xaa, 0x75, 0x0a, 0x94, 0x72, 0xab, 0xe1,
0x8c, 0x45, 0xb5, 0x78, 0x10, 0x01, 0xef, 0x1f, 0xb3, 0x05, 0x6f, 0xa6, 0xc3, 0xac, 0x7f,
0x6d, 0xf0, 0x31, 0xc4, 0x83, 0xb3, 0x4f, 0x50, 0x26, 0x92, 0x40, 0x1a, 0xdd, 0xec, 0xfb,
0xcb, 0xef, 0x63, 0xfe, 0x41, 0xd8, 0x8d, 0x1f, 0xdc, 0xec, 0xfc, 0x48, 0x95, 0xcc, 0x09,
0x1e, 0x30, 0x6e, 0x22, 0x9e, 0x24, 0x97, 0x2e, 0xe6, 0x0c, 0xdf, 0x3d, 0x20, 0x32, 0xaa,
0x9c, 0xc9, 0x45, 0x14, 0xaf, 0xaa, 0xf5, 0x17, 0xd2, 0x01, 0x98, 0x33, 0xbe, 0x2a, 0x9f,
0x7b, 0x9d, 0x98, 0x7c, 0x54, 0x22, 0xfe, 0x72, 0x72, 0x04, 0xc3, 0x2c, 0xc0, 0x14, 0x0b,
0xa9, 0x40, 0x7e, 0x46, 0xa1, 0x75, 0x16, 0x1a, 0x27, 0x9e, 0xf2, 0x82, 0x96, 0xc0, 0x7d,
0xaf, 0x18, 0x75, 0xfb, 0xbb, 0xab, 0x16, 0x66, 0xc0, 0xa9, 0xd7, 0x93, 0x4c, 0x48, 0x6d,
0xce, 0x0b, 0x88, 0xd4, 0x21, 0x93, 0x84, 0x89, 0x55, 0x05, 0xd5, 0x02, 0x01, 0x11
};

static const char* REAL_CERT_STRING = "Certificate name:\n\
  /tmp\n\
Validity:\n\
  NotBefore: 20131101T171122.000000\n\
  NotAfter: 20141101T171122.000000\n\
Subject Description:\n\
  2.5.4.41: NDN Testbed Root\n\
Public key bits:\n\
MIIBIDANBgkqhkiG9w0BAQEFAAOCAQ0AMIIBCAKCAQEA06x+elwzWCHa4I3byrYC\n\
MAIVxQpRVLuOXp0h+BS+5GNgMVPi7+40o4zSJG+kiU8CIH1mtj8RQAzBX9hFI5VA\n\
yOC8nS8D8YOfBwt2yRDZPgt1E5PpyYUBiDYuq/zmJDL8xjxAlxrMzVOqD/uj/vkk\n\
cBM/T1t9Q6p1CpRyq+GMRbV4EAHvH7MFb6bDrH9t8DHEg7NPUCaSQBrd7PvL72P+\n\
QdiNH9zs/EiVzAkeMG4iniSXLuYM3z0gMqqcyUUUr6r1F9IBmDO+Kp97nZh8VCL+\n\
cnIEwyzAFAupQH5GoXUWGiee8oKWwH2vGHX7u6sWZsCp15NMSG3OC4jUIZOEiVUF\n\
1QIBEQ==\n";

static string getCertificateString(const Certificate& certificate)
{
  ostringstream certificateString;
  certificate.printCertificate(certificateString);
  return certificateString.str();
}

class TestCertificate : public ::testing::Test {
public:
  TestCertificate()
  {
    toyCertNotBefore = 1388100174000L;
    toyCertNotAfter = 1388100174000L;
    Certificate cert;
    cert.setName(Name("/test/KEY/ksk-1457560485494/ID-CERT/%FD%00%00%01S%80H%E1%F3"));
    cert.setNotBefore(toyCertNotBefore);
    cert.setNotAfter(toyCertNotAfter);

    cert.addSubjectDescription(CertificateSubjectDescription(TEST_OID, "TEST NAME"));
    ptr_lib::shared_ptr<PublicKey> tempPublicKey(new PublicKey
      (Blob(PUBLIC_KEY, sizeof(PUBLIC_KEY))));
    cert.setPublicKeyInfo(*tempPublicKey);

    toyCert = cert;
  }

  MillisecondsSince1970 toyCertNotBefore;
  MillisecondsSince1970 toyCertNotAfter;
  Certificate toyCert;
};

TEST_F(TestCertificate, Representation)
{
  ASSERT_EQ(string(CERT_STRING), getCertificateString(toyCert)) <<
    "Certificate dump does not have expected format";
}

TEST_F(TestCertificate, EncodeDecode)
{
  toyCert.encode();
  const Blob& cert_data = toyCert.getContent();
  Data plainData;
  plainData.setName(toyCert.getName());
  plainData.setContent(cert_data);
  // The constructor Certificate(Data) calls decode().
  Certificate decoded_cert(plainData);

  ASSERT_EQ(getCertificateString(toyCert), getCertificateString(decoded_cert)) <<
    "Certificate representation changed after encoding";
}

TEST_F(TestCertificate, Extension)
{
  // Now add an extension.
  string name("/hello/kitty");
  int trustClass = 0;
  int trustLevel = 300;

  ptr_lib::shared_ptr<DerSequence> extValueRoot(new DerSequence());
  ptr_lib::shared_ptr<DerOctetString> extValueName
    (new DerOctetString((uint8_t*)&name[0], name.size()));
  ptr_lib::shared_ptr<DerInteger> extValueTrustClass(new DerInteger(trustClass));
  ptr_lib::shared_ptr<DerInteger> extValueTrustLevel(new DerInteger(trustLevel));

  extValueRoot->addChild(extValueName);
  extValueRoot->addChild(extValueTrustClass);
  extValueRoot->addChild(extValueTrustLevel);

  Blob extValueData = extValueRoot->encode();

  string oidString = "1.3.6.1.5.32.1";
  bool isCritical = true;
  CertificateExtension certExtension(oidString, isCritical, extValueData);
  toyCert.encode();
  Certificate cert(toyCert);
  cert.addExtension(certExtension);

  cert.encode();
  Blob certData = cert.getContent();
  Data plainData;
  plainData.setContent(certData);
  // The constructor Certificate(Data) calls decode().
  Certificate decodedCert(plainData);
  ASSERT_EQ(1, decodedCert.getExtensionList().size()) <<
    "Wrong number of certificate extensions after decoding";

  CertificateExtension& decodedExtension = decodedCert.getExtensionList()[0];
  ASSERT_EQ(oidString, decodedExtension.getOid().toString()) <<
    "Certificate extension has the wrong OID after decoding";
  ASSERT_EQ(isCritical, decodedExtension.getIsCritical()) <<
    "Certificate extension has the wrong isCritical value after decoding";

  // Decode and check the extension value.
  ptr_lib::shared_ptr<DerNode> parsedExtValue = DerNode::parse
    (decodedExtension.getValue());
  const std::vector<ptr_lib::shared_ptr<DerNode> >& decodedExtValueRoot =
    parsedExtValue->getChildren();
  ASSERT_EQ(3, decodedExtValueRoot.size()) <<
    "Wrong number of certificate extension value items after decoding";
  
  DerOctetString& decodedName = dynamic_cast<DerOctetString&>(*decodedExtValueRoot[0]);
  DerInteger& decodedTrustClass = dynamic_cast<DerInteger&>(*decodedExtValueRoot[1]);
  DerInteger& decodedTrustLevel = dynamic_cast<DerInteger&>(*decodedExtValueRoot[2]);
  ASSERT_TRUE(Blob((const uint8_t *)&name[0], name.size()).equals
              (decodedName.toVal())) <<
    "Wrong extension value name after decoding";
  ASSERT_EQ(trustClass, decodedTrustClass.toIntegerVal()) <<
    "Wrong extension value trust class after decoding";
  ASSERT_EQ(trustLevel, decodedTrustLevel.toIntegerVal()) <<
    "Wrong extension value trust level after decoding";
}

TEST_F(TestCertificate, Decode)
{
  Data data(Name("/tmp"));
  data.setContent(Blob(REAL_CERT, sizeof(REAL_CERT)));
  // The constructor Certificate(Data) calls decode().
  Certificate realCert(data);

  ASSERT_EQ(string(REAL_CERT_STRING), getCertificateString(realCert)) <<
    "Certificate representation changed after decoding";
}

TEST_F(TestCertificate, Oid)
{
  string oidString = "1.2.840.113549.1.1.11";
  DerNode::DerOid derOid(oidString);
  string expectedEncoding = "06092a864886f70d01010b";

  ASSERT_EQ(expectedEncoding, derOid.encode().toHex()) <<
    "Incorrect OID encoding";
  Blob value = derOid.toVal();
  ASSERT_EQ(oidString, string((const char*)value.buf(), value.size())) <<
    "Incorrect decoded OID";
}

TEST_F(TestCertificate, PrepareUnsignedCertificate)
{
  ptr_lib::shared_ptr<MemoryIdentityStorage> identityStorage
    (new MemoryIdentityStorage());
  ptr_lib::shared_ptr<MemoryPrivateKeyStorage> privateKeyStorage
    (new MemoryPrivateKeyStorage());
  IdentityManager identityManager(identityStorage, privateKeyStorage);
  Name keyName("/test/ksk-1457560485494");
  identityStorage->addKey
    (keyName, KEY_TYPE_RSA, Blob(PUBLIC_KEY, sizeof(PUBLIC_KEY)));

  vector<CertificateSubjectDescription> subjectDescriptions;
  subjectDescriptions.push_back(CertificateSubjectDescription
    (TEST_OID, "TEST NAME"));
  ptr_lib::shared_ptr<IdentityCertificate> newCertificate =
    identityManager.prepareUnsignedIdentityCertificate
      (keyName, keyName.getPrefix(1), toyCertNotBefore, toyCertNotAfter,
       subjectDescriptions);

  // Update the generated certificate version to equal the one in toyCert.
  newCertificate->setName
    (Name(newCertificate->getName().getPrefix(-1).append
     (toyCert.getName().get(-1))));

  // Make a copy to test encoding.
  IdentityCertificate certificateCopy(*newCertificate);
  ASSERT_EQ(getCertificateString(toyCert), getCertificateString(certificateCopy)) <<
    "Prepared unsigned certificate dump does not have the expected format";
}

int
main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

