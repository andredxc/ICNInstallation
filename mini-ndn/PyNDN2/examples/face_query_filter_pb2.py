# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: face-query-filter.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='face-query-filter.proto',
  package='ndn_message',
  syntax='proto2',
  serialized_pb=_b('\n\x17\x66\x61\x63\x65-query-filter.proto\x12\x0bndn_message\"\xb4\x04\n\x16\x46\x61\x63\x65QueryFilterMessage\x12O\n\x11\x66\x61\x63\x65_query_filter\x18\x96\x01 \x03(\x0b\x32\x33.ndn_message.FaceQueryFilterMessage.FaceQueryFilter\x1a\xae\x02\n\x0f\x46\x61\x63\x65QueryFilter\x12\x0f\n\x07\x66\x61\x63\x65_id\x18i \x01(\x04\x12\x13\n\nuri_scheme\x18\x83\x01 \x01(\t\x12\x0b\n\x03uri\x18r \x01(\t\x12\x12\n\tlocal_uri\x18\x81\x01 \x01(\t\x12\x42\n\nface_scope\x18\x84\x01 \x01(\x0e\x32-.ndn_message.FaceQueryFilterMessage.FaceScope\x12N\n\x10\x66\x61\x63\x65_persistency\x18\x85\x01 \x01(\x0e\x32\x33.ndn_message.FaceQueryFilterMessage.FacePersistency\x12@\n\tlink_type\x18\x86\x01 \x01(\x0e\x32,.ndn_message.FaceQueryFilterMessage.LinkType\"%\n\tFaceScope\x12\r\n\tNON_LOCAL\x10\x00\x12\t\n\x05LOCAL\x10\x01\"?\n\x0f\x46\x61\x63\x65Persistency\x12\x0e\n\nPERSISTENT\x10\x00\x12\r\n\tON_DEMAND\x10\x01\x12\r\n\tPERMANENT\x10\x02\"0\n\x08LinkType\x12\x12\n\x0ePOINT_TO_POINT\x10\x00\x12\x10\n\x0cMULTI_ACCESS\x10\x01')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)



_FACEQUERYFILTERMESSAGE_FACESCOPE = _descriptor.EnumDescriptor(
  name='FaceScope',
  full_name='ndn_message.FaceQueryFilterMessage.FaceScope',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NON_LOCAL', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LOCAL', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=453,
  serialized_end=490,
)
_sym_db.RegisterEnumDescriptor(_FACEQUERYFILTERMESSAGE_FACESCOPE)

_FACEQUERYFILTERMESSAGE_FACEPERSISTENCY = _descriptor.EnumDescriptor(
  name='FacePersistency',
  full_name='ndn_message.FaceQueryFilterMessage.FacePersistency',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='PERSISTENT', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ON_DEMAND', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PERMANENT', index=2, number=2,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=492,
  serialized_end=555,
)
_sym_db.RegisterEnumDescriptor(_FACEQUERYFILTERMESSAGE_FACEPERSISTENCY)

_FACEQUERYFILTERMESSAGE_LINKTYPE = _descriptor.EnumDescriptor(
  name='LinkType',
  full_name='ndn_message.FaceQueryFilterMessage.LinkType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='POINT_TO_POINT', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MULTI_ACCESS', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=557,
  serialized_end=605,
)
_sym_db.RegisterEnumDescriptor(_FACEQUERYFILTERMESSAGE_LINKTYPE)


_FACEQUERYFILTERMESSAGE_FACEQUERYFILTER = _descriptor.Descriptor(
  name='FaceQueryFilter',
  full_name='ndn_message.FaceQueryFilterMessage.FaceQueryFilter',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='face_id', full_name='ndn_message.FaceQueryFilterMessage.FaceQueryFilter.face_id', index=0,
      number=105, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='uri_scheme', full_name='ndn_message.FaceQueryFilterMessage.FaceQueryFilter.uri_scheme', index=1,
      number=131, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='uri', full_name='ndn_message.FaceQueryFilterMessage.FaceQueryFilter.uri', index=2,
      number=114, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='local_uri', full_name='ndn_message.FaceQueryFilterMessage.FaceQueryFilter.local_uri', index=3,
      number=129, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='face_scope', full_name='ndn_message.FaceQueryFilterMessage.FaceQueryFilter.face_scope', index=4,
      number=132, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='face_persistency', full_name='ndn_message.FaceQueryFilterMessage.FaceQueryFilter.face_persistency', index=5,
      number=133, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='link_type', full_name='ndn_message.FaceQueryFilterMessage.FaceQueryFilter.link_type', index=6,
      number=134, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=149,
  serialized_end=451,
)

_FACEQUERYFILTERMESSAGE = _descriptor.Descriptor(
  name='FaceQueryFilterMessage',
  full_name='ndn_message.FaceQueryFilterMessage',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='face_query_filter', full_name='ndn_message.FaceQueryFilterMessage.face_query_filter', index=0,
      number=150, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_FACEQUERYFILTERMESSAGE_FACEQUERYFILTER, ],
  enum_types=[
    _FACEQUERYFILTERMESSAGE_FACESCOPE,
    _FACEQUERYFILTERMESSAGE_FACEPERSISTENCY,
    _FACEQUERYFILTERMESSAGE_LINKTYPE,
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=41,
  serialized_end=605,
)

_FACEQUERYFILTERMESSAGE_FACEQUERYFILTER.fields_by_name['face_scope'].enum_type = _FACEQUERYFILTERMESSAGE_FACESCOPE
_FACEQUERYFILTERMESSAGE_FACEQUERYFILTER.fields_by_name['face_persistency'].enum_type = _FACEQUERYFILTERMESSAGE_FACEPERSISTENCY
_FACEQUERYFILTERMESSAGE_FACEQUERYFILTER.fields_by_name['link_type'].enum_type = _FACEQUERYFILTERMESSAGE_LINKTYPE
_FACEQUERYFILTERMESSAGE_FACEQUERYFILTER.containing_type = _FACEQUERYFILTERMESSAGE
_FACEQUERYFILTERMESSAGE.fields_by_name['face_query_filter'].message_type = _FACEQUERYFILTERMESSAGE_FACEQUERYFILTER
_FACEQUERYFILTERMESSAGE_FACESCOPE.containing_type = _FACEQUERYFILTERMESSAGE
_FACEQUERYFILTERMESSAGE_FACEPERSISTENCY.containing_type = _FACEQUERYFILTERMESSAGE
_FACEQUERYFILTERMESSAGE_LINKTYPE.containing_type = _FACEQUERYFILTERMESSAGE
DESCRIPTOR.message_types_by_name['FaceQueryFilterMessage'] = _FACEQUERYFILTERMESSAGE

FaceQueryFilterMessage = _reflection.GeneratedProtocolMessageType('FaceQueryFilterMessage', (_message.Message,), dict(

  FaceQueryFilter = _reflection.GeneratedProtocolMessageType('FaceQueryFilter', (_message.Message,), dict(
    DESCRIPTOR = _FACEQUERYFILTERMESSAGE_FACEQUERYFILTER,
    __module__ = 'face_query_filter_pb2'
    # @@protoc_insertion_point(class_scope:ndn_message.FaceQueryFilterMessage.FaceQueryFilter)
    ))
  ,
  DESCRIPTOR = _FACEQUERYFILTERMESSAGE,
  __module__ = 'face_query_filter_pb2'
  # @@protoc_insertion_point(class_scope:ndn_message.FaceQueryFilterMessage)
  ))
_sym_db.RegisterMessage(FaceQueryFilterMessage)
_sym_db.RegisterMessage(FaceQueryFilterMessage.FaceQueryFilter)


# @@protoc_insertion_point(module_scope)
