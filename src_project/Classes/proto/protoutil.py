#coding:utf8
'''
Created on 2014-08-06

@author: zs
'''

from . import errorcode_pb2
from app.share import log
from app.share.proto.errorcode_pb2 import ERROR_NONE


def ParseReq(MessageClass, request_proto):
    if not MessageClass:
        return None
    req = MessageClass()
    req.ParseFromString(request_proto)
    log.info("%s:\n\t%s" % (req.DESCRIPTOR.name, '\n\t'.join(str(req).split('\n'))))
    return req


def ProduceRes(MessageClass):
    res = MessageClass()
    res.errorcode = errorcode_pb2.ERROR_NONE
    return res


def Serialize(message, errorcode=errorcode_pb2.ERROR_NONE):
    try:
        message.HasField('errorcode')
    except ValueError:
        pass
    else:
        message.errorcode = errorcode

    bytesize = message.ByteSize()
    size_warning_str = ''

    if bytesize > 3000:
        size_warning_str = "________may need size optimization"
        
    log.debug("Opcode[%s], Size[%d]:%s\n\t%s" % (message.DESCRIPTOR.name, bytesize,size_warning_str,'\n\t'.join(str(message).split('\n'))))
    return message.SerializeToString()


def HasField(message, field_name):
    try:
        return message.HasField(field_name)
    except ValueError:
        return False

def is_error(errorcode):
    if errorcode != ERROR_NONE:
        return True
    return False

