#include "LayerLogin.h"
#include "tool/Tools.h"
#include "view/Layer/Tip/TipContent.h"
#include "view/Layer/Menu/GameMenu.h"
#include "platform/MissionWeiXin.h"
#include "model/GamerData.h"
#include "platform/JniFun.h"
#include "view/Layer/Lobby/LobbyView.h"
#include "controller/lobby/LobbyController.h"
#include "util/GameConst.h"
#include "model/MjData.h"
//#include "IosHelper.h"
bool LayerLogin::init()
{
	if(!ParentInfo::init()) return false;
	uiLoadAndShow();
	//注册捕捉监听
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(LayerLogin::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

	this->_eventDispatcher->addCustomEventListener(CustomEvent::key_show_game_menu,CC_CALLBACK_1(LayerLogin::showGameMenu,this));

	srand(unsigned(time(0)));

	return true;
}
void LayerLogin::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	CCLOG("--------------keyrelease!");
	if (keycode == EventKeyboard::KeyCode::KEY_RETURN  || EventKeyboard::KeyCode::KEY_ESCAPE == keycode || EventKeyboard::KeyCode::KEY_BACKSPACE == keycode)  //返回
	{
		CCLOG("--------------keybacespace!");
		if(UserDefault::getInstance()->getBoolForKey("ishaveback")==false)
		{
			CCLOG("--------------keyaddlobby!");
			UserDefault::getInstance()->setBoolForKey("ishaveback",true);
			LobbyView *l_b=LobbyView::create();
			l_b->showUILogoutTip(false);
			Director::getInstance()->getRunningScene()->addChild(l_b,1000000);
		}
	}
}

//UI加载并且显示
void LayerLogin::uiLoadAndShow()
{
	auto loginUI = CSLoader::createNode("res/loading/Login.csb") ;   //Loading
	this->addChild(loginUI);

	btn_yk_login = (Button*)loginUI->getChildByName("btn_yk_login");
	btnLogin = (Button*)loginUI->getChildByName("btnLogin");//微信登录按钮
	if (MjData::getInstance()->IsVisitorLogin())
	{
		btn_yk_login->addTouchEventListener(CC_CALLBACK_2(LayerLogin::LoginButtonHandler, this));
		btnLogin->setVisible(false);
		btn_yk_login->setVisible(true);		
		loginUI->getChildByName("txt_agreement")->setVisible(false);
	}
	else
	{
		btnLogin->addTouchEventListener(CC_CALLBACK_2(LayerLogin::LoginButtonHandler, this));
		btnLogin->setVisible(true);
		btn_yk_login->setVisible(false);
	}

	auto txt_agreement = ((Text*)loginUI->getChildByName("txt_agreement"));
	txt_agreement->setTouchEnabled(true);
	txt_agreement->addTouchEventListener(CC_CALLBACK_2(LayerLogin::LoginButtonHandler, this));

	auto cbIsAgree = (CheckBox*)txt_agreement->getChildByName("cbIsAgree"); //是否同意
	cbIsAgree->setSelected(UserDefault::getInstance()->getBoolForKey(isAgreeUseInfo,true));
	cbIsAgree->addEventListener(CC_CALLBACK_2(LayerLogin::LoginCheckBoxHandler, this));
	txt_logining = ((Text*)loginUI->getChildByName("txt_logining"));
	txt_logining->setVisible(false);
	UserDefault::getInstance()->setBoolForKey("isupdate",true);

	std::string key=cocos2d::UserDefault::getInstance()->getStringForKey("accesstoken","");
	if (key !="")
	{
		checkupdate();
	}
}
void LayerLogin::loginwithbreak()
{
	if(UserDefault::getInstance()->getBoolForKey(isAgreeUseInfo,true)==true&&UserDefault::getInstance()->getBoolForKey("isupdate")==false)
		{
			if(MjData::getInstance()->IsVisitorLogin())
			{
				txt_logining ->setVisible(false);
			}
			else
			{
				txt_logining ->setVisible(true);
			}
			btnLogin->setEnabled(false);
			btn_yk_login->setEnabled(false);
			CCLOG("btn===============weixin=======login---------------");
			bool isTest = false;
			if (MjData::getInstance()->getisinapple() == 1)
			{
				this->visitorLogin();
				return;
			}
			
			if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
			{
				if(isTest)
				{
					String * pID = String::createWithFormat("152"); 
					GamerData::getInstance()->setOpenid(pID->getCString());
					GamerData::getInstance()->setNick(pID->getCString());
					GamerData::getInstance()->setSex(1);
					MissionWeiXin::getinstance()->req_login();
				} 
				else
				{
					std::string key=cocos2d::UserDefault::getInstance()->getStringForKey("accesstoken");
					std::string id=cocos2d::UserDefault::getInstance()->getStringForKey("openid");
					if(key!=""&&id!="")
					{
						MissionWeiXin::getinstance()->logonWeiXin(); 
					}
					else
					{
						JniFun::longinWX("wx9ac9ddb90cdcadb7","257306b69877fa65bf2259e4d977bff3");  
					}
				}				
			}
            else if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
            {
                String * pID = String::createWithFormat("153");
				GamerData::getInstance()->setOpenid(pID->getCString());
                //String * pname = String::createWithFormat(Tools::getChineseByKey("TestWeixinNick").c_str());
				GamerData::getInstance()->setNick(pID->getCString());
				GamerData::getInstance()->setSex(1);
				//GamerData::getInstance()->setHeadUrl("http://wx.qlogo.cn/mmopen/zwcAehH3CGVQr5tic5micKlZAaRo1Qw25cJxh6VV7icCucDeXhQTFcYCL0wia0I8nVOicywUNZQpSNB4Qw4TicTGEAw4upz2TKUKsA/0");
				MissionWeiXin::getinstance()->req_login();
            }
            else if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
            {
				if (isTest)
				{
					String * pID = String::createWithFormat("1521");
					GamerData::getInstance()->setOpenid(pID->getCString());
					GamerData::getInstance()->setNick(pID->getCString());
					GamerData::getInstance()->setSex(1);
					MissionWeiXin::getinstance()->req_login();
				} 
				else
				{
					std::string key=cocos2d::UserDefault::getInstance()->getStringForKey("accesstoken");
					std::string id=cocos2d::UserDefault::getInstance()->getStringForKey("openid");
					if(key!=""&&id!="")
					{
						MissionWeiXin::getinstance()->logonWeiXin();
					}
					else
					{
						JniFun::longinWX("wx9ac9ddb90cdcadb7","257306b69877fa65bf2259e4d977bff3");  
					}
				}
            }
		}
}
void LayerLogin::checkupdate()
{
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
	rapidjson::Document d;
	d.SetObject();
	rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();
	d.AddMember(rapidjson::Value("version",alloctor),rapidjson::Value(version.c_str(),alloctor),alloctor);
	d.AddMember(rapidjson::Value("platform",alloctor),rapidjson::Value(plat.c_str(),alloctor),alloctor);
	LobbyController::getInstance()->setLayerLoadingVisible(true);
	Http::getInstance()->sendData("version_verify",CC_CALLBACK_1(LayerLogin::responseupdate,this),d,false);
}
void LayerLogin::responseupdate(std::string res)
{
	LobbyController::getInstance()->setLayerLoadingVisible(false);
	log("%s",res.c_str());
	rapidjson::Document d;
	d.Parse<0>(res.c_str());
	if(!d.HasMember("ResultCode")){
		return;
	}
	int  resultCode  = d["ResultCode"].GetInt();
	if(resultCode==0)
	{
		bool isupoate=d["IsUpdate"].GetBool();
		bool isForceUpdate= d["isForceUpdate"].GetBool();
		std::string url=d["Url"].GetString();
		int tag_apple=d["TAG"].GetInt();

		if(CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
		{
			MjData::getInstance()->setisinapple(tag_apple);
			if (tag_apple == 1)
			{
				//GameConst::URL = GameConst::URL_version_verify;
				GamerData::getInstance()->setHostUrl(GameConst::URL_version_verify);
			}
			if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
			{
			  GamerData::getInstance()->setHostUrl(GameConst::URL_version_verify);
			}
		}
		else
		{
			MjData::getInstance()->setisinapple(0);
		}
		if(isupoate==false)
		{
			UserDefault::getInstance()->setBoolForKey("isupdate",false);
		}
		else
		{
			UserDefault::getInstance()->setBoolForKey("isupdate",true);
			TipContent *tip=TipContent::create();
			tip->showuiupdate(url,isForceUpdate);
			addChild(tip,9);
		}
	}
	loginwithbreak();
}
//按钮回调函数
void LayerLogin::LoginButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType)
{
	if (touchType != ui::Widget::TouchEventType::ENDED) return;
	Button* pBtn = (Button*) pRef;
	string name = pBtn->getName();
	if (name == "btnLogin" || "btn_yk_login" == name){
		scheduleOnce(schedule_selector(LayerLogin::UpdateBtn),4);
		checkupdate();
	}else if (name == "txt_agreement"){
		//用户信息协议查看
		auto tipContent= TipContent::create();
		tipContent->showUIPlayAgreement();
		this->addChild(tipContent,8);
	}
}
//复选框回调函数
void LayerLogin::LoginCheckBoxHandler(Ref* sender,ui::CheckBox::EventType type)
{
	bool isSelect = true;
	switch (type)
	{
	case CheckBox::EventType::SELECTED :
		isSelect = true;
		break;

	case CheckBox::EventType::UNSELECTED:
		isSelect = false;
		break;
	}
	CheckBox* pCB = (CheckBox*) sender;
	string name = pCB->getName();
	if (name == "cbIsAgree"){
		//是否同意
		CCLOG("checkbox--------------------------isAgree-----------xxxxxxxxxx");
		UserDefault::getInstance()->setBoolForKey(isAgreeUseInfo,isSelect);
	}
}
void LayerLogin::UpdateBtn(float time)
{
	txt_logining ->setVisible(false);
	btnLogin->setEnabled(true);
	if (MjData::getInstance()->IsVisitorLogin())
	{
		btn_yk_login->setEnabled(true);
	}
	else
	{
		btnLogin->setEnabled(true);
	}
}

void LayerLogin::onEnter()
{
	ParentInfo::onEnter();
}
void LayerLogin::onExit()
{
	unschedule(schedule_selector(LayerLogin::UpdateBtn));
	this->_eventDispatcher->removeCustomEventListeners(CustomEvent::key_show_game_menu);
	ParentInfo::onExit();
}

void LayerLogin::showGameMenu(EventCustom* evt)
{
	int status = GamerData::getInstance()->getStatus();
	int roomid=	GamerData::getInstance()->getTableId();
	Scene *s=Scene::create();
	int num = s->getChildrenCount();
	GameMenu *g=GameMenu::create();
	g->initwithuserinfo("","","");
	s->addChild(g);
	s->setName("menu");
	if(status==3)
	{
		g->enterroom(String::createWithFormat("%d",roomid)->getCString());
	}
	Director::getInstance()->replaceScene(s);
}

void LayerLogin::visitorLogin()
{	
	//struct timeval now;
	//gettimeofday(&now, NULL); // linux 下获取当前时间，精确到微妙
	//srand((unsigned int)(now.tv_sec*1000 + now.tv_usec/1000)); // set random see
	//unsigned long num = (unsigned long)(CCRANDOM_0_1() * 10000000000);
	int num=rand()%1000000+1000000;
	String * pID = String::createWithFormat("yk%d",num);
	GamerData::getInstance()->setOpenid(pID->getCString());
	GamerData::getInstance()->setNick(pID->getCString());
	GamerData::getInstance()->setSex(1);
	MissionWeiXin::getinstance()->req_login();
}