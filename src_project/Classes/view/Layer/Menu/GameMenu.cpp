#include "GameMenu.h"
#include "view/Layer/Tip/TipContent.h"
#include "view/Layer/Main/GameMain.h"
#include "net/Http.h"
#include "model/GamerData.h"
#include "model/MjData.h"
#include "tool/Tiperror.h"
#include "platform/MissionWeiXin.h"
#include "platform/JniFun.h"
#include "view/Layer/Lobby/LobbyView.h"
#include "SimpleAudioEngine.h"

#include "util/GameConst.h"
#include "controller/lobby/LobbyController.h"
#include "controller/login/LoginCommand.h"

void GameMenu::onEnter()
{

	this->_eventDispatcher->addCustomEventListener("addgamemain",CC_CALLBACK_1(GameMenu::addgamemain,this));
	this->_eventDispatcher->addCustomEventListener("cutsuccess",CC_CALLBACK_1(GameMenu::delayshare,this));
	this->_eventDispatcher->addCustomEventListener(GameConst::key_event_activity,CC_CALLBACK_1(GameMenu::showUIActivity,this));
	this->_eventDispatcher->addCustomEventListener(CustomEvent::key_show_ui_message,CC_CALLBACK_1(GameMenu::showUIMessage,this));
	this->_eventDispatcher->addCustomEventListener(CustomEvent::key_show_ui_bind_confirm,CC_CALLBACK_1(GameMenu::showUIBindConfirm,this));
	this->_eventDispatcher->addCustomEventListener(CustomEvent::key_update_ui_bind,CC_CALLBACK_1(GameMenu::updateUIBindConfirm,this));
	this->_eventDispatcher->addCustomEventListener(CustomEvent::key_show_laba,CC_CALLBACK_1(GameMenu::showLaba,this));
	this->_eventDispatcher->addCustomEventListener(CustomEvent::key_update_self_info,CC_CALLBACK_1(GameMenu::updateSelfInfo,this));
	this->_eventDispatcher->addCustomEventListener(CustomEvent::key_set_visible_loading_layer,CC_CALLBACK_1(GameMenu::setVisibleLoadingLayer,this));
	this->_eventDispatcher->addCustomEventListener(CustomEvent::key_show_game_main,CC_CALLBACK_1(GameMenu::showGameMain,this));
	this->_eventDispatcher->addCustomEventListener(CustomEvent::key_show_low_net_layer,CC_CALLBACK_1(GameMenu::showLowNet,this));
	this->_eventDispatcher->addCustomEventListener(CustomEvent::key_show_update_head,CC_CALLBACK_1(GameMenu::updatehead,this));
	this->_eventDispatcher->addCustomEventListener(CustomEvent::key_show_request_headinfo,CC_CALLBACK_1(GameMenu::requestHeadInfo,this));
	ParentInfo::onEnter();
}
void GameMenu::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
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

			SocketUtil::getInstance()->test();
		}
	}
}

void GameMenu::onExit()
{
	this->_eventDispatcher->removeCustomEventListeners("addgamemain");
	this->_eventDispatcher->removeCustomEventListeners("cutsuccess");
	this->_eventDispatcher->removeCustomEventListeners(GameConst::key_event_activity);
	this->_eventDispatcher->removeCustomEventListeners(CustomEvent::key_show_ui_message);
	this->_eventDispatcher->removeCustomEventListeners(CustomEvent::key_show_ui_bind_confirm);
	this->_eventDispatcher->removeCustomEventListeners(CustomEvent::key_update_ui_bind);
	this->_eventDispatcher->removeCustomEventListeners(CustomEvent::key_show_laba);
	this->_eventDispatcher->removeCustomEventListeners(CustomEvent::key_update_self_info);
	this->_eventDispatcher->removeCustomEventListeners(CustomEvent::key_set_visible_loading_layer);
	this->_eventDispatcher->removeCustomEventListeners(CustomEvent::key_show_game_main);
	this->_eventDispatcher->removeCustomEventListeners(CustomEvent::key_show_low_net_layer);
	this->_eventDispatcher->removeCustomEventListeners(CustomEvent::key_show_update_head);
	this->_eventDispatcher->removeCustomEventListeners(CustomEvent::key_show_request_headinfo);
	unschedule(schedule_selector(GameMenu::setVisibleLoadingLayer2));
	unschedule(schedule_selector(GameMenu::labaSchedule));
	ParentInfo::onExit();
}
void GameMenu::requestHeadInfo(EventCustom *evt)
{
	LobbyController::getInstance()->getShengLv(GamerData::getInstance()->getUId(),false);
}
void GameMenu::delayshare(EventCustom *evt)
{
	scheduleOnce(schedule_selector(GameMenu::delaysherebyschedule),1);
}
void GameMenu::delaysherebyschedule(float dt)
{
	MissionWeiXin::getinstance()->callback();
}
bool GameMenu::init()
{
	if(!ParentInfo::init()) return false;

	//注册捕捉监听
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(GameMenu::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

	Tools::stopallbgmusic();
	Tools::playBackMusic("dlyy.mp3");
	uiLoadAndShow();

	ParticleSystem* m_emitter1 = ParticleSystemQuad::create("res/partical/Desktop.plist"); 
	m_emitter1->setPosition(Vec2(200,500));
	addChild(m_emitter1,3); 
	return true;
}
void GameMenu::httpReqLaba()
{
    //获取公告内容
     rapidjson::Document d;
     d.SetObject();
     rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();
     Http::getInstance()->sendData("querrylaba",CC_CALLBACK_1(GameMenu::httpResLaba,this),d,true);

   
}

void GameMenu::httpResLaba(std::string res)
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
	 
		std::string laba=d["Context"].GetString();
		text_notice->setText(laba);
        labaSchedule(0);
        schedule(schedule_selector(GameMenu::labaSchedule),30.0f);

        httpReqHealthyNotice();

    }
}

void GameMenu::httpReqHealthyNotice()
{
    //获取公告内容
     rapidjson::Document d;
     d.SetObject();
     rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();
     Http::getInstance()->sendData("querryhealthynotice",CC_CALLBACK_1(GameMenu::httpResHealthyNotice,this),d,true);
}
void GameMenu::httpResHealthyNotice(std::string res)
{
    log("%s",res.c_str());
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    if(!d.HasMember("ResultCode")){
        return;
    }
    int  resultCode  = d["ResultCode"].GetInt(); //◊¥Ã¨
    if(resultCode==0)
    {
        rapidjson::Value& uerdetail=d["Context"];
        for(int i=0;i<uerdetail.Size();i++)
        {
            rapidjson::Value&vale=uerdetail[i];
            std::string msg=vale["msg"].GetString();
            text_noticeHealthy[i]->setText(msg);
        }
    }

}

void GameMenu::updateHeadInfo()
{
    String *s=String::createWithFormat("ID:%d",GamerData::getInstance()->getUId());
    UserId->setString(s->getCString());
    
    String *s1=String::createWithFormat("%d",GamerData::getInstance()->getRoomCard());
    goldNum->setString(s1->getCString());
}
void GameMenu::updatehead(EventCustom *evt)
{
	String *s=String::createWithFormat("ID:%d",GamerData::getInstance()->getUId());
	UserId->setString(s->getCString());

	String *s1=String::createWithFormat("%d",GamerData::getInstance()->getRoomCard());
	goldNum->setString(s1->getCString());
}
void GameMenu::createroom()
{
	//SocketUtil::getInstance()->StopConnect();
	LobbyController::getInstance()->setLayerLoadingVisible(true);
    //创建房间
    
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();
    d.AddMember("RoundLimit",MjData::getInstance()->getjushu(),alloctor);
	d.AddMember("IsMenGangMulti2",MjData::getInstance()->getIsgang_men(),alloctor);
	d.AddMember("IsGenZhuang",MjData::getInstance()->getIsgenZhuang(),alloctor);
	//MjData::getInstance()->setpalyrule(2);//测试
	d.AddMember("PlayRule",MjData::getInstance()->getpalyrule(),alloctor);
	CCLOG("---%d ---%d ---%d",MjData::getInstance()->getjushu(),MjData::getInstance()->getIsgang_men(),MjData::getInstance()->getIsgenZhuang());
    Http::getInstance()->sendData("createroom",CC_CALLBACK_1(GameMenu::createroomresponse,this),d,true);
}
void GameMenu::createroomresponse(std::string res)
{
	//LobbyController::getInstance()->setLayerLoadingVisible(false);
    log("%s",res.c_str());
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    int  resultCode  = d["ResultCode"].GetInt(); //状态
    if(resultCode != 0){
		LobbyController::getInstance()->setLayerLoadingVisible(false);
        const string errStr = d["ErrMsg"].GetString();
        addChild(Tiplayerr::create(errStr), 10);
        return;
    }

	//((TipContent *)(this->getChildByName("enterroom")))->removeFromParent();
	//((Node *)(this->getChildByName("enterroom")))->removeFromParent();

    //socket连接以及桌子和座位的信息
    string   serverUrl = d["Host"].GetString();		//服务器 
    int      port      = d["Port"].GetInt();		//端口号
    int      tableId   = d["TableID"].GetInt();		//桌子id
    int      seatId    = d["SeatID"].GetInt();		//座位id

    GamerData::getInstance()->setTableId(tableId);

    GamerData::getInstance()->setSeatId(seatId);
    GamerData::getInstance()->setServerIP(serverUrl);
    GamerData::getInstance()->setServerPort(port);


   //socket连接服务器
    bool isConnectB = SocketUtil::getInstance()->isConnected();
    if(isConnectB)
	{
		CCLOG("============GameMenu::createroomresponse===========StopConnect==");
		SocketUtil::getInstance()->StopConnect();
	}
    bool isConnect = SocketUtil::getInstance()->connectServer();
    if (isConnect)
    {//服务器连接成功
		unschedule(schedule_selector(GameMenu::setVisibleLoadingLayer2));
		scheduleOnce(schedule_selector(GameMenu::setVisibleLoadingLayer2),15);
		LoginCommand::getInstance()->requestLogin(GamerData::getInstance()->getUId(),GamerData::getInstance()->getTableId());
  //      auto gameMain = GameMain::create();
		//gameMain->login();
  //      this->addChild(gameMain,9);
    }
	else
	{
		unschedule(schedule_selector(GameMenu::setVisibleLoadingLayer2));
		scheduleOnce(schedule_selector(GameMenu::setVisibleLoadingLayer2),10);
		//LobbyController::getInstance()->setLayerLoadingVisible(false);
	}
}
void GameMenu::initwithuserinfo(std::string url,std::string name,std::string openid)
{
	updateHeadInfo();
    nickName->setString(GamerData::getInstance()->getNick().c_str());

	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	path += GamerData::getInstance()->getOpenid()+".png";
	Sprite *sp=Sprite::create(path.c_str());
	if(sp!=nullptr)
	{
		sprite_headImg->setTexture(sp->getTexture());
		return;
	}

	if (GamerData::getInstance()->getHeadUrl() == "")
	{
		return;
	}
    CCLOG("%s",url.c_str());
    cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
    request->setUrl(GamerData::getInstance()->getHeadUrl().c_str());
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(GameMenu::onGetFinished));
    request->setTag("GET test1");
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
    
}

 void GameMenu::onGetFinished(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
 {
     if (!response)
     {
         return;
     }
     
     // You can get original request type from: response->request->reqType
     if (0 != strlen(response->getHttpRequest()->getTag()))
     {
         log("%s completed", response->getHttpRequest()->getTag());
     }
     int statusCode = response->getResponseCode();
     if (!response->isSucceed())
     {
         log("response failed");
         log("error buffer: %s", response->getErrorBuffer());
         return;
     }     
     //get data
     std::vector<char> *buffer = response->getResponseData();     

  //   //create image
  //   CCImage* img = new CCImage;
  //   img->initWithImageData((unsigned char*)buffer->data(),buffer->size()); 	 
  //   //create texture
  //   cocos2d::CCTexture2D* texture = new CCTexture2D();
  //   bool isImg = texture->initWithImage(img);
  //   img->release();     
	 //sprite_headImg->setTexture(texture);
  
     
     //write file
     std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	 path += GamerData::getInstance()->getOpenid()+".png";
     
	 FILE *fp = fopen(path.c_str(), "wb+");
	 fwrite(buffer->data(), 1,buffer->size(), fp);
	 fclose(fp);

	 Sprite *sp=Sprite::create(path.c_str());
	 if(sp!=nullptr)
	 {
		 sprite_headImg->setTexture(sp->getTexture());
	 } 
 }
 void GameMenu::end(float dt)
{
//    WeiChatLogin::getInstance()->endRecord();
 //   WeiChatLogin::getInstance()->playaudio(cocos2d::FileUtils::getInstance()->getWritablePath()+"SoundRecord.wav");
}
//ui加载并且显示
void GameMenu::uiLoadAndShow()
{
	auto menu = CSLoader::createNode("res/loading/GameMenu.csb") ;   //大厅
	//auto menu = CSLoader::createNode("res/loading/lobbyCsd/LobbyMain.csb") ;   //大厅
	this->addChild(menu);


	//sp_createroom=(Sprite *)menu->getChildByName("jr_5");
	auto goldBarBg = (ImageView*)menu->getChildByName("goldBarBg");
	goldNum = (Text*)goldBarBg->getChildByName("goldNum");//钻石数量显示
	auto btnAddGold = (Button*)goldBarBg->getChildByName("btnAddGold");//钻石增加按钮
	btnAddGold->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler, this));

	Button *bt_head=(Button *)menu->getChildByName("Button_head");
	bt_head->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler,this));

	nickName = (Text*)menu->getChildByName("nickName");   //玩家昵称
	UserId = (Text*)menu->getChildByName("userId");	  //玩家ID
	sprite_headImg = (Sprite*)menu->getChildByName("sprite_headImg");//玩家头像


	auto btnShare = (Button*)menu->getChildByName("btnShare"); //分享按钮
	btnShare->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler, this));
	

	auto btnShareCircle = (Button*)menu->getChildByName("btnShareCircle"); //分享按钮
	btnShareCircle->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler, this));



	auto btnNotice = (Button*)menu->getChildByName("btnNotice"); //通知按钮
	btnNotice->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler, this));
	auto btnAchievement = (Button*)menu->getChildByName("btnAchievement"); //成就按钮
	btnAchievement->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler, this));
	auto btnHelp = (Button*)menu->getChildByName("btnHelp"); //帮助按钮
	btnHelp->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler, this));
	auto btnSet = (Button*)menu->getChildByName("btnSet"); //设置按钮
	btnSet->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler, this));
	auto btnGet = (Button*)menu->getChildByName("btnGet"); //免费领取按钮
	btnGet->setVisible(false);
	auto btnNewPlayer = (Button*)menu->getChildByName("btnNewPlayer"); //新手礼包按钮
	//btnNewPlayer->setVisible(false);
	btnNewPlayer->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler, this));
	btnCreateRoom = (Button*)menu->getChildByName("btnCreateRoom"); //创建房间按钮
	btnCreateRoom->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler, this));
	
	btnJoinRoom = (Button*)menu->getChildByName("btnJoinRoom"); //加入房间按钮
	btnJoinRoom->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler, this));
	btnBackRoom = (Button*)menu->getChildByName("btnBackRoom"); //返回房间按钮
	btnBackRoom->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler, this));

    //公告
    panel_notice = (Layout*)menu->getChildByName("panelNotice");
    text_notice = (Text*)(panel_notice->getChildByName("Text_notice"));

    //健康公告
    auto healthy = (ImageView*)menu->getChildByName("iconTip");
    text_noticeHealthy[0] = (Text*)(healthy->getChildByName("Text_1"));
    text_noticeHealthy[1] = (Text*)(healthy->getChildByName("Text_2"));
    text_noticeHealthy[2] = (Text*)(healthy->getChildByName("Text_3"));
    text_noticeHealthy[3] = (Text*)(healthy->getChildByName("Text_4"));
    text_noticeHealthy[4] = (Text*)(healthy->getChildByName("Text_5"));


	static_cast<Button*>(menu->getChildByName("btn_feedback"))->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler,this));
	static_cast<Button*>(menu->getChildByName("btn_binding"))->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler,this));
	static_cast<Button*>(menu->getChildByName("btn_activity"))->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler,this));
	static_cast<Button*>(menu->getChildByName("btn_msg"))->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler,this));
	static_cast<Button*>(menu->getChildByName("goldBarBg")->getChildByName("btn_addCard"))->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler,this));

	if(MjData::getInstance()->getisinapple()==1)
	{
		btnShare->setVisible(false);
		btnShare->setEnabled(false);
		btnShareCircle->setEnabled(false);
		btnShareCircle->setVisible(false);
		static_cast<Button*>(menu->getChildByName("btn_feedback"))->setVisible(false);
		static_cast<Button*>(menu->getChildByName("btn_feedback"))->setEnabled(false);
		static_cast<Button*>(menu->getChildByName("btn_binding"))->setVisible(false);
		static_cast<Button*>(menu->getChildByName("btn_binding"))->setEnabled(false);
		static_cast<Button*>(menu->getChildByName("btn_activity"))->setVisible(false);
		static_cast<Button*>(menu->getChildByName("btn_activity"))->setEnabled(false);
		bt_head->setEnabled(false);
		((ImageView*)menu->getChildByName("goldBarBg")->getChildByName("img_click"))->setEnabled(false);
		static_cast<Button*>(menu->getChildByName("goldBarBg")->getChildByName("btn_addCard"))->setEnabled(false);
		static_cast<Button*>(menu->getChildByName("goldBarBg")->getChildByName("btn_addCard"))->setVisible(false);
		((Sprite*)menu->getChildByName("goldBarBg")->getChildByName("icon_fangka_7"))->setVisible(false);
		goldNum->setVisible(false);
		btnAddGold->setVisible(false);
		btnAddGold->setEnabled(false);
		panel_notice->setVisible(false);
		((Sprite *)menu->getChildByName("Sprite_9"))->setVisible(false);
	}



	((ImageView*)menu->getChildByName("goldBarBg")->getChildByName("img_click"))->addTouchEventListener(CC_CALLBACK_2(GameMenu::ButtonHandler,this));
	Node* node = (Node*)(menu->getChildByName("btn_binding")->getChildByName("tip_gift"));

	cocostudio::timeline::ActionTimeline* action = CSLoader::createTimeline("res/loading/GameMenu.csb");
	action->play("anim_gift",true);
	node->runAction(action);

	refreshjoinroom();
}
void GameMenu::setsanding()
{
	MjData::getInstance()->setpalyrule(2);
}
void GameMenu::setsandingliangfang()
{
	MjData::getInstance()->setpalyrule(4);
}
void GameMenu::refreshjoinroom()
{
	if(GamerData::getInstance()->getStatus()==4)//准备状态 qie wei jiesan
	{
		//直接进入游戏
	     this->enterroom(String::createWithFormat("%d",GamerData::getInstance()->getTableId())->getCString());
		/*btnCreateRoom->setEnabled(false);
		btnJoinRoom->setVisible(false);
		btnJoinRoom->setEnabled(false);
		btnBackRoom->setVisible(true);
		btnBackRoom->setEnabled(true);*/
		//sp_createroom->setTexture("res/loading/gamemenu/fh.png");
	}
	else
	{
		btnCreateRoom->setEnabled(true);
		btnJoinRoom->setVisible(true);
		btnJoinRoom->setEnabled(true);
		btnBackRoom->setVisible(false);
		btnBackRoom->setEnabled(false);
		//sp_createroom->setTexture("res/loading/gamemenu/jr.png");

		SEND_CUSTOM_MSG(CustomEvent::key_update_self_info,nullptr);
	}
}
void GameMenu::endluyin(float dt)
{
	std::string path=JniFun::stopSoundRecord();
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(path.c_str());
}
void GameMenu::requestshengpingfu(int uid)
{
	rapidjson::Document d;
	d.SetObject();
	rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();
	
	d.AddMember("UserID",GamerData::getInstance()->getUId(),alloctor);
	Http::getInstance()->sendData("get_ju_cnt",CC_CALLBACK_1(GameMenu::responseshengpingfu,this),d,true);
}
void GameMenu::responseshengpingfu(std::string res)
{
	log("%s",res.c_str());
	rapidjson::Document d;
	d.Parse<0>(res.c_str());
	int  resultCode  = d["ResultCode"].GetInt(); //状态
	if(resultCode != 0){
		const string errStr = d["ErrMsg"].GetString();
		addChild(Tiplayerr::create(errStr), 10);
		return;
	}
	int juwin=d["JuWin"].GetInt();
	int juping=d["JuDraw"].GetInt();
	int julose=d["JuLose"].GetInt();
	UserDefault::getInstance()->setIntegerForKey("juwin",juwin);
	UserDefault::getInstance()->setIntegerForKey("juping",juping);
	UserDefault::getInstance()->setIntegerForKey("julose",julose);
	int zong = juwin+juping+julose;
	UserDefault::getInstance()->setIntegerForKey("zongJu",zong);
	float shengLv = 0;
	if (zong == 0)
	{
		shengLv = 0;
	}
	else
	{
		shengLv = juwin*100.0/zong;
	}	
	UserDefault::getInstance()->setFloatForKey("shengLv",shengLv);

	
		auto tipConent = TipContent::create();
		//tipConent->showUIplayerInfo();
		tipConent->showUIplayerInfoInGame(0);
		this->addChild(tipConent,9);
		
}
//按钮回调函数
void GameMenu::ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType)
{
	if (touchType != ui::Widget::TouchEventType::ENDED) return;
	Button* pBtn = (Button*) pRef;
	string name = pBtn->getName();
	if (name == "btnAddGold"){
		//钻石增加
		CCLOG("--------------------------btnAddGold------------------");
		//Platform::Login();
	//	JniFun::startSoundRecord();
		//schedule(schedule_selector(GameMenu::endluyin),5);
		
	}
	else if(name=="Button_head"){
		//个人信息
		CCLOG("--------------------------btnHead------------------");

		//requestshengpingfu(GamerData::getInstance()->getUId());
		LobbyController::getInstance()->getShengLv(GamerData::getInstance()->getUId(),true);
		 
	}else if (name == "btnShare")
	{//分享
		CCLOG("--------------------------btnShare------------------");
		std::string jinping=Tools::getChineseByKey("jinping");
		std::string jinpingmajiang=Tools::getChineseByKey("jinpingmajiang");
		MissionWeiXin::getinstance()->shareUrlWeiXin("http://d.laiyagame.com/jinping/download.html",jinping.c_str(),jinpingmajiang.c_str(),0);
		
	}else if (name == "btnShareCircle")
	{//分享
		CCLOG("--------------------------btnShare------------------");

		auto lobbyView = LobbyView::create();
		lobbyView->showUIShare();
		this->addChild(lobbyView);
		//MissionWeiXin::getinstance()->shareUrlWeiXin("http://v.baidu.com/","baile","baile",1);
	}else if (name == "btnNotice")
	{//通知
		auto tipConent = TipContent::create();
		tipConent->showUINotice();
		this->addChild(tipConent,9);
	}else if (name == "btnAchievement")
	{//成就
		//reqzjlb();
		LobbyController::getInstance()->getHistoryRecord();
		/*
		auto tipConent = TipContent::create();
		tipConent->showUIAchievement("sss");
		this->addChild(tipConent,9);
		*/
	}else if (name == "btnHelp")
	{//帮助
		//auto tipConent = TipContent::create();
		//tipConent->showUIHelp();
		//this->addChild(tipConent,9);

		auto lobbyView = LobbyView::create();
		lobbyView->showUIRule();
		this->addChild(lobbyView);

	}else if (name == "btnSet")
	{//设置
		//auto tipConent = TipContent::create();
		//tipConent->showUISet();
		//this->addChild(tipConent,9);

		auto lobbyView = LobbyView::create();
		lobbyView->showUISetting(false);
		this->addChild(lobbyView);

	}else if (name == "btnCreateRoom")
	{//创建房间
		CCLOG("--------------------------btnCreateRoom------------------");
		
		
		//auto tipConent = TipContent::create();
		//tipConent->showUICreateRoom();
		//this->addChild(tipConent,9);

		auto lobbyView = LobbyView::create();
		lobbyView->showUICreateRoom();
		this->addChild(lobbyView);
		
	}else if (name == "btnJoinRoom")
	{//加入房间
		CCLOG("--------------------------btnJoinRoom------------------");
		//auto tipConent = TipContent::create();
		//tipConent->showUIEnterRoom();
		//this->addChild(tipConent,9);

		auto lobbyView = LobbyView::create();
		lobbyView->showUIJoinRoom();
		this->addChild(lobbyView);
	}else if (name == "btnBackRoom")
	{//返回房间
		CCLOG("--------------------------btnBackRoom------------------");

		
		this->enterroom(String::createWithFormat("%d",GamerData::getInstance()->getTableId())->getCString());
	}
	else if(name == "btnNewPlayer")
	{
       requestaddstone();
	}
	else if(name == "btn_feedback")
	{
		auto lobbyView = LobbyView::create();
		lobbyView->showUIFeedback();
		this->addChild(lobbyView);
	}
	else if(name == "btn_binding")
	{
		auto lobbyView = LobbyView::create();
		lobbyView->showUIBinding();
		lobbyView->setName("showUIBinding");
		this->addChild(lobbyView);
	}
	else if(name == "btn_activity")
	{
		//auto lobbyView = LobbyView::create();
		//lobbyView->showUIActivity();
		//this->addChild(lobbyView);
		bool isShowActivityPic = true;
		EventCustom* ec =new EventCustom("");
		ec->setUserData(&isShowActivityPic);
		showUIActivity(ec);
		//SEND_CUSTOM_MSG(GameConst::key_event_activity,&isShowActivityPic);
	}
	else if(name == "btn_addCard" || name == "img_click")
	{
		auto lobbyView = LobbyView::create();
		lobbyView->showUIAddCard();
		this->addChild(lobbyView);
	}
	else if(name == "btn_msg")
	{
		//auto lobbyView = LobbyView::create();
		//lobbyView->showUIMessage();
		//this->addChild(lobbyView);
		LobbyController::getInstance()->getMsgList();
	}
}
void GameMenu::reqzjlb()
{
	rapidjson::Document d;
	d.SetObject();
	rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();

	d.AddMember("UserID",GamerData::getInstance()->getUId(),alloctor);
	Http::getInstance()->sendData("get_history",CC_CALLBACK_1(GameMenu::reszjlb,this),d,true);
}
void GameMenu::reszjlb(std::string res)
{
	log("%s",res.c_str());
	rapidjson::Document d;
	d.Parse<0>(res.c_str());
	int  resultCode  = d["ResultCode"].GetInt(); //状态
	if(resultCode != 0){
		const string errStr = d["ErrMsg"].GetString();
		addChild(Tiplayerr::create(errStr), 10);
		return;
	}
		auto tipConent = TipContent::create();
		tipConent->showUIAchievement(res);
		this->addChild(tipConent,9);
		
}
void GameMenu::requestaddstone()
{
	rapidjson::Document d;
	d.SetObject();
	rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();

	d.AddMember("UserID",GamerData::getInstance()->getUId(),alloctor);
	Http::getInstance()->sendData("newcomer_reward",CC_CALLBACK_1(GameMenu::responseaddstone,this),d,true);
} 
void GameMenu::responseaddstone(std::string res)
{
	log("%s",res.c_str());
	rapidjson::Document d;
	d.Parse<0>(res.c_str());
	int  resultCode  = d["ResultCode"].GetInt(); //状态
	if(resultCode != 0){
		const string errStr = d["ErrMsg"].GetString();
		addChild(Tiplayerr::create(errStr), 10);

		return;
	}
	const string errStr = d["Msg"].GetString();
	addChild(Tiplayerr::create(errStr), 10);

	int goldchange=d["BigGoldChange"].GetInt();
	GamerData::getInstance()->setRoomCard(GamerData::getInstance()->getRoomCard()+goldchange);
	updateHeadInfo();
}
void GameMenu::enterroom(std::string roomid)
{
    //加入房间
	//加入房间
	rapidjson::Document d;
	d.SetObject();
	rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();
	
	d.AddMember("RoomID",atoi(roomid.c_str()),alloctor);
	Http::getInstance()->sendData("enterroom",CC_CALLBACK_1(GameMenu::enterroomresponse,this),d,true);

}
void GameMenu::enterroomresponse(std::string res)
{
	log("%s",res.c_str());
	rapidjson::Document d;
	d.Parse<0>(res.c_str());
	int  resultCode  = d["ResultCode"].GetInt(); //状态
	if(resultCode != 0){
		const string errStr = d["ErrMsg"].GetString();
        addChild(Tiplayerr::create(errStr), 10);
		return;
	}
	//SEND_CUSTOM_MSG(GameConst::key_remove_lobby);
	
    if(this->getChildByName("enterroom")!=nullptr)
    {
		((Node *)(this->getChildByName("enterroom")))->removeFromParent();
    }	
	if(this->getChildByName("showUIJoinRoom")!=nullptr)
	{
		((Node *)(this->getChildByName("showUIJoinRoom")))->removeFromParent();
	}
	
	//socket连接以及桌子和座位的信息
	string   serverUrl = d["Host"].GetString();		//服务器 
	int      port      = d["Port"].GetInt();		//端口号
	int      tableId   = d["TableID"].GetInt();		//桌子id
	int      seatId    = d["SeatID"].GetInt();		//座位id
	int     playrule=d["PlayRule"].GetInt();
	GamerData::getInstance()->setTableId(tableId);

	GamerData::getInstance()->setSeatId(seatId);

	GamerData::getInstance()->setServerIP(serverUrl);
	GamerData::getInstance()->setServerPort(port);
	MjData::getInstance()->setpalyrule(playrule);

	CCLOG("ismenggang%d",d["IsMenGangMulti2"].GetInt());
	CCLOG("ismenggang%d",d["IsGenZhuang"].GetInt());
	MjData::getInstance()->setjushu(d["RoundLimit"].GetInt());
	if(d["IsMenGangMulti2"].GetInt()==1)
	{
		MjData::getInstance()->setIsgang_men(1);
	}
	else
	{
		MjData::getInstance()->setIsgang_men(0);
	}
	MjData::getInstance()->setIsgenZhuang(d["IsGenZhuang"].GetInt());
	
	//socket连接服务器
	bool isConnectB = SocketUtil::getInstance()->isConnected();
	if(isConnectB) 
	{
		CCLOG("============GameMenu::enterroomresponse===========StopConnect==");
		SocketUtil::getInstance()->StopConnect();
	}
	bool isConnect = SocketUtil::getInstance()->connectServer();
	if (isConnect)
	{//服务器连接成功
		LobbyController::getInstance()->setLayerLoadingVisible(true);
		unschedule(schedule_selector(GameMenu::setVisibleLoadingLayer2));
		scheduleOnce(schedule_selector(GameMenu::setVisibleLoadingLayer2),15);
		LoginCommand::getInstance()->requestLogin(GamerData::getInstance()->getUId(),GamerData::getInstance()->getTableId());

		//auto gameMain = GameMain::create();
		//gameMain->login();
		//this->addChild(gameMain,9);
	}       
	else
	{
		//LobbyController::getInstance()->setLayerLoadingVisible(false);
		unschedule(schedule_selector(GameMenu::setVisibleLoadingLayer2));
		scheduleOnce(schedule_selector(GameMenu::setVisibleLoadingLayer2),10);
	}
}
void GameMenu::addgamemain(EventCustom *evt)
{
	scheduleOnce(schedule_selector(GameMenu::delay_addmain),0.3);
}
void GameMenu::delay_addmain(float dt)
{
	/*
	GameMain *g_m=GameMain::create();
	addChild(g_m,99);

	g_m->mj_player->refreshhead();
	*/
}


void GameMenu::labaSchedule(float a)
{
    text_notice->setPositionX(panel_notice->getContentSize().width+10);
    text_notice->runAction(MoveBy::create(28.0f,Vec2(0-panel_notice->getContentSize().width-text_notice->getContentSize().width,0)));
}

void GameMenu::showUIActivity(EventCustom *evt)
{
	bool* isShowActivityPic = (bool*)evt->getUserData();
	if (*isShowActivityPic == false)
	{
		return;
	}

	if (this->getChildByTag(8888))
	{
		return;
	}
	auto lobbyView = LobbyView::create();
	lobbyView->showUIActivity();
	lobbyView->setTag(8888);
	this->addChild(lobbyView);
}

void GameMenu::showUIMessage(EventCustom *evt)
{
	//vector<MessageInfo>* vectorMsg = (vector<MessageInfo>*)evt->getUserData();
	vector<MessageInfo*>* vectorMsg = (vector<MessageInfo*>*)evt->getUserData();
	auto lobbyView = LobbyView::create();
	lobbyView->showUIMessage(*vectorMsg);
	this->addChild(lobbyView);
}

void GameMenu::showUIBindConfirm(EventCustom *evt)
{ 
	BindParentInfo* info = (BindParentInfo*)evt->getUserData();
	auto view = LobbyView::create();
	view->showUIBindConfirm(info->nickName,info->userId);
	//view->showUIBindConfirm("info.nickName","info.userId");
	view->setName("showUIBindConfirm");
	this->addChild(view);
}

void GameMenu::updateUIBindConfirm(EventCustom *evt)
{
	int* type = (int*)evt->getUserData();
	Node* lay = this->getChildByName("showUIBindConfirm");
	if (lay)
	{
		lay->removeFromParent();
	}
	Node* bindLayer = (Layer*)this->getChildByName("showUIBinding");
	if (bindLayer)
	{
		Node* nodeRoot = bindLayer->getChildByName("Layer_showUIBinding");
		if (nodeRoot)
		{
			Node* temp = nodeRoot->getChildByName("layer_bg");
			if (temp)
			{
				if (*type == 1)
				{
					((Button*)temp->getChildByName("btn_binding_code"))->setEnabled(false);
					((TextField*)temp->getChildByName("TextField_Code"))->setEnabled(false);
				}
				else
				{
					((Button*)temp->getChildByName("btn_binding_person"))->setEnabled(false);
					((TextField*)temp->getChildByName("TextField_Person"))->setEnabled(false);			
				}
			}
		}
	}
}

void GameMenu::showLaba(EventCustom *evt)
{
	unschedule(schedule_selector(GameMenu::labaSchedule));
	string* temp = (string*)evt->getUserData();
	//std::string laba=d["Context"].GetString();
	//text_notice->setText(laba);
	text_notice->setText(*temp);
	labaSchedule(0);
	schedule(schedule_selector(GameMenu::labaSchedule),30.0f);
}

void GameMenu::updateSelfInfo(EventCustom *evt)
{
	log("-----updateSelfInfo-----");
}

void GameMenu::setVisibleLoadingLayer(EventCustom* evt)
{
	bool* visible = (bool*)evt->getUserData();
	LobbyController::getInstance()->setLayerLoadingVisible(*visible);
}

void GameMenu::showGameMain(EventCustom* evt)
{
	unschedule(schedule_selector(GameMenu::setVisibleLoadingLayer2));
	if ((Node *)(this->getChildByName("enterroom")))
	{
		((Node *)(this->getChildByName("enterroom")))->removeFromParent();
	}
	auto gameMain = GameMain::create();
	this->addChild(gameMain,9);
}

void GameMenu::showLowNet(EventCustom* evt)
{
	LobbyController::getInstance()->setLayerNetworkErrorVisible(true);
}

void GameMenu::setVisibleLoadingLayer2(float time)
{
	LobbyController::getInstance()->setLayerLoadingVisible(false);
	LobbyController::getInstance()->setLayerNetworkErrorVisible(true);	
}