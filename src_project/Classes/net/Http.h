/*
 *   ClassName   :    Http
 *   Description :    Http通信
 *   Author      :      
 *   Date        :	  11.9
*/
#ifndef _Http_H_
#define _Http_H_
#include "cocos2d.h"
#include "network/HttpClient.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
using namespace cocos2d;
using namespace network;
using namespace std;

#define Server_login_guest                      "login_guest" /// 微信登录

class Http
{
public:
	Http();
	~Http();
	static Http* getInstance();
	void sendData( string tag,std::function<void(string)> responseFunc , rapidjson::Document &d,bool addUserId = true,const bool isShowNetLoading = true);
	void onHttpComplete(HttpClient* httpClient,HttpResponse* response);
	bool checkResend(string tag );
	bool isBusy();
	void setIsBusy(bool _isBusy);
private:
	static Http* m_http;
	std::function<void(string)> responseFunc;
	std::map<string,std::function<void(string)>>     m_serverMap;
	bool busy;
};
#endif
