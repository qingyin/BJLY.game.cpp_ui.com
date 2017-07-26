#pragma once
#include "cocos2d.h"
#include "network/HttpClient.h"
USING_NS_CC;
using namespace network;
using namespace std;

class HttpManagerDelegate
{
public:
	virtual void onHttpManagerRequestCompleted(HttpClient* sender,HttpResponse* response) = 0;
};

class HttpManager
{
public:
	HttpManager(void);
	~HttpManager(void);
	CC_SYNTHESIZE(HttpManagerDelegate*,_httpManagerDelegate,HttpDelegate);
	void sendGetRequest(string url,string requestTag,bool isImmediateSend = false);
	void sendPostRequest(string requestTag,string postData);
private:
	void onHttpRequestCompleted(HttpClient* sender,HttpResponse* response);
};

