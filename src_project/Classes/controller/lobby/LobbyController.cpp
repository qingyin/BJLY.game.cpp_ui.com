#include "LobbyController.h"
#include "net/Http.h"
#include "model/LobbyData.h"

#include "util/GameConst.h"
#include "tool/Tools.h"
#include "tool/Tiperror.h"
#include "view/Layer/Lobby/LayerLoading.h"
#include "view/Layer/Lobby/LobbyView.h"
#include "view/Layer/Tip/TipContent.h"
#include "model/GamerData.h"
#include "model/MjData.h"
#include "platform/JniFun.h"

LobbyController* LobbyController::mLobbyController = nullptr;


LobbyController::LobbyController()
{
	mHttpManager = new HttpManager();
	mHttpManager->setHttpDelegate(this);
}
LobbyController::~LobbyController(void)
{
}

LobbyController* LobbyController::getInstance()
{
	if (mLobbyController == nullptr)
	{
		mLobbyController = new LobbyController();
	}
	return mLobbyController;
}

void LobbyController::bindUser()
{
	rapidjson::Document d;
	d.SetObject();
	rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
	if (mBindType == PROMOTER_ID)
	{
		d.AddMember(rapidjson::Value("partnerId",allocator),rapidjson::Value(userId.c_str(),allocator),allocator);
		sendRequest(RequestUrl::BIND_PARTNER,d);
	}
	else
	{
		d.AddMember(rapidjson::Value("invitePlayerId",allocator),rapidjson::Value(userId.c_str(),allocator),allocator);
		sendRequest(RequestUrl::BIND_PLAYER,d);	
	}
}

void LobbyController::getMsgList()
{
	rapidjson::Document d;
	d.SetObject();
	sendRequest(RequestUrl::GET_PLAYER_MESSAGE,d);
}
void LobbyController::getActivityPicList()
{
	rapidjson::Document d;
	d.SetObject();
	sendRequest(RequestUrl::GET_ACTIVITY_PICLIST,d);
}
void LobbyController::getActivityInfo(bool isShowActivityPic)
{
	this->isShowActivityPic = isShowActivityPic;
	getAllWXCode();

	if(MjData::getInstance()->getisinapple() !=1)
	{
		getActivityPicList();
	}
	//testReadTimeout();
	//getMsgList();
	//getPromoterInfo("555123");
}
void LobbyController::loadImg(string url,string tag)
{
	mHttpManager->sendGetRequest(url,tag,true);
}

void LobbyController::getAllWXCode()
{
	rapidjson::Document d;
	d.SetObject();
	sendRequest(RequestUrl::GET_CONTACT_INFO,d);
}

void LobbyController::getPromoterInfo(string promoterID)
{
	rapidjson::Document d;
	rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
	d.SetObject();
	d.AddMember("partnerId",rapidjson::Value(promoterID.c_str(),allocator),allocator);
	sendRequest(RequestUrl::GET_PARTNER_INFO,d);
	inputUserIdCode = promoterID;
}
void LobbyController::getInviterInfo(string inviteCode)
{
	rapidjson::Document d;
	rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
	d.SetObject();
	d.AddMember("inviteCode",rapidjson::Value(inviteCode.c_str(),allocator),allocator);
	sendRequest(RequestUrl::GETP_LAYER_INFO_BY_INVITE_CODE,d);
	inputUserIdCode = inviteCode;
}
void LobbyController::getShengLv(int uid,bool isHeadClicked)
{
	this->isHeadClicked = isHeadClicked;
	rapidjson::Document d;
	d.SetObject();
	sendRequest(RequestUrl::GET_JU_CNT,d);
}
void LobbyController::getHistoryRecord()
{
	rapidjson::Document d;
	d.SetObject();
	sendRequest(RequestUrl::GET_HISTORY,d);
}


void LobbyController::onHttpRequestCompletedDataHandle(string data,string tag)
{
	if( tag.find(GameConst::key_activity_id_,0) == 0)
	{
		saveImg(data,tag);
		return;
	}
	rapidjson::Document d;
	d.Parse<0>(data.c_str());
	if (d.HasParseError())
	{
		log("----parse---error=%d",d.GetParseError());
		return;
	}
	Scene *s = Director::getInstance()->getRunningScene();
	int  resultCode  = d["ResultCode"].GetInt(); //״̬
	if(resultCode != 0){
		const string errStr = d["ErrMsg"].GetString();
		s->addChild(Tiplayerr::create(errStr), 10);
		return;
	}
	if (tag.compare(RequestUrl::GET_JU_CNT) == 0)
	{		
		LobbyAdapter::getInstance()->saveGameStats(d);
		SEND_CUSTOM_MSG(CustomEvent::key_show_update_head);

		if(isHeadClicked==true)
		{
			auto tipConent = TipContent::create();
			tipConent->showUIplayerInfoInGame(0);
			Director::getInstance()->getRunningScene()->addChild(tipConent,9);
		}

		
	}
	else if (tag.compare(RequestUrl::GET_HISTORY) == 0)
	{
		Scene *s = Director::getInstance()->getRunningScene();
		int  resultCode  = d["ResultCode"].GetInt(); //״̬
		if(resultCode != 0){
			const string errStr = d["ErrMsg"].GetString();
			s->addChild(Tiplayerr::create(errStr), 10);
			return;
		}
		auto tipConent = TipContent::create();
		tipConent->showUIAchievement(data);
		s->addChild(tipConent,9);
	}
	else if (tag.compare(RequestUrl::GET_ACTIVITY_PICLIST) == 0)
	{
		bool isHad = LobbyAdapter::getInstance()->checkActiviyInfoSame(d["Data"]);
		if (isHad)
		{
			SEND_CUSTOM_MSG(GameConst::key_event_activity,&isShowActivityPic);
		}
		else
		{
			vector<ActivityInfo> vectorInfo =	LobbyAdapter::getInstance()->parseActivityInfo(d["Data"]);
			LobbyData::getInstance()->setIntegerForKey(GameConst::key_activity_num,vectorInfo.size());
			for (int i=0;i<vectorInfo.size();i++)
			{
				string tag = GameConst::key_activity_id_ + StringUtils::format("%d",i+1)+".png";
				string url = vectorInfo[i].picUrl;
				loadImg(url,tag);
			}
			loadedImgNum = 0;
		}
	}
	else if (tag.compare(RequestUrl::GET_PARTNER_INFO) == 0)
	{
		BindParentInfo* info =	LobbyAdapter::getInstance()->parseBindParentInfoData(d["Data"]);
		SEND_CUSTOM_MSG(CustomEvent::key_show_ui_bind_confirm,info);
		userId = info->userId;
		mBindType = PROMOTER_ID;
	}
	else if (tag.compare(RequestUrl::GETP_LAYER_INFO_BY_INVITE_CODE) == 0)
	{
		BindParentInfo* info =	LobbyAdapter::getInstance()->parseBindParentInfoData(d["Data"]);
		SEND_CUSTOM_MSG(CustomEvent::key_show_ui_bind_confirm,info);
		userId = info->userId;
		mBindType = INVITATION_CODE;
	}
	else if (tag.compare(RequestUrl::BIND_PLAYER) == 0)
	{
		LobbyData::getInstance()->setStringForKey(GameConst::key_RefereeCode,inputUserIdCode);
		int type = 1;
		SEND_CUSTOM_MSG(CustomEvent::key_update_ui_bind,&type);
		SEND_CUSTOM_MSG(CustomEvent::key_update_self_info,nullptr);
	}
	else if (tag.compare(RequestUrl::BIND_PARTNER) == 0)
	{
		LobbyData::getInstance()->setStringForKey(GameConst::key_myPromoterID,inputUserIdCode);
		int type = 2;
		SEND_CUSTOM_MSG(CustomEvent::key_update_ui_bind,&type);
		SEND_CUSTOM_MSG(CustomEvent::key_update_self_info,nullptr);
	}
	else if (tag.compare(RequestUrl::GET_PLAYER_MESSAGE) == 0)
	{
		//vector<MessageInfo> vectorInfo = LobbyAdapter::getInstance()->parseMessageInfo(d["Data"]);
		vector<MessageInfo*> vectorInfo = LobbyAdapter::getInstance()->parseMessageInfoData(d["Data"]);		
		SEND_CUSTOM_MSG(CustomEvent::key_show_ui_message,&vectorInfo);
	}
	else if (tag.compare(RequestUrl::GET_CONTACT_INFO) == 0)
	{
		LobbyAdapter::getInstance()->saveAllWXCode(d["Data"]);
		string laba = d["Data"]["speakerContent"].GetString();
		SEND_CUSTOM_MSG(CustomEvent::key_show_laba,&laba);
	}
	else if (tag.compare(RequestUrl::WEICHAT_LOGIN) == 0)
	{
		//LobbyAdapter::getInstance()->saveWeiXinLogin(d["Data"]);
		LobbyAdapter::getInstance()->saveWeiXinLogin(d);
		LobbyController::getInstance()->getActivityInfo(true);
		SEND_CUSTOM_MSG(CustomEvent::key_show_game_menu,nullptr);
	}
	else if (tag.compare(RequestUrl::VERSION_VERIFY) == 0)
	{
		int tag_apple=d["TAG"].GetInt();
		MjData::getInstance()->setisinapple(tag_apple);
		SEND_CUSTOM_MSG(CustomEvent::key_version_verify);		
	}	
}

void LobbyController::onHttpManagerRequestCompleted(HttpClient* sender,HttpResponse* response)
{
	setLayerLoadingVisible(false);
	const char* tag = response->getHttpRequest()->getTag();
	if (!response->isSucceed() || response->getResponseCode() != 200)
	{
		log("response failed");
		log("error buffer:%s,responseCode=%d",response->getErrorBuffer(),response->getResponseCode());

		//if (!response->isSucceed() && response->getResponseCode() == -1)
		{
			setLayerNetworkErrorVisible(true);
		}
		return;
	}
	std::vector<char>* head = response->getResponseHeader();
	string headStr = "";
	for (unsigned int i = 0; i < head->size(); i++)
	{
		headStr += (*head)[i];
	}
	log("Http Test,dump header data:%s\n",headStr.c_str());

	std::vector<char> *buffer = response->getResponseData();
	string temp = "";
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		temp +=(*buffer)[i];
	}
	log("Http Test, dump response data:%s\n",temp.c_str());
	onHttpRequestCompletedDataHandle(temp,tag);
}

void LobbyController::setLayerLoadingVisible(bool isVisible)
{
	Scene *s = Director::getInstance()->getRunningScene();
	if (s)
	{
		Node* loading = s->getChildByName("LayerLoading");
		if (isVisible)
		{
			if (!loading)
			{
				auto layer = LayerLoading::create();
				s->addChild(layer);
			}
		} 
		else
		{
			if (loading)
			{
				loading->removeFromParent();
			}
		}
	}
}

void LobbyController::setLayerNetworkErrorVisible(bool isVisible)
{
	Scene *s = Director::getInstance()->getRunningScene();
	if (s)
	{
		Node* layerError = s->getChildByName("Tiplayerr");
		if (isVisible)
		{
			if (!layerError)
			{
				const string  netError = Tools::getChineseByKey("NetError");
				auto temp = Tiplayerr::create(netError);
				temp->setName("Tiplayerr");
				s->addChild(temp);
			}
		} 
		else
		{
			if (layerError)
			{
				layerError->removeFromParent();
			}
		}
	}
}

void LobbyController::saveImg(string data,string tag)
{
	//write file
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	path+=tag;
	bool exist = CCFileUtils::sharedFileUtils()->isFileExist(path);

	FILE *fp = fopen(path.c_str(), "wb+");
	//fwrite(buffer->data(), 1,buffer->size(), fp);
	fwrite(data.c_str(),1,data.length(),fp);
	fclose(fp);
	loadedImgNum = loadedImgNum + 1;
	int totalNum = LobbyData::getInstance()->getIntegerForKey(GameConst::key_activity_num);
	if (totalNum <= loadedImgNum)
	{
		SEND_CUSTOM_MSG(GameConst::key_event_activity,&isShowActivityPic);
	}
}

void LobbyController::sendRequest(string tag,rapidjson::Document& doc)
{
	setLayerLoadingVisible(true);
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	string accessKey = GamerData::getInstance()->getAccessKey();
	string deviceID = GamerData::getInstance()->getOpenid();
	doc.AddMember("accessKey",rapidjson::Value(accessKey.c_str(),allocator),allocator);
	doc.AddMember("DeviceID",rapidjson::Value(deviceID.c_str(),allocator),allocator);
	doc.AddMember("UserID",GamerData::getInstance()->getUId(),allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
	doc.Accept(write);
	mHttpManager->sendPostRequest(tag,buffer.GetString());
}

void LobbyController::testReadTimeout()
{
	rapidjson::Document d;
	d.SetObject();
	sendRequest(RequestUrl::TEST_READ_TIMEOUT,d);
}

void LobbyController::weixinLogin()
{
	rapidjson::Document d;
	d.SetObject();
	rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();
	d.AddMember(rapidjson::Value("version",alloctor),rapidjson::Value("1.1",alloctor),alloctor);
	d.AddMember(rapidjson::Value("WeiChatID",alloctor),rapidjson::Value((GamerData::getInstance()->getOpenid()).c_str(),alloctor),alloctor);
	d.AddMember(rapidjson::Value("WeiChatNick",alloctor),rapidjson::Value((GamerData::getInstance()->getNick()).c_str(),alloctor),alloctor);
	d.AddMember(rapidjson::Value("WeiChatFaceAddress",alloctor),rapidjson::Value((GamerData::getInstance()->getHeadUrl()).c_str(),alloctor),alloctor);
	//d.AddMember(rapidjson::Value("Sex",alloctor),rapidjson::Value((GamerData::getInstance()->getSex()).c_str(),alloctor),alloctor);
	d.AddMember("Sex",GamerData::getInstance()->getSex(),alloctor);
	d.AddMember("IsNetChange",UserDefault::getInstance()->getBoolForKey("qiehuanwanluo"),alloctor);
	CCLOG("---isqiehuanwangluo%d",UserDefault::getInstance()->getBoolForKey("qiehuanwanluo"));
	//Http::getInstance()->sendData("weichat_login",CC_CALLBACK_1(MissionWeiXin::LoginLobbyCallback,this),d,true);
	sendRequest(RequestUrl::WEICHAT_LOGIN,d);
}

void LobbyController::versionVerify()
{
	rapidjson::Document d;
	d.SetObject();

	std::string plat;
	string version = JniFun::getVersion();
	if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	{
		plat="Android";
	}
	else if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	{
		plat="IOS";
	}
	else if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	{
		plat="Win32";
		version ="1.6";
	}
	rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();
	d.AddMember(rapidjson::Value("version",alloctor),rapidjson::Value(version.c_str(),alloctor),alloctor);
	d.AddMember(rapidjson::Value("platform",alloctor),rapidjson::Value(plat.c_str(),alloctor),alloctor);
	LobbyController::getInstance()->setLayerLoadingVisible(true);
	sendRequest(RequestUrl::VERSION_VERIFY,d);
}