
#include "MjNode.h"
#include "tool/Tools.h"
bool MjNode::init()
{
	if(!Node::init()) return false;
	isCardSelected = false;
	iscanoperateornot=true;
	return true;
}
void MjNode::initBtnWithId(BYTE _id,bool isUse, int wDelta, int hDelta)
{
	this->id = _id;
	mj_value = (id / 0x10)*10 + id % 0x10;
	log("%d",mj_value);
	btnMj = Sprite::create("res/cards/mj_bg2.png");
	btnMj->setAnchorPoint(Vec2::ZERO);
	btnMj->setName("pokerBtn");
	//if(isUse)btnMj->addTouchEventListener(CC_CALLBACK_2(MjNode::ButtonHandler, this));
	this->addChild(btnMj,0);
	this->setContentSize(btnMj->getContentSize());
	valueMj = Sprite::create(StringUtils::format("res/cards/mj_%d.png",mj_value));
	valueMj->setAnchorPoint(Vec2(0.5f,0.5f));
	valueMj->setPosition(Vec2(this->getContentSize().width/2.0f+wDelta,this->getContentSize().height/2.0f-16.0f+hDelta));
	btnMj->addChild(valueMj,1);

}
//设置当前麻将为已出牌状态
void MjNode::setStateOut()
{
	//btnMj->loadTextures("res/cards/mj_bg1.png", "res/cards/mj_bg1.png","res/cards/mj_bg1.png");
	//valueMj->setPosition(Vec2(this->getContentSize().width/2.0f,this->getContentSize().height/2.0f+16.0f));

}
void MjNode::setstatecantoperate( bool iscanoperate)
{
	//btnMj->setEnabled(iscanoperate);
	iscanoperateornot=iscanoperate;
}

//按钮回调函数
void MjNode::ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType)
{
	if (touchType != ui::Widget::TouchEventType::ENDED) return;
	Button* pBtn = (Button*) pRef;
	string name = pBtn->getName();
	if (name == "pokerBtn"){
		//麻将被选中
		if (!isCardSelected)
		{
			isCardSelected = true;
			SEND_CUSTOM_MSG("playing_btn_chooseCard",this);
		}
		else
		{
			if(UserDefault::getInstance()->getBoolForKey("iscanoperatecard")==true)
			{
				SEND_CUSTOM_MSG("playing_broadcast_outCard");
			}
		}
	}
}
///获取pMjNode的逻辑值
unsigned int MjNode::getLogicValue()
{
	return mj_value;
}
