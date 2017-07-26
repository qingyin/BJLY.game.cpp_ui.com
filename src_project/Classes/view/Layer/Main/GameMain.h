#pragma once

#include "view/ParentInfo/ParentInfo.h"
#include "MjNode.h"
#include "GameController.h"
#include "Playing_Laiya.h"
#include  "tool/Tools.h"
#include "view/Layer/Main/Playing_parent.h"
class GameMain : public ParentInfo
{
public:
	void onEnter();
	void onExit();
	virtual bool init();
	CREATE_FUNC(GameMain);


	void gameMainStart(EventCustom* evt);		//��Ϸ��ʼ
	void gameMainStopHeart(EventCustom* evt);		//��Ϸ��ʼ
	void gameMainExit(EventCustom* evt);		//��Ϸ�˳�
	void gameMainDismiss(EventCustom* evt);		//��Ϸ�˳�
	void gameMainDismissNoDeduct(EventCustom* evt);		//��Ϸ�˳�
	void gameMainStopSchedule(EventCustom* evt);		//��Ϸ�˳�
	void login();

	void send_heart(float dt);
	void checkHeart(float dt);
	void stopjiance();
	void beginheart();
	void gameMainBeginHeart(EventCustom *evt);
	void gameMainJointableFailed(EventCustom *evt);
	void revNetOffline(EventCustom* evt);

	

	public:
	GameController* mj_controller;   //�齫���Ʋ�
	Playing_parent*		mj_player;		 //��Ҳ�

	int loseNum;//��¼���������ص� ����

	

	

};
