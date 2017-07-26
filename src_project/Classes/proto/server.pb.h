// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: server.proto

#ifndef PROTOBUF_server_2eproto__INCLUDED
#define PROTOBUF_server_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include "command.pb.h"
// @@protoc_insertion_point(includes)

namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_server_2eproto();
void protobuf_AssignDesc_server_2eproto();
void protobuf_ShutdownFile_server_2eproto();


enum SerOpcode {
  GMSG_ENTER_ROOM = 10000,
  GMSG_LEAVE_ROOM = 10001,
  GMSG_ADMIN_OPERATE = 10002,
  GMSG_CHANGE_USR_STATUS = 10003,
  GMSG_KICK_FROM_GATE = 10004,
  GMSG_ON_LOGIN = 10005,
  GMSG_GM_COMMAND = 10006,
  GMSG_ADMIN_ANALYSIS = 10007,
  GMSG_AUTHORIZE = 10008,
  GMSG_ON_LOAD_READY = 10009,
  GMSG_PAY_COMMAND = 10010,
  GMSG_OTHER_LOGIN = 10011,
  GMSG_ONLY_LOGIN = 10012
};
bool SerOpcode_IsValid(int value);
const SerOpcode SerOpcode_MIN = GMSG_ENTER_ROOM;
const SerOpcode SerOpcode_MAX = GMSG_ONLY_LOGIN;
const int SerOpcode_ARRAYSIZE = SerOpcode_MAX + 1;

const ::google::protobuf::EnumDescriptor* SerOpcode_descriptor();
inline const ::std::string& SerOpcode_Name(SerOpcode value) {
  return ::google::protobuf::internal::NameOfEnum(
    SerOpcode_descriptor(), value);
}
inline bool SerOpcode_Parse(
    const ::std::string& name, SerOpcode* value) {
  return ::google::protobuf::internal::ParseNamedEnum<SerOpcode>(
    SerOpcode_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::pb::SerOpcode>() {
  return ::pb::SerOpcode_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_server_2eproto__INCLUDED