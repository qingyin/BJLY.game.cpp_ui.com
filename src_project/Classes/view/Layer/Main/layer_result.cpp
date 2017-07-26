#include "layer_result.h"
#include "model/GamerDataDeal.h"
#include "model/MjData.h"
#include "platform/MissionWeiXin.h"
#include "view/Layer/Main/layer_result1.h"
#include "view/Layer/Main/Playing_three.h"
#include "view/Layer/Main/Layer_result3.h"
#include "view/Layer/Main/Layer_result_pk.h"
#include "view/Layer/Lobby/LobbyView.h"
void layer_result::onEnter()
{
	ParentInfo::onEnter();
	
	this->_eventDispatcher->addCustomEventListener("responsegetresultdetail",CC_CALLBACK_1(layer_result::addresultdetail,this));
	this->_eventDispatcher->addCustomEventListener("readySuccessForRemoveResult",CC_CALLBACK_1(layer_result::readyForRemoveSelf,this));
	
}
void layer_result::onExit()
{
	this->_eventDispatcher->removeCustomEventListeners("responsegetresultdetail");
	this->_eventDispatcher->removeCustomEventListeners("readySuccessForRemoveResult");
	ParentInfo::onExit();
}
void layer_result::readyForRemoveSelf(EventCustom *evt)
{

	layer_result_pk *l_pk=(layer_result_pk *)CCDirector::getInstance()->getRunningScene()->getChildByTag(2001);
	l_pk->removeFromParent();
	this->removeFromParent();
}
void layer_result::addresultdetail(EventCustom* evt)
{
	
}
bool layer_result::init()
{
	if(!ParentInfo::init())
	{
		return false;
	}

	SEND_CUSTOM_MSG("onresultunscheduleQuake");

	Node *n_root=CSLoader::createNode("res/loading/layer_result1.csb");
	addChild(n_root);

	//翻牌机
	Sprite *sp_bg=(Sprite *)n_root->getChildByName("bg_fanpaiji_643");
	Sprite *mj_bg=(Sprite *)sp_bg->getChildByName("mj_bg");
	sp_mj_value=(Sprite *)mj_bg->getChildByName("mj_value");

	sp_win_tag=(Sprite *)n_root->getChildByName("title_result");//你赢了 你输了 黄庄

	sp_ishuang=(Sprite *)n_root->getChildByName("is_huangzhuang");//黄庄
	sp_ishuang->setVisible(false);

	bt_share=(Button *)n_root->getChildByName("Button_share");
	bt_next=(Button *)n_root->getChildByName("Button_jixu");
	bt_detail=(Button *)n_root->getChildByName("Button_suanfen");

	bt_share->addClickEventListener(CC_CALLBACK_0(layer_result::clickbt_share,this));
	bt_next->addClickEventListener(CC_CALLBACK_0(layer_result::clickbt_next,this));
	bt_detail->addClickEventListener(CC_CALLBACK_0(layer_result::clickbt_detail,this));

	if(MjData::getInstance()->getisinapple()==1)
	{
		bt_share->setVisible(false);
		bt_share->setEnabled(false);
	}

	bt_next->setTag(0);

	for(int i=0;i<4;i++)
	{
		Node *n_palyer=(Node *)n_root->getChildByName(String::createWithFormat("Node_jiesuantiao_%d",i+1)->getCString());
		arr_n_players.push_back(n_palyer);

		if((MjData::getInstance()->getpalyrule()==2||MjData::getInstance()->getpalyrule()==4)&&i==3)
		{
			n_palyer->setVisible(false);
		}
		if((MjData::getInstance()->getpalyrule()==3||MjData::getInstance()->getpalyrule()==5)&&(i==2||i==3))
		{
			n_palyer->setVisible(false);
		}
	}
	Sprite *bg_rule=(Sprite *)n_root->getChildByName("bg_rule_zhuomian_1");
	Text *tx_id=(Text *)bg_rule->getChildByName("Text_fangjian_0");
	tx_id->setText(String::createWithFormat("%d", GamerData::getInstance()->getTableId())->getCString());
	Text *tx_jushu=(Text *)bg_rule->getChildByName("Text_fangjian_0_0");
	if(MjData::getInstance()->getjushu()==4)
	{
		String *form=String::createWithFormat("%d/%d%s",MjData::getInstance()->getjushu()-1-MjData::getInstance()->getleftjushu(),MjData::getInstance()->getjushu(),Tools::getChineseByKey("Ju").c_str());
		tx_jushu->setText(form->getCString());
	}
	else if(MjData::getInstance()->getjushu()==8)
	{
	//	tx_jushu->setText(Tools::getChineseByKey("16ju").c_str());
		String *form=String::createWithFormat("%d/%d%s",MjData::getInstance()->getjushu()-1-MjData::getInstance()->getleftjushu(),MjData::getInstance()->getjushu(),Tools::getChineseByKey("Ju").c_str());
		tx_jushu->setText(form->getCString());
	}
	Text *tx_zigang=(Text *)bg_rule->getChildByName("Text_fangjian_0_0_0");
	if(MjData::getInstance()->getIsgang_men())
	{
		tx_zigang->setText(Tools::getChineseByKey("zigang").c_str());
	}
	else
	{
		tx_zigang->setText(Tools::getChineseByKey("zhuanwan").c_str());
	}
	Text *tx_genzhuang=(Text *)bg_rule->getChildByName("Text_fangjian_0_0_0_0");
	if(MjData::getInstance()->getIsgenZhuang())
	{
		tx_genzhuang->setText(Tools::getChineseByKey("gen").c_str());
	}
	else
	{
		tx_genzhuang->setText(Tools::getChineseByKey("bugen").c_str());
	}

	Button *bt_pk=(Button *)n_root->getChildByName("Button_pk");
	bt_pk->addClickEventListener(CC_CALLBACK_0(layer_result::showresultpk,this));

	return true;
}
void layer_result::showresultpk()
{
	SEND_CUSTOM_MSG("showresultpk");
}
void layer_result::clickbt_detail()
{
	//TableCommand::getInstance()->resquestresultdetail();
	l_detail->setVisible(true);
	l_detail->setZOrder(100);
}
void layer_result::initwithdata(oneroundresult one_re)
{
	//每个人的结果信息
	std::vector<resultitem>arr_palyer_data;
	

	for(int i=0;i<one_re.arr_resluts.size();i++)
	{
		arr_palyer_data.push_back(one_re.arr_resluts[i]);
	}
	//标志
	
	if(one_re.is_huangzhuang==1)//黄庄
	{
		sp_ishuang->setVisible(true);
		sp_ishuang->setTexture("res/loading/layer_result/title_huangzhuang.png");
	}
	else
	{
		sp_ishuang->setVisible(false);
	}
	
   for(int j=0;j<arr_palyer_data.size();j++)
	{
		if(arr_palyer_data[j].uid==GamerData::getInstance()->getUId())
		{
		  //找到我
			if(arr_palyer_data[j].gold_change==0)//不输不赢
			{
				sp_win_tag->setTexture("res/srcRes/title_pingju.png");
				win_tag=3;
			}
			else if(arr_palyer_data[j].gold_change>0)//赢了
			{
				sp_win_tag->setTexture("res/srcRes/title_win.png");
				win_tag=1;
			}
			else if(arr_palyer_data[j].gold_change<0)//输了
			{
				sp_win_tag->setTexture("res/loading/layer_result/title_title_lose.png");
				win_tag=2;
			}
		}
	}
  
      int value_mj=one_re.fanpaiji_id/16*10+one_re.fanpaiji_id%16;
	  String *fanji_path=String::createWithFormat("res/cards/mj_%d.png",value_mj);
	  sp_mj_value->setTexture(fanji_path->getCString());
	

	//刷新每个用户的信息
	for(int i=0;i<arr_palyer_data.size();i++)
	{
		hu_type h_t;
		GamerData * p_palyer_info=GamerDataDeal::getInstance()->getGamerData(arr_palyer_data[i].uid);

		CCLOG("-----%d",arr_palyer_data[i].uid);

		uid[i]=p_palyer_info->getUId();

		Node *n_player=arr_n_players[i];
		
		//头像
		Sprite *sp_head=(Sprite *)n_player->getChildByName("touxiang_492");

		

		BYTE viewid=GetViewID(GamerData::getInstance()->getSeatId(),p_palyer_info->getSeatId());

		Sprite *sp_icon_tingpai=(Sprite *)n_player->getChildByName("icon_chong_495_0");

		if(p_palyer_info->getistingpai()==1)
		{
			sp_icon_tingpai->setVisible(true);
		}
		else
		{
			sp_icon_tingpai->setVisible(false);
		}

		Sprite *sp_bg_tiao=(Sprite *)n_player->getChildByName("bg_paixing_others");
		if(viewid==0)
		{
			sp_bg_tiao->setTexture("res/loading/layer_result/bg_paixing_mine.png");
		}
		else
		{
			sp_bg_tiao->setTexture("res/loading/layer_result/bg_paixing_others.png");
		}



		std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
		String *s=String::createWithFormat("%s%d.png",path.c_str(),p_palyer_info->getUId());
		sp_head->setTexture(s->getCString());//保存到本地的别的玩家的头像
		float acle=73/sp_head->getContentSize().width;
		sp_head->setScale(acle);
		//鸡
		Sprite *ji_iocn=(Sprite *)n_player->getChildByName("icon_chong_495");
		if(p_palyer_info->getJi_type()==1)
		{
			ji_iocn->setVisible(true);
		}
		else if(p_palyer_info->getJi_type()==2)
		{
			ji_iocn->setVisible(true);
			ji_iocn->setTexture("res/srcRes/icon_ze.png");
		}
		else
		{
			ji_iocn->setVisible(false);
		}
		//总分
		Text *tx_zong=(Text *)n_player->getChildByName("Text_16_0_0");
		tx_zong->setString(String::createWithFormat("%d",p_palyer_info->getGold())->getCString());
		//名字
		Text *name=(Text *)n_player->getChildByName("Text_name");
		name->setString(p_palyer_info->getNick().c_str());

		//id
		Text *tx_id=(Text *)n_player->getChildByName("Text_16_0_1_0");
		tx_id->setString(String::createWithFormat("%d",p_palyer_info->getUId())->getCString());

        //是否时装
		Sprite *sp_zhuang=(Sprite *)n_player->getChildByName("qd1_0013_z_494");

		if(arr_palyer_data[i].uid==MjData::getInstance()->getbanker())
		{
			sp_zhuang->setVisible(true);
		}
		else
		{
			sp_zhuang->setVisible(false);
		}
		
		//加减的分数
		Text *tx_score=(Text *)n_player->getChildByName("Text_fenshu");
		//p_palyer_info->setGold(p_palyer_info->getGold()+arr_players_data_final[i].gold_change);
		Text *tx_score_fuhao=(Text *)n_player->getChildByName("Text_19");
	    h_t.fenzhi_win=arr_palyer_data[i].gold_change;
		if(arr_palyer_data[i].gold_change<=0)
		{
			tx_score->setString(String::createWithFormat("%d",arr_palyer_data[i].gold_change)->getCString());
			tx_score_fuhao->setVisible(false);
		}
		else
		{
			tx_score->setString(String::createWithFormat("+%d",arr_palyer_data[i].gold_change)->getCString());
			tx_score_fuhao->setVisible(false);
		}
		//叫牌
		Text *tx_jiao=(Text *)n_player->getChildByName("Text_15");
		//胡牌类型 0没叫 1有叫 2平胡， 3大对子， 4七对， 5龙七对， 6清一色， 7清七对， 8清大对， 9青龙背
		String *str_path=String::createWithFormat("hu_%d",arr_palyer_data[i].hu_type+1);
		std::string s1=Tools::getChineseByKey(str_path->getCString());
		tx_jiao->setString(s1);
		h_t.hutype=arr_palyer_data[i].hu_type;
		h_t.uid=p_palyer_info->getUId();
		
		//显示杠牌类型
		Text *tx_gang_type=(Text *)n_player->getChildByName("Text_gangtype");
		if(arr_palyer_data[i].gang_type==1)//1自摸 2点炮 3放热跑 4杠上花 5抢杠胡（有杠上花就没有自摸）
		{
			std::string path=Tools::getChineseByKey("zimo");
			tx_gang_type->setString(path.c_str());
			h_t.gang_type=1;
		}
		else if(arr_palyer_data[i].gang_type==2)
		{
			std::string path=Tools::getChineseByKey("dianpao");
			tx_gang_type->setString(path.c_str());
			h_t.gang_type=2;
		}
		else if(arr_palyer_data[i].gang_type==3)
		{
			std::string path=Tools::getChineseByKey("fangrepao");
			tx_gang_type->setString(path.c_str());
			h_t.gang_type=3;
		}
		else if(arr_palyer_data[i].gang_type==4)
		{
			std::string path=Tools::getChineseByKey("gangshanghua");
			tx_gang_type->setString(path.c_str());
			h_t.gang_type=4;
		}
		else if(arr_palyer_data[i].gang_type==5)
		{
			std::string path=Tools::getChineseByKey("qiangganghu");
			tx_gang_type->setString(path.c_str());
			h_t.gang_type=5;
		}
		else
		{
			Sprite *sp_gang=(Sprite *)n_player->getChildByName("bg_hupaifangshi_big");
			sp_gang->setVisible(false);
			tx_gang_type->setVisible(false);
			h_t.gang_type=0;
		}
		arr_hu.push_back(h_t);

		Node *n_ji=n_player->getChildByName("Node_ji");
		Sprite *sp_ji=(Sprite *)n_ji->getChildByName("ji_1")->getChildByName("mj_value");
		int jinum_me=arr_palyer_data[i].jinum;
		if(p_palyer_info->getJi_type()==1)
		{
			sp_ji->getParent()->setVisible(true);
			sp_ji->setTexture("res/cards/mj_11.png");
			jinum_me=jinum_me-1;
		}
		else
		{
			sp_ji->getParent()->setVisible(false);
		}
		for(int p=1;p<4;p++)
		{
			Sprite *sp_ji1=(Sprite *)n_ji->getChildByName(String::createWithFormat("ji_%d",p+1)->getCString())->getChildByName("mj_value");
			sp_ji1->getParent()->setVisible(false);
		}
		for(int l=1;l<jinum_me+1;l++)
		{
			Sprite *sp_ji1=(Sprite *)n_ji->getChildByName(String::createWithFormat("ji_%d",l+1)->getCString())->getChildByName("mj_value");
		    sp_ji1->getParent()->setVisible(true);
			sp_ji1->setTexture("res/cards/mj_11.png");
		}
		
		//套牌
	    std::vector<weaveitem>arr_weaves;
		for(int k=0;k<arr_palyer_data[i].arr_weaves.size();k++)
		{
			arr_weaves.push_back(arr_palyer_data[i].arr_weaves[k]);
		}
		float x=292;
		float y=-36.94;
		float bottom=49;
		float middle=115;
		for(int m=0;m<4;m++)
		{
			Node *n_big=(Node *)n_player->getChildByName(String::createWithFormat("node_chengxing_%d",m+1)->getCString());
			n_big->setVisible(false);
			if(arr_weaves.size()>m)
			{
				n_big->setVisible(true);
				if(arr_weaves[m].weavekin==9||arr_weaves[m].weavekin==10||arr_weaves[m].weavekin==11)
				{
						if(arr_weaves[m].weavekin==9)
						{
							n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
							n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
							n_big->getChildByName("mj_sp_chengxing_3")->setVisible(false);
							n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
							n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

							n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
							initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),arr_weaves[m].cardid);
							n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
							initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),arr_weaves[m].cardid);
							n_big->getChildByName("mj_sp_chengxing_6")->setVisible(true);
							initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_6")->getChildByName("mj_value"),arr_weaves[m].cardid);

							n_big->setPosition(Vec2(x,y));
							x=x+10+(383-257);
						}
						else if(arr_weaves[m].weavekin==10)
						{
							n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
							n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
							n_big->getChildByName("mj_sp_chengxing_3")->setVisible(false);
							n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
							n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);

							n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
							initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),arr_weaves[m].cardid);
							n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
							initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),arr_weaves[m].cardid);
							n_big->getChildByName("mj_sp_chengxing_8")->setVisible(true);
							initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_8")->getChildByName("mj_value"),arr_weaves[m].cardid);
							n_big->setPosition(Vec2(x-(305-257),y));
							x=x+10+(381-305);
						}
						else if(arr_weaves[m].weavekin==11)
						{
							n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);
							n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
							n_big->getChildByName("mj_sp_chengxing_1")->setVisible(false);
							n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
							n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);

							n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
							initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),arr_weaves[m].cardid);
							n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
							initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),arr_weaves[m].cardid);
							n_big->getChildByName("mj_sp_chengxing_4")->setVisible(true);
							initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_4")->getChildByName("mj_value"),arr_weaves[m].cardid);
							n_big->setPosition(Vec2(x-(344-257),y));
							x=x+10+(466-344);
						}
				}
				else if(arr_weaves[m].weavekin==1)//peng
				{
                    n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

					n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),arr_weaves[m].cardid);
					n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),arr_weaves[m].cardid);
					n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),arr_weaves[m].cardid);

					n_big->setPosition(Vec2(x-bottom,y));
					x=x+10+middle;
				}
					else if(arr_weaves[m].weavekin==2)//左杠
					{
						n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

						n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),arr_weaves[m].cardid);
						n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),arr_weaves[m].cardid);
						n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),arr_weaves[m].cardid);
						n_big->getChildByName("mj_sp_chengxing_6")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_6")->getChildByName("mj_value"),arr_weaves[m].cardid);

						n_big->setPosition(Vec2(x,y));
						x=x+10+middle+bottom;
					}
					else if(arr_weaves[m].weavekin==3)//右杠
					{
						n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

						n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),arr_weaves[m].cardid);
						n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),arr_weaves[m].cardid);
						n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),arr_weaves[m].cardid);
						n_big->getChildByName("mj_sp_chengxing_4")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_4")->getChildByName("mj_value"),arr_weaves[m].cardid);

						n_big->setPosition(Vec2(x-bottom,y));
						x=x+10+middle+bottom;
					}
					else if(arr_weaves[m].weavekin==4)//对门杠
					{
						n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

						n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),arr_weaves[m].cardid);
						n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),arr_weaves[m].cardid);
						n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),arr_weaves[m].cardid);
						n_big->getChildByName("mj_sp_chengxing_5")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_5")->getChildByName("mj_value"),arr_weaves[m].cardid);

						n_big->setPosition(Vec2(x-bottom,y));
						x=x+10+middle;
					}
					else if(arr_weaves[m].weavekin==5)//补杠
					{
						n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

						n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),arr_weaves[m].cardid);
						n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),arr_weaves[m].cardid);
						n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),arr_weaves[m].cardid);
						n_big->getChildByName("mj_sp_chengxing_7")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_7")->getChildByName("mj_value"),arr_weaves[m].cardid);

						n_big->setPosition(Vec2(x-bottom,y));
						x=x+10+middle;
					}
					else if(arr_weaves[m].weavekin==6)//暗杠
					{
						n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
						n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

						n_big->getChildByName("mj_sp_chengxing_7")->setVisible(true);
						initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_7")->getChildByName("mj_value"),arr_weaves[m].cardid);


						n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
						Sprite *sp_big1=(Sprite *)n_big->getChildByName("mj_sp_chengxing_1");
						Sprite *sp_1=(Sprite *)sp_big1->getChildByName("mj_value");//暗杠要把最上面那个牌变成暗杠的
						sp_1->setVisible(false);

						n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
						Sprite *sp_big2=(Sprite *)n_big->getChildByName("mj_sp_chengxing_2");
						Sprite *sp_2=(Sprite *)sp_big2->getChildByName("mj_value");//暗杠要把最上面那个牌变成暗杠的
						sp_2->setVisible(false);

						n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
						Sprite *sp_big3=(Sprite *)n_big->getChildByName("mj_sp_chengxing_3");
						Sprite *sp_3=(Sprite *)sp_big3->getChildByName("mj_value");//暗杠要把最上面那个牌变成暗杠的
						sp_3->setVisible(false);
						
					    sp_big1->setTexture("res/cards/mj_bg4.png");
						sp_big2->setTexture("res/cards/mj_bg4.png");
						sp_big3->setTexture("res/cards/mj_bg4.png");

						n_big->setPosition(Vec2(x-bottom,y));
						x=x+10+middle;
					}
				}
			}
		//手牌
		std::vector<int >arr_hands;
		for(int p=0;p<arr_palyer_data[i].handcards.size();p++)
		{
			arr_hands.push_back(arr_palyer_data[i].handcards[p]);
		}
	   sortMjByLaiya(arr_hands);
	   Node *n_shoupai=(Node *)n_player->getChildByName("nodeCards");
	   for(int o=0;o<14;o++)
	   {
		   Sprite *sp_shoupai=(Sprite *)n_shoupai->getChildByName(String::createWithFormat("poker_%d",o+1)->getCString());
		   sp_shoupai->setVisible(false);
	   }
	   //胡牌
	   Sprite *sp_hu_pai=(Sprite *)n_shoupai->getChildByName("poker_hu");
	   if(arr_palyer_data[i].hu_type>=2)
	   {
		   sp_hu_pai->setVisible(true);
		   Sprite *sp_hu_value=(Sprite *)sp_hu_pai->getChildByName("mj_value");
		   int card_hu_value=arr_palyer_data[i].hu_cardid/16*10+arr_palyer_data[i].hu_cardid%16;
		   String *hu_path=String::createWithFormat("res/cards/mj_%d.png",card_hu_value);
		   sp_hu_value->setTexture(hu_path->getCString());
	   }
	   else
	   {
		   sp_hu_pai->setVisible(false);
	   }
	   for(int x=0;x<14;x++)
	   {
		   if(x<arr_hands.size())
		   {
			   Sprite *mj_shoupai=(Sprite *)n_shoupai->getChildByName(String::createWithFormat("poker_%d",x+1)->getCString());
			   mj_shoupai->setVisible(true);
			   Sprite *sp_hua=(Sprite *)mj_shoupai->getChildByName("mj_value");
			   int mj_real_value=arr_hands[x]/16*10+arr_hands[x]%16;
			   sp_hua->setTexture(String::createWithFormat("res/cards/mj_%d.png",mj_real_value)->getCString());
		   }
	   }
	}

}
void layer_result::sortMjByLaiya(std::vector<int > &arr_mjs)
{
	std::sort(arr_mjs.begin(), arr_mjs.end(), [](int a,int b){
		return a>b;
	});
}
void layer_result::initcardWithCardIds(Sprite *sp_card,int cardid)
{
	int cardreal=cardid/16*10+cardid%16;//传过来的麻将的牌值必须是16进制的
	String *path=String::createWithFormat("res/cards/mj_%d.png",cardreal);
	sp_card->setTexture(path->getCString());
}
void layer_result::initwithdissmiss()
{
    SEND_CUSTOM_MSG("gamemainstopschedule");
	this->removeAllChildren();
	Node *dissmiss_result=CSLoader::createNode("res/loading/Layer_dismiss_success.csb");
	addChild(dissmiss_result);
	Sprite *n_dissmiss_result=(Sprite *)dissmiss_result->getChildByName("bg");
	for(int i=0;i<4;i++)
	{
		GamerData *p_palyer_info=GamerDataDeal::getInstance()->getGamerDataBySeat(i);
		String *s=String::createWithFormat("Node_player%d",i+1);
		Node *n_player=n_dissmiss_result->getChildByName(s->getCString());
		//头像
		Sprite *sp_head=(Sprite *)n_player->getChildByName("sp_head");
		BYTE viewid=GetViewID(GamerData::getInstance()->getSeatId(),p_palyer_info->getSeatId());
		std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
		String *s_name=String::createWithFormat("%s%d.png",path.c_str(),p_palyer_info->getUId());
		sp_head->setTexture(s_name->getCString());//保存到本地的别的玩家的头像
		float scale_rate= float(46*1.5)/sp_head->getContentSize().height;
		sp_head->setScale(scale_rate);
		//名字
		Text *name=(Text *)n_player->getChildByName("Text_name");
		name->setString(p_palyer_info->getNick().c_str());
		//id
		Text *id=(Text *)n_player->getChildByName("Text_id_num");
		id->setString(String::createWithFormat("%d",p_palyer_info->getUId())->getCString());
		//钻石数
		Text *tx_zuanshi=(Text *)n_player->getChildByName("Text_zuanshi_num");
		tx_zuanshi->setString(String::createWithFormat("%d",p_palyer_info->getRoomCard())->getCString());

		Text *tx_score=(Text *)n_player->getChildByName("Text_addgold");
		int addscore=p_palyer_info->getGold()-1000;
		tx_score->setString(String::createWithFormat("%d",addscore)->getCString());
		//大赢家
		int bigwinuid=0;
		int index;
		for(int j=0;j<4;j++)
		{
			if(GamerDataDeal::getInstance()->getGamerDataBySeat(j)->getGold()>bigwinuid)
			{
				bigwinuid=GamerDataDeal::getInstance()->getGamerDataBySeat(j)->getGold();
				index=j;
			}
		}
		Sprite *sp_hu=(Sprite *)n_player->getChildByName("sp_ishu");
		if(index==i)
		{
			//sp_hu->setVisible(true);
			//sp_hu->setTexture("loading/icon/datanchuang_50.png");
			sp_hu->setVisible(false);
		}
		else
		{
			sp_hu->setVisible(false);
		}
	}
	bt_share=(Button *)n_dissmiss_result->getChildByName("bt_fenxiang");
	bt_next=(Button *)n_dissmiss_result->getChildByName("bt_continiu");
	MjData::getInstance()->setleftjushu(0);
	bt_next->setTag(1);
	bt_share->addClickEventListener(CC_CALLBACK_0(layer_result::clickbt_share,this));
	bt_next->addClickEventListener(CC_CALLBACK_0(layer_result::clickbt_next,this));
}
void layer_result::clickbt_share()
{
	CCLOG("share111111");
//	MissionWeiXin::getinstance()->cutscreen();
//	MissionWeiXin::getinstance()->shareScreenWeiXin("screenshot.png",0);
	//LobbyView *l_b=LobbyView::create();
	//l_b->showUIWeiXinShare(2);
	//this->addChild(l_b);
	int flag = 0;
	MissionWeiXin::getinstance()->cutscreen(flag);
}
void layer_result::clickbt_next()
{
	if(MjData::getInstance()->getleftjushu()==-1) 
	{
		if(bt_next->getTag()==0)
		{
			//bt_next->setTag(1);
			
			SEND_CUSTOM_MSG("showresult3");
			this->removeFromParent();
		}
		else if(bt_next->getTag()==1)
		{
			//回到大厅4
			layer_result_pk *l_pk=(layer_result_pk *)CCDirector::getInstance()->getRunningScene()->getChildByTag(2001);
			l_pk->removeFromParent();
			GamerData::getInstance()->setStatus(0);
			SEND_CUSTOM_MSG("gamemainexit");
			this->removeFromParent();
		}
	}
	else
	{
		layer_result_pk *l_pk=(layer_result_pk *)CCDirector::getInstance()->getRunningScene()->getChildByTag(2001);
		l_pk->removeFromParent();
		TableCommand::getInstance()->requestready();
		this->removeFromParent();
		
	}
	
}