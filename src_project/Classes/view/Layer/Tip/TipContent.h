/*
 *   ClassName   :   TipContent.h
 *   Description :    �û�ʹ��Э�����֪ͨ
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

	//��ʾ�û�Э��
	void showUIPlayAgreement();
	//��ʾ֪ͨ��Ϣ
	void showUINotice();
	//��ʾ����ս��
	void showUIAchievement(std::string res);
	//��ʾ����
	void showUIHelp();
	//��ʾ����
	void showUISet();
	//��ʾ������ս������
	void showUISet_ingame();
	//��ʾ�Ƿ�ͬ���ɢ����
	void showUIDismissAsk();

	//��ʾ�����ȡ
	void showUIFreeGold();
	//��ʾ�������
	void showUiNewPlayerGift();

	//��ʾ��������
	void showUICreateRoom();
	//��ʾ���뷿��
	void showUIEnterRoom();
	//��ʾ������Ϣ
	void showUIplayerInfoInGame(int viewid);
	void showUiBreakFromServer();//�ӷ������Ͽ�����
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

	//��ť�ص�����
	void ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType);
	void ButtonHandler_ingame(Ref* pRef, ui::Widget::TouchEventType touchType);
	void ButtonHandler_enterroom(Ref* pRef, ui::Widget::TouchEventType touchType);
	void ButtonHandler_list(Ref* pRef, ui::Widget::TouchEventType touchType);
	void ButtonHandler_list1(Ref* pRef, ui::Widget::TouchEventType touchType);
	//��ʱ����10���Զ��رյ�ǰ����
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

    //��ϵ��ʽ
    std::vector<Text*> text_Relation;   //����ǳ�

	int fanpaijicard;

};
#endif
