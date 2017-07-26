#include "net/Http.h"
#include "model/GamerData.h"
#include "tool/Tools.h"
#include "platform/Platform.h"
#include "controller/lobby/LobbyController.h"
#include "util/GameConst.h"

static bool isHaveLoading = false;
Http* Http::m_http = nullptr;
 
Http::Http(){
	busy = false;

	HttpClient* httpClient = HttpClient::getInstance();
	auto str = FileUtils::getInstance()->getWritablePath() + "cook.txt";
	httpClient->enableCookies(str.c_str());
	HttpClient::getInstance()->setTimeoutForConnect(10);
	HttpClient::getInstance()->setTimeoutForRead(15);
}
Http::~Http(){
	CC_SAFE_DELETE(m_http);
}
Http* Http::getInstance(){
	if (m_http == nullptr){
       m_http = new Http();
	   m_http->busy = false;
	}
	return m_http;
}
void Http::sendData( string tag, std::function<void(string)> responseFunc, rapidjson::Document &d,bool addUserId,bool isShowNetLoading )
{
	if (busy)return;
	busy = true;
	if(isShowNetLoading){
		if(!isHaveLoading){
			isHaveLoading = true;
			//----NetLoadingLayer::createLoading();
		}
	}

	//if (!checkResend(tag)) return; //暂定
	//this->m_serverMap.insert(std::make_pair(tag,responseFunc));
	this->responseFunc = responseFunc;
		
	if(addUserId){
		rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();
		string accessKey = GamerData::getInstance()->getAccessKey();
		d.AddMember(rapidjson::Value("accessKey",alloctor),rapidjson::Value(accessKey.c_str(),alloctor),alloctor);
		d.AddMember(rapidjson::Value("DeviceID",alloctor),rapidjson::Value(GamerData::getInstance()->getOpenid().c_str(),alloctor),alloctor);
     	d.AddMember("UserID",GamerData::getInstance()->getUId(),alloctor);
		log("%d",GamerData::getInstance()->getUId());
	}
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
	d.Accept(write);
	const string postData = buffer.GetString();
	std::string _url = GamerData::getInstance()->getHostUrl() + tag;
	HttpRequest* request = new HttpRequest();
	request->setTag(tag.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setUrl(_url.c_str());
	request->setRequestData(postData.c_str(),strlen(postData.c_str()));
	request->setResponseCallback(CC_CALLBACK_2(Http::onHttpComplete,this));
	HttpClient::getInstance()->send(request);
	request->release();
}
void Http::onHttpComplete(HttpClient* httpClient,HttpResponse* response)
{
	busy = false;
	if(isHaveLoading){
		isHaveLoading = false;
		//----NetLoadingLayer::removeLoading();
	}
	//LobbyController::getInstance()->setLayerLoadingVisible(false);
	if (!response){
		
		return;
	}
    vector<char> *head = response->getResponseHeader();

//	this->m_serverMap.clear();
	const char* tag = response->getHttpRequest()->getTag(); 
	if (0 != strlen(tag)){
	   log("Net tag: %s",tag);
	}
	int statusCode = response->getResponseCode(); ///状态码
	log("Net statusCode : %d",statusCode);
	if (!response->isSucceed()||statusCode!=200){ ///网络错误		
		/**----
		GamerData::getInstance()->setStatus(eUserStatusFree); ///自由状态
		const string  errorStr = Tool::getUTF8Char("NetError");
		Tool::showTipInfo(errorStr.c_str(),false);	
        if (Tool::isInGame)
        {
            SEND_CUSTOM_MSG(Game_killGameHall);
        }
		**/
		LobbyController::getInstance()->setLayerLoadingVisible(false);
		string headStr = "";
		for (unsigned int i = 0; i < head->size(); i++)
		{
			headStr += (*head)[i];
		}
		log("Http Test,dump header data:%s\n",headStr.c_str());
		if (!response->isSucceed())
		{
			log("response failed");
			log("error buffer:%s",response->getErrorBuffer());
		}
		if (!response->isSucceed() && (statusCode == -1 || statusCode > 400))
		{
			LobbyController::getInstance()->setLayerNetworkErrorVisible(true);		
		}


		return;
	}
	std::string data = "";
	std::vector<char> *buffer = response->getResponseData();
	for (int i = 0; i < buffer->size(); i++)
	{
		 data += (*buffer)[i];
	}
	log("json %s tag %s",data.c_str(),tag);
	log("-----json%s",data.c_str());
	
	responseFunc(data);
}

/////检查是否重发 
bool Http::checkResend(string tag )
{
	bool isResend = true;
	std::map<string,std::function<void(string)>>::iterator it; 
	it = this->m_serverMap.find(tag);
	if (it != this->m_serverMap.end()){  ///没找到
		isResend = false;
	}
	return isResend;
}
bool Http::isBusy()
{
	return busy;
}
void Http::setIsBusy(bool _isBusy)
{
	busy = _isBusy;
}


