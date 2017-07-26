#include "layer_chat.h"
#include "controller/table/TableCommand.h"
#include "tool/MaskLayer.h"
bool layer_chat::init()
{
	if(!ParentInfo::init())
	{
		return false;
	}

	

	Node *n_chat=CSLoader::createNode("res/loading/Layer_chat.csb");
	addChild(n_chat);

	b_changyongyu=(Button *)n_chat->getChildByName("Button_changyongyu");
	b_changyongyu->addTouchEventListener(CC_CALLBACK_2(layer_chat::ButtonHandler, this));
	Button_biaoqing=(Button *)n_chat->getChildByName("Button_biaoqing");
	Button_biaoqing->addTouchEventListener(CC_CALLBACK_2(layer_chat::ButtonHandler, this));

	//Button * back_=(Button *)n_chat->getChildByName("Button_back");
	//back_->addTouchEventListener(CC_CALLBACK_2(layer_chat::ButtonHandler, this));

	

	tx_chat=(TextField *)n_chat->getChildByName("TextField_1");
	bt_send=(Button *)n_chat->getChildByName("Button_send");
	bt_send->addTouchEventListener(CC_CALLBACK_2(layer_chat::ButtonHandler,this));

	Button *bt_back=(Button *)n_chat->getChildByName("Button_back");
	bt_back->addTouchEventListener(CC_CALLBACK_2(layer_chat::ButtonHandler,this));
	if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS||CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	{
		this->setDelete(false);
		bt_back->setVisible(true);
	}
	else
	{
		this->setDelete(true);
		bt_back->setVisible(false);
	}

		
	list=(ListView *)n_chat->getChildByName("ListView_1");
	v_origin_list=list->getPosition();
	for(int i=0;i<8;i++)
	{
		String *name=String::createWithFormat("Button_%d",i+1);
		Button *bt_chan=(Button *)list->getChildByName(name->getCString());
		bt_chan->addTouchEventListener(CC_CALLBACK_2(layer_chat::ButtonHandler,this));
	}


	n_biaoqing=n_chat->getChildByName("Node_emoji");
	v_origin_biaoqiang=n_biaoqing->getPosition();
	for(int i=0;i<15;i++)
	{
		String *name=String::createWithFormat("emoji_%d",i+1);
		Button *bt_chan=(Button *)n_biaoqing->getChildByName(name->getCString());
		bt_chan->addTouchEventListener(CC_CALLBACK_2(layer_chat::ButtonHandler,this));
	}
	refreshchat(0);

	return true;
}
void layer_chat::ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType)
{
	Button *b=(Button *)pRef;
	int tag=b->getTag();
	std::string name=b->getName();
	if(name=="Button_changyongyu")
	{
		refreshchat(0);
	}
	else if(name=="Button_biaoqing")
	{
		refreshchat(1);
	}
	else if(name=="Button_send")
	{
		if(tx_chat->getString()!="")
		{
			TableCommand::getInstance()->requestcustomchat(tx_chat->getString());
			tx_chat->setString("");
			this->removeFromParent();
		}
	}
	else if(name=="Button_back")
	{
		this->removeFromParent();
	}
	else
	{
		if(tag>100&&tag<200)//changyongyu
		{
			if(touchType==ui::Widget::TouchEventType::ENDED)
			{
				send_tag=tag;
				scheduleOnce(schedule_selector(layer_chat::removeself),0.01);
			}
		}
		else if(tag>200)//biaoqing
		{
			send_tag=tag;
			scheduleOnce(schedule_selector(layer_chat::removeself),0.01);
		}
	}

}
void layer_chat::removeself(float dt)
{
	if(send_tag>=100&&send_tag<=300)
	{
		TableCommand::getInstance()->requestchat(send_tag);
	}
	this->removeFromParent();
}
void layer_chat::refreshchat(int tag)
{
	if(tag==0)
	{
		list->setVisible(true);
		list->setPosition(v_origin_list);
	//	b_changyongyu->setEnabled(false);
		b_changyongyu->loadTextures("res/loading/chat/bg_right_checked.png","res/loading/chat/bg_right_checked.png","res/loading/chat/bg_right_checked.png");
		Button_biaoqing->loadTextures("res/loading/chat/bg_left.png","res/loading/chat/bg_left.png","res/loading/chat/bg_left.png");
		n_biaoqing->setVisible(false);

		n_biaoqing->setPosition(Vec2(10000,10000));
		
		//Button_biaoqing->setEnabled(true);
	}
	else
	{
		b_changyongyu->loadTextures("res/loading/chat/bg_right.png","res/loading/chat/bg_right.png","res/loading/chat/bg_right.png");
		Button_biaoqing->loadTextures("res/loading/chat/btn_left_checked.png","res/loading/chat/btn_left_checked.png","res/loading/chat/btn_left_checked.png");

		list->setVisible(false);
		list->setPosition(Vec2(10000,10000));
		//b_changyongyu->setEnabled(true);
		n_biaoqing->setVisible(true);
		n_biaoqing->setPosition(v_origin_biaoqiang);
		//Button_biaoqing->setEnabled(false);
	}
}