#pragma once

#include "controller/BaseCommand.h"

class LoginCommand : public BaseCommand
{
public:
    ~LoginCommand();
    static LoginCommand* getInstance();
    ///登录
    void requestLogin(const int _uid,const int _table_id);
    void responseLogin(const char* buf,const int len);

    void requestHeart();
	void responseheart(const char *buf,const int len);
    void onRecv(const int opcode,const char* buf,const int len ) ; // 接收消息


private:
    static LoginCommand* m_loginCommand;
};
