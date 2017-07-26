#include "LobbyMain.h"
#include "LobbyView.h"

bool LobbyMain::init()
{
	if (!ParentInfo::init())
	{
		return false;
	}
	auto root_node = CSLoader::createNode("res/loading/lobbyCsd/LobbyMain.csb");
	this->addChild(root_node);

	auto node_btn = root_node->getChildByName("node_btn");
	auto node_center = root_node->getChildByName("node_center");
	auto node_bottom = root_node->getChildByName("node_bottom");

	Vector<Node*>& children = node_btn->getChildren();
	for (const auto& item : children)
	{
		static_cast<Button*>(item)->addTouchEventListener(CC_CALLBACK_2(LobbyMain::BtnHandler,this));
	}

	auto node_head = root_node->getChildByName("node_head");
	Text* txt_playerName =(Text*) node_head->getChildByName("sprite_name_bg")->getChildByName("txt_playerName");
	Text* txt_playerID =(Text*) node_head->getChildByName("sprite_name_bg")->getChildByName("txt_playerID");	 
	Text* txt_cardNum =(Text*)node_head->getChildByName("sprite_card_bg")->getChildByName("txt_cardNum");
	Button* btn = (Button*)node_head->getChildByName("sprite_card_bg")->getChildByName("btn_addCard");
	btn->addTouchEventListener(CC_CALLBACK_2(LobbyMain::BtnHandler,this));

	Sprite* sprite_head = (Sprite*)node_head->getChildByName("sprite_head");
	((Button*)node_head->getChildByName("btn_head"))->addTouchEventListener(CC_CALLBACK_2(LobbyMain::BtnHandler,this));
	Text* txt_notice =(Text*) root_node->getChildByName("sprite_notice")->getChildByName("txt_notice");

	return true;
}
void LobbyMain::onEnter()
{
	ParentInfo::onEnter();
}
void LobbyMain::onExit()
{
	ParentInfo::onExit();
}
void LobbyMain::BtnHandler(Ref* pRef, ui::Widget::TouchEventType touchType)
{
	if (touchType != ui::Widget::TouchEventType::ENDED)
	{
		return;
	}
	string btn_name = ((Button*)(pRef))->getName();
	CCLOG("---------------------------%s%s",btn_name.data(),"---------------------------");
	auto lobbyView = LobbyView::create();
	this->addChild(lobbyView);
	if (btn_name == "btn_binding"){
		lobbyView->showUIBinding();
	}else if (btn_name == "btn_rule"){
		lobbyView->showUIRule();
	}else if (btn_name == "btn_record"){
		lobbyView->showUIRecord();
	}else if (btn_name == "btn_activity"){
		lobbyView->showUIActivity();
	}else if (btn_name == "btn_feedback"){
		lobbyView->showUIFeedback();
	}else if (btn_name == "btn_share"){
		lobbyView->showUIShare();
	}else if (btn_name == "btn_msg"){
		//lobbyView->showUIMessage();
	}else if (btn_name == "btn_setting"){
		lobbyView->showUISetting(false);
	}else if (btn_name == "btn_createRoom"){
		lobbyView->showUICreateRoom();
	}else if (btn_name == "btn_joinRoom"){
		lobbyView->showUIJoinRoom();
	}else if (btn_name == "btn_head"){
		lobbyView->showUISelfInfo();
	}else if (btn_name == "btn_addCard")	{
		lobbyView->showUIAddCard();
	}else{
		CCLOG("-------LobbyMain-----click null");
	}
}