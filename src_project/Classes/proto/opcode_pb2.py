# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: opcode.proto

from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='opcode.proto',
  package='pb',
  serialized_pb='\n\x0copcode.proto\x12\x02pb*\xcd\x07\n\x06Opcode\x12\x11\n\rMSG_PING_PONG\x10\x01\x12\x15\n\x11MSG_PING_PONG_ASK\x10\x11\x12\r\n\tMSG_LOGIN\x10\x02\x12\x12\n\x0eMSG_JOIN_TABLE\x10\x03\x12\x1c\n\x18MSG_JOIN_TABLE_BROADCAST\x10\x04\x12\x13\n\x0fMSG_LEAVE_TABLE\x10\x05\x12\x1d\n\x19MSG_LEAVE_TABLE_BROADCAST\x10\x06\x12\x17\n\x13MSG_BREAK_BROADCAST\x10\x07\x12\x1c\n\x18MSG_BREAK_BACK_BROADCAST\x10\x08\x12\r\n\tMSG_READY\x10\t\x12\x17\n\x13MSG_READY_BROADCAST\x10\n\x12\x1d\n\x19MSG_DISMISS_ASK_BROADCAST\x10\x0c\x12\x16\n\x12MSG_DISMISS_ANSWER\x10\r\x12 \n\x1cMSG_DISMISS_ANSWER_BROADCAST\x10\x0e\x12\x19\n\x15MSG_DISMISS_BROADCAST\x10\x0f\x12\x12\n\x0eMSG_GET_JU_CNT\x10\x10\x12\x1d\n\x19MSG_ROUND_START_BROADCAST\x10\x65\x12\x1e\n\x1aMSG_ROUND_RESULT_BROADCAST\x10\x66\x12\x1f\n\x1bMSG_START_REPLACE_BROADCAST\x10g\x12\x1a\n\x16MSG_DISPATCH_BROADCAST\x10h\x12\x0b\n\x07MSG_OUT\x10i\x12\x15\n\x11MSG_OUT_BROADCAST\x10j\x12\x1d\n\x19MSG_OPERATE_ASK_BROADCAST\x10k\x12 \n\x1cMSG_OPERATE_RESULT_BROADCAST\x10l\x12\x0f\n\x0bMSG_OPERATE\x10m\x12\x0f\n\x0bMSG_MINGLOU\x10n\x12\x19\n\x15MSG_MINGLOU_BROADCAST\x10o\x12\x13\n\x0fMSG_MINGLOU_ASK\x10p\x12\x0c\n\x08MSG_CHAT\x10x\x12\x16\n\x12MSG_CHAT_BROADCAST\x10y\x12\x19\n\x15MSG_HISTORY_BROADCAST\x10z\x12\x12\n\x0eMSG_VOICE_TALK\x10{\x12\x1c\n\x18MSG_VOICE_TALK_BROADCAST\x10|\x12\x13\n\x0fMSG_CHAT_CUSTOM\x10}\x12\x1d\n\x19MSG_CHAT_CUSTOM_BROADCAST\x10~\x12\x11\n\x0cMSG_GAME_END\x10\xe7\x07\x12\x15\n\x10MSG_SOCIAL_BEGIN\x10\xe8\x07\x12\x13\n\x0eMSG_SOCIAL_END\x10\xcf\x0f\x12\x12\n\rMSG_NET_BEGIN\x10\xd0\x0f\x12\x10\n\x0bMSG_NET_END\x10\xda\x0f')

_OPCODE = _descriptor.EnumDescriptor(
  name='Opcode',
  full_name='pb.Opcode',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='MSG_PING_PONG', index=0, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_PING_PONG_ASK', index=1, number=17,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_LOGIN', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_JOIN_TABLE', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_JOIN_TABLE_BROADCAST', index=4, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_LEAVE_TABLE', index=5, number=5,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_LEAVE_TABLE_BROADCAST', index=6, number=6,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_BREAK_BROADCAST', index=7, number=7,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_BREAK_BACK_BROADCAST', index=8, number=8,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_READY', index=9, number=9,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_READY_BROADCAST', index=10, number=10,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_DISMISS_ASK_BROADCAST', index=11, number=12,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_DISMISS_ANSWER', index=12, number=13,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_DISMISS_ANSWER_BROADCAST', index=13, number=14,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_DISMISS_BROADCAST', index=14, number=15,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_GET_JU_CNT', index=15, number=16,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_ROUND_START_BROADCAST', index=16, number=101,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_ROUND_RESULT_BROADCAST', index=17, number=102,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_START_REPLACE_BROADCAST', index=18, number=103,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_DISPATCH_BROADCAST', index=19, number=104,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_OUT', index=20, number=105,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_OUT_BROADCAST', index=21, number=106,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_OPERATE_ASK_BROADCAST', index=22, number=107,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_OPERATE_RESULT_BROADCAST', index=23, number=108,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_OPERATE', index=24, number=109,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_MINGLOU', index=25, number=110,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_MINGLOU_BROADCAST', index=26, number=111,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_MINGLOU_ASK', index=27, number=112,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_CHAT', index=28, number=120,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_CHAT_BROADCAST', index=29, number=121,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_HISTORY_BROADCAST', index=30, number=122,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_VOICE_TALK', index=31, number=123,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_VOICE_TALK_BROADCAST', index=32, number=124,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_CHAT_CUSTOM', index=33, number=125,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_CHAT_CUSTOM_BROADCAST', index=34, number=126,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_GAME_END', index=35, number=999,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_SOCIAL_BEGIN', index=36, number=1000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_SOCIAL_END', index=37, number=1999,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_NET_BEGIN', index=38, number=2000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_NET_END', index=39, number=2010,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=21,
  serialized_end=994,
)

Opcode = enum_type_wrapper.EnumTypeWrapper(_OPCODE)
MSG_PING_PONG = 1
MSG_PING_PONG_ASK = 17
MSG_LOGIN = 2
MSG_JOIN_TABLE = 3
MSG_JOIN_TABLE_BROADCAST = 4
MSG_LEAVE_TABLE = 5
MSG_LEAVE_TABLE_BROADCAST = 6
MSG_BREAK_BROADCAST = 7
MSG_BREAK_BACK_BROADCAST = 8
MSG_READY = 9
MSG_READY_BROADCAST = 10
MSG_DISMISS_ASK_BROADCAST = 12
MSG_DISMISS_ANSWER = 13
MSG_DISMISS_ANSWER_BROADCAST = 14
MSG_DISMISS_BROADCAST = 15
MSG_GET_JU_CNT = 16
MSG_ROUND_START_BROADCAST = 101
MSG_ROUND_RESULT_BROADCAST = 102
MSG_START_REPLACE_BROADCAST = 103
MSG_DISPATCH_BROADCAST = 104
MSG_OUT = 105
MSG_OUT_BROADCAST = 106
MSG_OPERATE_ASK_BROADCAST = 107
MSG_OPERATE_RESULT_BROADCAST = 108
MSG_OPERATE = 109
MSG_MINGLOU = 110
MSG_MINGLOU_BROADCAST = 111
MSG_MINGLOU_ASK = 112
MSG_CHAT = 120
MSG_CHAT_BROADCAST = 121
MSG_HISTORY_BROADCAST = 122
MSG_VOICE_TALK = 123
MSG_VOICE_TALK_BROADCAST = 124
MSG_CHAT_CUSTOM = 125
MSG_CHAT_CUSTOM_BROADCAST = 126
MSG_GAME_END = 999
MSG_SOCIAL_BEGIN = 1000
MSG_SOCIAL_END = 1999
MSG_NET_BEGIN = 2000
MSG_NET_END = 2010




# @@protoc_insertion_point(module_scope)
