#pragma once
#include "controller/BaseCommand.h"
class LobbyCommand : public BaseCommand
{
public:
	static LobbyCommand* getInstance();
	virtual ~LobbyCommand(void);
	void Get();
	virtual void onRecv(const int opcode,const char* buf,const int len) ; // 接收消息



	void bindPromoterID(string promoterID);
	void httpReqPromoterID(string res);

	void bindInvitationCode(string code);
	void httpReqInvitationCode(string res);

	void getPromoterIDAndInvitationCode();
	void httpResPromoterIDAndInvitationCode(string res);

private:
	static LobbyCommand* mLobbyCommand;
	string  promoterID;
	string  invitationCode;
};

