#pragma once

#include "view/ParentInfo/ParentInfo.h"
#include "network/HttpClient.h"
class GameMenu : public ParentInfo
{
public:
    virtual bool init();
	void onEnter();
	void onExit();
    void initwithuserinfo(std::string url ,std::string name,std::string openid);
    void onGetFinished(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void end(float dt);
    void httpReqLaba();
    void httpReqHealthyNotice();
    void httpResLaba(std::string res);
    void httpResHealthyNotice(std::string res);
    
    void createroom();
    void createroomresponse(std::string res);
    
    void enterroom(std::string roomid);
    void enterroomresponse(std::string res);
    void updateHeadInfo();//更新
	void addgamemain(EventCustom *evt);
	void delay_addmain(float dt);
	void refreshjoinroom();

	void requestshengpingfu(int uid);
	void responseshengpingfu(std::string res);


	void delayshare(EventCustom *evt);
	void delaysherebyschedule(float dt);

	void requestaddstone();
	void responseaddstone(std::string res);

    void labaSchedule(float a);
    //void update(float a);
	void reqzjlb();
	void reszjlb(std::string res);

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	//录音回调
	void endluyin(float dt);
	
	CREATE_FUNC(GameMenu);

	void showUIActivity(EventCustom *evt);
	void showUIMessage(EventCustom *evt);
	void showUIBindConfirm(EventCustom *evt);
	void updateUIBindConfirm(EventCustom *evt);
	void showLaba(EventCustom *evt);
	void updateSelfInfo(EventCustom *evt);

	void refreshAchivement();
	void setsanding();
	void setsandingliangfang();
	void updatehead(EventCustom *evt);
	void requestHeadInfo(EventCustom *evt);
private:
	//ui加载并且显示
	void uiLoadAndShow();
	//按钮回调函数
	void ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType);

	void setVisibleLoadingLayer(EventCustom* evt);
	void setVisibleLoadingLayer2(float time);
	void showGameMain(EventCustom* evt);
	void showLowNet(EventCustom* evt);

private:
	Text* goldNum;    //钻石数量显示
	Text* nickName;   //玩家昵称
	Text* UserId;	  //玩家ID
	Sprite* sprite_headImg;
	Button* btnJoinRoom; //加入房间
	Button* btnBackRoom; //返回房间
	Button*btnCreateRoom;
	Text* text_notice;   //玩家昵称
    Layout* panel_notice;

	Sprite *sp_createroom;
	Sprite *sp_returnroom;

    //健康公告
	Text* text_noticeHealthy[5];   //玩家昵称
};
