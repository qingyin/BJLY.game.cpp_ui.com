#include "layer_dismiss.h"
#include "model/GamerData.h"
#include "model/GamerDataDeal.h"
#include "tool/Tools.h"
#include "controller/table/TableCommand.h"
void layer_dismiss::onEnter()
{
	ParentInfo::onEnter();
	this->_eventDispatcher->addCustomEventListener("failddissmiss",CC_CALLBACK_1(layer_dismiss::failddissmiss,this));
	this->_eventDispatcher->addCustomEventListener("responseplayergareeornotbroadcast",CC_CALLBACK_1(layer_dismiss::responseplayerisgareeornotbroadcast,this));
}
void layer_dismiss::onExit()
{
	this->_eventDispatcher->removeCustomEventListeners("failddissmiss");
	this->_eventDispatcher->removeCustomEventListeners("responseplayergareeornotbroadcast");
	ParentInfo::onExit();
}
void layer_dismiss::failddissmiss(EventCustom *evt)
{
	this->removeFromParent();
}
bool layer_dismiss::init()
{
	if(!ParentInfo::init())
	{
		return false;
	}

	Node *n_dismiss=CSLoader::createNode("res/loading/dismissRoom.csb");
	addChild(n_dismiss);

	for(int i=0;i<4;i++)
	{
		String *name=String::createWithFormat("text_name%d",i+1);
		Text *tx=(Text *)n_dismiss->getChildByName(name->getCString());
		arr_text_name.push_back(tx);
		if(i!=0)
		{
			tx->setVisible(false);
		}
	}
	for(int i=0;i<3;i++)
	{
		String *name=String::createWithFormat("text_state%d",i+2);
		Text *tx=(Text *)n_dismiss->getChildByName(name->getCString());
		arr_text_state.push_back(tx);
		tx->setVisible(false);
	}
	tx_fen=(Text *)n_dismiss->getChildByName("text_2_1");
	tx_miao=(Text *)n_dismiss->getChildByName("text_2_2");
	dismiss_time=300;
	bt_agree=(Button *)n_dismiss->getChildByName("btnAgree");
	bt_agree->addClickEventListener(CC_CALLBACK_0(layer_dismiss::agreornot,this,true));

	bt_disagree=(Button *)n_dismiss->getChildByName("btnDecline");
	bt_disagree->addClickEventListener(CC_CALLBACK_0(layer_dismiss::agreornot,this,false));

	arr_color.push_back(Color3B(255,255,0));
	arr_color.push_back(Color3B(255,0,0));
	arr_color.push_back(Color3B(77,77,77));
	   
	return true;
}
void layer_dismiss::agreornot(bool isagree)
{
	//发出同意或者拒绝请求
	TableCommand::getInstance()->requestagreeornot(isagree);
	//this->removeFromParent();
	bt_agree->setVisible(false);
	bt_disagree->setVisible(false);
	bt_agree->setEnabled(false);
	bt_disagree->setEnabled(false);

}
void layer_dismiss::responseplayerisgareeornotbroadcast(EventCustom *evt)
{
	GS2C_DismissAnswerBroadcast *data=(GS2C_DismissAnswerBroadcast *)evt->getUserData();
	int error=data->errorcode();
	if(error==0)
	{
		int uid=data->uid();
		int isagree=data->is_agree();
		changestatebyuid(uid,isagree);
	}
}
void layer_dismiss::changestatebyuid(int uid,int isagree)
{
	for(int i=0;i<3;i++)
	{
		if(uid==arr_text_state[i]->getTag())
		{
			int index;
			if(isagree==0)
			{
				index=3;
			}
			else if(isagree==1)
			{
				index=2;
			}
			String *path=String::createWithFormat("state%d",index);
			std::string name=Tools::getChineseByKey(path->getCString());
			arr_text_state[i]->setString(name.c_str());
			arr_text_state[i]->setVisible(true);
			arr_text_state[i]->setColor(arr_color[i]);
			arr_text_name[i+1]->setVisible(true);
			break;
		}
	}
}
void layer_dismiss::initwithaskuid(int uid)
{
	//初始化名字
	GamerData *g_d_ask=GamerDataDeal::getInstance()->getGamerData(uid);
	arr_text_name[0]->setString(g_d_ask->getNick());
	
	int index=1;
	for(int i=0;i<GamerDataDeal::getInstance()->m_gamerDataM.size();i++)
	{
		GamerData *g_d=GamerDataDeal::getInstance()->getGamerDataBySeat(i);
		if(g_d->getUId()!=uid)
		{
			arr_text_name[index]->setString(g_d->getNick());
			arr_text_name[index]->setTag(g_d->getUId());
			arr_text_state[index-1]->setTag(g_d->getUId());
			std::string str=Tools::getChineseByKey("state1");//全是等待状态
			arr_text_state[index-1]->setString(str.c_str());
			if(g_d->getStatus()==3)
			{
				std::string str1=Tools::getChineseByKey("state2");//全是等待状态
				arr_text_state[index-1]->setString(str1.c_str());
			}
			index++;
		}
	}
	//判断是否显示同意拒绝
	if(uid==GamerData::getInstance()->getUId())
	{
		bt_agree->setVisible(false);
		bt_disagree->setVisible(false);
		bt_agree->setEnabled(false);
		bt_disagree->setEnabled(false);

	}
	else
	{
		bt_agree->setVisible(true);
		bt_disagree->setVisible(true);
		bt_agree->setEnabled(true);
		bt_disagree->setEnabled(true);
	}
	//开启倒计时
	schedule(schedule_selector(layer_dismiss::updatetime),1.0f);
}
void layer_dismiss::updatetime(float dt)
{
	if(dismiss_time-1>=0)
	{
		//这里进行退出房间操作
		dismiss_time=dismiss_time-1;
	}
	//刷新倒计时
	int fen=dismiss_time/60;
	tx_fen->setString(String::createWithFormat("%d",fen)->getCString());
	int miao=dismiss_time%60;
	tx_miao->setString(String::createWithFormat("%d",miao)->getCString());
}
void layer_dismiss::initwithusersstatus(std::vector<int> arr_status)
{
	
}
