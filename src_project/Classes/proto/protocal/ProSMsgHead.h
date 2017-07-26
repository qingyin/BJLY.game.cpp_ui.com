#pragma once


#pragma pack(1)

struct ProSMsgHead 
{
	char		HEAD_0;		//主命令字
	char		HEAD_1;		//子命令字
	char		HEAD_2;		//主命令字
	char		HEAD_3;		//子命令字
	char		ProtoVersion;		//子命令字
	char		flag;		//子命令字
	int         ServerVersion;
	int         index;
	int         len;
	int         opcode;
	char        accessID[32];	
	ProSMsgHead()
	{
		memset(this, 0, sizeof(*this));
	}
};  

#pragma pack()
