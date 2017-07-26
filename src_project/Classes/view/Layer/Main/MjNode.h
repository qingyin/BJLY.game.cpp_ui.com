#pragma once
#include "cocos2d.h"
#include "cocostudio/cocostudio.h"
#include "ui/CocosGUI.h"
#include  "tool/Tools.h"
using namespace cocos2d;
using namespace std;
using namespace ui;
using namespace cocostudio;

class MjNode : public Node
{
public:
	bool init();
	CREATE_FUNC(MjNode);
	void initBtnWithId(BYTE _id,const bool isUse = true, int wDelta = 0, int hDelta = 0);			//根据id获取麻将牌值 Button
	unsigned int getLogicValue();
	void setStateOut();						//设置当前麻将为已出牌状态
	void setstatecantoperate(bool iscanoperate);
	
	BYTE id;
	CC_SYNTHESIZE(bool,isCardSelected,IsCardSelected);//当前是否被选中(true:是;false:否)

private:
	//按钮回调函数
	void ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType);
	
public:
	Sprite* btnMj;
	Sprite* valueMj;
	unsigned int mj_value;
	bool iscanoperateornot;
};
