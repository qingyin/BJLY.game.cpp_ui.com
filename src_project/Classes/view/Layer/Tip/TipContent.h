/*
 *   ClassName   :   TipContent.h
 *   Description :    用户使用协议或者通知
 *   Author      :      
 *   Date        :	  12.21
*/
#ifndef   _TipContent_H_
#define   _TipContent_H_

#include "view/ParentInfo/ParentInfo.h"
class TipContent : public ParentInfo
{
public:
	virtual bool init();
	CREATE_FUNC(TipContent);

	//显示用户协议
	void showUIPlayAgreement();
	//显示通知信息
	void showUINotice();
	//显示个人战绩
	void showUIAchievement(std::string res);
	//显示攻略
	void showUIHelp();
	//显示设置
	void showUISet();
	//显示设置在战斗界面
	void showUISet_ingame();
	//显示是否同意解散房间
	void showUIDismissAsk();

	//显示免费领取
	void showUIFreeGold();
	//显示新手礼包
	void showUiNewPlayerGift();

	//显示创建房间
	void showUICreateRoom();
	//显示加入房间
	void showUIEnterRoom();
	//显示个人信息
	void showUIplayerInfoInGame(int viewid);
	void showUiBreakFromServer();//从服务器断开连接
	void showUiFanpaiji(int card_id);
    void createroom();
	void sp_settexture(Sprite *sp,std::string text_path);
	void showuiupdate(std::string url,bool isForceUpdate);
	void openurl(std::string url);

    void httpReqRelation();
    void httpResRelation(std::string res);

	void initlist1withdata(int roomid,int round);
    
    void selectedEvent(cocos2d::Ref *pSender, CheckBoxEventType type);

	void reqplay(int round);
	void resplay(std::string res);

	void restart2miao(float dt);
	void removeself__fanpai();

	void clickcanle();
private:

	//按钮回调函数
	void ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType);
	void ButtonHandler_ingame(Ref* pRef, ui::Widget::TouchEventType touchType);
	void ButtonHandler_enterroom(Ref* pRef, ui::Widget::TouchEventType touchType);
	void ButtonHandler_list(Ref* pRef, ui::Widget::TouchEventType touchType);
	void ButtonHandler_list1(Ref* pRef, ui::Widget::TouchEventType touchType);
	//定时器：10秒自动关闭当前界面
	void closeUI(float ft);

    void slider_callback_music(Ref *pSender, ui::Slider::EventType type);
    void slider_callback_effect(Ref *pSender, ui::Slider::EventType type);

public:
    CheckBox *c_jushu_4;
    CheckBox *c_jushu_8;
	std::vector<Text *>tx_enterroom;
	std::vector<Button *>bt_enterroom;
	std::vector<int >room_id;
	int enterroom_tx_num;
	ListView *list;
	ListView *list1;
	std::vector<int>arr_roomid;
	std::vector<int>arr_round;
	std::vector<int >arr_playrule;
	int right_roomid;

    //联系方式
    std::vector<Text*> text_Relation;   //玩家昵称

	int fanpaijicard;

};
#endif
