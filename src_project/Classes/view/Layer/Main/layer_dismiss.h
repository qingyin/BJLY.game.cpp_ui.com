#ifndef LAYER_DISMISS_H
#define LAYER_DISMISS_H
#include "view/ParentInfo/ParentInfo.h"
class layer_dismiss:public ParentInfo
{
public:
	virtual bool init();
	void onEnter();
	void onExit();
	CREATE_FUNC(layer_dismiss);
	void initwithaskuid(int uid);
	void agreornot(bool isagree);
	void updatetime(float dt);
	void changestatebyuid(int uid,int state);
	void failddissmiss(EventCustom *evt);
	void responseplayerisgareeornotbroadcast(EventCustom *evt);
	void initwithusersstatus(std::vector<int> arr_status);
public:
	std::vector<Text *>arr_text_name;
	std::vector<Text *>arr_text_state;
	std::vector<Color3B>arr_color;
	int dismiss_time;
	Button *bt_agree;
	Button *bt_disagree;
	Text *tx_fen;
	Text *tx_miao;
};

#endif