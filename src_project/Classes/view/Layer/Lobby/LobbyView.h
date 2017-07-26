#pragma once

#include "view/ParentInfo/ParentInfo.h"
#include "view/Layer/Lobby/PageViewEx.h"
#include "adapter/LobbyAdapter.h"

class LobbyView : public ParentInfo
{
public:
	virtual bool init(); 
	CREATE_FUNC(LobbyView);
	
	void onEnter();
	void onExit();

	void showUIActivity();
	void showUIBinding();
	void updateUIBinding(EventCustom* evt);
	void deleteself(EventCustom* evt);
	void showUIFeedback();
	void showUISelfInfo();
	void showUIMessage(vector<MessageInfo> vectorMsg);
	void showUIMessage(vector<MessageInfo*> vectorMsg);
	void showUIRecord();
	void showUIRule();
	void showUISetting(bool isIngame);
	void showUIShare();
	void showUIAddCard();
	void showUICreateRoom();
	void showUIJoinRoom();
	void showUILogoutTip(bool WXLogout);
	void showUIBindConfirm(string name,string id);
	void showUIBindConfirm();
	void showUIWeiXinShare(int type);
	virtual void update(float dt);
private:	
	bool checkInputNumber(string inputString);
	void setCKSelectedFlag();
	void setCreateViewSelectedFlag(int type);//1:¾ÖÊý£¬2:Íæ·¨
	void pageViewAutoScroll(float time);
	Layer* genTableViewIndex(int cellNum);
	void btnHandle(Ref* sender);
	void joinRoomBtnHandle(Ref* sender);
	void checkBoxEvent(cocos2d::Ref *pSender, CheckBoxEventType type);
	void sliderEvent(cocos2d::Ref* pSender,ui::Slider::EventType type);
	void pageViewEvent(cocos2d::Ref *pSender, PageViewEventType type);    
	void pageViewEvent2(cocos2d::Ref* sender, cocos2d::ui::PageView::EventType type);
	
	void TouchEventHandler(Ref* pRef, ui::Widget::TouchEventType touchType);
	Node* LoadCsb(string pathCsb);
	CheckBox* checkbox_native;
	CheckBox* checkbox_general;

	CheckBox* checkbox_ju_4;
	CheckBox* checkbox_ju_8;
	CheckBox* checkbox_gang_men;
	CheckBox* checkbox_gang_zhuangwan;

	CheckBox* checkbox_select_game[5];

	std::vector<int> joinRoomCode;
	PageViewEx* pv_ad;

	Node* nodeUIBindConfirm;
	void changeIndicator();
	void updateGameCheckBox(int selectedIndex);
	bool isPauseScroll;
#define ROOM_CODE_MAX_LEN 6
};

