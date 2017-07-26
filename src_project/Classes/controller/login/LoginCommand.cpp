#include "LoginCommand.h"
#include "controller/table/TableCommand.h"
#include "model/GamerData.h"
#include "util/GameConst.h"
LoginCommand* LoginCommand::m_loginCommand = nullptr;
LoginCommand::~LoginCommand()
{
    CC_SAFE_DELETE(m_loginCommand);
}

LoginCommand* LoginCommand::getInstance()
{
    if(m_loginCommand == nullptr){
        m_loginCommand = new LoginCommand();
    }
    return m_loginCommand;
}
void LoginCommand::requestLogin(const int _uid,const int _table_id)
{
    pb::C2GS_Login login;
    login.set_uid(_uid);
    login.set_table_id(_table_id);
    std::string buf;
    login.SerializeToString(&buf);
    SEND_BUF_MSG(Opcode::MSG_LOGIN, buf);
}
void LoginCommand::requestHeart()
{
    pb::C2GS_PingPong login;
    std::string buf;
    login.SerializeToString(&buf);
    SEND_BUF_MSG(Opcode::MSG_PING_PONG, buf);
}

// 接收消息
void LoginCommand::onRecv(const int opcode,const char* buf,const int len)
{
    switch (opcode)
    {
    case Opcode::MSG_LOGIN:
        responseLogin(buf,len);
        break;
    case Opcode::MSG_PING_PONG:
		responseheart(buf,len);
        break;
    default:
        break;
    }	
}
void LoginCommand::responseheart(const char *buf,const int len)
{
	pb::GS2C_PingPong login;
	login.ParseFromArray(buf,len);
	int  error = login.errorcode();
	UserDefault::getInstance()->setBoolForKey("isconnect",true);
}
void LoginCommand::responseLogin(const char* buf,const int len)
{
    pb::GS2C_Login login;
    login.ParseFromArray(buf,len);
    int  error = login.errorcode();
    if(error == 0)
    {
       TableCommand::getInstance()->requestJoinTable(GamerData::getInstance()->getTableId(),GamerData::getInstance()->getSeatId());
    }
	else
	{
		bool b = false;
		SEND_CUSTOM_MSG(CustomEvent::key_set_visible_loading_layer,&b);
	}
}
