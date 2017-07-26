#include "layer_result3.h"
#include "model/GamerDataDeal.h"
#include "model/MjData.h"
#include "platform/MissionWeiXin.h"
#include "view/Layer/Main/layer_result.h"
#include "view/Layer/Main/Playing_three.h"
#include "view/Layer/Lobby/LobbyView.h"
#include "util/GameConst.h"
void layer_result_end::onEnter()
{
	ParentInfo::onEnter();
}
void layer_result_end::onExit()
{
	ParentInfo::onExit();
}

bool layer_result_end::init()
{
	if(!ParentInfo::init())
	{
		return false;
	}
	n_root=CSLoader::createNode("res/loading/Layer_result3.csb");
	addChild(n_root);

	return true;
}
void layer_result_end::initwithdata(result_total_all arr)
{
	int biggistWin=0;
	int round_num=0;
	for(int i=0;i<arr.arr_total_all.size();i++)
	{
		String *path_name=String::createWithFormat("bg_suanfen_others_%d",i+1);

		Sprite *sp_big=(Sprite *)n_root->getChildByName(path_name->getCString());

		result_total r_a=arr.arr_total_all.at(i);
		round_num=r_a.arr_fen_perround.size();
		int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(r_a.total_uid)->getSeatId());

		GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(viewid);

		Sprite *sp_head=(Sprite *)sp_big->getChildByName("touxiang_5");
		std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
		String *s=String::createWithFormat("%s%d.png",path.c_str(),g->getUId());
		sp_head->setTexture(s->getCString());//保存到本地的别的玩家的头像
		float acle=70/sp_head->getContentSize().width;
		sp_head->setScale(acle);

		Text *tx_name=(Text *)sp_big->getChildByName("Text_1");
		tx_name->setString(g->getNick());

		Text *tx_uid=(Text *)sp_big->getChildByName("Text_1_0");
		String *tx_uid_path=String::createWithFormat("%d",g->getUId());
		tx_uid->setString(tx_uid_path->getCString());
       


		Text *tx_fenshu=(Text *)sp_big->getChildByName("Text_1_1_4_1_0");
		String *tx_7=String::createWithFormat("%d",g->getGold()-1000);
		tx_fenshu->setString(tx_7->getCString());


		for(int j=0;j<8;j++)
		{
			String *score_s=String::createWithFormat("Text_fenshu_%d",j+1);
			Text *tx_score=(Text *)sp_big->getChildByName(score_s->getCString());
			tx_score->setVisible(false);
		}
		for(int j=0;j<r_a.arr_fen_perround.size();j++)
		{
			String *score_s=String::createWithFormat("Text_fenshu_%d",j+1);
			Text *tx_score=(Text *)sp_big->getChildByName(score_s->getCString());
			tx_score->setVisible(true);
			if(r_a.arr_fen_perround[j]<0)
			{
				tx_score->setString(String::createWithFormat("%d",r_a.arr_fen_perround[j])->getCString());
			}
			else if(r_a.arr_fen_perround[j]>=0)
			{
				tx_score->setString(String::createWithFormat("+%d",r_a.arr_fen_perround[j])->getCString());
			}
			
		}

		if(g->getGold()>=biggistWin)
		{
			biggistWin=g->getGold();
		}
	}

	for(int i=0;i<8;i++)
	{
		String *score_s=String::createWithFormat("Text_jushu_%d",i+1);
		Text *tx_score=(Text *)n_root->getChildByName(score_s->getCString());
		if(i<round_num)
		{
			tx_score->setVisible(true);
		}
		else
		{
			tx_score->setVisible(false);
		}
	}
	for(int i=0;i<arr.arr_total_all.size();i++)
	{
		String *path_name=String::createWithFormat("bg_suanfen_others_%d",i+1);

		Sprite *sp_big=(Sprite *)n_root->getChildByName(path_name->getCString());
        

		result_total r_a=arr.arr_total_all.at(i);

		int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(r_a.total_uid)->getSeatId());

		GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(viewid);
		Sprite *sp_wintag=(Sprite *)sp_big->getChildByName("icon_dayingjia_6");
		if(biggistWin!=1000)
		{
			if(g->getGold()>=biggistWin)
			{
				sp_wintag->setVisible(true);
			}
			else
			{
				sp_wintag->setVisible(false);
			}
		}
		else
		{
			sp_wintag->setVisible(false);
		}
		Sprite *sp_fangzhu=(Sprite *)sp_big->getChildByName("qd6_0021__19");
		if(i==0)
		{
			sp_fangzhu->setVisible(true);
		}
		else
		{
			sp_fangzhu->setVisible(false);
		}
	}
	for(int i=0;i<4;i++)
	{
		String *path_name=String::createWithFormat("bg_suanfen_others_%d",i+1);

		Sprite *sp_big=(Sprite *)n_root->getChildByName(path_name->getCString());
		if(i>=arr.arr_total_all.size())
		{
			sp_big->setVisible(false);
		}
	}
	Button *bt_fanhui=(Button *)n_root->getChildByName("Button_1");
	bt_fanhui->addClickEventListener(CC_CALLBACK_0(layer_result_end::backform,this));

	Button *bt_share=(Button *)n_root->getChildByName("Button_1_0");
    bt_share->addClickEventListener(CC_CALLBACK_0(layer_result_end::sharewinxin,this));
	if(MjData::getInstance()->getisinapple()==1)
	{
		bt_share->setVisible(false);
		bt_share->setEnabled(false);
	}
}
void layer_result_end::backform()
{
	GamerData::getInstance()->setStatus(0);	
	SEND_CUSTOM_MSG("stopHerat");
	SEND_CUSTOM_MSG("gamemainexit");
	SEND_CUSTOM_MSG(CustomEvent::key_show_request_headinfo);
	bool b = false;
	SEND_CUSTOM_MSG("loseconnect",&b);
	//SEND_CUSTOM_MSG("gamemainstopschedule");
	this->removeFromParent();
}
void layer_result_end::sharewinxin()
{
	//MissionWeiXin::getinstance()->cutscreen();
	//LobbyView *l_b=LobbyView::create();
	//l_b->showUIWeiXinShare(2);
	//addChild(l_b,1000);
	int flag = 0;
	MissionWeiXin::getinstance()->cutscreen(flag);
}

