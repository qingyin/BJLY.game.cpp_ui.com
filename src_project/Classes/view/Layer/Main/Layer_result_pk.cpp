#include "layer_result_pk.h"
#include "model/GamerDataDeal.h"
#include "model/MjData.h"
#include "platform/MissionWeiXin.h"
#include "view/Layer/Main/layer_result.h"
#include "view/Layer/Main/Playing_three.h"

void layer_result_pk::onEnter()
{
	ParentInfo::onEnter();
}
void layer_result_pk::onExit()
{
	ParentInfo::onExit();
}
bool layer_result_pk::init()
{
	if(!ParentInfo::init())
	{
		return false;
	}
	n_root=CSLoader::createNode("res/loading/Layer_result_pk.csb");

	addChild(n_root);

	

	return true;
}
void layer_result_pk::initwithdata(arr_pklist arr_p)
{

	Sprite *sp_line=(Sprite *)n_root->getChildByName("pk_line2_1");
	if(MjData::getInstance()->getpalyrule()!=1)
	{
		sp_line->setVisible(false);
	}
	//头像
	for(int i=0;i<arr_p.arrpklist.size()+1;i++)
	{
		int totalgold=0;
		GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(i);

		String *bg_path=String::createWithFormat("bg_touxiang_%d",i+1);
		Sprite *bg=(Sprite *)n_root->getChildByName(bg_path->getCString());

		Sprite *sp_icon=(Sprite *)bg->getChildByName("touxiang_7");
		std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
		String *s=String::createWithFormat("%s%d.png",path.c_str(),g->getUId());
		sp_icon->setTexture(s->getCString());//保存到本地的别的玩家的头像
		float acle=70/sp_icon->getContentSize().width;
		sp_icon->setScale(acle);

		Text *tx_name=(Text *)bg->getChildByName("Text_name");
		tx_name->setString(g->getNick());
		
		if(i<arr_p.arrpklist.size() )
		{
		int uid=arr_p.arrpklist[i].uid;
		int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uid)->getSeatId());
		String *n_path=String::createWithFormat("Node_user_%d",viewid);
		Node *n_n=n_root->getChildByName(n_path->getCString());

		for(int j=0;j<8;j++)
		{
			String *ju_score=String::createWithFormat("Text_winscore_%d",j+1);
			Text *tx_fen=(Text *)n_n->getChildByName(ju_score->getCString());
			if(j<arr_p.arrpklist[i].arr_perround_score.size())
			{
				if(arr_p.arrpklist[i].arr_perround_score[j]<0)
				{
					std::string wopei=Tools::getChineseByKey("wopei");
					std::string fen=Tools::getChineseByKey("fen");
					tx_fen->setString(String::createWithFormat("%s%d%s",wopei.c_str(),arr_p.arrpklist[i].arr_perround_score[j]*-1,fen.c_str())->getCString());
				}
				else if(arr_p.arrpklist[i].arr_perround_score[j]>0)
				{
					std::string wopei=Tools::getChineseByKey("peiwo");
					std::string fen=Tools::getChineseByKey("fen");
					tx_fen->setString(String::createWithFormat("%s%d%s",wopei.c_str(),arr_p.arrpklist[i].arr_perround_score[j],fen.c_str())->getCString());
				}
				else
				{
					tx_fen->setString(String::createWithFormat("%s",Tools::getChineseByKey("wu").c_str())->getCString());
				}
				totalgold=totalgold+arr_p.arrpklist[i].arr_perround_score[j];
				tx_fen->setVisible(true);
			}
			else
			{
				tx_fen->setVisible(false);
			}
		}
		Text *tx_total=(Text *)n_n->getChildByName("Text_winscore_9");
		
			if(totalgold<0)
			{
				std::string wopei=Tools::getChineseByKey("wopei");
				std::string fen=Tools::getChineseByKey("fen");
				tx_total->setString(String::createWithFormat("%s%d%s",wopei.c_str(),totalgold*-1,fen.c_str())->getCString());
			}
			else if(totalgold>0)
			{
				std::string wopei=Tools::getChineseByKey("peiwo");
				std::string fen=Tools::getChineseByKey("fen");
				tx_total->setString(String::createWithFormat("%s%d%s",wopei.c_str(),totalgold,fen.c_str())->getCString());
			}
			else
			{
				tx_total->setString(String::createWithFormat("%s",Tools::getChineseByKey("wu").c_str())->getCString());
			}
		}

		
	}
	Node *n_dijiju=n_root->getChildByName("Node_user_1_2");
	for(int i=0;i<8;i++)
	{
		String *str_dijiju=String::createWithFormat("Text_winscore_%d",i+1);
		Text *tx_dijiju=(Text *)n_dijiju->getChildByName(str_dijiju->getCString());
	    if(i<arr_p.arrpklist[0].arr_perround_score.size())
		{
			tx_dijiju->setVisible(true);
		}
		else
		{
			tx_dijiju->setVisible(false);
		}
	}


	for(int i=0;i<4;i++)
	{
		String *path_touciang=String::createWithFormat("bg_touxiang_%d",i+1);
		Node *n_touxiang_=n_root->getChildByName(path_touciang->getCString());
		if(i>=arr_p.arrpklist.size()+1)
		{
			n_touxiang_->setVisible(false);
		}
	}

	for(int i=0;i<3;i++)
	{
		String *path_touciang=String::createWithFormat("Node_user_%d",i+1);
		Node *n_touxiang_=n_root->getChildByName(path_touciang->getCString());
		if(i>=arr_p.arrpklist.size())
		{
			n_touxiang_->setVisible(false);
		}
	}


	Button *bt_back=(Button *)n_root->getChildByName("Button_remove");
	bt_back->addClickEventListener(CC_CALLBACK_0(layer_result_pk::backform,this));
}
void layer_result_pk::backform()
{
	this->setZOrder(-1);
	this->setVisible(false);
}

