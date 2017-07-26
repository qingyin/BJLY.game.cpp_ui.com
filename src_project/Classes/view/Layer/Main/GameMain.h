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


	void gameMainStart(EventCustom* evt);		//游戏开始
	void gameMainStopHeart(EventCustom* evt);		//游戏开始
	void gameMainExit(EventCustom* evt);		//游戏退出
	void gameMainDismiss(EventCustom* evt);		//游戏退出
	void gameMainDismissNoDeduct(EventCustom* evt);		//游戏退出
	void gameMainStopSchedule(EventCustom* evt);		//游戏退出
	void login();

	void send_heart(float dt);
	void checkHeart(float dt);
	void stopjiance();
	void beginheart();
	void gameMainBeginHeart(EventCustom *evt);
	void gameMainJointableFailed(EventCustom *evt);
	void revNetOffline(EventCustom* evt);

	

	public:
	GameController* mj_controller;   //麻将控制层
	Playing_parent*		mj_player;		 //玩家层

	int loseNum;//记录发心跳不回的 次数

	

	

};
