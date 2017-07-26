#include "MissionWeiXin.h"
#include "platform/JniFun.h"
#include "model/GamerData.h"
#include "model/LobbyData.h"
#include "view/Layer/Menu/GameMenu.h"
#include "tool/Tools.h"
#include "util/GameConst.h"
#include "controller/lobby/LobbyController.h"

MissionWeiXin::MissionWeiXin()
	:m_pJinMissionSink(NULL)
{
}

MissionWeiXin::~MissionWeiXin()
{

}
static MissionWeiXin *m_x=nullptr;
MissionWeiXin *MissionWeiXin::getinstance()
{
	if(m_x==nullptr)
	{
		m_x=new MissionWeiXin();
	}
	return m_x;
}
void MissionWeiXin::logonWeiXin()
{
	std::string key=cocos2d::UserDefault::getInstance()->getStringForKey("accesstoken");
	std::string id=cocos2d::UserDefault::getInstance()->getStringForKey("openid");
	if(key!=""&&id!="")
	{
		Req_UserInfo(key,id);
	}
	else
	{
		JniFun::longinWX("wx9ac9ddb90cdcadb7","257306b69877fa65bf2259e4d977bff3");

	}
}
void MissionWeiXin::restWeiXin()
{
	
}
void MissionWeiXin::setMissionSink( IWeiXinMissionSink* pJniMissionSink )
{
	m_pJinMissionSink = pJniMissionSink;
}

IWeiXinMissionSink* MissionWeiXin::getMissionSink()
{
	return m_pJinMissionSink;
}
void MissionWeiXin::setNetState(int state_net)
{
	UserDefault::getInstance()->setIntegerForKey("netstate",state_net);
}
void MissionWeiXin::Req_Fail_token(std::string param)
{
	if (m_pJinMissionSink)
	{
		m_pJinMissionSink->onWxLoginFail(param);
	}
}
void MissionWeiXin::checknetwork(int networkstate)
{
	CCLOG("qiehuanwangluo111111%d",UserDefault::getInstance()->getBoolForKey("qiehuanwanluo"));
	if(UserDefault::getInstance()->getBoolForKey("qiehuanwanluo")==false)
	{
		   UserDefault::getInstance()->setBoolForKey("qiehuanwanluo",true);
			CCLOG("qiehuanwangluo%d",UserDefault::getInstance()->getBoolForKey("qiehuanwanluo"));
			SEND_CUSTOM_MSG("stopHerat");//关闭心跳检测	
			bool b = true;
			SEND_CUSTOM_MSG("loseconnect",&b);	
	}		
}
void MissionWeiXin::setBatteryRate(int level_beterry)
{
	UserDefault::getInstance()->setFloatForKey("level_beterry",level_beterry);
	//SEND_CUSTOM_MSG("refreshBettery");
}
void MissionWeiXin::Req_Access_token(std::string param)
{
	CCLOG("accaaaaaaaaaaaaa%s",param.c_str());
	std::string kUrl = "https://api.weixin.qq.com/sns/oauth2/access_token?";
	std::string kUr2 = "appid=wx9ac9ddb90cdcadb7&secret=257306b69877fa65bf2259e4d977bff3&code=";
	std::string kUr3 = "&grant_type=authorization_code";
	cocos2d::String *s=cocos2d::String::createWithFormat("%s%s%s%s",kUrl.c_str(),kUr2.c_str(),param.c_str(),kUr3.c_str());
	CCLOG("accaaaaaaaaaaaaa111111111111%s",s->getCString());
	cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
	request->setUrl(s->getCString());
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	request->setResponseCallback(CC_CALLBACK_2(MissionWeiXin::Rsp_Access_token,this));
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}
void MissionWeiXin::cutscreen(int n_type)
{
	UserDefault::getInstance()->setIntegerForKey("cut_share_ntype",n_type);
	RenderTexture *render=RenderTexture::create(1280, 720,Texture2D::PixelFormat::RGBA8888);
	Scene *s=Director::getInstance()->getRunningScene();
	render->setPosition(Point(50, 100));
	render->begin();
	s->visit();
	render->end();
	render->saveToFile("screen.jpg",Image::Format::JPG);	
	CCLOG("cut");
	SEND_CUSTOM_MSG("cutsuccess");
}
void MissionWeiXin::callback()
{
	shareScreenWeiXin(FileUtils::getInstance()->getWritablePath()+"screen.jpg",UserDefault::getInstance()->getIntegerForKey("cut_share_ntype"));
}
void MissionWeiXin::Rsp_Access_token(HttpClient *sender,HttpResponse *response)
{
	std::string data = "";
	std::vector<char> *buffer = response->getResponseData();
	for (int i = 0; i < buffer->size(); i++)
	{
		data += (*buffer)[i];
	}

	CCLOG("data=========%s",data.c_str());
	rapidjson::Document doc;  
	doc.Parse<0>(data.c_str());//<通过Parse方法将Json数据解析出来  

    if(doc.HasMember("errcode"))
    {
        int errcode = doc["errcode"].GetInt();
        CCLOG("Rsp_Access_token====%d",errcode);
        if(errcode!=0)
	    {
		    return;
	    }
    }

	const std::string acc=doc["access_token"].GetString();
	CCLOG("acccccccc====%s",acc.c_str());
	const std::string open=doc["openid"].GetString();
	CCLOG("tag1");

	cocos2d::UserDefault::getInstance()->setStringForKey("accesstoken",acc.c_str());
	cocos2d::UserDefault::getInstance()->setStringForKey("openid",open.c_str());

	Req_UserInfo(acc.c_str(),open.c_str());
	CCLOG("tag2");
}

void MissionWeiXin::Req_UserInfo(std::string access_token,std::string open_id)
{
	CCLOG("tag3");
	std::string kUrl = "https://api.weixin.qq.com/sns/userinfo?";
	cocos2d::String *s=cocos2d::String::createWithFormat("%saccess_token=%s&openid=%s",kUrl.c_str(),access_token.c_str(),open_id.c_str());
	CCLOG("tag4%s",s->getCString());
	cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
	request->setUrl(s->getCString());
	CCLOG("tag5");
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	CCLOG("tag9");
	request->setResponseCallback(CC_CALLBACK_2(MissionWeiXin::Rsp_UserInfo,this));
	CCLOG("tag8");
	cocos2d::network::HttpClient::getInstance()->send(request);
	CCLOG("tag10");
	request->release();
	CCLOG("tag11");
}
void MissionWeiXin::Rsp_UserInfo(HttpClient *sender,HttpResponse *response)
{
    std::string data = "";
    std::vector<char> *buffer = response->getResponseData();
    for (int i = 0; i < buffer->size(); i++)
    {
        data += (*buffer)[i];
    }
    CCLOG("data=========%s",data.c_str());
    rapidjson::Document doc;  
    doc.Parse<0>(data.c_str());//<通过Parse方法将Json数据解析出来  
    if(doc.HasMember("errcode"))
    {
        int errcode = doc["errcode"].GetInt();
        CCLOG("Rsp_Access_token====%d",errcode);
        if(errcode!=0)
        {
            cocos2d::UserDefault::getInstance()->setStringForKey("accesstoken","");
            cocos2d::UserDefault::getInstance()->setStringForKey("openid","");
            logonWeiXin();
            return;
        }
    }

    const std::string nickname=doc["nickname"].GetString();
    const std::string openid=doc["openid"].GetString();
    const std::string headimage=doc["headimgurl"].GetString();
    int sex=doc["sex"].GetInt();
    GamerData::getInstance()->setNick(nickname.c_str());
    GamerData::getInstance()->setOpenid(openid.c_str());
    GamerData::getInstance()->setHeadUrl(headimage.c_str());
    GamerData::getInstance()->setSex(sex);
	
   	req_login();
}

void MissionWeiXin::req_login()
{
	////登陆
	//rapidjson::Document d;
	//d.SetObject();
	//rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();
	//d.AddMember(rapidjson::Value("version",alloctor),rapidjson::Value("1.1",alloctor),alloctor);
	//d.AddMember(rapidjson::Value("WeiChatID",alloctor),rapidjson::Value((GamerData::getInstance()->getOpenid()).c_str(),alloctor),alloctor);
	//d.AddMember(rapidjson::Value("WeiChatNick",alloctor),rapidjson::Value((GamerData::getInstance()->getNick()).c_str(),alloctor),alloctor);
	//d.AddMember(rapidjson::Value("WeiChatFaceAddress",alloctor),rapidjson::Value((GamerData::getInstance()->getHeadUrl()).c_str(),alloctor),alloctor);
	////d.AddMember(rapidjson::Value("Sex",alloctor),rapidjson::Value((GamerData::getInstance()->getSex()).c_str(),alloctor),alloctor);
	//d.AddMember("Sex",GamerData::getInstance()->getSex(),alloctor);
	//d.AddMember("IsNetChange",UserDefault::getInstance()->getBoolForKey("qiehuanwanluo"),alloctor);
	//CCLOG("---isqiehuanwangluo%d",UserDefault::getInstance()->getBoolForKey("qiehuanwanluo"));
	//Http::getInstance()->sendData("weichat_login",CC_CALLBACK_1(MissionWeiXin::LoginLobbyCallback,this),d,true);

	LobbyController::getInstance()->weixinLogin();
}
void MissionWeiXin::LoginLobbyCallback(std::string res)
{
    log("%s",res.c_str());
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    if(!d.HasMember("ResultCode")){
        return;
    }
    int  resultCode  = d["ResultCode"].GetInt();
    if(resultCode==0)
    {
        int userid=d["UserID"].GetInt();
        GamerData::getInstance()->setUId(userid);
        int biggold=d["BigGold"].GetInt();
        GamerData::getInstance()->setRoomCard(biggold);

        int status=d["Status"].GetInt();
        GamerData::getInstance()->setStatus(status);

        std::string acceesskey=d["accessKey"].GetString();
        GamerData::getInstance()->setAccessKey(acceesskey);

        std::string ip=d["IP"].GetString();
        GamerData::getInstance()->setUserip(ip);

		int roomid=d["RoomID"].GetInt();
		GamerData::getInstance()->setTableId(roomid);
		
		LobbyData::getInstance()->setStringForKey(GameConst::key_myPromoterID,d["PromoterID"].GetString());
		LobbyData::getInstance()->setStringForKey(GameConst::key_myInviteCode,d["InviteCode"].GetString());
		LobbyData::getInstance()->setStringForKey(GameConst::key_RefereeCode,d["RefereeID"].GetString());
		GamerData::getInstance()->setMyInviteCode(d["InviteCode"].GetString());
        Scene *s=Scene::create();
        GameMenu *g=GameMenu::create();
        g->initwithuserinfo("","","");
        s->addChild(g);
        s->setName("menu");
		if(status==3)
		{
			g->enterroom(String::createWithFormat("%d",roomid)->getCString());
			//g->httpReqLaba();
			//LobbyController::getInstance()->getAllWXCode();
			LobbyController::getInstance()->getActivityInfo(false);
		}
        else
        {
			//g->httpReqLaba();
			LobbyController::getInstance()->getActivityInfo(true);
        }
        Director::getInstance()->replaceScene(s);
    }
}

void MissionWeiXin::Req_RefreshToken()
{
	
}
void MissionWeiXin::Rsp_RefreshToken()
{
	
}

void MissionWeiXin::shareScreenWeiXin(std::string strImagic,int nShareType /*= SHARE_SESSION*/)
{
	CCLOG("cut111");
	captureScreen(true,strImagic,nShareType);
}
void MissionWeiXin::captureScreen(bool succeed, const std::string& outputFile,int nShareType)
{
	CCLOG("cut33333");
	if (succeed)
	{
		CCLOG("2222222");
		cocos2d::log("MissionWeiXin captureScreen:%s",outputFile.c_str());
		JniFun::shareImageWX(outputFile.c_str(),nShareType);
	}
	else
	{
		cocos2d::log("MissionWeiXin captureScreen failed!");
	}
}
void MissionWeiXin::shareTextWeiXin(std::string kText,int nShareType /*= SHARE_SESSION*/)
{
	JniFun::shareTextWX(kText.c_str(),nShareType);
}
void MissionWeiXin::shareUrlWeiXin(std::string kUrl,std::string kTitle,std::string kDesc,int nShareType)
{
	JniFun::shareUrlWX(kUrl.c_str(),kTitle.c_str(),kDesc.c_str(),nShareType);
}
