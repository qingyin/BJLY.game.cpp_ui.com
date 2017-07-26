#ifndef LAYER_CHAT_H
#define  LAYER_CHAT_H
#include "view/ParentInfo/ParentInfo.h"
class layer_chat:public ParentInfo
{
public:
	virtual bool init();
	CREATE_FUNC(layer_chat);
	void ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType);
	void refreshchat(int tag);
	void removeself(float dt);
public:
	ListView *list;
	Node *n_biaoqing;
	Button *b_changyongyu;
	Button *Button_biaoqing;
	TextField *tx_chat;
	Button *bt_send;

	Vec2 v_origin_list;
	Vec2 v_origin_biaoqiang;

	int send_tag;
};

#endif