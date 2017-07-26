#include "LobbyView.h"
#include "tool/Tools.h"
#include "tool/Tiperror.h"
#include "CellItemRecord.h"
#include "CellItemMsg.h"
#include "AudioEngine.h"

#include "platform/MissionWeiXin.h"
#include "platform/JniFun.h"
#include "model/LobbyData.h"
#include "model/MjData.h"
#include "controller/lobby/LobbyCommand.h"
#include "view/Layer/Menu/GameMenu.h"
#include "controller/table/TableCommand.h"
#include "controller/lobby/LobbyController.h"

#include "util/GameConst.h"
#include "util/GameResources.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <regex>
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <regex.h>
#endif

bool LobbyView::init()
{
	if(!ParentInfo::init()) return false;
	nodeUIBindConfirm = nullptr;
	isPauseScroll = true;
	log("----------LobbyView::init()----------");
	return true;
}

void LobbyView::onEnter()
{
	log("----------LobbyView::onEnter()---------111-");
	ParentInfo::onEnter();
	//this->_eventDispatcher->addCustomEventListener(GameConst::key_event_activity,CC_CALLBACK_1(LobbyView::showUIActivity,this));
	this->_eventDispatcher->addCustomEventListener(GameConst::key_remove_lobby,CC_CALLBACK_1(LobbyView::deleteself,this));
	//scheduleUpdate();
	log("----------LobbyView::onEnter()---------222-");
}
void LobbyView::onExit()
{

	this->_eventDispatcher->removeCustomEventListeners(GameConst::key_remove_lobby);
	ParentInfo::onExit();

	//auto dispatcher = Director::getInstance()->getEventDispatcher();
	//dispatcher->dispatchCustomEvent(CustomEvent::key_update_ui_bind);
	log("----------LobbyView::onExit()----------");
}

void LobbyView::deleteself(EventCustom* evt)
{
	  if(this->getName()=="showUIJoinRoom") 
	  {
		  this->removeFromParent();
	  }
	  if(this->getName()=="enterroom")
	  {
		  this->removeFromParent();
	  }
		
}
Node* LobbyView::LoadCsb(string pathCsb)
{
	Node* root = CSLoader::createNode(pathCsb);
	this->addChild(root);
	Node* bgNode = root->getChildByName("layer_bg");
	Button* btnExit = (Button*)bgNode->getChildByName("btn_exit");
	if (btnExit)
	{
		btnExit->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	}
	return bgNode;
}

void LobbyView::sliderEvent(cocos2d::Ref* pSender,ui::Slider::EventType type)
{
	string sliderName = ((Slider*)pSender)->getName();
	if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		int persent = ((Slider*)pSender)->getPercent();
		if (sliderName == "slider_bg_music"){
			Tools::setBackMusicVolume(persent*0.01);
			experimental::AudioEngine::setVolume(Tools::g_backGroundMusicID, Tools::getMusicVolume());
		}else if (sliderName == "slider_soundEffect"){
			Tools::saveEffectVolume(persent*0.01);
		}else{

		}
	}
}
void LobbyView::checkBoxEvent(cocos2d::Ref *pSender, CheckBoxEventType type)
{
	string cbName = ((CheckBox*)pSender)->getName();
	switch (type)
	{
	case CheckBoxEventType::CHECKBOX_STATE_EVENT_SELECTED:
		if (cbName == "checkbox_native"){
			checkbox_general->setSelected(false);
			Tools::setLanguage(1);
		}else if (cbName == "checkbox_general"){
			checkbox_native->setSelected(false);
			Tools::setLanguage(2);		

		}else if (cbName == "checkbox_ju_4")	{
			checkbox_ju_8->setSelected(false);
			MjData::getInstance()->setjushu(4);
		}else if (cbName == "checkbox_ju_8"){
			checkbox_ju_4->setSelected(false);
			MjData::getInstance()->setjushu(8);


		}else if (cbName == "checkbox_gang_men"){
			checkbox_gang_zhuangwan->setSelected(false);
			MjData::getInstance()->setIsgang_men(1);
			MjData::getInstance()->setIsgang_zhuangwan(0);
		}else if (cbName == "checkbox_gang_zhuangwan"){
			checkbox_gang_men->setSelected(false);
			MjData::getInstance()->setIsgang_men(0);
			MjData::getInstance()->setIsgang_zhuangwan(1);
		}else	if(cbName.find("ck_game_",0) == 0){
			String index = cbName.substr(strlen("ck_game_"));
			updateGameCheckBox(index.intValue());
		}else{

		}
		
		break;
	case CheckBoxEventType::CHECKBOX_STATE_EVENT_UNSELECTED:
		if (cbName == "checkbox_native"){
			checkbox_general->setSelected(true);
			Tools::setLanguage(2);
		}else if (cbName == "checkbox_general"){
			checkbox_native->setSelected(true);
			Tools::setLanguage(1);

		}else if (cbName == "checkbox_ju_4")	{
			checkbox_ju_8->setSelected(true);
			MjData::getInstance()->setjushu(8);
		}else if (cbName == "checkbox_ju_8"){
			checkbox_ju_4->setSelected(true);
			MjData::getInstance()->setjushu(4);


		}else if (cbName == "checkbox_gang_men"){
			checkbox_gang_zhuangwan->setSelected(true);
			MjData::getInstance()->setIsgang_men(0);
			MjData::getInstance()->setIsgang_zhuangwan(1);
		}else if (cbName == "checkbox_gang_zhuangwan"){
			checkbox_gang_men->setSelected(true);
			MjData::getInstance()->setIsgang_men(1);
			MjData::getInstance()->setIsgang_zhuangwan(0);
		}else{

		}
		break;
	default:
		break;
	}

}
void LobbyView::btnHandle(Ref* sender)
{
	Button* btn = (Button*)sender;
	Node* parent = btn->getParent();
	string btnName = btn->getName();

	if (btnName == "btn_exit"){
		this->removeAllChildrenWithCleanup(true);
		this->removeFromParentAndCleanup(true);
	}else if (btnName == "btn_logout"){
		btn->getParent()->setVisible(false);
		this->showUILogoutTip(true);
	}else if (btnName == "btn_cancle_logout")	{
		UserDefault::getInstance()->setBoolForKey("ishaveback",false);
		this->removeAllChildrenWithCleanup(true);
		this->removeFromParentAndCleanup(true);
	}else if (btnName == "btn_ok_logout"){
		UserDefault::getInstance()->setBoolForKey("ishaveback",false);
		this->removeAllChildrenWithCleanup(true);
		this->removeFromParentAndCleanup(true);
		int tag = btn->getTag();
		if (tag == 4455)
		{
			cocos2d::UserDefault::getInstance()->setStringForKey("accesstoken","");
			cocos2d::UserDefault::getInstance()->setStringForKey("openid","");
		}
		//退出登录
		CCDirector::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}else if (btnName == "btnDismissRoom" || btnName == "btn_backLobby")	{

		TableCommand::getInstance()->requestLeaveTable(1);
		this->removeFromParent();
	}else if (btnName == "btn_share")	{
		auto lobbyView = LobbyView::create();
		lobbyView->showUIWeiXinShare(0);
		this->getParent()->addChild(lobbyView);
	}else if (btnName == "btn_createRoom")	{
		((GameMenu*)this->getParent())->createroom();
	}else if (btnName == "btn_binding_code"){
		string code = ((TextField*)parent->getChildByName("TextField_Code"))->getStringValue();
		//bool isFlag = checkInputNumber(code);
		if (code != "")
		{
			LobbyController::getInstance()->getInviterInfo(code);
		}
	}else if (btnName == "btn_binding_person"){
		string person = ((TextField*)parent->getChildByName("TextField_Person"))->getStringValue();
		if (person != "")
		{
			LobbyController::getInstance()->getPromoterInfo(person);
		}
	}else if (btnName == "txt_native" || btnName == "txt_general"){
		setCKSelectedFlag();
	}else if (btnName == "btn_copy"){
		string wxCode = ((Text*)parent->getChildByName("txt_wxCode"))->getString();
		JniFun::copyText(wxCode.c_str());

		const string  copySuccess = Tools::getChineseByKey("copySuccess");
		auto temp = Tiplayerr::create(copySuccess);
		temp->setName("Tiplayerr");
		this->addChild(temp);
	}
	else if (btnName == "btn_confirm_banding")
	{
		log("-------btnLoginout----");
		//this->removeAllChildrenWithCleanup(true);
		//this->removeFromParentAndCleanup(true);
		LobbyController::getInstance()->bindUser();
	}
	else if (btnName == "img_click_4ju" || btnName == "img_click_8ju")
	{
		setCreateViewSelectedFlag(1);
	}
	else if (btnName == "img_click_zi" || btnName == "img_click_meng")
	{
		setCreateViewSelectedFlag(2);
	}else if (btnName.find("btn_copy_",0) == 0)
	{
		log("---btn_name=%s---",btnName.c_str());
		string name = "txt_"+btnName.substr(strlen("btn_copy_"));
		string value = ((Text*)parent->getChildByName(name))->getString();
		JniFun::copyText(value.c_str());

		const string  copySuccess = Tools::getChineseByKey("copySuccess");
		auto temp = Tiplayerr::create(copySuccess);
		temp->setName("Tiplayerr");
		this->addChild(temp);
	}
	else if (btnName == "btn_share_qun")
	{		
		int  type =btn->getTag();
		if (type == 0)
		{
			std::string jinping=Tools::getChineseByKey("jinping");
			std::string jinpingmajiang=Tools::getChineseByKey("menushare");
			String *jinpinginveiteadd=String::createWithFormat(jinpingmajiang.c_str(),GamerData::getInstance()->getMyInviteCode().c_str());
			MissionWeiXin::getinstance()->shareUrlWeiXin("http://d.laiyagame.com/jinping/download.html",jinping.c_str(),jinpinginveiteadd->getCString(),0);
		}
		else if(type == 1)
		{
			int flag = 0;
			SEND_CUSTOM_MSG("WeiXinShareInGame",&flag);
		}
		else if(type==2)
		{
			this->setVisible(false);
			int flag = 0;
			MissionWeiXin::getinstance()->cutscreen(flag);
			this->removeFromParent();
		}
	}
	else if (btnName == "btn_share_quan")
	{
		int  type =btn->getTag();
		if (type == 0)
		{
			std::string jinping=Tools::getChineseByKey("jinping");
			std::string jinpingmajiang=Tools::getChineseByKey("menushare");
			String *jinpinginveiteadd=String::createWithFormat(jinpingmajiang.c_str(),GamerData::getInstance()->getMyInviteCode().c_str());
			MissionWeiXin::getinstance()->shareUrlWeiXin("http://d.laiyagame.com/jinping/download.html",jinpinginveiteadd->getCString(),jinpinginveiteadd->getCString(),1);
		}
		else if(type == 1)
		{
			int flag = 1;
			SEND_CUSTOM_MSG("WeiXinShareInGame",&flag);
		}
		else if(type==2)
		{
			this->setVisible(false);
			int flag = 1;
			MissionWeiXin::getinstance()->cutscreen(flag);
			this->removeFromParent();
		}
	}	
	else{

	}
}

Layer* LobbyView::genTableViewIndex(int cellNum)
{
	//LayerColor* bg = LayerColor::create(Color4B(125,0,0,125));
	Layer* bg = Layer::create();
	string path_spot_bright = GameRes::spot_bright;
	string path_spot_dark = GameRes::spot_dark;
	double total_width = 0,height = 0,spaceX = 20;
	for (int i=0;i<cellNum;i++)
	{
		Sprite* sprite_spot_dark = Sprite::create(path_spot_dark);
		Sprite* sprite_spot_bright = Sprite::create(path_spot_bright);
		sprite_spot_dark->setName("sprite_spot_dark_"+StringUtils::format("%d",i+1));
		sprite_spot_bright->setName("sprite_spot_bright");
		sprite_spot_bright->setPosition(sprite_spot_dark->getContentSize().width*0.5,sprite_spot_dark->getContentSize().height*0.5);
		sprite_spot_bright->setVisible(false);
		sprite_spot_dark->addChild(sprite_spot_bright);
		sprite_spot_dark->setAnchorPoint(Vec2(0.5,0.5));
		total_width += spaceX*0.5;
		sprite_spot_dark->setPosition(total_width+sprite_spot_dark->getContentSize().width*0.5,sprite_spot_dark->getContentSize().height*0.5);
		bg->addChild(sprite_spot_dark);
		total_width = total_width + sprite_spot_dark->getContentSize().width+spaceX*0.5;
		height = sprite_spot_dark->getContentSize().height;
	}
	bg->setAnchorPoint(Vec2(0.5,0.5));
	bg->setContentSize(Size(total_width,height));
	bg->setName("cell_index_bg");
	return bg;
}
void LobbyView::showUIActivity()
{
	string pathCsb = "res/loading/lobbyCsd/LayerActivity.csb";
	Node* root = LoadCsb(pathCsb);
	pv_ad = (PageViewEx*) root->getChildByName("pageView_ad");
	Size size = pv_ad->getContentSize();
	int activityNum = LobbyData::getInstance()->getIntegerForKey(GameConst::key_activity_num,0);
	std::string pathBase = CCFileUtils::sharedFileUtils()->getWritablePath()+GameConst::key_activity_id_;
	for (int i = 0; i < activityNum; i++) {
		Layout* layout1 = Layout::create();
		layout1->setSize(Size(size.width, size.height));
		string path = StringUtils::format("%s%d.png",pathBase.c_str(),i+1);
		ImageView* imageView = ImageView::create(path);
		imageView->setScale9Enabled(true);
		imageView->setPosition(Point(layout1->getSize().width / 2, layout1->getSize().height / 2));
		imageView->setScaleX(size.width/imageView->getContentSize().width);
		imageView->setScaleY(size.height/imageView->getContentSize().height);
		layout1->addChild(imageView);		
		pv_ad->addPage(layout1);
	}
	Layer* cell_bg = genTableViewIndex(activityNum);
	cell_bg->setPosition(root->getContentSize().width*0.5-cell_bg->getContentSize().width*0.5,25);
	root->addChild(cell_bg);
	if (activityNum > 0)
	{
		cell_bg->getChildByName("sprite_spot_dark_1")->getChildByName("sprite_spot_bright")->setVisible(true);	
		pv_ad->scrollToPage(0);
	}
    pv_ad->setCustomScrollThreshold(100);
    pv_ad->setTouchEnabled(true);
    pv_ad->setPageCount(activityNum);
    int count = pv_ad->getPageCount();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	pv_ad->addEventListener_pageView(CC_CALLBACK_2(LobbyView::pageViewEvent2, this));
#else
	pv_ad->addEventListenerPageView(this, pagevieweventselector(LobbyView::pageViewEvent));
#endif

	pv_ad->addTouchEventListener(CC_CALLBACK_2(LobbyView::TouchEventHandler,this));
	isPauseScroll = false;
	unschedule(schedule_selector(LobbyView::pageViewAutoScroll));
	schedule(schedule_selector(LobbyView::pageViewAutoScroll),5);
}
void LobbyView::pageViewEvent(cocos2d::Ref *pSender, PageViewEventType type)
{
	switch (type) {
	case cocos2d::ui::PAGEVIEW_EVENT_TURNING:
		{
			changeIndicator();
		}
		break;
	default:
		break;
	}
}

void LobbyView::pageViewEvent2(cocos2d::Ref* sender, cocos2d::ui::PageView::EventType type)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	switch (type) {
	case PageView::EventType::TURNING:
		{
			changeIndicator();
		}
		break;

	default:
		break;
	}
#endif
}
void LobbyView::showUIBinding()
{
	string pathCsb = "res/loading/lobbyCsd/LayerBinding.csb";
	//Node* root = LoadCsb(pathCsb);
	Node* csb = CSLoader::createNode(pathCsb);
	csb->setName("Layer_showUIBinding");
	this->addChild(csb);
	Node* root = csb->getChildByName("layer_bg");
	Button* btnExit = (Button*)root->getChildByName("btn_exit");
	if (btnExit)
	{
		btnExit->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	}
	
	string code = LobbyData::getInstance()->getStringForKey(GameConst::key_RefereeCode,"");
	string promoterId = LobbyData::getInstance()->getStringForKey(GameConst::key_myPromoterID,"");

	((TextField*)root->getChildByName("TextField_Code"))->setString(code);
	if (code != ""){
		((Button*)root->getChildByName("btn_binding_code"))->setEnabled(false);
		((TextField*)root->getChildByName("TextField_Code"))->setEnabled(false);
	}else{
		((TextField*)root->getChildByName("TextField_Code"))->setFocused(true);
	}
	
	((TextField*)root->getChildByName("TextField_Person"))->setString(promoterId);
	if (promoterId != ""){
		((Button*)root->getChildByName("btn_binding_person"))->setEnabled(false);
		((TextField*)root->getChildByName("TextField_Person"))->setEnabled(false);
	}

	((Button*)root->getChildByName("btn_binding_code"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	((Button*)root->getChildByName("btn_binding_person"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));

	//auto dispatcher = Director::getInstance()->getEventDispatcher();
	//dispatcher->addCustomEventListener(CustomEvent::key_update_ui_bind,CC_CALLBACK_1(LobbyView::updateUIBinding,this));
}
void LobbyView::showUIFeedback()
{
	string pathCsb = "res/loading/lobbyCsd/LayerFeedback.csb";
	Node* root = LoadCsb(pathCsb);
	Text* txt = (Text*)root->getChildByName("txt_wxCode");
	string wx = LobbyData::getInstance()->getStringForKey(GameConst::key_wx_base_feedback,"");
	txt->setString(wx);
	((Button*)root->getChildByName("btn_copy"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
}
void LobbyView::showUISelfInfo()
{
	string pathCsb = "res/loading/lobbyCsd/LayerSelfInfo.csb";
	Node* root = LoadCsb(pathCsb);

}

void LobbyView::showUIMessage(vector<MessageInfo*> vectorMsg)
{
	string pathCsb = "res/loading/lobbyCsd/LayerMessage.csb";
	Node* root = LoadCsb(pathCsb);
	ListView* listView_msg = (ListView*)root->getChildByName("listView_msg");
	string msg = "恭喜你，好友绑定成功，系统赠送你3张房卡！恭喜你，好友绑定成功，系统赠送你3张房卡！恭喜你，好友绑定成功，系统赠送你3张房卡！",timeDate = "2017.3.5",title = "奖励";

	//for (int i=0;i<10;i++)
	for (int i=0;i<vectorMsg.size();i++)
	{
		auto cell = CellItemMsg::create();
		cell->setData(vectorMsg[i]->id,vectorMsg[i]->createTime,vectorMsg[i]->content,vectorMsg[i]->title);

		Layout* default_item = Layout::create();
		default_item->setTouchEnabled(true);  
		default_item->setSize(Size(950,150)); 
		default_item->addChild(cell);  
		listView_msg->pushBackCustomItem(default_item);
	}
}
void LobbyView::showUIMessage(vector<MessageInfo> vectorMsg)
{
	string pathCsb = "res/loading/lobbyCsd/LayerMessage.csb";
	Node* root = LoadCsb(pathCsb);
	ListView* listView_msg = (ListView*)root->getChildByName("listView_msg");
	string msg = "恭喜你，好友绑定成功，系统赠送你3张房卡！恭喜你，好友绑定成功，系统赠送你3张房卡！恭喜你，好友绑定成功，系统赠送你3张房卡！",timeDate = "2017.3.5",title = "奖励";

	//for (int i=0;i<10;i++)
	for (int i=0;i<vectorMsg.size();i++)
	{
		auto cell = CellItemMsg::create();
		cell->setData(vectorMsg[i].id,vectorMsg[i].createTime,vectorMsg[i].content,vectorMsg[i].title);

		Layout* default_item = Layout::create();
		default_item->setTouchEnabled(true);  
		default_item->setSize(Size(950,150)); 
		default_item->addChild(cell);  
		listView_msg->pushBackCustomItem(default_item);
	}
}
void LobbyView::showUIRecord()
{
	string pathCsb = "res/loading/lobbyCsd/LayerRecord.csb";
	Node* root = LoadCsb(pathCsb);	
	ListView* listView_record = (ListView*)root->getChildByName("listView_record");

	string roomCode = "123456",timeDate = "2017.3.5",playNameScore="张明：50";
	for (int i=0;i<10;i++)
	{
		auto cell = CellItemRecord::create();
		cell->setData(roomCode,timeDate,playNameScore,playNameScore,playNameScore,playNameScore,i);

		Layout* default_item = Layout::create();
		default_item->setTouchEnabled(true);  
		default_item->setSize(Size(950,150)); 
		default_item->addChild(cell);  
		listView_record->pushBackCustomItem(default_item);
	}
}
void LobbyView::showUIRule()
{
	string pathCsb = "res/loading/lobbyCsd/LayerRule.csb";
	Node* root = LoadCsb(pathCsb);
}
void LobbyView::showUISetting(bool isIngame)
{
	string pathCsb = "res/loading/lobbyCsd/LayerSetting.csb";
	Node* root = LoadCsb(pathCsb);
	checkbox_native = (CheckBox*)root->getChildByName("checkbox_native");
	checkbox_native->addEventListenerCheckBox(this,checkboxselectedeventselector(LobbyView::checkBoxEvent));
	//checkbox_native->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));

	checkbox_general = (CheckBox*)root->getChildByName("checkbox_general");
	//checkbox_general->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	checkbox_general->addEventListenerCheckBox(this,checkboxselectedeventselector(LobbyView::checkBoxEvent));
	if (isIngame)
	{		
		root->getChildByName("btn_logout")->setVisible(false);

		if(GamerData::getInstance()->getStatus()>=2)
		{
			Button *bt_backlobby=(Button *)root->getChildByName("btn_backLobby");
			Button *btn_logout=(Button *)root->getChildByName("btnDismissRoom");
			bt_backlobby->loadTextures(GameRes::btn_jsfj,GameRes::btn_jsfj_down);
			btn_logout->loadTextures(GameRes::btn_jsfj,GameRes::btn_jsfj_down);
		}
			if (GamerData::getInstance()->getUId() == MjData::getInstance()->getbanker())
			{
				((Button*)root->getChildByName("btnDismissRoom"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
				root->getChildByName("btn_backLobby")->setVisible(false);
				root->getChildByName("btn_logout")->setVisible(false);
			} 
			else
			{
				((Button*)root->getChildByName("btn_backLobby"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
				root->getChildByName("btnDismissRoom")->setVisible(false);
				root->getChildByName("btn_logout")->setVisible(false);
			}
		
	}else{
		((Button*)root->getChildByName("btn_logout"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
		root->getChildByName("btnDismissRoom")->setVisible(false);
		root->getChildByName("btn_backLobby")->setVisible(false);
	}

	if (Tools::getLanguage() == 1)	{
		checkbox_native->setSelected(true);
		checkbox_general->setSelected(false);
	}else{
		checkbox_native->setSelected(false);
		checkbox_general->setSelected(true);
	}
	((Slider*)root->getChildByName("slider_bg_music"))->addEventListener(CC_CALLBACK_2(LobbyView::sliderEvent,this));
	((Slider*)root->getChildByName("slider_bg_music"))->setPercent(Tools::getMusicVolume()*100);
	((Slider*)root->getChildByName("slider_soundEffect"))->addEventListener(CC_CALLBACK_2(LobbyView::sliderEvent,this));
	((Slider*)root->getChildByName("slider_soundEffect"))->setPercent(Tools::getEffectVolume()*100);
	
	Text* txt = (Text*)root->getChildByName("txt_native");
	txt->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	txt->setTouchEnabled(true);

	Text* txt_general = (Text*)root->getChildByName("txt_general");
	txt_general->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	txt_general->setTouchEnabled(true);

	Text* txt_version = (Text*)root->getChildByName("txt_version");
	txt_version->setString(JniFun::getVersion());
}
void LobbyView::showUIShare()
{
	string pathCsb = "res/loading/lobbyCsd/LayerShare.csb";
	Node* root = LoadCsb(pathCsb);
	//((Button*)root->getChildByName("bg_dark2")->getChildByName("btn_share"))->setVisible(false);
	((Button*)root->getChildByName("bg_dark2")->getChildByName("btn_share"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));

}
void LobbyView::showUILogoutTip(bool WXLogout)
{
	string pathCsb = "res/loading/lobbyCsd/LayerTip.csb";
	Node* root = LoadCsb(pathCsb);
	
	((Button*)root->getChildByName("btn_cancle_logout"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	Button* btn = ((Button*)root->getChildByName("btn_ok_logout"));
	btn->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	if (WXLogout)
	{
		btn->setTag(4455);
	}
	else
	{
		btn->setTag(44556);
	}
}

void LobbyView:: showUIAddCard()
{
	string strValue1 = StringUtils::format("%d",1);
	string strValue2 = StringUtils::format("%d",2);
	// LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_service_+strValue1,"laiyaGame1");
	// LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_service_+strValue2,"laiyaGame1");

	// LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_agent_+strValue1,"jiameng1");
	// LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_agent_+strValue2,"jiameng2");

	// LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_buy_+strValue1,"buy1");
	// LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_buy_+strValue2,"buy2");

	string pathCsb = "res/loading/lobbyCsd/LayerAddCard.csb";
	Node* root = LoadCsb(pathCsb);

	Text* txt = (Text*)root->getChildByName("txt_service1");
	string temp = "";
	temp = LobbyData::getInstance()->getStringForKey(GameConst::key_wx_base_service_+strValue1,"");
	txt->setString(temp);
	temp = LobbyData::getInstance()->getStringForKey(GameConst::key_wx_base_service_+strValue2,"");
	txt = (Text*)root->getChildByName("txt_service2");
	if (temp == "")
	{
		txt->setVisible(false);
		root->getChildByName("btn_copy_service2")->setVisible(false);
	}
	else
	{
		txt->setString(temp);
	}

	txt = (Text*)root->getChildByName("txt_agent1");
	temp = LobbyData::getInstance()->getStringForKey(GameConst::key_wx_base_agent_+strValue1,"");
	txt->setString(temp);
	temp = LobbyData::getInstance()->getStringForKey(GameConst::key_wx_base_agent_+strValue2,"");
	txt = (Text*)root->getChildByName("txt_agent2");
	if (temp == "")
	{
		txt->setVisible(false);
		root->getChildByName("btn_copy_agent2")->setVisible(false);
	}
	else
	{
		txt->setString(temp);
	}

	txt = (Text*)root->getChildByName("txt_buy1");
	temp = LobbyData::getInstance()->getStringForKey(GameConst::key_wx_base_buy_+strValue1,"");
	txt->setString(temp);
	temp = LobbyData::getInstance()->getStringForKey(GameConst::key_wx_base_buy_+strValue2,"");
	txt = (Text*)root->getChildByName("txt_buy2");
	if (temp == "")
	{
		txt->setVisible(false);
		root->getChildByName("btn_copy_buy2")->setVisible(false);
	}
	else
	{
		txt->setString(temp);
	}

	((Button*)root->getChildByName("btn_copy_service1"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	((Button*)root->getChildByName("btn_copy_service2"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	((Button*)root->getChildByName("btn_copy_agent1"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	((Button*)root->getChildByName("btn_copy_agent2"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	((Button*)root->getChildByName("btn_copy_buy1"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	((Button*)root->getChildByName("btn_copy_buy2"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
}
void LobbyView:: showUICreateRoom()
{
	this->setName("enterroom");
	string pathCsb = "res/loading/lobbyCsd/LayerCreateRoom.csb";
	Node* root = LoadCsb(pathCsb);

	checkbox_ju_4 = (CheckBox*)root->getChildByName("checkbox_ju_4");
	checkbox_ju_4->addEventListenerCheckBox(this,checkboxselectedeventselector(LobbyView::checkBoxEvent));
	checkbox_ju_8 = (CheckBox*)root->getChildByName("checkbox_ju_8");
	checkbox_ju_8->addEventListenerCheckBox(this,checkboxselectedeventselector(LobbyView::checkBoxEvent));
	checkbox_gang_men = (CheckBox*)root->getChildByName("checkbox_gang_men");
	checkbox_gang_men->addEventListenerCheckBox(this,checkboxselectedeventselector(LobbyView::checkBoxEvent));
	checkbox_gang_zhuangwan = (CheckBox*)root->getChildByName("checkbox_gang_zhuangwan");
	checkbox_gang_zhuangwan->addEventListenerCheckBox(this,checkboxselectedeventselector(LobbyView::checkBoxEvent));
	((Button*)root->getChildByName("btn_createRoom"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));

	((ImageView*)root->getChildByName("img_click_4ju"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	((ImageView*)root->getChildByName("img_click_8ju"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	((ImageView*)root->getChildByName("img_click_meng"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	((ImageView*)root->getChildByName("img_click_zi"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	
	MjData::getInstance()->setjushu(4);
	MjData::getInstance()->setIsgang_men(1);
	MjData::getInstance()->setpalyrule(1);
	for (int i=0;i<5;i++)
	{
		checkbox_select_game[i] = (CheckBox*)root->getChildByName("bg_ck")->getChildByName(StringUtils::format("ck_game_%d",i));
		checkbox_select_game[i]->addEventListenerCheckBox(this,checkboxselectedeventselector(LobbyView::checkBoxEvent));
	}
	checkbox_select_game[0]->setSelected(true);
	checkbox_select_game[0]->setEnabled(false);



	if(MjData::getInstance()->getisinapple()==1)
	{
		
		ImageView *sp_si=(ImageView *)root->getChildByName("img_4ju");
		sp_si->setVisible(false);
		ImageView *sp_ba=(ImageView *)root->getChildByName("img_8ju");
		sp_ba->setVisible(false);

		Text *tx_si=(Text *)root->getChildByName("txt_4ju_two");
		tx_si->setVisible(false);
		Text *tx_b=(Text *)root->getChildByName("txt_8ju_three");
		tx_b->setVisible(false);

		Text *tx_1=(Text *)root->getChildByName("Text_1");
		tx_1->setVisible(false);

		Text *tx_1_0=(Text *)root->getChildByName("Text_1_0");
		tx_1_0->setVisible(false);
	}
}
void LobbyView:: showUIJoinRoom()
{
	this->setName("showUIJoinRoom");
	string pathCsb = "res/loading/lobbyCsd/LayerJoinRoom.csb";
	Node* root = LoadCsb(pathCsb);
	for (int i=1;i<7;i++)
	{
		((TextAtlas*)root->getChildByName(StringUtils::format("txtNum_%d",i)))->setString("");
	}
	for (int i=0;i<10;i++)
	{		
		((Button*)root->getChildByName(StringUtils::format("btn_num_%d",i)))->addClickEventListener(CC_CALLBACK_1(LobbyView::joinRoomBtnHandle,this));
    }
	((Button*)root->getChildByName("btn_rewrite"))->addClickEventListener(CC_CALLBACK_1(LobbyView::joinRoomBtnHandle,this));
	((Button*)root->getChildByName("btn_del"))->addClickEventListener(CC_CALLBACK_1(LobbyView::joinRoomBtnHandle,this));

}
void LobbyView::joinRoomBtnHandle(Ref* sender)
{
	Button* btn = (Button*)sender;
	string btnName = btn->getName();
	Node* nodeParent = btn->getParent();
	String num = Helper::getSubStringOfUTF8String(btnName,btnName.length()-1,1);
	
	
	if (btnName == "btn_del"){
		if (joinRoomCode.size() > 0){
			((TextAtlas*)nodeParent->getChildByName(StringUtils::format("txtNum_%d",joinRoomCode.size())))->setString("");
			joinRoomCode.pop_back();
		}
	}else if (btnName == "btn_rewrite"){
		if (joinRoomCode.size() > 0)
		{
			for (int i=0;i<joinRoomCode.size();i++)
			{
				((TextAtlas*)nodeParent->getChildByName(StringUtils::format("txtNum_%d",i+1)))->setString("");
			}
			joinRoomCode.clear();
		}
	}else{
		if (joinRoomCode.size() < ROOM_CODE_MAX_LEN)
		{			
			joinRoomCode.push_back(num.intValue());
			((TextAtlas*)nodeParent->getChildByName(StringUtils::format("txtNum_%d",joinRoomCode.size())))->setString(num.getCString());
			if (joinRoomCode.size() == ROOM_CODE_MAX_LEN)
			{
				GameMenu *g=(GameMenu *)this->getParent();
				char s_room[10]={0};
				sprintf(s_room,"%d%d%d%d%d%d",joinRoomCode[0],joinRoomCode[1],joinRoomCode[2],joinRoomCode[3],joinRoomCode[4],joinRoomCode[5]);
				g->enterroom(s_room);
			}

		}
	}
}

void LobbyView::showUIBindConfirm(string name,string id)
{
	string pathCsb = "res/loading/lobbyCsd/LayerBindConfirm.csb";
	Node* root = LoadCsb(pathCsb);
	Text* txt_name = (Text*)root->getChildByName("txt_name");
	txt_name->setString(name);

	Text* txt_ID = (Text*)root->getChildByName("txt_ID");
	txt_ID->setString(id);

	((Button*)root->getChildByName("btn_confirm_banding"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	((Button*)root->getChildByName("btn_exit"))->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	nodeUIBindConfirm = root;
}

void LobbyView::pageViewAutoScroll(float time)
{
	if (isPauseScroll == false)
	{
		int index = pv_ad->getScrollToIndex();
		log("---------LobbyView::pageViewAutoScroll-------%f--index========%d",time,index);
		if (index != -1)
		{
			pv_ad->scrollToPage(index);
		}
	}
}

void LobbyView::setCKSelectedFlag()
{
	if(checkbox_native->getSelectedState())
	{
		checkbox_native->setSelected(false);
		checkbox_general->setSelected(true);
		Tools::setLanguage(2);
	}
	else
	{
		checkbox_native->setSelected(true);
		checkbox_general->setSelected(false);
		Tools::setLanguage(1);
	}
}

void LobbyView::setCreateViewSelectedFlag(int type)//1:局数，2:玩法
{
	if (type == 1)
	{
		if (checkbox_ju_4->getSelectedState())
		{
			checkbox_ju_4->setSelected(false);
			checkbox_ju_8->setSelected(true);
			MjData::getInstance()->setjushu(8);
		}
		else
		{
			checkbox_ju_4->setSelected(true);
			checkbox_ju_8->setSelected(false);
			MjData::getInstance()->setjushu(4);
		}
	} 
	else
	{
		if (checkbox_gang_men->getSelectedState())
		{
			checkbox_gang_men->setSelected(false);
			checkbox_gang_zhuangwan->setSelected(true);

			MjData::getInstance()->setIsgang_men(0);
			MjData::getInstance()->setIsgang_zhuangwan(1);
		}
		else
		{
			checkbox_gang_men->setSelected(true);
			checkbox_gang_zhuangwan->setSelected(false);

			MjData::getInstance()->setIsgang_men(1);
			MjData::getInstance()->setIsgang_zhuangwan(0);
		}
	}
}
void LobbyView::update(float dt)
{
	//log("----LobbyView-------update");
}

void LobbyView::updateUIBinding(EventCustom* evt)
{
	log("---------updateUIBinding-----------");
	//return;


	char* type = (char*)evt->getUserData();
	Node* Layer_showUIBinding = this->getChildByName("Layer_showUIBinding");
	if (Layer_showUIBinding)
	{
		Node* temp = Layer_showUIBinding->getChildByName("layer_bg");
		if (temp)
		{
			if (type == "1")
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
	//Scene *s = Director::getInstance()->getRunningScene();
	//Node* node = s->getChildByName("showUIBindConfirm");
	//if (node)
	//{
	//	node->removeFromParent();
	//}	
}

bool LobbyView::checkInputNumber(string inputString)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	std::regex pattern("^\d{6}$)");
	if ( !std::regex_match( inputString, pattern ) )
	{
		return false;
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	char ss[100] = {};
	sprintf(ss,"%s",inputString.c_str());
	regmatch_t pmatch[4];
	regex_t match_regex;

	regcomp( &match_regex,
		"(^\d{6}$)",
		REG_EXTENDED );
	if ( regexec( &match_regex, ss, 4, pmatch, 0 ) != 0 )
	{
		return false;
	}
	regfree( &match_regex );
	#endif
	return true;
}

void LobbyView::changeIndicator()
{
	int activityNum = pv_ad->getPageCount();
	log("%d",(int)pv_ad->getCurPageIndex() + 1);
	int pageIndex = (int)pv_ad->getCurPageIndex() + 1;
	Node* parent = pv_ad->getParent();
	for (int i=0;i<activityNum;i++)
	{
		parent->getChildByName("cell_index_bg")->getChildByName(StringUtils::format("sprite_spot_dark_%d",(i+1)))->getChildByName("sprite_spot_bright")->setVisible(false);
	}
	if (activityNum > 0)
	{
		parent->getChildByName("cell_index_bg")->getChildByName(StringUtils::format("sprite_spot_dark_%d",pageIndex))->getChildByName("sprite_spot_bright")->setVisible(true);
	}
}

void LobbyView::TouchEventHandler(Ref* pRef, ui::Widget::TouchEventType touchType)
{ 
	if (touchType == ui::Widget::TouchEventType::BEGAN)
	{
		log("---------------------BEGAN-");
		isPauseScroll = true;
	}
	else if (touchType == ui::Widget::TouchEventType::MOVED)
	{
	}
	else if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		log("---------------------ENDED-");
		isPauseScroll = false;
	}
	else if (touchType == ui::Widget::TouchEventType::CANCELED)
	{
		log("---------------------CANCELED-");
	}
	else
	{
		log("---------------------defaut-");
	}
}


void LobbyView::showUIWeiXinShare(int type)
{
	string pathCsb = "res/loading/lobbyCsd/LayerWeiXinShare.csb";
	Node* root = LoadCsb(pathCsb);
	//root->setUserData(&type);
	Button *bt_quan=((Button*)root->getChildByName("btn_share_quan"));
	Button *bt_qun=((Button*)root->getChildByName("btn_share_qun"));
	bt_quan->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	bt_qun->addClickEventListener(CC_CALLBACK_1(LobbyView::btnHandle,this));
	bt_qun->setTag(type);
	bt_quan->setTag(type);
	this->setDelete(true);
}

void LobbyView::updateGameCheckBox(int selectedIndex)
{
	for (int i=0;i<5;i++)
	{
		checkbox_select_game[i]->setSelected(false);
		checkbox_select_game[i]->setEnabled(true);
	}
	checkbox_select_game[selectedIndex]->setSelected(true);
	checkbox_select_game[selectedIndex]->setEnabled(false);
	MjData::getInstance()->setpalyrule(selectedIndex+1);
}