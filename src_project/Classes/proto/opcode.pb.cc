// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: opcode.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "opcode.pb.h"

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

const ::google::protobuf::EnumDescriptor* Opcode_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_opcode_2eproto() {
  protobuf_AddDesc_opcode_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "opcode.proto");
  GOOGLE_CHECK(file != NULL);
  Opcode_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_opcode_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_opcode_2eproto() {
}

void protobuf_AddDesc_opcode_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\014opcode.proto\022\002pb*\262\010\n\006Opcode\022\021\n\rMSG_PIN"
    "G_PONG\020\001\022\r\n\tMSG_LOGIN\020\002\022\022\n\016MSG_JOIN_TABL"
    "E\020\003\022\034\n\030MSG_JOIN_TABLE_BROADCAST\020\004\022\023\n\017MSG"
    "_LEAVE_TABLE\020\005\022\035\n\031MSG_LEAVE_TABLE_BROADC"
    "AST\020\006\022\027\n\023MSG_BREAK_BROADCAST\020\007\022\034\n\030MSG_BR"
    "EAK_BACK_BROADCAST\020\010\022\r\n\tMSG_READY\020\t\022\027\n\023M"
    "SG_READY_BROADCAST\020\n\022\035\n\031MSG_DISMISS_ASK_"
    "BROADCAST\020\014\022\026\n\022MSG_DISMISS_ANSWER\020\r\022 \n\034M"
    "SG_DISMISS_ANSWER_BROADCAST\020\016\022\031\n\025MSG_DIS"
    "MISS_BROADCAST\020\017\022\022\n\016MSG_GET_JU_CNT\020\020\022\031\n\025"
    "MSG_GET_RESULT_DETAIL\020\021\022\024\n\020MSG_RESULT_TO"
    "TAL\020\022\022\021\n\rMSG_RESULT_PK\020\023\022\035\n\031MSG_DINGQUE_"
    "ASK_BROADCAST\020\024\022\026\n\022MSG_DINGQUE_ANSWER\020\025\022"
    " \n\034MSG_DINGQUE_ANSWER_BROADCAST\020\026\022\035\n\031MSG"
    "_ROUND_START_BROADCAST\020e\022\036\n\032MSG_ROUND_RE"
    "SULT_BROADCAST\020f\022\032\n\026MSG_DISPATCH_BROADCA"
    "ST\020g\022\013\n\007MSG_OUT\020h\022\025\n\021MSG_OUT_BROADCAST\020i"
    "\022\035\n\031MSG_OPERATE_ASK_BROADCAST\020j\022 \n\034MSG_O"
    "PERATE_RESULT_BROADCAST\020k\022\017\n\013MSG_OPERATE"
    "\020l\022\017\n\013MSG_MINGLOU\020n\022\031\n\025MSG_MINGLOU_BROAD"
    "CAST\020o\022\023\n\017MSG_MINGLOU_ASK\020p\022\014\n\010MSG_CHAT\020"
    "x\022\026\n\022MSG_CHAT_BROADCAST\020y\022\031\n\025MSG_HISTORY"
    "_BROADCAST\020z\022\022\n\016MSG_VOICE_TALK\020{\022\034\n\030MSG_"
    "VOICE_TALK_BROADCAST\020|\022\023\n\017MSG_CHAT_CUSTO"
    "M\020}\022\035\n\031MSG_CHAT_CUSTOM_BROADCAST\020~\022\021\n\014MS"
    "G_GAME_END\020\347\007\022\025\n\020MSG_SOCIAL_BEGIN\020\350\007\022\023\n\016"
    "MSG_SOCIAL_END\020\317\017\022\022\n\rMSG_NET_BEGIN\020\320\017\022\020\n"
    "\013MSG_NET_END\020\332\017", 1095);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "opcode.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_opcode_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_opcode_2eproto {
  StaticDescriptorInitializer_opcode_2eproto() {
    protobuf_AddDesc_opcode_2eproto();
  }
} static_descriptor_initializer_opcode_2eproto_;
const ::google::protobuf::EnumDescriptor* Opcode_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Opcode_descriptor_;
}
bool Opcode_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
    case 110:
    case 111:
    case 112:
    case 120:
    case 121:
    case 122:
    case 123:
    case 124:
    case 125:
    case 126:
    case 999:
    case 1000:
    case 1999:
    case 2000:
    case 2010:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)