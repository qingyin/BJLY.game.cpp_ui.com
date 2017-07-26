#include "LobbyCommand.h"
#include "net/Http.h"
#include "model/LobbyData.h"


LobbyCommand* LobbyCommand::mLobbyCommand = nullptr;
LobbyCommand::~LobbyCommand(void)
{
}

LobbyCommand* LobbyCommand::getInstance()
{
	if (mLobbyCommand == nullptr)
	{
		mLobbyCommand = new LobbyCommand();
	}
	return mLobbyCommand;
}
void LobbyCommand::onRecv(const int opcode,const char* buf,const int len)
{

}

void LobbyCommand::bindPromoterID(string promoterID)
{
	rapidjson::Document d;
	d.SetObject();
	rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
	d.AddMember(rapidjson::Value("promoter",allocator),rapidjson::Value(promoterID.c_str(),allocator),allocator);
	Http::getInstance()->sendData("promoter",CC_CALLBACK_1(LobbyCommand::httpReqPromoterID,this),d,false);
	this->promoterID = promoterID;
}

void LobbyCommand::httpReqPromoterID(string res)
{
	log("%s",res.c_str());
	rapidjson::Document d;
	d.Parse<0>(res.c_str());
	if (!d.HasMember("ResultCode"))
	{
		return;
	}
	int result = d["ResultCode"].GetInt();
	if (result == 0){
	}
}
void LobbyCommand::bindInvitationCode(string code)
{
	rapidjson::Document d;
	d.SetObject();
	rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
	d.AddMember(rapidjson::Value("InvitationCod",allocator),rapidjson::Value(code.c_str(),allocator),allocator);
	Http::getInstance()->sendData("InvitationCod",CC_CALLBACK_1(LobbyCommand::httpReqInvitationCode,this),d,false);
	this->invitationCode = code;
}

void LobbyCommand::httpReqInvitationCode(string res)
{
	log("%s",res.c_str());
	rapidjson::Document d;
	d.Parse<0>(res.c_str());
	if (!d.HasMember("ResultCode"))
	{
		return;
	}
	int result = d["ResultCode"].GetInt();
	if (result == 0){
	}
}
void LobbyCommand::getPromoterIDAndInvitationCode()
{
	rapidjson::Document d;
	d.SetObject();
	rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();
	Http::getInstance()->sendData("PromoterIDAndInvitationCode",CC_CALLBACK_1(LobbyCommand::httpResPromoterIDAndInvitationCode,this),d,true);
}

void LobbyCommand::httpResPromoterIDAndInvitationCode(string res)
{
	log("%s",res.c_str());
	rapidjson::Document d;
	d.Parse<0>(res.c_str());
	if (!d.HasMember("ResultCode"))
	{
		return;
	}
	int result = d["ResultCode"].GetInt();
	if (result == 0)
	{
		string PromoterID = d["PromoterID"].GetString();

		string InvitationCode = d["InvitationCode"].GetString();
	}
}