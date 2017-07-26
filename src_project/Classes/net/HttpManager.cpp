#include "HttpManager.h"
#include "util/GameConst.h"
#include "model/GamerData.h"

HttpManager::HttpManager(void)
{
	_httpManagerDelegate = nullptr;
}
HttpManager::~HttpManager(void)
{
}
void HttpManager::sendGetRequest(string url,string requestTag,bool isImmediateSend)
{
	HttpRequest* request = new (std::nothrow) HttpRequest();
	request->setRequestType(HttpRequest::Type::GET);
	request->setUrl(url.c_str());
	request->setResponseCallback(CC_CALLBACK_2(HttpManager::onHttpRequestCompleted,this));
	request->setTag(requestTag.c_str());
	if (isImmediateSend)
	{
		HttpClient::getInstance()->sendImmediate(request);
	} 
	else
	{
		HttpClient::getInstance()->send(request);
	}
	request->release();
}

void HttpManager::sendPostRequest(string requestTag,string postData)
{
	string url = GamerData::getInstance()->getHostUrl();
	string tempUrl(url,0,url.length()-1);
	HttpRequest* request = new (std::nothrow) HttpRequest();
	request->setRequestType(HttpRequest::Type::POST);
	std::string _url = tempUrl + requestTag;
	request->setUrl(_url.c_str());
	request->setResponseCallback(CC_CALLBACK_2(HttpManager::onHttpRequestCompleted,this));
	request->setTag(requestTag.c_str());
	request->setRequestData(postData.c_str(),postData.length());
	HttpClient::getInstance()->send(request);
	request->release();
}
void HttpManager::onHttpRequestCompleted(HttpClient* sender,HttpResponse* response)
{
	if (!response)
	{
		return;
	}
	const char* tag = response->getHttpRequest()->getTag();
	if (0 != strlen(tag))
	{
		log("%s completed",tag);
	}
	log("HTTP Status Code::%ld, tag = %s",response->getResponseCode(),tag);
	if (!response->isSucceed())
	{
		log("response failed");
		log("error buffer:%s",response->getErrorBuffer());
	}
	if (_httpManagerDelegate)
	{
		_httpManagerDelegate->onHttpManagerRequestCompleted(sender,response);
	}
}