// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: version.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "version.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace pb {

namespace {

const ::google::protobuf::EnumDescriptor* protocol_Version_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_version_2eproto() {
  protobuf_AddDesc_version_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "version.proto");
  GOOGLE_CHECK(file != NULL);
  protocol_Version_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_version_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_version_2eproto() {
}

void protobuf_AddDesc_version_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rversion.proto\022\002pb*(\n\020protocol_Version\022"
    "\024\n\020protocol_version\020\003", 61);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "version.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_version_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_version_2eproto {
  StaticDescriptorInitializer_version_2eproto() {
    protobuf_AddDesc_version_2eproto();
  }
} static_descriptor_initializer_version_2eproto_;
const ::google::protobuf::EnumDescriptor* protocol_Version_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return protocol_Version_descriptor_;
}
bool protocol_Version_IsValid(int value) {
  switch(value) {
    case 3:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)