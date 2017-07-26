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

	//游戏开始
	void startGame_gameController(int left_card_cnt, int left_round_cnt);
	void setLeftCardCnt(int left_card_cnt);

public:
	//UI加载并且显示
	void uiLoadAndShow();
	//按钮回调函数
	void ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType);
	//游戏开始
	void gameMainStart(EventCustom* evt);
	void setArrowRoatation(int bankerViewId);
	//修改箭头指向方位根据玩家[0:当前玩家;1:下家;2:对门;3:上家]
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
	Node* nodeWait;  //邀请好友,解散房间等
	Node* nodeGame;	  //游戏中
	TextAtlas* numTime_game; //游戏中倒计时计数
	Text* numCards_game;//游戏中剩余的麻将数
	Text* numJuShu_game;//游戏中剩余的局数
	Sprite* Arrow;		//箭头(指向当前出牌)
	std::vector<Sprite *>arr_arrows;//箭头数组
	Node *n_luyinanimate;
	std::string luyin_path;
	ImageView *bgtime;
	Node *nodeBottom;

	Sprite *bg_rule;
	Button *bt_go;
	Node *node_system;
	

};
