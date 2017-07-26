#pragma once

#include "view/ParentInfo/ParentInfo.h"
#include "tool/Tools.h"
class GameController : public ParentInfo
{
public:
	void onEnter();
	void onExit();
	virtual bool init();
	CREATE_FUNC(GameController);

	//��Ϸ��ʼ
	void startGame_gameController(int left_card_cnt, int left_round_cnt);
	void setLeftCardCnt(int left_card_cnt);

public:
	//UI���ز�����ʾ
	void uiLoadAndShow();
	//��ť�ص�����
	void ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType);
	//��Ϸ��ʼ
	void gameMainStart(EventCustom* evt);
	void setArrowRoatation(int bankerViewId);
	//�޸ļ�ͷָ��λ�������[0:��ǰ���;1:�¼�;2:����;3:�ϼ�]
	void setArrowDirection(int index);
	void update(float dt);
	void arrowvisible(bool isvisible);

	void playluyin(float dt);

	void begintimehjisshiqi(float dt);
	void begintimehjisshiqiQuake(float dt);

	 void onresult(EventCustom* evt);
	 void stopQuake(EventCustom* evt);


	 void showLuxiangController();

	 void refreshjushu();

	 void shouhuibgrule();

	 void refreshberrty(float dt);
	 void WeiXinShareInGame(EventCustom* evt);
private:
	Node* nodeWait;  //�������,��ɢ�����
	Node* nodeGame;	  //��Ϸ��
	TextAtlas* numTime_game; //��Ϸ�е���ʱ����
	Text* numCards_game;//��Ϸ��ʣ����齫��
	Text* numJuShu_game;//��Ϸ��ʣ��ľ���
	Sprite* Arrow;		//��ͷ(ָ��ǰ����)
	std::vector<Sprite *>arr_arrows;//��ͷ����
	Node *n_luyinanimate;
	std::string luyin_path;
	ImageView *bgtime;
	Node *nodeBottom;

	Sprite *bg_rule;
	Button *bt_go;
	Node *node_system;
	

};
