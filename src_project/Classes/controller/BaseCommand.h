#pragma once

#include "tool/Tools.h"
#include "proto/command.pb.h"
#include "socket/SocketUtil.h"
#include "model/GamerData.h"

class BaseCommand
{
public:
	virtual void onRecv(const int opcode,const char* buf,const int len) = 0; // 接收消息
};


