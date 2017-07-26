#include "Playing_three.h"
#include "controller/login/LoginCommand.h"
#include "GameController.h"
#include "view/Layer/Main/layer_result.h"
#include "model/MjData.h"
#include "view/Layer/Main/GameMain.h"
#include "model/GamerDataDeal.h"
#include "AudioEngine.h"
#include "tool/Tools.h"
#include "view/Layer/Main/layer_dismiss.h"
#include "view/Layer/Tip/TipContent.h"
#include "view/Scene/SceneLoading.h"
#include "platform/JniFun.h"
#include "view/Layer/Main/Layer_result_pk.h"
#include "controller/MainCommand.h"
#define outcard_delaytime 2000.0f
#define  scalefloat 0.7
#define  hight_diamon 40
#define  scale_current_diamond 1
void Playing_three::onEnter()
{
    Layer::onEnter();
    this->_eventDispatcher->addCustomEventListener("playerjointable",CC_CALLBACK_1(Playing_three::joinTable,this));

    this->_eventDispatcher->addCustomEventListener("playerleavetablebroadcast",CC_CALLBACK_1(Playing_three::leaveTableBroadcast,this));
    this->_eventDispatcher->addCustomEventListener("PlayingBroadcast_BuHua",CC_CALLBACK_1(Playing_three::buHuaBroadcast,this));
    this->_eventDispatcher->addCustomEventListener("playing_btn_chooseCard",CC_CALLBACK_1(Playing_three::selectCard,this));
    this->_eventDispatcher->addCustomEventListener("playerout",CC_CALLBACK_1(Playing_three::outCard,this));
    this->_eventDispatcher->addCustomEventListener("realoutcard",CC_CALLBACK_1(Playing_three::outcardformserver,this));
    this->_eventDispatcher->addCustomEventListener("getsiglecardbroadcast",CC_CALLBACK_1(Playing_three::systemgetsiglecardbroadcast,this));
    this->_eventDispatcher->addCustomEventListener("operateaskbroadcast",CC_CALLBACK_1(Playing_three::responseoperate,this));
    this->_eventDispatcher->addCustomEventListener("operatesuccess",CC_CALLBACK_1(Playing_three::resultofoperate,this));
    this->_eventDispatcher->addCustomEventListener("operatesuccessbroadcast",CC_CALLBACK_1(Playing_three::responseoperatebroadcast,this));
    this->_eventDispatcher->addCustomEventListener("responseminglouask",CC_CALLBACK_1(Playing_three::responseminglouask,this));
    this->_eventDispatcher->addCustomEventListener("responsemingloubroadcast",CC_CALLBACK_1(Playing_three::responsemingloubroadcast,this));
    this->_eventDispatcher->addCustomEventListener("responseoneroundendbroadcast",CC_CALLBACK_1(Playing_three::responseonroundendbroadcast,this));
    this->_eventDispatcher->addCustomEventListener("responsebreakbackbroadcast",CC_CALLBACK_1(Playing_three::responsebreakbackbroadcast,this));
    this->_eventDispatcher->addCustomEventListener("playerreconnect",CC_CALLBACK_1(Playing_three::responsereconnect,this));
    this->_eventDispatcher->addCustomEventListener("playing_broadcast_outCard",CC_CALLBACK_1(Playing_three::outCardBroadcast,this));
    this->_eventDispatcher->addCustomEventListener("responsedismissask",CC_CALLBACK_1(Playing_three::dismissAskBroadcast,this));
    this->_eventDispatcher->addCustomEventListener("responseplayeffect",CC_CALLBACK_1(Playing_three::responsepalyeffect,this));
	this->_eventDispatcher->addCustomEventListener("chat",CC_CALLBACK_1(Playing_three::responsechatbroadcast,this));
	this->_eventDispatcher->addCustomEventListener("customchat",CC_CALLBACK_1(Playing_three::responsecustomchatbroadcast,this));
	this->_eventDispatcher->addCustomEventListener("responsedismisssuccessbroadcast",CC_CALLBACK_1(Playing_three::dismisssuccessbroadcast,this));
	this->_eventDispatcher->addCustomEventListener("responsebreakbroadcast",CC_CALLBACK_1(Playing_three::responsebreakbroadcast,this));
	this->_eventDispatcher->addCustomEventListener("responsereadybroadcast",CC_CALLBACK_1(Playing_three::responsereadybroadcast,this));
	this->_eventDispatcher->addCustomEventListener("responseready",CC_CALLBACK_1(Playing_three::responseready,this));
	this->_eventDispatcher->addCustomEventListener("responsegetplayerinfo",CC_CALLBACK_1(Playing_three::responsegetplayerinfo,this));
	this->_eventDispatcher->addCustomEventListener("loseconnect",CC_CALLBACK_1(Playing_three::losconnect,this));
	this->_eventDispatcher->addCustomEventListener("responsegetresulttotal",CC_CALLBACK_1(Playing_three::addresulttotal,this));
	this->_eventDispatcher->addCustomEventListener("showresult3",CC_CALLBACK_1(Playing_three::showresult3,this));
	
    this->_eventDispatcher->addCustomEventListener("restartbyconfirm",CC_CALLBACK_1(Playing_three::restartbyLoseConfirm,this));

	this->_eventDispatcher->addCustomEventListener("responseresultpk",CC_CALLBACK_1(Playing_three::responsepkbroadcast,this));
	this->_eventDispatcher->addCustomEventListener("showresultpk",CC_CALLBACK_1(Playing_three::responseshowpk,this));

	this->_eventDispatcher->addCustomEventListener("dingqueaskbroadcast",CC_CALLBACK_1(Playing_three::responseaskdingquebroadcast,this));
	//this->_eventDispatcher->addCustomEventListener("showresultpk",CC_CALLBACK_1(Playing_three::responsedingqueanser,this));
	this->_eventDispatcher->addCustomEventListener("userdingquebroadcast",CC_CALLBACK_1(Playing_three::responseanserBroadcast,this));
	this->_eventDispatcher->addCustomEventListener("mydingquesuccess",CC_CALLBACK_1(Playing_three::mydingquesuccess,this));
	mj_isSelectedMj = false;
    mj_selectedMj = nullptr;
    isminglou_ing=false;
    isminglou_over=false;
    m_left_card_cnt = 0;//0121

	isOutCarding=false;
	outcardingId=-1;
	iscanchupai=false;//是否能出牌
	dingqueshu=0;
	Tools::stopallbgmusic();
    Tools::playBackMusic("yxyy.mp3");
}

void Playing_three::onExit()
{
    Tools::stopallbgmusic();
	Tools::playBackMusic("dlyy.mp3");
    this->_eventDispatcher->removeCustomEventListeners("playerjointable");
    this->_eventDispatcher->removeCustomEventListeners("playerleavetablebroadcast");
    this->_eventDispatcher->removeCustomEventListeners("PlayingBroadcast_BuHua");
    this->_eventDispatcher->removeCustomEventListeners("playing_btn_chooseCard");
    this->_eventDispatcher->removeCustomEventListeners("playerout");
    this->_eventDispatcher->removeCustomEventListeners("realoutcard");
    this->_eventDispatcher->removeCustomEventListeners("getsiglecardbroadcast");
    this->_eventDispatcher->removeCustomEventListeners("operateaskbroadcast");
    this->_eventDispatcher->removeCustomEventListeners("operatesuccess");
    this->_eventDispatcher->removeCustomEventListeners("operatesuccessbroadcast");
    this->_eventDispatcher->removeCustomEventListeners("responseminglouask");
    this->_eventDispatcher->removeCustomEventListeners("responsemingloubroadcast");
    this->_eventDispatcher->removeCustomEventListeners("responseoneroundendbroadcast");
    this->_eventDispatcher->removeCustomEventListeners("responsebreakbackbroadcast");
    this->_eventDispatcher->removeCustomEventListeners("playerreconnect");
    this->_eventDispatcher->removeCustomEventListeners("playing_broadcast_outCard");
    this->_eventDispatcher->removeCustomEventListeners("responsedismissask");
    this->_eventDispatcher->removeCustomEventListeners("responseplayeffect");
	this->_eventDispatcher->removeCustomEventListeners("chat");
	this->_eventDispatcher->removeCustomEventListeners("customchat");
	this->_eventDispatcher->removeCustomEventListeners("responsedismisssuccessbroadcast");
	this->_eventDispatcher->removeCustomEventListeners("responsebreakbroadcast");
	this->_eventDispatcher->removeCustomEventListeners("responsereadybroadcast");
	this->_eventDispatcher->removeCustomEventListeners("responsegetplayerinfo");
	this->_eventDispatcher->removeCustomEventListeners("responseready");
	this->_eventDispatcher->removeCustomEventListeners("responsegetresulttotal");
	this->_eventDispatcher->removeCustomEventListeners("showresult3");
	this->_eventDispatcher->removeCustomEventListeners("loseconnect");
	this->_eventDispatcher->removeCustomEventListeners("restartbyconfirm");
	this->_eventDispatcher->removeCustomEventListeners("responseresultpk");
	this->_eventDispatcher->removeCustomEventListeners("showresultpk");
	this->_eventDispatcher->removeCustomEventListeners("dingqueaskbroadcast");
	this->_eventDispatcher->removeCustomEventListeners("userdingquebroadcast");
	this->_eventDispatcher->removeCustomEventListeners("mydingquesuccess");
    Layer::onExit();
}
void Playing_three::responseaskdingquebroadcast(EventCustom *evt)
{
	Node *n_action_dingque=nodeCards[0]->getChildByName("node_actions_dingque");
	for(int i=0;i<3;i++)
	{
		String *str_que=String::createWithFormat("action_%d",i+1);
		Button *bt_ding=(Button *)n_action_dingque->getChildByName(str_que->getCString());
		bt_ding->setVisible(true);
	    bt_ding->addClickEventListener(CC_CALLBACK_0(Playing_three::clickdingquecallback,this,i+1));
	}

}
void Playing_three::mydingquesuccess(EventCustom *evt)
{
	Node *n_action_dingque=nodeCards[0]->getChildByName("node_actions_dingque");
	for(int i=0;i<3;i++)
	{
		String *str_que=String::createWithFormat("action_%d",i+1);
		Button *bt_ding=(Button *)n_action_dingque->getChildByName(str_que->getCString());
		bt_ding->setVisible(false);
		bt_ding->setEnabled(false);
	}
}
void Playing_three::clickdingquecallback(int que_num)
{
	TableCommand::getInstance()->requestdingque(que_num);
}
void Playing_three::responseanserBroadcast(EventCustom *evt)
{
	GS2C_DingQueBroadcast  *join=(GS2C_DingQueBroadcast  *)evt->getUserData();
	int error=join->errorcode();
	if(error==0)
	{
		int uid=join->uid();
		int que_mm=join->quemen();
		GamerData *g_user=GamerDataDeal::getInstance()->getGamerData(uid);
		int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uid)->getSeatId());
		g_user->setquedemen(que_mm);
		dingqueshu++;
		if(viewid==0)
		{
			GamerData::getInstance()->setquedemen(que_mm);
			//这里要把我缺的那一门给放到外边并且不缺的要置灰 且 不可以操作
		    refreshMjsPos();
			refreshdingque(que_mm,viewid);
		}
		else
		{
			refreshdingque(que_mm,viewid);
		}
		if(dingqueshu==3)
		{
			for(int i=0;i<3;i++)
			{
				refreshdingque(GamerDataDeal::getInstance()->getGamerDataBySeat(i)->getquedemen(),i);
			}
			dingqueshu=0;
		}
	}
}


void Playing_three::restartbyLoseConfirm(EventCustom *evt)
{
	restarapp_main(0);
}
void Playing_three::responseshowpk(EventCustom *evt)
{
	layer_result_pk *l_end=(layer_result_pk *)CCDirector::getInstance()->getRunningScene()->getChildByTag(2001);
	l_end->setVisible(true);
	l_end->setZOrder(10000);
}
void Playing_three::showresult3(EventCustom *evt)
{
	layer_result_end *l_end=(layer_result_end *)CCDirector::getInstance()->getRunningScene()->getChildByTag(199);
	l_end->setVisible(true);
	l_end->setZOrder(10000);
}
void Playing_three::addresulttotal(EventCustom* evt)
{
    //关闭心跳检测
	SEND_CUSTOM_MSG("stopHerat");

	//解析数据
	GS2C_ResultTotalBroadcast    * outcard = (GS2C_ResultTotalBroadcast   *) evt->getUserData();
	::google::protobuf::RepeatedPtrField< ::pb::ResultTotalItem > cards=outcard->result_list();

	result_total_all r_s;
	std::vector<result_total> arr_result_total;
	for(int i=0;i<cards.size();i++)
	{
		ResultTotalItem r_t=cards.Get(i);
		
		result_total r_i_one;	
		r_i_one.total_uid=r_t.uid();
		r_i_one.total_fen=r_t.total_fen();

		for(int j=0;j<r_t.score_round().size();j++)
		{
			int score_perround=r_t.score_round().Get(j);
			r_i_one.arr_fen_perround.push_back(score_perround);
		}
		arr_result_total.push_back(r_i_one);
	}
	r_s.arr_total_all=arr_result_total;
	layer_result_end* layer_end=layer_result_end::create();
	layer_end->setTag(199);
	CCDirector::getInstance()->getRunningScene()->addChild(layer_end,-1);
	layer_end->initwithdata(r_s);
	UserDefault::getInstance()->setBoolForKey("iscanbreak",false);
	if(diamisssuccess==2)
	{

		layer_end->setVisible(true);
		layer_end->setZOrder(10000);
	}
	else
	{
		layer_end->setVisible(false);
	}
	
}
void Playing_three::responsebreakbroadcast(EventCustom *evt)
{
	 GS2C_BreakBroadcast  *join=(GS2C_BreakBroadcast  *)evt->getUserData();
	 int error=join->errorcode();
	 if(error==0)
	 {
		 int uid=join->uid();
		 int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uid)->getSeatId());
		 Sprite *isonline=(Sprite *) nodePlayers[viewid]->getChildByName("isOnline");
		 isonline->setVisible(true);
         if( GamerDataDeal::getInstance()->getGamerData(uid)->getStatus()==6)
         {
             nodePlayers[viewid]->getChildByName("icon_ready")->setVisible(false);
         }
		 GamerDataDeal::getInstance()->getGamerData(uid)->setStatus(3);

		 if(uid==GamerData::getInstance()->getUId())//离线的是我本人
		 {
			 tp_lose->setVisible(true);
			 tp_lose->setZOrder(10000);
		 }
	 }
}
void Playing_three::responsepkbroadcast(EventCustom *evt)
{
	
	arr_pklist arr_pk;
	GS2C_ResultPKBroadcast *g_pk=(GS2C_ResultPKBroadcast*)evt->getUserData();  
	int err=g_pk->errorcode();
	std::vector<pKlist>arr_list;
	for(int i=0;i<g_pk->pk_list().size();i++)
	{
		pKlist pk;
		ResultPKItem re_item=(ResultPKItem)g_pk->pk_list().Get(i);
		pk.uid=re_item.uid();
		for(int j=0;j<re_item.pk_score_round().size();j++)
		{
			pk.arr_perround_score.push_back(re_item.pk_score_round().Get(j));
		}
		arr_list.push_back(pk);
	}
	arr_pk.arrpklist=arr_list;
	layer_result_pk *l_pp=(layer_result_pk *)CCDirector::getInstance()->getRunningScene()->getChildByTag(2001);
	if(l_pp!=nullptr)
	{
		l_pp->removeFromParent();
	}
	layer_result_pk *l_pk=layer_result_pk::create();
	l_pk->initwithdata(arr_pk);
	l_pk->setVisible(false);
	l_pk->setTag(2001);
	CCDirector::getInstance()->getRunningScene()->addChild(l_pk,-1);
	
}
void Playing_three::restarapp_main(float dt)
{
	MainCommand::getInstance()->lenDeque.clear();
	MainCommand::getInstance()->msgDeque.clear();
	MainCommand::getInstance()->opcodeDeque.clear();
	SocketUtil::getInstance()->m_map.clear();
	auto loadingScene = SceneLoading::createScene();
	CCDirector::getInstance()->replaceScene(loadingScene);

}
void Playing_three::losconnect(EventCustom *evt)
{

	tp_lose->setVisible(true);
	tp_lose->setZOrder(10000);
}
void Playing_three::responsereconnect(EventCustom *evt)
{
    m_mjList.clear();
    m_players_chengxing_mjs[0].clear();
    m_players_chengxing_mjs[1].clear();
    m_players_chengxing_mjs[2].clear();
    m_players_chengxing_mjs[3].clear();
    m_arr_players_mjs[0].clear();
    m_arr_players_mjs[1].clear();
    m_arr_players_mjs[2].clear();
    m_arr_players_mjs[3].clear();

	arr_jipai[0].clear();
	arr_jipai[1].clear();
	arr_jipai[2].clear();
	arr_jipai[3].clear();


	UserDefault::getInstance()->setBoolForKey("iscanoperatecard",false);

    //解析数据出来
    GS2C_JoinTable *join=(GS2C_JoinTable *)evt->getUserData();
    ReconnectItem reconnet=join->reconnect();
	int bankerid=join->banker_uid();
	GamerData *g_banker=GamerDataDeal::getInstance()->getGamerData(bankerid);
	int bankerviewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(bankerid)->getSeatId());

	//重连回来 看看是否正在解散房间
	bool isjiesan=false;
	int uid_dissmiss;
	for(int i=0;i<reconnet.user_dismiss_status().size();i++)
	{
		if(reconnet.user_dismiss_status().Get(i)!=0)
		{
			isjiesan=true;
		}
		if(reconnet.user_dismiss_status().Get(i)==4)
		{
			uid_dissmiss=GamerDataDeal::getInstance()->getGamerDataBySeat(i)->getUId();
		}
	}
	if(isjiesan)
	{
		layer_dismiss *l_d=layer_dismiss::create();
		l_d->initwithaskuid(uid_dissmiss);
		this->getParent()->addChild(l_d,10);

		for(int i=0;i<reconnet.user_dismiss_status().size();i++)
		{
			if(reconnet.user_dismiss_status().Get(i)!=4&&reconnet.user_dismiss_status().Get(i)!=0&&reconnet.user_dismiss_status().Get(i)!=1)
			{
				if(reconnet.user_dismiss_status().Get(i)==2)
				{
					l_d->changestatebyuid(GamerDataDeal::getInstance()->getGamerDataBySeat(i)->getUId(),1);
				}
				else if(reconnet.user_dismiss_status().Get(i)==1)
				{
					l_d->changestatebyuid(GamerDataDeal::getInstance()->getGamerDataBySeat(i)->getUId(),0);
				}
				if(i==0)//我自己选择了
				{
					l_d->bt_agree->setVisible(false);
					l_d->bt_agree->setEnabled(false);
					l_d->bt_disagree->setVisible(false);
					l_d->bt_disagree->setEnabled(false);
				}
			}
		}
	}
    //自己手中扑克
    for(int i=0;i<reconnet.hand_cards().size();i++)
    {
        MjNode *p=MjNode::create();
        p->setAnchorPoint(Vec2(0.5,0.5));
        p->initBtnWithId(reconnet.hand_cards().Get(i));
        nodeCards[0]->getChildByName("nodeCards")->addChild(p);
        m_mjList.pushBack(p);
    }
	for(int i=0;i<reconnet.quemen().size();i++)
	{
		int quedemen=reconnet.quemen().Get(i);
		GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(i);
		g->setquedemen(quedemen);
		if(g->getUId()==GamerData::getInstance()->getUId())
		{
			GamerData::getInstance()->setquedemen(quedemen);
		}
		if(reconnet.quemen().Get(i)!=0)
		{
			dingqueshu++;
		}
		//refreshdingque(g->getquedemen(),i);
	}
	for(int i=0;i<3;i++)
	{
		refreshdingque(GamerDataDeal::getInstance()->getGamerDataBySeat(i)->getquedemen(),i);
	}
	
    refreshMjsPos();

   nodeCards[0]->setVisible(true);
   nodeCards[1]->setVisible(true);
   nodeCards[2]->setVisible(true);
 //  nodeCards[3]->setVisible(true);

    //所有玩家手牌数组
    for(int i=0;i<reconnet.hand_cnts().size();i++)
    {
        hands_cnt[i]=reconnet.hand_cnts().Get(i);
    }
	
    for(int i=0;i<reconnet.weaves1().size();i++)
    {
        operate_result o_r;
        WeaveItem w1=reconnet.weaves1().Get(i);
        o_r.card_id=w1.card_id();
        o_r.operate_code=w1.weave_kind();
		m_players_chengxing_mjs[0].push_back(o_r);
    }

    refreshxingpaipos(m_players_chengxing_mjs[0],nodeCards[0]->getChildByName("node_chengxing_cards"));


	for(int i=0;i<reconnet.weaves2().size();i++)
	{
		operate_result o_r;
		WeaveItem w1=reconnet.weaves2().Get(i);
		o_r.card_id=w1.card_id();
		o_r.operate_code=w1.weave_kind();
		m_players_chengxing_mjs[1].push_back(o_r);
	}

	refreshxingpaiposofothers(m_players_chengxing_mjs[1],nodeCards[1]->getChildByName("node_chengxing_cards"),1,0);

	for(int i=0;i<reconnet.weaves3().size();i++)
	{
		operate_result o_r;
		WeaveItem w1=reconnet.weaves3().Get(i);
		o_r.card_id=w1.card_id();
		o_r.operate_code=w1.weave_kind();
		m_players_chengxing_mjs[2].push_back(o_r);
	}

	refreshxingpaiposofothers(m_players_chengxing_mjs[2],nodeCards[2]->getChildByName("node_chengxing_cards"),2,0);

	for(int i=0;i<reconnet.weaves4().size();i++)
	{
		operate_result o_r;
		WeaveItem w1=reconnet.weaves4().Get(i);
		o_r.card_id=w1.card_id();
		o_r.operate_code=w1.weave_kind();
		m_players_chengxing_mjs[3].push_back(o_r);
	}

	//refreshxingpaiposofothers(m_players_chengxing_mjs[3],nodeCards[3]->getChildByName("node_chengxing_cards"),3,0);

    for(int i=0;i<reconnet.dismiss_cards_1().size();i++)
    {
        m_arr_players_mjs[0].push_back(reconnet.dismiss_cards_1().Get(i));
    }
	refreshoutcardByViewId(0);
   
    for(int i=0;i<reconnet.dismiss_cards_2().size();i++)
    {
        m_arr_players_mjs[1].push_back(reconnet.dismiss_cards_2().Get(i));
    }
    refreshoutcardByViewId(1);

    
	for(int i=0;i<reconnet.dismiss_cards_3().size();i++)
	{
		m_arr_players_mjs[2].push_back(reconnet.dismiss_cards_3().Get(i));
	}
	refreshoutcardByViewId(2);

	for(int i=0;i<reconnet.dismiss_cards_4().size();i++)
	{
		m_arr_players_mjs[3].push_back(reconnet.dismiss_cards_4().Get(i));
	}
	//refreshoutcardByViewId(3);
    
	for(int i=0;i<reconnet.ji_types().size();i++)
	{
		CCLOG("%d",reconnet.ji_types().Get(i));
		GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(i);
		g->setJi_type(reconnet.ji_types().Get(i));
	}
	for(int i=0;i<reconnet.ji_cnts().size();i++)
	{
       int jinum=reconnet.ji_cnts().Get(i);
	   CCLOG("%d",jinum);
	   for(int j=0;j<jinum;j++)
	   {
		   arr_jipai[i].push_back(0);
	   }
	   GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(i);
	   
	   if(g->getJi_type()==1)
	   {
		   arr_jipai[i].at(0)=1;
	   }
	}
	
	for(int i=0;i<3;i++)
	{
		refreshjipaiOfPlayer(i);
	}
	for(int i=0;i<reconnet.is_tingpais().size();i++)
	{
		GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(i);
		if(g->getUId()==GamerData::getInstance()->getUId())
		{
			if(reconnet.is_tingpais().Get(i)==1)
			{
				Sprite *sp_icon_ting=(Sprite *)nodePlayers[i]->getChildByName("icon_tingpai");
				sp_icon_ting->setVisible(true);
				isminglou_over=true;
				for(int j=0;j<m_mjList.size();j++)
				{
					m_mjList.at(j)->setstatecantoperate(false);
				}
			}
		}
		else
		{
			if(reconnet.is_tingpais().Get(i)==1)
			{
				Sprite *sp_icon_ting=(Sprite *)nodePlayers[i]->getChildByName("icon_tingpai");
				sp_icon_ting->setVisible(true);
			}
		}
	}
	MjData::getInstance()->setleftcards(reconnet.left_card_cnt());

    auto controlLayer = (GameController *)(this->getParent()->getChildByName("mj_controller"));

    if (reconnet.current_uid()==255 || reconnet.current_uid()==0)
    {
		controlLayer->setArrowRoatation(bankerviewid);
        controlLayer->setArrowDirection(2);
    } 
    else
    {
        GamerData *pCurrent=GamerDataDeal::getInstance()->getGamerData(reconnet.current_uid());
        BYTE viewId = GetViewID(GamerData::getInstance()->getSeatId(),pCurrent->getSeatId());
		controlLayer->setArrowRoatation(bankerviewid);
        controlLayer->setArrowDirection(viewId);
    }


  
    GameMain *g_m=(GameMain *)this->getParent();

    g_m->mj_controller->startGame_gameController(reconnet.left_card_cnt(),reconnet.left_round());
	
	MjData::getInstance()->setleftjushu(reconnet.left_round());
   

  

    
    std::vector<int >arr_act;
    for(int i=0;i<reconnet.actions().size();i++)
    {
        arr_act.push_back(reconnet.actions().Get(i));
    }

    
    for (int i = 0; i < 3; i++)
    {
        
        auto nodePlayer = (Node*)nodePlayers[i];
		Sprite *sp_ischongfengji=(Sprite *)nodePlayer->getChildByName("icon_chongfengji");
		GamerData *g_m=GamerDataDeal::getInstance()->getGamerDataBySeat(i);
		if(g_m->getJi_type()==2)
		{
			sp_ischongfengji->setVisible(true);
			sp_ischongfengji->setTexture("res/srcRes/icon_ze.png");
		}
		else if(g_m->getJi_type()==1)
		{
			sp_ischongfengji->setVisible(true);
			sp_ischongfengji->setTexture("res/loading/play/icon_chong.png");
		}
		if(g_m->getStatus()==5||g_m->getStatus()==6)
		{
			nodePlayer->setPosition(posWait_three[i]);
			if(g_m->getStatus()==5)
			{
				Sprite *icon_ready=(Sprite*)nodePlayers[i]->getChildByName("icon_ready");
				icon_ready->setVisible(false);
				if(g_m->getUId()==GamerData::getInstance()->getUId())//是我本人就请求准备
				{
					TableCommand::getInstance()->requestready();
				}
			}
			else if(g_m->getStatus()==6)
			{
				Sprite *icon_ready=(Sprite*)nodePlayers[i]->getChildByName("icon_ready");
				icon_ready->setVisible(true);
			}
		}
		else
		{
			nodePlayer->setPosition(posGame_three[i]);
			if(g_m->getStatus()==3)
			{
				Sprite *sp_isonline=(Sprite *)nodePlayers[i]->getChildByName("isOnline");
				sp_isonline->setVisible(true);
			}
		}
        auto nodeCard = (Node*)nodeCards[i];
        Sprite *i_out=(Sprite *)nodeCard->getChildByName("node_outcard")->getChildByName("mj_bg_poker_out");
        i_out->setVisible(false);
    } 
	
}
void Playing_three::playluxiang_player(std::vector<playluxiang> arr_luxiang)
{
    arr_luxiang_data=arr_luxiang;
	right_ji_num_luxiang=0;
    initplayer();
    for(int i=0;i<3;i++)
    {
        nextstep(0);
		ji_num_players_luxiang[i]=0;
    }
    nextstep(0);
    for(int i=0;i<3;i++)
    {
        refreshshoupaifromluxiang(i);
        refreshchupaifromluxiang(i);
        refreshxingpaifromluxiang(i);
        refreshjipaifromluxiang(i);
    }
    refreshzhishifromluxiang(0);
}
void Playing_three::refreshminglou(int viewid)
{
   
}
void Playing_three::mingloufromluxiang(playluxiang p)
{
   

}
void Playing_three::dispathercardsfromluxing(playluxiang p)
{
    std::vector<int >arr_cards=p.cardid;
    int uerid=p.actionuerid;
    int cardlen=p.cardlen;
    int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uerid)->getSeatId());
    Node *n_shou=arr_shoupai_luxiang[viewid];
    for(int i=0;i<14;i++)
    {
        String *s_name=String::createWithFormat("mj_%d",i+1);
        Sprite *mj=(Sprite *)n_shou->getChildByName(s_name->getCString());
        Sprite *hua=(Sprite *)mj->getChildByName("mj_huase");

        if(i<cardlen)
        {
            int cardid=arr_cards[i];
            int vale=cardid/16*10+cardid%16;
            mj->setTag(cardid);
            String *path=String::createWithFormat("res/cards/mj_%d.png",vale);
            hua->setTexture(path->getCString());
            arr_shoupai[viewid].push_back(cardid);
        }
        else
        {
            mj->setVisible(false);
        }
    }
	refreshshoupaifromluxiang(viewid);
    arr_luxiang_data.erase(arr_luxiang_data.begin());
}
void Playing_three::refreshjipaifromluxiang(int viewid)
{
	Node *n_ji=arr_jipai_luxiang[viewid];

	for(int i=0;i<4;i++)
	{
		String *ji_path=String::createWithFormat("mj_bg_%d",i+1);
		Sprite *ji=(Sprite *)n_ji->getChildByName(ji_path->getCString());
		ji->setVisible(false);
	}
	GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(viewid);
	if(g->getJi_type()==1)
	{
		for(int i=0;i<ji_num_players_luxiang[viewid];i++)
		{
			String *ji_path=String::createWithFormat("mj_bg_%d",i+1);
			Sprite *ji=(Sprite *)n_ji->getChildByName(ji_path->getCString());
			ji->setVisible(true);
			Sprite *ji_texture=(Sprite *)ji->getChildByName("mj_value");
			ji_texture->setTexture("res/cards/mj_11.png");
		}
	}
	else
	{
		for(int i=0;i<ji_num_players_luxiang[viewid];i++)
		{
			String *ji_path=String::createWithFormat("mj_bg_%d",i+2);
			Sprite *ji=(Sprite *)n_ji->getChildByName(ji_path->getCString());
			ji->setVisible(true);
			Sprite *ji_texture=(Sprite *)ji->getChildByName("mj_value");
			ji_texture->setTexture("res/cards/mj_11.png");
		}
	}
}
void Playing_three::chupaifomluxiang(playluxiang p)
{
    int uid=p.actionuerid;
    int cardlen=p.cardlen;
    std::vector<int >arr_cards=p.cardid;
   
    int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uid)->getSeatId());
    int logicvale;
    for(int i=0;i<arr_shoupai[viewid].size();i++)
    {
        if(arr_shoupai[viewid].at(i)==p.cardid[0])
        {
            //找到出的牌 剔除数组 加入出牌数组
			if(p.cardid[0]==17)//这是张 鸡牌
			{
				if(right_ji_num_luxiang==0)//这是 冲锋鸡
				{
					//放冲锋鸡动画
					GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(viewid);
					g->setJi_type(1);
					Sprite *hua=(Sprite *)arr_node_actions[viewid]->getChildByName("action_detail");
					hua->setTexture("res/srcRes/12.png");
					CallFunc *visible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,hua,true));
					DelayTime *de=DelayTime::create(0.5*luxiang_rate);
					CallFunc *invisible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,hua,false));
					CallFunc *nextstep=CallFunc::create(CC_CALLBACK_0(Playing_three::updateactions,this,0));
					Sequence *se=Sequence::create(visible,de,invisible,nextstep,nullptr);
					hua->runAction(se);
				}
				ji_num_players_luxiang[viewid]++;
				refreshjipaifromluxiang(viewid);
				right_ji_num_luxiang++;
			}
			else
			{
				arr_outcard[viewid].push_back(arr_shoupai[viewid].at(i));
			}
			
			logicvale=arr_shoupai[viewid].at(i);
			arr_shoupai[viewid].erase(arr_shoupai[viewid].begin()+i);
            break;
        }
    }
    //刷新手牌
    refreshshoupaifromluxiang(viewid);

    //做动画 出牌动画 ，做完动画 刷新出牌界面 进行下一步骤
    //拿到出牌精灵
	if(p.cardid[0]!=17)
	{
		Node *action_out_node=arr_node_actions[viewid];
		Sprite *sp_mj_out=(Sprite *)action_out_node->getChildByName("outcard");
		Sprite *huase_outcard=(Sprite *)sp_mj_out->getChildByName("huase");
		int vale=logicvale/16*10+logicvale%16;
		String *path=String::createWithFormat("res/cards/mj_%d.png",vale);
		huase_outcard->setTexture(path->getCString());

		//找到运动结束的位置
		String *end_pos_path=String::createWithFormat("mj_%d",arr_outcard[viewid].size());
		Sprite *sp_end=(Sprite *)arr_outcard_luxiang[viewid]->getChildByName(end_pos_path->getCString());
		Vec2 v=sp_mj_out->getParent()->convertToNodeSpace(sp_end->getParent()->convertToWorldSpace(sp_end->getPosition()));
		CallFunc *isvisible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,sp_mj_out,true));
		CallFunc *invisible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,sp_mj_out,false));
		float scalede=sp_mj_out->getScale();
		Vec2 v_origin=sp_mj_out->getPosition();
		ScaleTo *st=ScaleTo::create(0.5*luxiang_rate,0.3);
		MoveTo *mt=MoveTo::create(0.5*luxiang_rate,v);
		Spawn *spw=Spawn::create(st,mt,nullptr);
		MoveTo *mt1=MoveTo::create(0,v_origin);
		ScaleTo *st_or=ScaleTo::create(0,scalede);
		CallFunc *refreshout=CallFunc::create(CC_CALLBACK_0(Playing_three::refreshchupaifromluxiang,this,viewid));
		CallFunc *nextstep=CallFunc::create(CC_CALLBACK_0(Playing_three::updateactions,this,0));
		Sequence *se=Sequence::create(isvisible,spw,invisible,mt1,st_or,refreshout,nextstep,nullptr);
		sp_mj_out->runAction(se);
	}
    arr_luxiang_data.erase(arr_luxiang_data.begin());

}
void Playing_three::refreshchupaifromluxiang(int viewid)
{
    Node *n_out=arr_outcard_luxiang[viewid];
    for(int i=0;i<24;i++)
    {
        String *name=String::createWithFormat("mj_%d",i+1);
        Sprite *sp_mj=(Sprite *)n_out->getChildByName(name->getCString());
        Sprite *huase=(Sprite *)sp_mj->getChildByName("mj_huase");
        if(i<arr_outcard[viewid].size())
        {
            sp_mj->setVisible(true);
            int vale=arr_outcard[viewid].at(i)/16*10+arr_outcard[viewid].at(i)%16;
            String *path=String::createWithFormat("res/cards/mj_%d.png",vale);
            huase->setTexture(path->getCString());
        }
        else
        {
            sp_mj->setVisible(false);
        }
    }
}
void Playing_three::refreshshoupaifromluxiang(int viewid)
{
    std::sort(arr_shoupai[viewid].begin(), arr_shoupai[viewid].end(), [](int a,int b){
         return a > b;
    });
    Node *n_shou=arr_shoupai_luxiang[viewid];
    for(int i=0;i<14;i++)
    {
        String *s_name=String::createWithFormat("mj_%d",i+1);
        Sprite *mj=(Sprite *)n_shou->getChildByName(s_name->getCString());
        Sprite *hua=(Sprite *)mj->getChildByName("mj_huase");

        if(i<arr_shoupai[viewid].size())
        {
			mj->setVisible(true);
            int cardid=arr_shoupai[viewid].at(i);
            int vale=cardid/16*10+cardid%16;
            mj->setTag(cardid);
            String *path=String::createWithFormat("res/cards/mj_%d.png",vale);
            hua->setTexture(path->getCString());
        }
        else
        {
            mj->setVisible(false);
        }
    }
}
int Playing_three::getlogicvalue(int a)
{
    return a/16*10+a%16;
}
void Playing_three::mopaifromluxiang(playluxiang p)
{
    int card=p.cardid[0];
    int actionid=p.actionuerid;
    int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(actionid)->getSeatId());
    arr_shoupai[viewid].push_back(card);
	int value_=getlogicvalue(p.cardid[0]);

    refreshshoupaifromluxiang(viewid);

    arr_luxiang_data.erase(arr_luxiang_data.begin());
    updateactions(0);
}
void Playing_three::buhuafromluxiang(playluxiang p)
{
    int cardlen=p.cardlen;
    int uerid=p.actionuerid;
    int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uerid)->getSeatId());

    Sprite *hua=(Sprite *)arr_node_actions[viewid]->getChildByName("action_detail");
    hua->setTexture("res/srcRes/14.png");

    CallFunc *visible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,hua,true));
    DelayTime *de=DelayTime::create(0.5*luxiang_rate);
    CallFunc *invisible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,hua,false));
    CallFunc *nextstep=CallFunc::create(CC_CALLBACK_0(Playing_three::updateactions,this,0));
    Sequence *se=Sequence::create(visible,de,invisible,nextstep,nullptr);
    hua->runAction(se);
    arr_luxiang_data.erase(arr_luxiang_data.begin());
}
void Playing_three::leftchifromluxiang(playluxiang p)
{
    int userid=p.actionuerid;
    int provide=p.provideuserid;
    int cardlen=p.cardlen;
    int actionkind=p.actionkind;
    std::vector<int >arr_cards=p.cardid;
    int card_chi=arr_cards[0];
    int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(userid)->getSeatId());
    int provideviewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(provide)->getSeatId());

	int  num_removefromshoupai;
	if(actionkind==12||actionkind==13||actionkind==14||actionkind==5)//碰
	{
		num_removefromshoupai=2;
		//加入到型牌
		xingpai_luxiang x_l;
		x_l.cardid=card_chi;
		x_l.operatecode=actionkind;
		arr_xingpai[viewid].push_back(x_l);
	}
	else if(actionkind==6||actionkind==7||actionkind==8)
	{
		num_removefromshoupai=3;
		//加入到型牌
		xingpai_luxiang x_l;
		x_l.cardid=card_chi;
		x_l.operatecode=actionkind;
		arr_xingpai[viewid].push_back(x_l);
	}
	else if(actionkind==9)
	{
		num_removefromshoupai=1;
		//加入到型牌
		for(int i=0;i<arr_xingpai[viewid].size();i++)
		{
			if(arr_xingpai[viewid].at(i).cardid==card_chi)//型牌中 有这张牌
			{
				arr_xingpai[viewid].at(i).operatecode=9;
				break;
			}
		}
	}
	else if(actionkind==10)
	{
		num_removefromshoupai=4;
		//加入到型牌
		xingpai_luxiang x_l;
		x_l.cardid=card_chi;
		x_l.operatecode=actionkind;
		arr_xingpai[viewid].push_back(x_l);
	}
	refreshxingpaifromluxiang(viewid);

	if(card_chi==17)//鸡牌
	{
		if(right_ji_num_luxiang==1)//冲锋鸡被捧走了
		{
			//放责任鸡动画
			ji_num_players_luxiang[provideviewid]=0;//没有鸡了
			Sprite *hua=(Sprite *)arr_node_actions[provideviewid]->getChildByName("action_detail");
			hua->setTexture("res/srcRes/13.png");
			CallFunc *visible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,hua,true));
			DelayTime *de=DelayTime::create(0.5*luxiang_rate);
			CallFunc *invisible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,hua,false));
			Sequence *se=Sequence::create(visible,de,invisible,nullptr);
			hua->runAction(se);
			GamerData *g_pro=GamerDataDeal::getInstance()->getGamerData(provide);
			g_pro->setJi_type(2);
		}
		else//普通鸡 被 捧走了
		{
			ji_num_players_luxiang[provideviewid]=ji_num_players_luxiang[provideviewid]-1;
		}
		refreshjipaifromluxiang(provideviewid);
	}
	else//普通牌
	{
		if(actionkind!=9&&actionkind!=10)
		{
			//处理提供者的出去的牌的排列
			arr_outcard[provideviewid].erase(arr_outcard[provideviewid].end()-1);
		}
		refreshchupaifromluxiang(provideviewid);
	}
    

    for(int i=0;i<num_removefromshoupai;i++)
    {
        for(int j=0;j<arr_shoupai[viewid].size();j++)
        {
            if(arr_shoupai[viewid].at(j)==arr_cards[0])
            {
                arr_shoupai[viewid].erase(arr_shoupai[viewid].begin()+j);
                break;
            }
        }
    }
    refreshshoupaifromluxiang(viewid);

    //显示吃动画
    Sprite *hua=(Sprite *)arr_node_actions[viewid]->getChildByName("action_detail");
    if(actionkind==8||actionkind==6||actionkind==7||actionkind==9||actionkind==10)
    {
        hua->setTexture("res/srcRes/10.png");
    }
    else
    {
        hua->setTexture("res/srcRes/9.png");
    }
    CallFunc *visible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,hua,true));
    DelayTime *de=DelayTime::create(0.5*luxiang_rate);
    CallFunc *invisible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,hua,false));
    CallFunc *nextstep=CallFunc::create(CC_CALLBACK_0(Playing_three::updateactions,this,0));
    Sequence *se=Sequence::create(visible,de,invisible,nextstep,nullptr);
    hua->runAction(se);
    arr_luxiang_data.erase(arr_luxiang_data.begin());
}
void Playing_three::refreshxingpaifromluxiang(int viewid)
{
    Node *n_xing=arr_xingpai_luxiang[viewid];
	std::vector<xingpai_luxiang> arr_mjs=arr_xingpai[viewid];

	//形牌进行整理

	float hegigh=0;
	float bottom_lenth=44;
	float top_lenth=44;
	float middle_lenth=82;

	float hegigh1=0;
	float bottom_lenth1=43;
	float top_lenth1=43;
	float middle_lenth1=105;

	float hegigh2=0;
	float bottom_lenth2=43;
	float top_lenth2=43;
	float middle_lenth2=82;

	float hegigh3=0;
	float bottom_lenth3=48;
	float top_lenth3=48;
	float middle_lenth3=145;
	for(int i=0;i<4;i++)
	{
		String *name_big=String::createWithFormat("node_chengxing_%d",i+1);
		Node *n_big=(Node *)arr_xingpai_luxiang[viewid]->getChildByName(name_big->getCString());
		n_big->setVisible(false);
	}
	for(int i=0;i<arr_mjs.size();i++)
	{
		
		String *name_big=String::createWithFormat("node_chengxing_%d",i+1);

		Node *n_big=(Node *)arr_xingpai_luxiang[viewid]->getChildByName(name_big->getCString());

		n_big->setVisible(true);

		xingpai_luxiang o_p=arr_mjs[i];
		
		
		//刷新形牌
		if(o_p.operatecode==12)
		{
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.cardid);
				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.cardid);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_6")->getChildByName("mj_value"),o_p.cardid);
			
			if(viewid==1)
			{
					n_big->setPosition(Vec2(0,hegigh));
					hegigh=hegigh+10+230-128;
			} 
			else if(viewid==2)
			{
				
					//n_big->setPosition(Vec2(hegigh1,0));
					//hegigh1=hegigh1-(937-827)-10;
				n_big->setPosition(Vec2(0,hegigh2));
				hegigh2=hegigh2-(679-584)-10;
				
			}
			else if(viewid==3)
			{
				
					n_big->setPosition(Vec2(0,hegigh2));
					hegigh2=hegigh2-(679-584)-10;
				
			}

		}
		else if(o_p.operatecode==5)
		{
            n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

			n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.cardid);
			

			if(viewid==1)
			{
				n_big->setPosition(Vec2(0,hegigh-bottom_lenth));
				hegigh=hegigh+middle_lenth+10;
				

			} 
			else if(viewid==2)
			{
				n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
				hegigh2=hegigh2-middle_lenth2-10;
			//	n_big->setPosition(Vec2(hegigh1+bottom_lenth1,0));
				//hegigh1=hegigh1-middle_lenth1-10;
				
			}
			else if(viewid==3)
			{
				n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
				hegigh2=hegigh2-middle_lenth2-10;
				

			}
	    }
		else if(o_p.operatecode==13)//1碰 2左杠 3右杠 4对门杠
		{
			
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.cardid);
				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.cardid);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_8")->getChildByName("mj_value"),o_p.cardid);
			

			if(viewid==1)
			{
				
					n_big->setPosition(Vec2(0,hegigh-bottom_lenth));
					hegigh=hegigh+10+231-172;
				

			} 
			else if(viewid==2)
			{
				n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
				hegigh2=hegigh2-(636-584)-10;
					//n_big->setPosition(Vec2(hegigh1+bottom_lenth1,0));
					//hegigh1=hegigh1-(896-827)-10;
				

			}
			else if(viewid==3)
			{
				
					n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
					hegigh2=hegigh2-(636-584)-10;
				
			}

		}
		else if(o_p.operatecode==14)//1碰 2左杠 3右杠 4对门杠
		{
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.cardid);
				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.cardid);
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_4")->getChildByName("mj_value"),o_p.cardid);
			if(viewid==1)
			{
				
					n_big->setPosition(Vec2(0,hegigh-(206-129)));
					hegigh=hegigh+10+299-206;
				

			} 
			else if(viewid==2)
			{
				n_big->setPosition(Vec2(0,hegigh2+(680-612)));
				hegigh2=hegigh2-(612-511)-10;
					//n_big->setPosition(Vec2(hegigh1+(937-862),0));
					//hegigh1=hegigh1-(862-749)-10;
				

			}
			else if(viewid==3)
			{
					n_big->setPosition(Vec2(0,hegigh2+(680-612)));
					hegigh2=hegigh2-(612-511)-10;
			}

		}
		
		else if(o_p.operatecode==6)//左杠
		{
			n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

			n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_6")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_6")->getChildByName("mj_value"),o_p.cardid);
			if(viewid==1)
			{
				n_big->setPosition(Vec2(0,hegigh));
				hegigh=hegigh+middle_lenth+10+top_lenth;
			}
			else if(viewid==2)
			{
				n_big->setPosition(Vec2(0,hegigh2));
				hegigh2=hegigh2-middle_lenth2-10-top_lenth2;
				//n_big->setPosition(Vec2(hegigh1,0));
				//hegigh1=hegigh1-middle_lenth1-10-top_lenth1;
			}
			else if(viewid==3)
			{
				n_big->setPosition(Vec2(0,hegigh2));
				hegigh2=hegigh2-middle_lenth2-10-top_lenth2;
			}

		}
		else if(o_p.operatecode==8)//右杠
		{
			n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

			n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_4")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_4")->getChildByName("mj_value"),o_p.cardid);
			if(viewid==1)
			{
				n_big->setPosition(Vec2(0,hegigh-bottom_lenth));
				hegigh=hegigh+middle_lenth+10+top_lenth;
			}
			else if(viewid==2)
			{
				n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
				hegigh2=hegigh2-middle_lenth2-10-top_lenth2;
				//n_big->setPosition(Vec2(hegigh1+bottom_lenth1,0));
				//hegigh1=hegigh1-middle_lenth1-10-top_lenth1;
			}
			else if(viewid==3)
			{
				n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
				hegigh2=hegigh2-middle_lenth2-10-top_lenth2;
			}

		}
		else if(o_p.operatecode==7)//对门杠
		{
			n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

			n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_5")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_5")->getChildByName("mj_value"),o_p.cardid);
			if(viewid==1)
			{
				n_big->setPosition(Vec2(0,hegigh-top_lenth));
				hegigh=hegigh+middle_lenth+10;
			}
			else if(viewid==2)
			{
				n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
				hegigh2=hegigh2-middle_lenth2-10;
			//	n_big->setPosition(Vec2(hegigh1+bottom_lenth1,0));
				//hegigh1=hegigh1-middle_lenth1-10-top_lenth1;
			}
			else if(viewid==3)
			{
				n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
				hegigh2=hegigh2-middle_lenth2-10;
			}

		}
		else if(o_p.operatecode==9)//补杠
		{
			n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

			n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.cardid);
			n_big->getChildByName("mj_sp_chengxing_7")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_7")->getChildByName("mj_value"),o_p.cardid);
			if(viewid==1)
			{
				n_big->setPosition(Vec2(0,hegigh-top_lenth));
				hegigh=hegigh+middle_lenth+10;
			}
			else if(viewid==2)
			{
				n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
				hegigh2=hegigh2-middle_lenth2-10;
				//n_big->setPosition(Vec2(hegigh1+bottom_lenth1,0));
				//hegigh1=hegigh1-middle_lenth1-10-top_lenth1;
			}
			else if(viewid==3)
			{
				n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
				hegigh2=hegigh2-middle_lenth2-10;
			}
		}
		else if(o_p.operatecode==10)//暗杠
		{
			n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
			n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

			n_big->getChildByName("mj_sp_chengxing_7")->setVisible(true);
			initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_7")->getChildByName("mj_value"),o_p.cardid);


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
			if(viewid==0)
			{
				sp_big1->setTexture("res/cards/mj_bg4.png");
				sp_big2->setTexture("res/cards/mj_bg4.png");
				sp_big3->setTexture("res/cards/mj_bg4.png");


			}
			else if(viewid==1)
			{
				sp_big1->setTexture("res/cards/mj_bg6.png");
				sp_big2->setTexture("res/cards/mj_bg6.png");
				sp_big3->setTexture("res/cards/mj_bg6.png");

				n_big->setPosition(Vec2(0,hegigh-top_lenth));
				hegigh=hegigh+middle_lenth+10;

			}
			else if(viewid==2)
			{
				/*sp_big1->setTexture("res/cards/mj_bg4.png");
				sp_big2->setTexture("res/cards/mj_bg4.png");
				sp_big3->setTexture("res/cards/mj_bg4.png");

				n_big->setPosition(Vec2(hegigh1+bottom_lenth1,0));
				hegigh1=hegigh1-middle_lenth1-10-top_lenth1;*/
				sp_big1->setTexture("res/cards/mj_bg6.png");
				sp_big2->setTexture("res/cards/mj_bg6.png");
				sp_big3->setTexture("res/cards/mj_bg6.png");

				n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
				hegigh2=hegigh2-middle_lenth2-10;

			}
			else if(viewid==3)
			{
				sp_big1->setTexture("res/cards/mj_bg6.png");
				sp_big2->setTexture("res/cards/mj_bg6.png");
				sp_big3->setTexture("res/cards/mj_bg6.png");

				n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
				hegigh2=hegigh2-middle_lenth2-10;

			}
		}
	}
}
void Playing_three::minggangfromluxiang(playluxiang p)
{
    
}
void Playing_three::angangfromluxiang(playluxiang p)
{
    
}
void Playing_three::refreshzhishifromluxiang(int viewid)
{
	GameController * controlLayer22 = (GameController *)this->getChildByTag(119);
	controlLayer22->setArrowDirection(viewid);
}
void Playing_three::nextstep(float dt)
{
	if(bt_pause_luxiang->getTag()==0)
	{
    if(arr_luxiang_data.size()<=0)
    {
        return;
    }
    playluxiang p=arr_luxiang_data[0];

    int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(p.actionuerid)->getSeatId());
    switch (p.actionkind)
    {
    case 1://fapai
        {
            //首先看是谁发牌
            dispathercardsfromluxing(p);     
            break;
        }
    case 2://听牌
        {
            buhuafromluxiang(p);
            refreshzhishifromluxiang(viewid);
            break;
        }
    case 3://出牌
        {
            chupaifomluxiang(p);
            refreshzhishifromluxiang(viewid);
            break;
        }
    case 4://摸排
        {
            mopaifromluxiang(p);
            refreshzhishifromluxiang(viewid);
            break;
        }
    case 5://碰
        {
            leftchifromluxiang(p);
            refreshzhishifromluxiang(viewid);
            break;
        }
    case 6://zuogang
        {
            leftchifromluxiang(p);
            refreshzhishifromluxiang(viewid);
            break;
        }
    case 7://中钢
        {
            leftchifromluxiang(p);
            refreshzhishifromluxiang(viewid);
            break;
        }
    case 8://右杠
        {
            leftchifromluxiang(p);
            refreshzhishifromluxiang(viewid);
            break;
        }
    case 9://补杠
        {
            leftchifromluxiang(p);
            refreshzhishifromluxiang(viewid);
            break;
        }
    case 10://暗杠
        {
            leftchifromluxiang(p);
            refreshzhishifromluxiang(viewid);
            break;
        }
    case  11://胡牌
        {
            hufromluxiang(p);
            refreshzhishifromluxiang(viewid);
            break;
        }
    case 12:
        {
           
			leftchifromluxiang(p);
			refreshzhishifromluxiang(viewid);
            break;
        }
	case 13:
		{
			
			leftchifromluxiang(p);
			refreshzhishifromluxiang(viewid);
			break;
		}
	case 14:
		{
			leftchifromluxiang(p);
			refreshzhishifromluxiang(viewid);
			break;
		}
    default:
        break;
    }
	}
}
void Playing_three::updateactions(float dt)
{
    schedule(schedule_selector(Playing_three::nextstep),2*luxiang_rate);
}
void Playing_three::hufromluxiang(playluxiang p)
{
    int uerid=p.actionuerid;
    int provide=p.provideuserid;
    std::vector<int>cards=p.cardid;
    int cardhu=cards[0];

    int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uerid)->getSeatId());
    if (arr_shoupai[viewid].size()<14&&provide!=uerid)
    {
        arr_shoupai[viewid].push_back(cardhu);
    } 
    refreshshoupaifromluxiang(viewid);

    Sprite *hua=(Sprite *)arr_node_actions[viewid]->getChildByName("action_detail");
    hua->setTexture("res/srcRes/11.png");

    CallFunc *visible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,hua,true));
    DelayTime *de=DelayTime::create(0.5*luxiang_rate);
    CallFunc *invisible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,hua,false));
    CallFunc *nextstep=CallFunc::create(CC_CALLBACK_0(Playing_three::updateactions,this,0));
    Sequence *se=Sequence::create(visible,de,nextstep,nullptr);
    hua->runAction(se);
    arr_luxiang_data.erase(arr_luxiang_data.begin());
}
void Playing_three::initplayer()
{
    for(int i=0;i<3;i++)
    {
        nodePlayers[i]->setVisible(true);
        Node *n_player=(Node *)nodePlayers[i];
        n_player->setPosition(posGameluxiang_three[i]);
		nodePlayers[i]->getParent()->setZOrder(115);

        for(int j=0;j<3;j++)
        {
            GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(j);
            int viewid=GetViewID(GamerData::getInstance()->getSeatId(),g->getSeatId());
            if(viewid==i)
            {
                Text *tx_nickname=(Text *)n_player->getChildByName("nickName");
                tx_nickname->setString(g->getNick());
                getheadpathlocalbyurl(g->getHeadUrl(),g->getUId());
                Text *tx_gold=(Text *)n_player->getChildByName("score");
                String *gold_num=String::createWithFormat("%d",g->getGold());
                tx_gold->setString(gold_num->getCString());
				Sprite *sp_quedemen=(Sprite*)n_player->getChildByName("icon_wan_2");
				if(g->getquedemen()!=0)
				{
					if(g->getquedemen()==1)
					{
						sp_quedemen->setTexture("res/loading/play/icon_wan.png");
					}
					else if(g->getquedemen()==2)
					{
						sp_quedemen->setTexture("res/loading/play/icon_tiao.png");
					}
					else if(g->getquedemen()==3)
					{
						sp_quedemen->setTexture("res/loading/play/icon_tong.png");
					}
				}
            }
        }
    }
    //加载录像行牌界面
    Node *n_luxiang=CSLoader::createNode("res/loading/Layer_luxiang_three.csb");
    addChild(n_luxiang,102);
   
	luxiang_rate=1;

   

	Node *sp_bg=(Node *)n_luxiang->getChildByName("bg_kongjian_1");
	Button *bt_back=(Button *)sp_bg->getChildByName("Button_back");
	bt_back->addClickEventListener(CC_CALLBACK_0(Playing_three::removeluxiang,this));

	Button *bt_next=(Button *)sp_bg->getChildByName("Button_next");
	bt_next->addClickEventListener(CC_CALLBACK_0(Playing_three::nextfromluxiang,this));
	Button *bt_before=(Button *)sp_bg->getChildByName("Button_befor");
	bt_before->addClickEventListener(CC_CALLBACK_0(Playing_three::beforefromluxiang,this));
	bt_pause_luxiang=(Button *)sp_bg->getChildByName("Button_pause");
	bt_pause_luxiang->addClickEventListener(CC_CALLBACK_0(Playing_three::pausefromluxiang,this));
	bt_pause_luxiang->setTag(0);
    //解析出各个手牌 行牌 打出牌节点
    for(int i=0;i<3;i++)
    {
        String *s_s=String::createWithFormat("Node_%d",i+1);
        Node *n_shoupai=n_luxiang->getChildByName(s_s->getCString());
        arr_shoupai_luxiang.push_back(n_shoupai);

        String *s_x=String::createWithFormat("node_chengxing_cards_%d",i+1);
        Node *n_xingpai=n_luxiang->getChildByName(s_x->getCString());
        arr_xingpai_luxiang.push_back(n_xingpai);

        String *s_o=String::createWithFormat("Node_outcard_%d",i+1);
        Node *n_out=n_luxiang->getChildByName(s_o->getCString());
        arr_outcard_luxiang.push_back(n_out);

        String *s_a=String::createWithFormat("Node_actions_%d",i+1);
        Node *n_action=n_luxiang->getChildByName(s_a->getCString());
        arr_node_actions.push_back(n_action);

		String *s_ji=String::createWithFormat("node_ji_%d",i+1);
		Node *n_ji=n_luxiang->getChildByName(s_ji->getCString());
		arr_jipai_luxiang.push_back(n_ji);
    }
}
void Playing_three::nextfromluxiang()
{
	if(luxiang_rate>0.1)
	{
		luxiang_rate=luxiang_rate-0.1;
	}
}
void Playing_three::beforefromluxiang()
{
	if(luxiang_rate<=3)
	{
		luxiang_rate=luxiang_rate+0.1;
	}
}
void Playing_three::pausefromluxiang()
{
	if(bt_pause_luxiang->getTag()==0)
	{
		bt_pause_luxiang->setTag(1);
		bt_pause_luxiang->loadTextureNormal("res/srcRes/icon_bofang.png");
		//关闭计时器

	}
	else
	{
		bt_pause_luxiang->setTag(0);
		bt_pause_luxiang->loadTextureNormal("res/loading/play/icon_zanting.png");
		//开启计时器
		nextstep(0);
	}
}
void Playing_three::responsepalyeffect(EventCustom *evt)
{
    int viewid=*((int *)evt->getUserData());

    String *str=String::createWithFormat("path_wav_%d",viewid);
    std::string path=UserDefault::getInstance()->getStringForKey(str->getCString());
    playEffectCustom(path.c_str(),viewid);
    // CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(path.c_str());

    Node *head_n=nodePlayers[viewid];

    ImageView *im=(ImageView*)head_n->getChildByName("Image_pao");
    im->setVisible(true);
	im->setContentSize(Size(100,63));
    Sprite *sp_yuyin=(Sprite *)im->getChildByName("Sprite_yuyin");
    sp_yuyin->setVisible(true);
    Vector<SpriteFrame *>arr_frames;
    for(int i=0;i<4;i++)
    {
        String *name=String::createWithFormat("res/srcRes/animate/voice/%d.png",i);
        Sprite *sp=Sprite::create(name->getCString());
        arr_frames.pushBack(sp->getSpriteFrame());
    }
    Animation *ani=Animation::createWithSpriteFrames(arr_frames);
    ani->setDelayPerUnit(1.0f/4);
    Animate *an=Animate::create(ani);
    RepeatForever *re=RepeatForever::create(an);
    sp_yuyin->runAction(re);


}
void Playing_three::removeluxiang()
{
    this->removeFromParent();

}
void Playing_three::chushihua(bool isluxiang)
{
	isinLuxiang=isluxiang;
    m_left_card_cnt = 0;//0121

    isminglou_over=false;//是否明楼完毕
    mj_isSelectedMj=false; //是否有已经选中的麻将(true:是;false:否)
    isminglou_ing=false;//是否正在进行名楼操作 只针对当前用户
	isOutCarding=false;
    //玩家加载
    loadAndShowPlayers();
}
bool Playing_three::init()
{
    if(!Layer::init()) 
    {
        return false;
    }
	emoji_num[0]=8;
	emoji_num[1]=3;
	emoji_num[2]=2;

	emoji_num[3]=9;

	emoji_num[4]=6;

	emoji_num[5]=13;

	emoji_num[6]=4;

	emoji_num[7]=5;

	emoji_num[8]=6;

	emoji_num[9]=9;

	emoji_num[10]=9;

	emoji_num[11]=4;

	emoji_num[12]=4;
	emoji_num[13]=2;
	emoji_num[14]=2;

    
    setOpacity(0);
	isOutCarding=false;
	outcardingId=-1;
	iscanchupai=true;//是否能出牌

	
	

	

	//加上拖动的牌
	mj_outcarding=MjNode::create();
	mj_outcarding->initBtnWithId(1);
	CCDirector::getInstance()->getRunningScene()->addChild(mj_outcarding,10000);
	mj_outcarding->setScale(0.7);
	mj_outcarding->btnMj->setTexture("res/cards/mj_bg1.png");
	mj_outcarding->valueMj->setPosition(mj_outcarding->valueMj->getPosition()+Vec2(0,30));
    mj_outcarding->setVisible(false);

	

	tp_lose=TipContent::create();
	tp_lose->showUiBreakFromServer();
	tp_lose->setVisible(false);
	 CCDirector::getInstance()->getRunningScene()->addChild(tp_lose,-1);
	
	 auto touchListener = EventListenerTouchOneByOne::create();//创建单点触摸事件监听器
	 touchListener->onTouchBegan = CC_CALLBACK_2(Playing_three::onTouchBegan,this);//触摸开始
	 touchListener->onTouchMoved = CC_CALLBACK_2(Playing_three::onTouchMoved,this);//触摸移动
	 touchListener->onTouchEnded = CC_CALLBACK_2(Playing_three::onTouchEnded,this);//触摸结束
	 _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);//注册分发器

    return true;
}

bool Playing_three::onTouchBegan(Touch* touch, Event *event)
{
	//遍历手里的牌看看点到了那张
	
		for(int i=0;i<m_mjList.size();i++)
		{
			Vec2 v_p=m_mjList.at(i)->convertTouchToNodeSpace(touch);
			if(m_mjList.at(i)->btnMj->getBoundingBox().containsPoint(v_p))
			{
				if(m_mjList.at(i)->btnMj->getColor()==Color3B(100,100,100))
				{
					return false;
				}
				m_mjList.at(i)->btnMj->setColor(Color3B(100,100,100));
				m_mjList.at(i)->valueMj->setColor(Color3B(100,100,100));
				isOutCarding=true;
				outcardingId=i;
				String *str_value=String::createWithFormat("res/cards/mj_%d.png",m_mjList.at(outcardingId)->getLogicValue());
				mj_outcarding->valueMj->setTexture(str_value->getCString());
				mj_outcarding->setPosition(touch->getLocation());
			}
		}
	
	return true;
}
void Playing_three::onTouchMoved(Touch* touch, Event *event)
{
	m_emitter1->setVisible(true);
	m_emitter1->setPosition(touch->getLocation());
    //如果有点到牌就让牌跟着手指移动 初始化打出牌 并设置位置
	CCLOG("2222%d333333%d",isOutCarding,outcardingId);
	    if(outcardingId<m_mjList.size()&&outcardingId!=-1&&isOutCarding==true)
		{
		Vec2 v_p=m_mjList.at(outcardingId)->convertTouchToNodeSpace(touch);
		String *str_value=String::createWithFormat("res/cards/mj_%d.png",m_mjList.at(outcardingId)->getLogicValue());
		mj_outcarding->valueMj->setTexture(str_value->getCString());
		mj_outcarding->setVisible(true);
		mj_outcarding->setPosition(touch->getLocation());
		}
	
}

void Playing_three::onTouchEnded(Touch* touch, Event *event)
{
	m_emitter1->setVisible(false);
	//判定当前牌的状态以及位置 来进行判断 是否出牌
	if(isOutCarding==true&&outcardingId!=-1)
	{

		mj_outcarding->setVisible(false);//把拖动的牌设置为不可见 
		//所有牌变为白色
		for(int i=0;i<m_mjList.size();i++)
		{
			m_mjList.at(i)->btnMj->setColor(Color3B(255,255,255));
			m_mjList.at(i)->valueMj->setColor(Color3B(255,255,255));
			
		}
		
		if(m_mjList.size()>outcardingId)
		{
			if(m_mjList.at(outcardingId)->getIsCardSelected()==true)//牌已经被提起了就直接打出去
			{
				CCLOG("%d  %d ",UserDefault::getInstance()->getBoolForKey("iscanoperatecard"),m_mjList.at(outcardingId)->iscanoperateornot);
				if(UserDefault::getInstance()->getBoolForKey("iscanoperatecard")==true&&m_mjList.at(outcardingId)->iscanoperateornot==true)
				{
					TableCommand::getInstance()->requestOutCard(m_mjList.at(outcardingId)->id);
					iscanchupai=false;
					// scheduleOnce(schedule_selector(Playing_three::recovercupai),1);
					for(int i=0;i<m_mjList.size();i++)
					{
						m_mjList.at(i)->setIsCardSelected(false);
					}
				}
			}
			else//如果没有被提起 还得判断他的位置
			{
				if( mj_outcarding->getParent()->convertToWorldSpace(mj_outcarding->getPosition()).getDistance(m_mjList.at(outcardingId)->getParent()->convertToWorldSpace(m_mjList.at(outcardingId)->getPosition()))<=100)
				{
					//拉起牌
					selectCardbylocal(m_mjList.at(outcardingId));
				}
				else
				{
					//出牌
					if(UserDefault::getInstance()->getBoolForKey("iscanoperatecard")==true&&m_mjList.at(outcardingId)->iscanoperateornot==true)
					{
						TableCommand::getInstance()->requestOutCard(m_mjList.at(outcardingId)->id);
						iscanchupai=false;
						// scheduleOnce(schedule_selector(Playing_three::recovercupai),1);
						//所有牌变为白色
						for(int i=0;i<m_mjList.size();i++)
						{
							m_mjList.at(i)->setIsCardSelected(false);
						}
					}
					else
					{
						selectCardbylocal(m_mjList.at(outcardingId));
					}
				}
			}
		}
		
		isOutCarding=false;
		outcardingId=-1;
		refreshcolor();
	}
	else
	{
		if (mj_selectedMj!=nullptr)
		{
			mj_selectedMj->setIsCardSelected(false);
			mj_selectedMj=nullptr;
		}
		for(int i=0;i<m_mjList.size();i++)
		{
			m_mjList.at(i)->setPositionY(1.64);
		}
	}
	
	
}
void Playing_three::recovercupai(float dt)
{
	iscanchupai=true;
}
//加载所有玩家显示初始化(玩家等待）
void Playing_three::loadAndShowPlayers()
{
	if(isinLuxiang==false)
	{
    m_current_diamond = Sprite::create("res/srcRes/diamond1.png");
    m_current_diamond->setScale(scale_current_diamond);
    m_current_diamond->setVisible(false);
	m_current_diamond->setPosition(Vec2(10000,10000));
	m_current_diamond->setAnchorPoint(Vec2(0.5,0));
	auto controlLayer = (GameController *)(this->getParent()->getChildByName("mj_controller"));
	controlLayer->addChild(m_current_diamond,3);
	}
	else
	{
		m_current_diamond = Sprite::create("res/srcRes/diamond1.png");
		m_current_diamond->setScale(scale_current_diamond);
		m_current_diamond->setVisible(false);
		m_current_diamond->setPosition(Vec2(10000,10000));
		m_current_diamond->setAnchorPoint(Vec2(0.5,0));
		auto controlLayer = (GameController *)(this->getChildByTag(119));
		controlLayer->addChild(m_current_diamond,3);
	}

	m_emitter1 = ParticleSystemQuad::create("res/partical/Desktop1.plist"); 
	m_emitter1->setPosition(Vec2(200,500));
	addChild(m_emitter1,3); 
	m_emitter1->setVisible(false);


	Sequence *se_diamond=Sequence::create(MoveBy::create(0.2,Vec2(0,hight_diamon)),MoveBy::create(0.2,Vec2(0,-1*hight_diamon)),nullptr);
	RepeatForever *re_diamond=RepeatForever::create(se_diamond);
	m_current_diamond->stopAllActions();
	m_current_diamond->runAction(re_diamond);

	Node *n_all=CSLoader::createNode("res/loading/mj_three.csb");
	addChild(n_all);

	Sprite *sp_icon_three=(Sprite *)n_all->getChildByName("text_wanfa_three_639");
	Sprite *sp_icon_three_two=(Sprite *)n_all->getChildByName("text_wanfa_threetwo_640");
	if(MjData::getInstance()->getpalyrule()==2)
	{
		sp_icon_three->setVisible(true);
		sp_icon_three_two->setVisible(false);
	}
	else
	{
		sp_icon_three->setVisible(false);
		sp_icon_three_two->setVisible(true);
	}

	UserDefault::getInstance()->setBoolForKey("isplayluyin",false);


	//解析所有的玩家
    for (int i = 0; i < 3; i++)
    {
		String *path_node_player_info=String::createWithFormat("player_info_%d",i+1);
        Node * mj_nodePLayer =n_all->getChildByName(path_node_player_info->getCString());

        mj_nodePLayer->setVisible(false);

		
			nodePlayers[i]=mj_nodePLayer;
			mj_nodePLayer->setPosition(posWait_three[i]);
			Button *bt_head=(Button *)mj_nodePLayer->getChildByName("Button_headclick");
			bt_head->setTag(i+1);
			bt_head->addTouchEventListener(CC_CALLBACK_2(Playing_three::ButtonHandler,this));
	
		
		String *path_node_player_cards1=String::createWithFormat("Node_player_%d",i+1);
		Node *n_cards=n_all->getChildByName(path_node_player_cards1->getCString());
		
		
			nodeCards[i]=n_cards;
		
        if(i!=0)
        {
           n_cards->setVisible(false);
        }
	
    }
	for(int i=0;i<3;i++)
	{
		Node *n_card=nodeCards[i]->getChildByName("nodeCards");
		for(int j=0;j<14;j++)
		{
			String *cardpath=String::createWithFormat("poker_%d",j+1);
			Sprite *sp_card=(Sprite *)n_card->getChildByName(cardpath->getCString());
			arr_hand_pos[i].push_back(sp_card->getPosition());
		}
	}
    //所有可以操作的按钮的集合
    for(int i=0;i<4;i++)
    {
        String *name=String::createWithFormat("action_%d",i+1);
        Button *bt_action=(Button *)nodeCards[0]->getChildByName("node_actions")->getChildByName(name->getCString());
        arr_actions.push_back(bt_action);
        bt_action->setVisible(false);
        bt_action->setEnabled(false);
    }
	//所有可以进行做吃又吃 杠选择的牌型展示
	node_detail_actions=(Node *)nodeCards[0]->getChildByName("node_detail_actions");
	setcards_detail_actionsisvisible(false);
	refreshactionsbutton(false);
	
}
void Playing_three::refreshdingque(int quedemen,int viewid)
{
	
	CCLOG("playrule=====%d",MjData::getInstance()->getpalyrule());
	if(MjData::getInstance()->getpalyrule()==2)
	{
		Node *n_player=nodePlayers[viewid];
		Sprite *sp_quedemen=(Sprite *)n_player->getChildByName("icon_wan_2");

		if(viewid==0)//我自己
		{
			Sprite *sp_tip=(Sprite *)n_player->getChildByName("txt_hint_1");
			if(quedemen==0)
			{
				sp_quedemen->setVisible(false);

				sp_tip->setVisible(true);
			}
			else if(quedemen==1)
			{
				sp_quedemen->setVisible(true);
				sp_quedemen->setTexture("res/loading/play/icon_wan.png");
				sp_tip->setVisible(false);
			}
			else if(quedemen==2)
			{
				sp_quedemen->setVisible(true);
				sp_quedemen->setTexture("res/loading/play/icon_tiao.png");
				sp_tip->setVisible(false);
			}
			else if(quedemen==3)
			{
				sp_quedemen->setVisible(true);
				sp_quedemen->setTexture("res/loading/play/icon_tong.png");
				sp_tip->setVisible(false);
			}
		}
		else//别的玩家
		{
			Sprite *sp_tip=(Sprite *)n_player->getChildByName("txt_dingquezhong_4");
			if(quedemen==0)
			{
				sp_quedemen->setVisible(false);

				sp_tip->setVisible(true);
			}
			else if(quedemen==1)
			{
				if(dingqueshu==3)
				{
					sp_quedemen->setVisible(true);
					sp_quedemen->setTexture("res/loading/play/icon_wan.png");
				}
				sp_tip->setVisible(false);
			}
			else if(quedemen==2)
			{
				if(dingqueshu==3)
				{
					sp_quedemen->setVisible(true);
					sp_quedemen->setTexture("res/loading/play/icon_tiao.png");
				}
				sp_tip->setVisible(false);
			}
			else if(quedemen==3)
			{
				if(dingqueshu==3)
				{
					sp_quedemen->setVisible(true);
					sp_quedemen->setTexture("res/loading/play/icon_tong.png");
				}
				sp_tip->setVisible(false);
			}
		}
	}
}
void Playing_three::setcards_detail_actionsisvisible(bool isvisible)
{
    node_detail_actions->setVisible(isvisible);
}
void Playing_three::refreshactionsbutton(bool iscanoperate)
{
    for(int i=0;i<arr_actions.size();i++)
    {
        arr_actions[i]->setVisible(iscanoperate);
        arr_actions[i]->setEnabled(iscanoperate);
    }
}
//按钮回调函数
void Playing_three::ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType)
{
    if (touchType != ui::Widget::TouchEventType::ENDED) return;
    Button* pBtn = (Button*) pRef;
    string name = pBtn->getName();
    if (name == "btnUserInfo"){
        //退出房间
        auto tag = pBtn->getTag();

    }
	else if(name=="Button_ready")
	{
		TableCommand::getInstance()->requestready();
	}
    else if(name=="Button_headclick"){

        auto tag = pBtn->getTag();
        //个人信息
        CCLOG("--------------------------btnHead------------------");

		GamerData *g_d=GamerDataDeal::getInstance()->getGamerDataBySeat(tag-1);


		TableCommand::getInstance()->requestplayerinfo(g_d->getUId());
        

    }
}
void Playing_three::responsegetplayerinfo(EventCustom *evt)
{
	GS2C_GetJuCnt * udata  = (GS2C_GetJuCnt  *)evt->getUserData();
	int sheng=udata->ju_win();
	int ping=udata->ju_draw();
	int fu=udata->ju_lose();
	int uid=udata->uid();
	int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uid)->getSeatId());
	UserDefault::getInstance()->setIntegerForKey("juwin",sheng);
	UserDefault::getInstance()->setIntegerForKey("juping",ping);
	UserDefault::getInstance()->setIntegerForKey("julose",fu);

	int zong = sheng+ping+fu;
	UserDefault::getInstance()->setIntegerForKey("zongJu",zong);
	float shengLv = 0;
	if (zong == 0)
	{
		shengLv = 0;
	}
	else
	{
		shengLv = sheng*100.0/zong;
	}	
	UserDefault::getInstance()->setFloatForKey("shengLv",shengLv);

	auto tipConent = TipContent::create();
	tipConent->showUIplayerInfoInGame(viewid);
	this->getParent()->addChild(tipConent,1000);
}
//游戏开始(玩家头像位置更新等)
void Playing_three::startGame_gamePlayer(int banker, int left_card_cnt)
{
    isminglou_ing=false;
    isminglou_over=false;
    m_left_card_cnt = left_card_cnt;
	arr_hutype.clear();
	time_all=0;

    MjData::getInstance()->setbanker(banker);

	int bankerviewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(banker)->getSeatId());
	auto controlLayer = (GameController *)(this->getParent()->getChildByName("mj_controller"));
	controlLayer->setArrowRoatation(MjData::getInstance()->getfangzhu_viewid());

    BYTE viewId = GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(banker)->getSeatId());

    for(int i=0;i<4;i++)
    {
        hands_cnt[i]=13;
        if(viewId==i)
        {
            hands_cnt[i]=13;
        }

    }
    for (int i = 0; i < 3; i++)
    {
		GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(i);
		g->setJi_type(0);

		refreshdingque(g->getquedemen(),i);
        //用户信息
        auto nodePlayer = nodePlayers[i];
		Sprite *icon_ready=(Sprite *)nodePlayer->getChildByName("icon_ready");
		icon_ready->setVisible(false);
		
        nodePlayer->runAction(MoveTo::create(0.5f,posGame_three[i]));
        Node * nodeCard = nodeCards[i]->getChildByName("nodeCards");
        Node *n_chengxing=nodeCards[i]->getChildByName("node_chengxing_cards");
        if(i!=0)
        {
			nodeCards[i]->setVisible(true);
            refreshxingpaiposofothers(m_players_chengxing_mjs[i],n_chengxing,i,0);//此处要进行手牌和形牌得重新排列刷新
        }
    } 

}
void Playing_three::getheadpathlocalbyurl(std::string url,int tag)
{
    cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(Playing_three::onGetFinished));
    request->setTag(String::createWithFormat("%d",tag)->getCString());
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();

}

void Playing_three::onGetFinished(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    if (!response)
    {
        return;
    }

    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        log("%s completed", response->getHttpRequest()->getTag());
    }
    int viewid=atoi(response->getHttpRequest()->getTag());
    int statusCode = response->getResponseCode();
    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer());
        return;
    }

    //get data
    std::vector<char> *buffer = response->getResponseData();

    //create image
    CCImage* img = new CCImage;
    img->initWithImageData((unsigned char*)buffer->data(),buffer->size());

    //create texture
    cocos2d::CCTexture2D* texture = new CCTexture2D();
    bool isImg = texture->initWithImage(img);
	if(isImg)
	{
		 img->release();
	}
   
	GamerData *g_d=GamerDataDeal::getInstance()->getGamerData(viewid);
	int view_id=GetViewID(GamerData::getInstance()->getSeatId(),g_d->getSeatId());
    Sprite * sp_head=(Sprite *) nodePlayers[view_id]->getChildByName("icon");
	if(isImg)
	{
		sp_head->setTexture(texture);
		sp_head->setScale(68.f/sp_head->getContentSize().width);
	}
    
   

    //iconHead->setContentSize(Size(70,70));

    //write file
    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    String *s=String::createWithFormat("%s%d.png",path.c_str(),viewid);



    FILE *fp = fopen(s->getCString(), "wb+");
    fwrite(buffer->data(), 1,buffer->size(), fp);
    fclose(fp);

}
//玩家加入桌子fset
void Playing_three::joinTable(EventCustom* evt)
{
    GamerData* pGamerData = (GamerData*) evt->getUserData();

    BYTE viewId = GetViewID(GamerData::getInstance()->getSeatId(),pGamerData->getSeatId());
	

    Sprite *iszhuang=(Sprite *)nodePlayers[viewId]->getChildByName("isHost");
    if(pGamerData->getUId()==MjData::getInstance()->getbanker())
    {
        iszhuang->setVisible(true);
    }
    else
    {
        iszhuang->setVisible(false);
    }

    if(pGamerData->getUId() == GamerData::getInstance()->getUId())
    {//当前玩家


        nodePlayers[0]->setVisible(true);

        auto nodePlayer = (Node*)nodePlayers[0];
        auto icon = (Sprite*)nodePlayer->getChildByName("icon");   //玩家头像
        auto btnUserInfo = (Button*)nodePlayer->getChildByName("btnUserInfo");//玩家信息按钮
        btnUserInfo->setTag(pGamerData->getUId());
        btnUserInfo->addTouchEventListener(CC_CALLBACK_2(Playing_three::ButtonHandler, this));
        auto nickName = (Text*)nodePlayer->getChildByName("nickName");//昵称
        nickName->setText(pGamerData->getNick());

       

        auto score = (Text*)nodePlayer->getChildByName("score");      //当前玩家积分
        score->setText(String::createWithFormat("%d",pGamerData->getGold())->getCString());


      
        auto isOnline = (ImageView*)nodePlayer->getChildByName("isOnline"); //当前玩家是否在线的标识
        auto isHost = (ImageView*)nodePlayer->getChildByName("isHost");   //当前玩家是否坐庄的标识


    }else{
        //其他玩家
        nodePlayers[viewId]->setVisible(true);
        auto nodePlayer = (Node*)nodePlayers[viewId];
        auto icon = (Sprite*)nodePlayer->getChildByName("icon");   //玩家头像
        auto btnUserInfo = (Button*)nodePlayer->getChildByName("btnUserInfo");//玩家信息按钮
        btnUserInfo->setTag(pGamerData->getUId());
        btnUserInfo->addTouchEventListener(CC_CALLBACK_2(Playing_three::ButtonHandler, this));
        auto nickName = (Text*)nodePlayer->getChildByName("nickName");//昵称
        nickName->setText(pGamerData->getNick());
       // auto tx_id=(Text *)nodePlayer->getChildByName("uerid");
        //tx_id->setString(String::createWithFormat("%d", pGamerData->getUId())->getCString());

        auto score = (Text*)nodePlayer->getChildByName("score");      //当前玩家积分
        score->setText(String::createWithFormat("%d",pGamerData->getGold())->getCString());

      
        auto isOnline = (ImageView*)nodePlayer->getChildByName("isOnline"); //当前玩家是否在线的标识
        auto isHost = (ImageView*)nodePlayer->getChildByName("isHost");   //当前玩家是否坐庄的标识
    }

    getheadpathlocalbyurl(pGamerData->getHeadUrl(),pGamerData->getUId());




	
	
	



}
//玩家离开桌子广播
void Playing_three::leaveTableBroadcast(EventCustom* evt)
{
    //此处只能收到别的玩家的 退出广播 自己的 另有他处处理
    GS2C_LeaveTableBroadcast* udata  = (GS2C_LeaveTableBroadcast *)evt->getUserData();
    int isbannodismiss=udata->is_banker_no_dismiss();
    int leave_reson=udata->leave_reason();
    int uid=udata->uid();
    GamerData* pGamerData = GamerDataDeal::getInstance()->getGamerData(uid);
    BYTE viewId = GetViewID(GamerData::getInstance()->getSeatId(),pGamerData->getSeatId());

    if(leave_reson==0)//普通退出
    {
        if(uid==MjData::getInstance()->getbanker())//房主正常退出
        {
            //找到房主 并设置状态 为离线
            GamerData *p= GamerDataDeal::getInstance()->getGamerData(uid);
            p->setStatus(4);
            //找到界面上的房主
            Sprite *isonline=(Sprite *) nodePlayers[viewId]->getChildByName("isOnline");
            isonline->setVisible(true);
        }
        else//玩家退出
        {
            //移除玩家
            GamerDataDeal::getInstance()->removeGamerData(uid);
            nodePlayers[viewId]->setVisible(false);
        }

    }
    else//解散房间
    {
        //把自己的状态设置为free
        GamerData::getInstance()->setStatus(0);
        //回到主界面 并断开服务器连接 清空用户数据
        GamerDataDeal::getInstance()->removeallGamerData();
        SocketUtil::getInstance()->StopConnect();
        SEND_CUSTOM_MSG("gamenotbegindismiss");

    }
}
void Playing_three::responsebreakbackbroadcast(EventCustom *evt)
{
    GS2C_BreakBackBroadcast * udata=(GS2C_BreakBackBroadcast *)evt->getUserData();
    int uid=udata->break_uid();
    GamerData *p = GamerDataDeal::getInstance()->getGamerData(uid);
    if(p!=nullptr)
    {
        BYTE viewid=GetViewID(GamerData::getInstance()->getSeatId(),p->getSeatId());
        nodePlayers[viewid]->getChildByName("isOnline")->setVisible(false);
    }
}
//玩家补花广播
void Playing_three::buHuaBroadcast(EventCustom* evt)
{
	/*
    GS2C_StartReplaceBroadcast* buhua = (GS2C_StartReplaceBroadcast*) evt->getUserData();
    google::protobuf::RepeatedField< ::google::protobuf::int32 > replaceusers = buhua->replace_uids();
    google::protobuf::RepeatedField< ::google::protobuf::int32 > hua_numbers = buhua->card_cnt_reals();
    if(replaceusers.size() == hua_numbers.size())
    {
        for (int i = 0; i < replaceusers.size(); i++)
        {
            int uid = replaceusers.Get(i);
            int numHua = hua_numbers.Get(i);
            buhuaActionManage(uid,numHua);

            //首先判断是谁进行的此次操作
            GamerData *p=GamerDataDeal::getInstance()->getGamerData(uid);
            //音效
            Tools::playCardByGender("buhua", p->getSex());
        }
    }
	*/
}

//发牌
void Playing_three::dispacherCard(google::protobuf::RepeatedField< ::google::protobuf::int32 > cards)
{
	
    const int idsSize = cards.size();                //手中牌数 	
	
    BYTE ids[14];
    for (int i = 0; i < idsSize; i++)
    {
        ids[i] = cards.Get(i);
    }
    BYTE temp;
    bool hasExchangeAction; //记录此次大循环中相邻的两个数是否发生过互换（如果没有互换，则数组已经是有序的）  
    for (int i = 0; i < idsSize; i++)    //数组有N个数，那么用N-1次大循环就可以排完  
    {  
        hasExchangeAction = false;  //每次大循环都假设数组有序  

        for (int j = 0; j < idsSize - i - 1; j++)    //从数组下标0处开始遍历，（length - i - 1 是刨除已经排好的大数）  
        {  
            BYTE p1 = ids[j];
            BYTE p2 = ids[j+1];
            if (p1 > p2)    //相邻两个数进行比较，如果前面的数大于后面的数，则将这相邻的两个数进行互换  
            {  
                temp = ids[j];  
                ids[j] = ids[j + 1];  
                ids[j + 1] = temp;  
                hasExchangeAction = true;   //发生过互换  
            }  
        }  
        if (!hasExchangeAction) //如果没有发生过互换，则数组已经是有序的了，跳出循环  
        {  
            break;  
        }  
    }
	

    Node* nodePlayer_1 = nodeCards[0]->getChildByName("nodeCards");
    for (int i = 0; i < idsSize; i++)
    {
        MjNode* pMjNode = MjNode::create();
        pMjNode->initBtnWithId(ids[i]);
        pMjNode->setAnchorPoint(Vec2(0.5f,0.5f));
        nodePlayer_1->addChild(pMjNode,20);
        pMjNode->setPosition(nodePlayer_1->getChildByName(String::createWithFormat("poker_%d",i+1)->getCString())->getPosition());
        m_mjList.pushBack(pMjNode);
    }
	refreshMjsPos();
	

}
//当前玩家选中要出的牌(本地)
void Playing_three::selectCard(EventCustom* evt)
{
    if (mj_selectedMj!=nullptr)
    {
        mj_selectedMj->setPositionY(mj_selectedMj->getPositionY()-30.0f);
        mj_selectedMj->setIsCardSelected(false);
    }
    mj_isSelectedMj = true;       //当前玩家是否有选中要出的牌(true：是;false:否)
    mj_selectedMj = (MjNode*)evt->getUserData();  //被选中的麻将牌
    mj_selectedMj->setPositionY(mj_selectedMj->getPositionY()+30.0f);
}
void Playing_three::selectCardbylocal(MjNode *mj)
{
	if (mj_selectedMj!=mj&&mj_selectedMj!=nullptr)
	{
		if(mj_selectedMj->getPosition().y>=15)
		{
			mj_selectedMj->setPositionY(mj_selectedMj->getPositionY()-30.0f);
		}
		mj_selectedMj->setIsCardSelected(false);
	}
	mj_isSelectedMj = true;       //当前玩家是否有选中要出的牌(true：是;false:否)
	mj_selectedMj = mj;  //被选中的麻将牌
	mj_selectedMj->setPositionY(mj_selectedMj->getPositionY()+30.0f);
	mj_selectedMj->setIsCardSelected(true);  
}
//出牌(本地)
void Playing_three::outCardBroadcast(EventCustom* evt)
{
    TableCommand::getInstance()->requestOutCard(mj_selectedMj->id);
}
void Playing_three::spsetvisible(Sprite *sp,bool isvisible)
{
	sp->setVisible(isvisible);
}
void Playing_three::outcardformserver(EventCustom *evt)
{
	refreshactionsbutton(false);

    GS2C_OutBroadcast * outcard = (GS2C_OutBroadcast *) evt->getUserData();
    int errorcode = outcard->errorcode();
    int  uerid = outcard->out_uid();
    int card=outcard->card();

	int ji_type=outcard->ji_type();
	
    GamerData *p=GamerDataDeal::getInstance()->getGamerData(uerid);

    BYTE viewId = GetViewID(GamerData::getInstance()->getSeatId(),p->getSeatId());//计算出当前出牌玩家的界面id

	
	if(card==17)
	{
			//手牌移除这张鸡
			if(viewId==0)
			{
				for(int i=0;i<m_mjList.size();i++)
				{
					if(m_mjList.at(i)->id==card)
					{
						mj_selectedMj=m_mjList.at(i);
						mj_selectedMj->removeFromParentAndCleanup(true);
						m_mjList.erase(m_mjList.begin()+i);//手中删除已出的牌
						mj_selectedMj=nullptr;
						break;
					}
				}
				hands_cnt[viewId]=hands_cnt[viewId]-1;
				refreshMjsPos();
			}
			else//如果是别人
			{
				hands_cnt[viewId]=hands_cnt[viewId]-1;
				refreshxingpaiposofothers(m_players_chengxing_mjs[viewId],nodeCards[viewId]->getChildByName("node_chengxing_cards"),viewId,0);
			}
			//加入鸡排
			if(ji_type==1)
			{
				arr_jipai[viewId].push_back(1);
				//这里要放音效冲锋机的 以及 冲锋机动画
				playAction_jiAnimation(viewId,1);
				GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(viewId);
				g->setJi_type(1);
				Tools::playOperateByGender(7,p->getSex());
			}
			else if(ji_type==2)
			{
				//这里放 普通级 音效 
				arr_jipai[viewId].push_back(2);
				Tools::playCardByGender(card,p->getSex(),Tools::getLanguage());
			}
			refreshjipaiOfPlayer(viewId);
			
			Node *node_jipai=nodeCards[viewId]->getChildByName("node_ji");
			int ji_pos=0;
			if(p->getJi_type()==1)
			{
				ji_pos=arr_jipai[viewId].size();
			}
			else
			{
				ji_pos=arr_jipai[viewId].size()+1;
			}
			String *ji_path=String::createWithFormat("mj_bg_%d",ji_pos);
			Sprite *ji=(Sprite *)node_jipai->getChildByName(ji_path->getCString());
			
			Vec2 v_worldpos=ji->getParent()->convertToWorldSpace(ji->getPosition());
			

			//m_current_diamond->setPosition(Vec2(ji->getContentSize().width/2,100));
			m_current_diamond->setPosition(v_worldpos);

			CCLOG("%f %f",ji->getContentSize().width,ji->getContentSize().height);

			Sequence *se_diamond=Sequence::create(MoveBy::create(0.5,Vec2(0,hight_diamon)),MoveBy::create(0.5,Vec2(0,-1*hight_diamon)),nullptr);
			RepeatForever *re_diamond=RepeatForever::create(se_diamond);
			m_current_diamond->stopAllActions();
			m_current_diamond->runAction(re_diamond);

			return;
	}
	else
	{
		Tools::playCardByGender(card,p->getSex(),Tools::getLanguage());
	}
        //做动画
        Node* outcard_ = nodeCards[viewId]->getChildByName("node_outcard");
		Sprite *sp_poker_out=(Sprite *)outcard_->getChildByName("mj_bg_poker_out");//找到这张做动画得牌
		sp_poker_out->setVisible(true);//设置为可见

		Vec2 origin_position=sp_poker_out->getPosition();//记录初始位置

		int id_cards=getlogicvalue(card);//获取打出拍得逻辑值
        String *path_texture=String::createWithFormat("res/cards/mj_%d.png",id_cards);//拼凑牌得路径
		Sprite *sp_mjvalue=(Sprite *)sp_poker_out->getChildByName("mj_value");
		sp_mjvalue->setTexture(path_texture->getCString());//设置图片

		//获取下一个打出牌

		String *index_out=String::createWithFormat("mj_bg_%d",m_arr_players_mjs[viewId].size()+1);

		Sprite *sp_out_=(Sprite *)outcard_->getChildByName(index_out->getCString());
       
        m_arr_players_mjs[viewId].push_back(card);

		
		
		
		Node *node_chudepai=nodeCards[viewId]->getChildByName("node_outcard");
		String *card_path=String::createWithFormat("mj_bg_%d",m_arr_players_mjs[ viewId].size());
		Sprite *card_sp=(Sprite *)node_chudepai->getChildByName(card_path->getCString());
		
		Vec2 v_world_pos=card_sp->getParent()->convertToWorldSpace(card_sp->getPosition());
		//card_sp->addChild(m_current_diamond);//把钻石贴到出的牌上
		float y_diamond;
		if(viewId==0||viewId==2)
		{
			y_diamond=110;
		}
		else
		{
			y_diamond=100;
		}
	//	m_current_diamond->setPosition(Vec2(card_sp->getContentSize().width/2,y_diamond));
		m_current_diamond->setPosition(v_world_pos);
		m_current_diamond->setVisible(false);
		Sequence *se_diamond=Sequence::create(MoveBy::create(0.5,Vec2(0,hight_diamon)),MoveBy::create(0.5,Vec2(0,-1*hight_diamon)),nullptr);
		RepeatForever *re_diamond=RepeatForever::create(se_diamond);
		m_current_diamond->stopAllActions();
		m_current_diamond->runAction(re_diamond);

		Vec2 posEnd = sp_out_->getPosition();
        auto distance = origin_position.getDistance(posEnd);
		 
		float angle;
		float delay;
		float angele2;
		float delay1;
		if(viewId==0)
		{
			angle=0;
			delay=0;
			angele2=0;
			delay1=0;
		}
		else if(viewId==1)
		{
			angle=90;
			delay=0.3;
			angele2=-90;
			delay1=0.3;
		}
		else if(viewId==2)
		{
			angle=180;
			delay=0.3;
			angele2=180;
			delay1=0.3;
		}
		else if(viewId==3)
		{
			angle=-90;
			delay=0.3;
			angele2=90;
			delay1=0.3;
		}
		auto action1= Spawn::create(RotateBy::create(delay,angle),MoveBy::create(0.3,Vec2(0,100)),ScaleTo::create(0.3,3),nullptr);
		DelayTime *de1=DelayTime::create(0.2);
		auto action = Spawn::create(RotateBy::create(delay1,angele2),MoveTo::create(0.3,posEnd),ScaleTo::create(0.3,0.8),nullptr);
		CallFunc *call=CallFunc::create(CC_CALLBACK_0(Playing_three::refreshoutcardByViewId,this,viewId));
		CallFunc *call_visible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,sp_poker_out,true));
		CallFunc *call_unvisible=CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,sp_poker_out,false));
		MoveTo *m_t=MoveTo::create(0,origin_position);
		Sequence *se1=Sequence::create(call_unvisible,m_t,nullptr);
		Sequence *se=Sequence::create(call_visible,action1,de1,action,se1,call,RotateTo::create(0,0),CallFunc::create(CC_CALLBACK_0(Playing_three::playeeffect_normal,this,"audio_card.mp3")),nullptr);
        sp_poker_out->runAction(se);
        scheduleOnce(schedule_selector(Playing_three::delayShowCurrentDiamond),0.8);
        hands_cnt[viewId]=hands_cnt[viewId]-1;


		if(viewId==GamerData::getInstance()->getViewId())
		{
			UserDefault::getInstance()->setBoolForKey("iscanoperatecard",false);
			
			for(int i=0;i<m_mjList.size();i++)
			{
				if(m_mjList.at(i)->id==card)
				{
					mj_selectedMj=m_mjList.at(i);
					mj_selectedMj->removeFromParentAndCleanup(true);
					m_mjList.erase(m_mjList.begin()+i);//手中删除已出的牌
					mj_selectedMj=nullptr;
					break;
				}
				/*
				if(m_mjList.at(i)==mj_selectedMj)
				{
					m_mjList.erase(m_mjList.begin()+i);//手中删除已出的牌
				}
				*/
			}
			
			refreshMjsPos();
		}
		else
		{
			refreshxingpaiposofothers(m_players_chengxing_mjs[viewId],nodeCards[viewId]->getChildByName("node_chengxing_cards"),viewId,0);
		}



 }
 void Playing_three::delayShowCurrentDiamond(float dt)
 {
	 m_current_diamond->setVisible(true);
 }
void Playing_three::minglououtcarddelay(float dt)
{
	SEND_CUSTOM_MSG("playing_broadcast_outCard");
}
void Playing_three::systemgetsiglecardbroadcast(EventCustom *evt)
{
    GS2C_DispatchBroadcast  * outcard = (GS2C_DispatchBroadcast  *) evt->getUserData();
    int errorcode = outcard->errorcode();
    int ishu=outcard->is_hu();
    int isgang=outcard->is_gang();

	
    if(errorcode==0)
    {
		
        mj_isSelectedMj =false;
        //此处要根据userid来判断当前能够进行操作的人是谁,来把箭头的方向改了以及剩余牌变化
        int cardid = outcard->card();
        int userid=outcard->dispatch_uid();

        m_left_card_cnt=outcard->left_cnt();

        //剩余张数
        auto controlLayer = (GameController *)(this->getParent()->getChildByName("mj_controller"));
        controlLayer->setLeftCardCnt(m_left_card_cnt);
        //箭头指向
        GamerData *p=GamerDataDeal::getInstance()->getGamerData(userid);
        BYTE viewId = GetViewID(GamerData::getInstance()->getSeatId(),p->getSeatId());
        controlLayer->setArrowDirection(viewId);

		CCLOG("systemgetsiglecardbroadcast viewid=%d cardid=%d",viewId,cardid);

        if(userid==GamerData::getInstance()->getUId())//当前玩家是自己
        {
            MjNode *p=MjNode::create();
            p->initBtnWithId(cardid);
            Node *n=(Node *)nodeCards[0]->getChildByName("nodeCards");
            p->setPosition(Vec2(m_mjList.at(0)->getPosition().x+108,1.64));
            p->setIsCardSelected(false);
            p->setAnchorPoint(Vec2(0.5f,0.5f));
            n->addChild(p);
            m_mjList.pushBack(p);
			refreshcolor();
			if(isminglou_over)
			{
                if(!ishu)//这张牌不能胡
                {
                    //自动出牌
                    mj_selectedMj=p;
                    mj_isSelectedMj=true;
					scheduleOnce(schedule_selector(Playing_three::minglououtcarddelay),0.5);
                }
            }
        }
        else
        {
            GamerData *p=GamerDataDeal::getInstance()->getGamerData(userid);
            BYTE viewId = GetViewID(GamerData::getInstance()->getSeatId(),p->getSeatId());//计算出当前出牌玩家的界面id
            for(int i=0;i<4;i++)
            {
                if(i!=0)
                {
                    if(viewId==i)
                    {
                        hands_cnt[i]=hands_cnt[i]+1;
                    }
                }
            }
            refreshxingpaiposofothers(m_players_chengxing_mjs[viewId],nodeCards[viewId]->getChildByName("node_chengxing_cards"),viewId,1);
        }
    }
}
void Playing_three::responseoperate(EventCustom *evt)
{
    arr_operates.clear();

    GS2C_OperateAskBroadcast   * outcard = (GS2C_OperateAskBroadcast   *) evt->getUserData();
    //int uid=outcard->current_uid();
    int errorcode=outcard->errorcode();
    int actioncard=outcard->action_card();
   
    google::protobuf::RepeatedField< ::google::protobuf::int32 >  actions=outcard->actions();

    google::protobuf::RepeatedField< ::google::protobuf::int32 >  gang_cars=outcard->gang_cards();

	
    //先解析操作 分割成吃碰杠类型

    int button_num=0;//记录操作数，最后添加过按钮
    for(int i=0;i<actions.size();i++)
    {
        //界面显示能进行的操作
        if(actions.Get(i)!=0)
        {
             if(actions.Get(i)==operate_showpeng)//碰牌
            {
                button_num++;
                arr_actions[button_num-1]->setVisible(true);
                arr_actions[button_num-1]->setEnabled(true);
                arr_actions[button_num-1]->loadTextures("res/srcRes/Z_peng.png","res/srcRes/Z_peng_light.png","res/srcRes/Z_peng_light.png");
                arr_actions[button_num-1]->addClickEventListener(CC_CALLBACK_0(Playing_three::peng_callfunc,this,operate_showpeng,actioncard));
            }
            else if(actions.Get(i)==operate_showgang)//杠牌
            {
                button_num++;
				//这里处理杠牌信息 多组杠牌要提示用户选择
				std::vector<operate_me>arr_gang;
				for(int j=0;j<gang_cars.size();j++)
				{
					operate_me o_p;
					o_p.operatecode=actions.Get(i);
					o_p.card_id=gang_cars.Get(j);
					o_p.arr_gang_mjs.push_back(gang_cars.Get(j));
					o_p.arr_gang_mjs.push_back(gang_cars.Get(j));
					o_p.arr_gang_mjs.push_back(gang_cars.Get(j));
					o_p.arr_gang_mjs.push_back(gang_cars.Get(j));
					arr_gang.push_back(o_p);
				}
                arr_actions[button_num-1]->setVisible(true);
                arr_actions[button_num-1]->setEnabled(true);
                arr_actions[button_num-1]->loadTextures("res/srcRes/Z_gang.png","res/srcRes/Z_gang_light.png","res/srcRes/Z_gang_light.png");
                arr_actions[button_num-1]->addClickEventListener(CC_CALLBACK_0(Playing_three::gang_callfunc,this,arr_gang));

            }
            else if(actions.Get(i)==operate_showting)//听牌
            {
                button_num++;
                arr_actions[button_num-1]->setVisible(true);
                arr_actions[button_num-1]->setEnabled(true);
                arr_actions[button_num-1]->loadTextures("res/srcRes/playing_btn_liang.png","res/srcRes/playing_btn_liang_h.png","res/srcRes/playing_btn_liang_h.png");
                arr_actions[button_num-1]->addClickEventListener(CC_CALLBACK_0(Playing_three::minglou_callfunc,this));//此处进行听牌操作
            }
            else if(actions.Get(i)==operate_showhu)//胡牌
            {
                button_num++;
                arr_actions[button_num-1]->setVisible(true);
                arr_actions[button_num-1]->setEnabled(true);
                arr_actions[button_num-1]->loadTextures("res/srcRes/Z_hu.png","res/srcRes/Z_hu_light.png","res/srcRes/Z_hu_light.png");
                arr_actions[button_num-1]->addClickEventListener(CC_CALLBACK_0(Playing_three::hu_callfunc,this,actioncard));
            }
        }
    }
    arr_actions[button_num]->loadTextures("res/srcRes/playing_btn_guo.png","res/srcRes/playing_btn_guo_h.png","res/srcRes/playing_btn_guo_h.png");
    arr_actions[button_num]->addClickEventListener(CC_CALLBACK_0(Playing_three::guo_callfunc,this));
    arr_actions[button_num]->setVisible(true);
    arr_actions[button_num]->setEnabled(true);

    operate_num=button_num+1;
    
}

//操作结果
void Playing_three::resultofoperate(EventCustom *evt)
{
    GS2C_Operate   * outcard = (GS2C_Operate  *) evt->getUserData();
    //int uid=outcard->current_uid();
    int errorcode=outcard->errorcode();
    //隐藏本人可以操作的按钮
   // refreshactionsbutton(false);
    if(errorcode==0)
    {
        if(outcard->operate_code()==0 )
        {
			refreshactionsbutton(false);
			if(isminglou_over==true)//明搂用户取消胡牌操作
			{
            //自动出牌
            mj_selectedMj=m_mjList.at(m_mjList.size()-1);
            mj_isSelectedMj=true;
            SEND_CUSTOM_MSG("playing_broadcast_outCard");
			}
        }
    }
    else if(errorcode==1)
    {
        for(int i=0;i<arr_actions.size();i++)
        {
            if(i<operate_num)
            {
                arr_actions[i]->setVisible(true);
                arr_actions[i]->setEnabled(true);
            }
            else
            {
                arr_actions[i]->setVisible(false);
                arr_actions[i]->setEnabled(false);
            }

        }
    }
}
void Playing_three::hupai_yinxiao(int op,int sex_)
{
	Tools::playOperateByGender(op,sex_);
}
void Playing_three::playeeffect_normal(std::string path)
{
	Tools::playEffect(path.c_str());
}
//操作结果广播
void Playing_three::responseoperatebroadcast(EventCustom *evt)
{
    GS2C_OperateResultBroadcast   * outcard = (GS2C_OperateResultBroadcast  *) evt->getUserData();
    //int uid=outcard->current_uid();
    int errorcode=outcard->errorcode();
    
    if(errorcode==0)
    {
        isminglou_ing=false;

        int uid=outcard->operate_uid();

        int provideuid=outcard->provide_uid();

        int operatecode=outcard->operate_code();

		int operatecard=outcard->operate_cardid();

		int is_zenrenji=outcard->is_zerenji();

        int hu_type=outcard->hu_type();

		int gang_type=outcard->gang_type();
		

        //首先判断是谁进行的此次操作
        GamerData *p=GamerDataDeal::getInstance()->getGamerData(uid);
        BYTE viewId = GetViewID(GamerData::getInstance()->getSeatId(),p->getSeatId());//计算出当前出牌玩家的界面id

        GamerData *pProvider=GamerDataDeal::getInstance()->getGamerData(provideuid);

        BYTE viewIdProvider = GetViewID(GamerData::getInstance()->getSeatId(),pProvider->getSeatId());//计算出当前出牌玩家的界面id

        //箭头指向
        auto controlLayer = (GameController *)(this->getParent()->getChildByName("mj_controller"));
        controlLayer->setArrowDirection(viewId);

        //音效
		if(operatecode==1||operatecode==2||operatecode==3||operatecode==4||operatecode==9||operatecode==10||operatecode==11)
		{
			m_current_diamond->setVisible(false);
		}
       // Tools::playOperateByGender(operatecode, p->getSex());
		if(operatecode==1||operatecode==2||operatecode==3||operatecode==4||operatecode==5||operatecode==6)
		{
			Tools::playOperateByGender(operatecode, p->getSex());
			
			
		}
		else if(operatecode==7)
		{
			Tools::playOperateByGender(11,p->getSex());
		}
		else if(operatecode==9||operatecode==10||operatecode==11)
		{
			Tools::playOperateByGender(20,p->getSex());
		}
		else  if(operatecode==8)//胡
		{
			if(gang_type!=1&&gang_type!=2&&gang_type!=3)
			{
			if(uid==provideuid) 
			{
				//自摸
				Tools::playOperateByGender(13,p->getSex());//2s后放胡牌音
				Sprite *sp_=Sprite::create("res/cards/mj_1.png");
				sp_->setVisible(false);
				addChild(sp_);
				DelayTime *de=DelayTime::create(1);
				CallFunc *call=CallFunc::create(CC_CALLBACK_0(Playing_three::hupai_yinxiao,this,10,p->getSex()));
				Sequence *se=Sequence::create(de,call,CallFunc::create(CC_CALLBACK_0(Playing_three::removeSp,this,sp_)),nullptr);
				sp_->runAction(se);
			}
			else
			{
                 //点炮
				Tools::playOperateByGender(8,p->getSex());//2s后放胡牌音效
				Sprite *sp_=Sprite::create("res/cards/mj_1.png");
				sp_->setVisible(false);
				addChild(sp_);
				DelayTime *de=DelayTime::create(1);
				CallFunc *call=CallFunc::create(CC_CALLBACK_0(Playing_three::hupai_yinxiao,this,10,p->getSex()));
				Sequence *se=Sequence::create(de,call,CallFunc::create(CC_CALLBACK_0(Playing_three::removeSp,this,sp_)),nullptr);
				sp_->runAction(se);
				
			}
			}
			else
			{
				if(gang_type==1)
				{
					Tools::playOperateByGender(21,p->getSex());//2s后放胡牌音
				}
				else if(gang_type==2)
				{
					Tools::playOperateByGender(22,p->getSex());//2s后放胡牌音
				}
				else if(gang_type==3)
				{
					Tools::playOperateByGender(23,p->getSex());//2s后放胡牌音
				}
				Sprite *sp_=Sprite::create("res/cards/mj_1.png");
				sp_->setVisible(false);
				addChild(sp_);
				DelayTime *de=DelayTime::create(1);
				CallFunc *call=CallFunc::create(CC_CALLBACK_0(Playing_three::hupai_yinxiao,this,10,p->getSex()));
				Sequence *se=Sequence::create(de,call,CallFunc::create(CC_CALLBACK_0(Playing_three::removeSp,this,sp_)),nullptr);
				sp_->runAction(se);
			}
		}

        if(operatecode!=operate_hu)
        {
			//操作成功动画
		//	playeraction_animation(viewId,operatecode); 
            //把手里的牌已经通知成型的 剔除 ，放到已经成型的数组里
            if(viewId==GamerData::getInstance()->getViewId())
            {
				refreshactionsbutton(false);

				if(operatecode==operate_zuopeng||operatecode==operate_youpeng||operatecode==operate_duimenpeng||operatecode==operate_peng)//碰牌
				{	
					//找到碰的2张牌移除手牌 
					int peng_num=0;//记录移除的手牌的数量
					for(int j=0;j<m_mjList.size();j++)
					{
						if(m_mjList.at(j)->id==operatecard)//找到一张
						{
							peng_num++;
							if(peng_num>=3)
							{
								break;
							}
							else
							{
								m_mjList.at(j)->removeFromParent();
								m_mjList.erase(m_mjList.begin()+j);
								j--;
							}
						}
					}
					//型牌里加入这组碰牌
				    operate_result xingpai_peng;
					xingpai_peng.card_id=operatecard;
					xingpai_peng.operate_code=operatecode;
					m_players_chengxing_mjs[0].push_back(xingpai_peng);
					refreshMjsPos();
					refreshxingpaipos(m_players_chengxing_mjs[0],nodeCards[0]->getChildByName("node_chengxing_cards"));

				}
				else if(operatecode==operate_yougang||operatecode==operate_zuogang||operatecode==operate_duimengang)
				{
					//找到碰的3张牌移除手牌 
					int peng_num=0;//记录移除的手牌的数量
					
					for(int j=0;j<m_mjList.size();j++)
					{
						if(m_mjList.at(j)->id==operatecard)//找到一张
						{
							peng_num++;
							if(peng_num>=4)
							{
								break;
							}
							else
							{
								m_mjList.at(j)->removeFromParent();
								m_mjList.erase(m_mjList.begin()+j);
								j--;
							}
						}
					}
					
					//型牌里加入这组碰牌
					operate_result xingpai_peng;
					xingpai_peng.card_id=operatecard;
					xingpai_peng.operate_code=operatecode;
					m_players_chengxing_mjs[0].push_back(xingpai_peng);
					refreshMjsPos();
					refreshxingpaipos(m_players_chengxing_mjs[0],nodeCards[0]->getChildByName("node_chengxing_cards"));


				}
				else if(operatecode==operate_angang)
				{
					CCLOG("angangle!!!!!!!");
					//找到碰的3张牌移除手牌 
					int peng_num=0;//记录移除的手牌的数量
					for(int j=0;j<m_mjList.size();j++)
					{
						if(m_mjList.at(j)->id==operatecard)//找到一张
						{
							peng_num++;
							if(peng_num>=5)
							{
								break;
							}
							else
							{
								m_mjList.at(j)->removeFromParent();
								m_mjList.erase(m_mjList.begin()+j);
								j--;
							}
						}
					}
					//型牌里加入这组碰牌
					operate_result xingpai_peng;
					xingpai_peng.card_id=operatecard;
					xingpai_peng.operate_code=operatecode;
					m_players_chengxing_mjs[0].push_back(xingpai_peng);
					refreshMjsPos();
					refreshxingpaipos(m_players_chengxing_mjs[0],nodeCards[0]->getChildByName("node_chengxing_cards"));
				}
				else if(operatecode==operate_bugang)
				{
					//找到碰的1张牌移除手牌 
					int peng_num=0;//记录移除的手牌的数量
					for(int j=0;j<m_mjList.size();j++)
					{
						if(m_mjList.at(j)->id==operatecard)//找到一张
						{
							peng_num++;
							if(peng_num>=2)
							{
								break;
							}
							else
							{
								m_mjList.at(j)->removeFromParent();
								m_mjList.erase(m_mjList.begin()+j);
								j--;
							}
						}
					}

					//型牌里找到这个碰牌数组 然后改变碰牌类型为杠牌

					for(int j=0;j<m_players_chengxing_mjs[0].size();j++)
					{
						operate_result o_gang=m_players_chengxing_mjs[0].at(j);
						if(o_gang.card_id==operatecard&&(o_gang.operate_code==operate_zuopeng||o_gang.operate_code==operate_youpeng||o_gang.operate_code==operate_duimenpeng||operate_peng==o_gang.operate_code))
						{
							m_players_chengxing_mjs[0].at(j).operate_code=operate_bugang;
							break;
						}
					}
					refreshMjsPos();
					refreshxingpaipos(m_players_chengxing_mjs[0],nodeCards[0]->getChildByName("node_chengxing_cards"));
				}
            }
            else //不是我自己
            {
				//手牌减少 //型牌加入
				if(operatecode==operate_zuopeng||operatecode==operate_duimenpeng||operatecode==operate_youpeng||operatecode==operate_peng)
				{
					hands_cnt[viewId]=hands_cnt[viewId]-2;
					operate_result xingpai_peng;
					xingpai_peng.card_id=operatecard;
					xingpai_peng.operate_code=operatecode;
					m_players_chengxing_mjs[viewId].push_back(xingpai_peng);
				}
				else if(operatecode==operate_zuogang||operatecode==operate_yougang||operatecode==operate_duimengang)
				{
					hands_cnt[viewId]=hands_cnt[viewId]-3;
					operate_result xingpai_peng;
					xingpai_peng.card_id=operatecard;
					xingpai_peng.operate_code=operatecode;
					m_players_chengxing_mjs[viewId].push_back(xingpai_peng);
				}
				else if(operatecode==operate_angang)
				{
					hands_cnt[viewId]=hands_cnt[viewId]-4;
					operate_result xingpai_peng;
					xingpai_peng.card_id=operatecard;
					xingpai_peng.operate_code=operatecode;
					m_players_chengxing_mjs[viewId].push_back(xingpai_peng);
				}
				else if(operatecode=operate_bugang)
				{
                    hands_cnt[viewId]=hands_cnt[viewId]-1;
					//把碰的变成杠的
					for(int j=0;j<m_players_chengxing_mjs[viewId].size();j++)
					{
						operate_result o_gang=m_players_chengxing_mjs[viewId].at(j);
						if(o_gang.card_id==operatecard&&(o_gang.operate_code==operate_zuopeng||o_gang.operate_code==operate_duimenpeng||o_gang.operate_code==operate_youpeng||o_gang.operate_code==operate_peng))
						{
							m_players_chengxing_mjs[viewId].at(j).operate_code=operate_bugang;
							break;
						}
					}
				}
                refreshxingpaiposofothers(m_players_chengxing_mjs[viewId],nodeCards[viewId]->getChildByName("node_chengxing_cards"),viewId,0);
            }

            //0122从已丢弃牌数组中删除最后一个
			int provideViewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(provideuid)->getSeatId());
            if (provideuid!=uid)
            {
				if(is_zenrenji==0)
				{
					m_arr_players_mjs[provideViewid].pop_back();
						
					refreshoutcardByViewId(provideViewid);
				}
				else  if(is_zenrenji==1)//责任及
				{
					playAction_jiAnimation(provideViewid,2);
					Tools::playOperateByGender(14,pProvider->getSex());
					for(int x=0;x<arr_jipai[provideViewid].size();x++)
					{
						if(arr_jipai[provideViewid].at(x)==1)
						{
							arr_jipai[provideViewid].erase(arr_jipai[provideViewid].begin()+x);//删除冲锋机
						}
					}
					refreshjipaiOfPlayer(provideViewid);
				}
				else if(is_zenrenji==2)//普通级
				{
					for(int x=0;x<arr_jipai[provideViewid].size();x++)
					{
						if(arr_jipai[provideViewid].at(x)==2)
						{
							arr_jipai[provideViewid].erase(arr_jipai[provideViewid].begin()+x);//删除普通级
						}
					}
					 if(operatecode==operate_zuogang||operatecode==operate_yougang||operatecode==operate_duimengang)//zheli jin xing gang chong feng ji de pan duan
					 {
						 for(int x=0;x<arr_jipai[provideViewid].size();x++)
						 {
							 if(arr_jipai[provideViewid].at(x)==1)
							 {
								 arr_jipai[provideViewid].erase(arr_jipai[provideViewid].begin()+x);//删除普通级
							 }
						 }

						// 这里要把 冲锋鸡的 图标去掉 并 设置 被杠冲锋鸡玩家的属性为 非冲锋鸡 玩家
						 Node *n=nodePlayers[provideViewid];
						 Sprite *icon=(Sprite *)n->getChildByName("icon_chongfengji");
						 GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(provideViewid);
						 icon->setVisible(false);
						 g->setJi_type(0);
					 }
					refreshjipaiOfPlayer(provideViewid);
				}
            }
			playeraction_animation(viewId,operatecode);
        }
        else
        {
			CCLOG("hu lei xing ===%d",hu_type); 
			CCLOG("gang lei xing ====%d",gang_type);
			if(viewId==0)
			{
				refreshactionsbutton(false);
			}
			if(provideuid!=uid)//点炮
			{
				GamerData *g_pro=GamerDataDeal::getInstance()->getGamerData(provideuid);
				int pro_viewid=GetViewID(GamerData::getInstance()->getSeatId(),g_pro->getSeatId());
				if(arr_jipai[pro_viewid].size()==1&&g_pro->getJi_type()==1&&operatecard==17)//是冲锋鸡且只有一个鸡被别人胡走了
				{
					g_pro->setJi_type(0);
				}
			}
			hu_type_struct hu_t;
			hu_t.gangtype=gang_type;
			hu_t.hutype=hu_type;
			hu_t.viewid=viewId;
			arr_hutype.push_back(hu_t);
        }
    }
}
void Playing_three::playAction_hu_animation()
{
	std::vector<int >arr_hu_viewid;//记录所有胡牌者的id
	int tim_all_animation=0;//记录动画时间
	
	for(int i=0;i<arr_hutype.size();i++)
	{
		 hu_type_struct hu_t=arr_hutype[i];
		 arr_hu_viewid.push_back(hu_t.viewid);
		 if(hu_t.gangtype!=0)
		 {
			 tim_all_animation=2;//总动画时间2s
			 Sprite *sp_temp_=Sprite::create("res/cards/mj_bg3.png");
			 sp_temp_->setVisible(false);
			 addChild(sp_temp_);
			
			 //放杠的动画 然后再放胡的动画 
             CallFunc *call_gang=CallFunc::create(CC_CALLBACK_0(Playing_three::playAction_gang_animationSigle,this,hu_t.viewid,hu_t.gangtype));
			 DelayTime *de_gang=DelayTime::create(1);
			 CallFunc *call_hu=CallFunc::create(CC_CALLBACK_0(Playing_three::playAction_hu_animationSigile,this,hu_t.viewid,hu_t.hutype));
			 DelayTime *de_hu=DelayTime::create(1);
			 CallFunc *call_remove=CallFunc::create(CC_CALLBACK_0(Playing_three::removeSp,this,sp_temp_));
			 Sequence *se=Sequence::create(call_gang,de_gang,call_hu,de_hu,call_remove,nullptr);
			 sp_temp_->runAction(se);
		 }
		 else
		 {
			 tim_all_animation=1;//总动画时间1s
			 Sprite *sp_temp_=Sprite::create("res/cards/mj_bg3.png");
			 sp_temp_->setVisible(false);
			 addChild(sp_temp_);
			 CallFunc *call_hu=CallFunc::create(CC_CALLBACK_0(Playing_three::playAction_hu_animationSigile,this,hu_t.viewid,hu_t.hutype));
			 DelayTime *de_hu=DelayTime::create(1);
			 CallFunc *call_remove=CallFunc::create(CC_CALLBACK_0(Playing_three::removeSp,this,sp_temp_));
			 Sequence *se=Sequence::create(call_hu,de_hu,call_remove,nullptr);
			 sp_temp_->runAction(se);
		 }
	}
	if(arr_hutype.size()>1)
	{
		Sprite *sp_temp_=Sprite::create("res/cards/mj_bg3.png");
		sp_temp_->setVisible(false);
		addChild(sp_temp_);
		DelayTime *de_showYipao=DelayTime::create(tim_all_animation);
		CallFunc *call_yipao=CallFunc::create(CC_CALLBACK_0(Playing_three::playAction_YipaoDuoxiangAnimation,this,arr_hu_viewid,arr_hutype.size()));
		DelayTime *de_yipao=DelayTime::create(3);//设定当前一炮双响动画时间为3s
		CallFunc *call_remove=CallFunc::create(CC_CALLBACK_0(Playing_three::removeSp,this,sp_temp_));
		Sequence *se=Sequence::create(de_showYipao,call_yipao,de_yipao,call_remove,nullptr);
		sp_temp_->runAction(se);
		time_all=tim_all_animation+3;
	}
	else//只有一个人胡牌
	{
		//根据当前的人的动画时间跳转结果界面
		Sprite *sp_temp_=Sprite::create("res/cards/mj_bg3.png");
		sp_temp_->setVisible(false);
		addChild(sp_temp_);
		DelayTime *de_yipao=DelayTime::create(tim_all_animation);//设定当前一炮双响动画时间为3s
		CallFunc *call_remove=CallFunc::create(CC_CALLBACK_0(Playing_three::removeSp,this,sp_temp_));
		Sequence *se=Sequence::create(de_yipao,call_remove,nullptr);
		sp_temp_->runAction(se);
		time_all=tim_all_animation;
	}
}
void Playing_three::removeSp(Sprite *sp)
{
	sp->removeFromParent();
}
void Playing_three::showRresultLayerByOverAnimation(float dt)
{
	cleanallscene();
	Sprite *sp_bg=Sprite::create("res/loading/wait/qd1_0018_bd.png");
	sp_bg->setPosition(Vec2(640,360));
	this->addChild(sp_bg);
	chushihua(false);
	refreshhead();

	layer_result *l_r=(layer_result *)CCDirector::getInstance()->getRunningScene()->getChildByName("result");
	l_r->setVisible(true);
}
void Playing_three::playAction_YipaoDuoxiangAnimation( std::vector<int >arr_hu_viewids,int hu_num)
{
	
}
void Playing_three::playAction_gang_animationSigle(int viewid,int gang_type)
{
	Sprite *sp_action_animation=(Sprite *)nodePlayers[viewid]->getChildByName("icon_action_animation");
	if(gang_type==1)
	{
		sp_action_animation->setTexture("res/srcRes/effect_gangshangkaihua.png");
	}
	else if(gang_type==2)
	{
		sp_action_animation->setTexture("res/srcRes/effect_repao.png");
	}
	else if(gang_type==3)
	{
		sp_action_animation->setTexture("res/srcRes/effect_qiangganghu.png");
	}
	sp_action_animation->setVisible(true);
	Sequence *se=Sequence::create(CallFuncN::create(CC_CALLBACK_0(Playing_three::sp_visible,this,sp_action_animation,true)),DelayTime::create(0.5),CallFuncN::create(CC_CALLBACK_0(Playing_three::sp_visible,this,sp_action_animation,false)),nullptr);
	sp_action_animation->runAction(se);
}
void Playing_three::playAction_hu_animationSigile(int viewid,int hu_type)
{
	Sprite *sp_action_animation=(Sprite *)nodePlayers[viewid]->getChildByName("icon_action_animation");
	sp_action_animation->setVisible(true);
	if(hu_type==1)
	{
		sp_action_animation->setTexture("res/srcRes/11.png");
	}
	else if(hu_type==2)
	{
		sp_action_animation->setTexture("res/srcRes/effect_daduizi.png");
	}
	else if(hu_type==3)
	{
		sp_action_animation->setTexture("res/srcRes/effect_qixiaodui.png");
	}
	else if(hu_type==4)
	{
		sp_action_animation->setTexture("res/srcRes/effect_longqidui.png");
	}
	else if(hu_type==5)
	{
		sp_action_animation->setTexture("res/srcRes/effect_qingyise.png");
	}
	else if(hu_type==6)
	{
		sp_action_animation->setTexture("res/srcRes/effect_qingqidui.png");
	}
	else if(hu_type==7)
	{
		sp_action_animation->setTexture("res/srcRes/effect_qingdadui.png");
	}
	else if(hu_type==8)
	{
		sp_action_animation->setTexture("res/srcRes/effect_qinglongqibei.png");
	}
	Sequence *se=Sequence::create(CallFuncN::create(CC_CALLBACK_0(Playing_three::sp_visible,this,sp_action_animation,true)),DelayTime::create(0.5),CallFuncN::create(CC_CALLBACK_0(Playing_three::sp_visible,this,sp_action_animation,false)),nullptr);
	sp_action_animation->runAction(se);
}
void Playing_three::playeraction_animation(int viewid,int operatecode)
{
    Sprite *sp_action_animation=(Sprite *)nodePlayers[viewid]->getChildByName("icon_action_animation");
	std::string texturepath;
    if(operatecode==operate_zuopeng||operatecode==operate_duimenpeng||operatecode==operate_youpeng||operatecode==operate_peng)
    {
        sp_action_animation->setTexture("res/srcRes/effect_peng_up.png");
		texturepath="res/srcRes/9.png";
    }
    else if(operatecode==operate_angang||operatecode==operate_bugang||operatecode==operate_zuogang||operatecode==operate_yougang||operatecode==operate_duimengang)
    {
        sp_action_animation->setTexture("res/srcRes/effect_gang_up.png");
		texturepath="res/srcRes/10.png";
    }
    else if(operatecode==operate_ting)
    {
        sp_action_animation->setTexture("res/srcRes/effect_ting_up.png");
		texturepath="res/srcRes/14.png";
    }
    else if(operatecode==operate_hu)
    {
        sp_action_animation->setTexture("res/srcRes/effect_hu_up.png");
		texturepath="res/srcRes/11.png";
    }
	else if(operatecode==11)//冲锋鸡
	{
		sp_action_animation->setTexture("res/srcRes/12.png");
	}
	else if(operatecode==12)//责任鸡
	{
		sp_action_animation->setTexture("res/srcRes/13.png");
	}
	ScaleTo *st=ScaleTo::create(0.2,0.8);
	ScaleTo *st1=ScaleTo::create(0.4,1.5);
    Sequence *se=Sequence::create(CallFuncN::create(CC_CALLBACK_0(Playing_three::sp_visible,this,sp_action_animation,true)),DelayTime::create(0.2),st1,st,CallFuncN::create(CC_CALLBACK_0(Playing_three::spsettexture,this,sp_action_animation,texturepath)),DelayTime::create(0.8),CallFuncN::create(CC_CALLBACK_0(Playing_three::sp_visible,this,sp_action_animation,false)),ScaleTo::create(0,1.0),nullptr);
    sp_action_animation->runAction(se);
}
void Playing_three::spsettexture(Sprite *sp,std::string path)
{
	sp->setTexture(path.c_str());
}
void Playing_three::playAction_jiAnimation(int viewid,int jitype)
{
	Sprite *sp_action_animation=(Sprite *)nodePlayers[viewid]->getChildByName("icon_action_animation");
	Node *n=nodePlayers[viewid];
	Sprite *icon=(Sprite *)n->getChildByName("icon_chongfengji");
	GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(viewid);
	if(jitype==1)//冲锋机
	{
		sp_action_animation->setTexture("res/srcRes/12.png");
        icon->setTexture("res/loading/play/icon_chong.png");
		icon->setVisible(true);
		g->setJi_type(1);
	}
	else if(jitype==2)
	{
		sp_action_animation->setTexture("res/srcRes/13.png");
		icon->setTexture("res/srcRes/icon_ze.png");
		g->setJi_type(2);
		icon->setVisible(true);
	}
	Sequence *se=Sequence::create(CallFuncN::create(CC_CALLBACK_0(Playing_three::sp_visible,this,sp_action_animation,true)),DelayTime::create(0.5),CallFuncN::create(CC_CALLBACK_0(Playing_three::sp_visible,this,sp_action_animation,false)),nullptr);
	sp_action_animation->runAction(se);
}
void Playing_three::sp_visible(Sprite *sp,bool isvisible)
{
    sp->setVisible(isvisible);
}
void Playing_three::refreshjipaiOfPlayer(int viewid)
{
	Node *node_jipai=nodeCards[viewid]->getChildByName("node_ji");
	
	for(int i=0;i<4;i++)
	{
		String *ji_path=String::createWithFormat("mj_bg_%d",i+1);
		Sprite *ji=(Sprite *)node_jipai->getChildByName(ji_path->getCString());
		ji->setVisible(false);
	}
	bool ishavechongfengji=false;

	for(int i=0;i<arr_jipai[viewid].size();i++)
	{
		if(arr_jipai[viewid].at(i)==1)//这一张是重逢及
		{
			ishavechongfengji=true;
			break;
		}
	}
	if(ishavechongfengji==true)
	{
		for(int i=0;i<arr_jipai[viewid].size();i++)
		{
			String *ji_path=String::createWithFormat("mj_bg_%d",i+1);
			Sprite *ji=(Sprite *)node_jipai->getChildByName(ji_path->getCString());
			ji->setVisible(true);
			Sprite *ji_texture=(Sprite *)ji->getChildByName("mj_value");
			ji_texture->setTexture("res/cards/mj_11.png");
		}
	}
	else
	{
		for(int i=0;i<arr_jipai[viewid].size();i++)
		{
			String *ji_path=String::createWithFormat("mj_bg_%d",i+2);
			Sprite *ji=(Sprite *)node_jipai->getChildByName(ji_path->getCString());
			ji->setVisible(true);
			Sprite *ji_texture=(Sprite *)ji->getChildByName("mj_value");
			ji_texture->setTexture("res/cards/mj_11.png");
		}
	}
}
void Playing_three::refreshoutcardByViewId(int viewid)
{
	//刷新玩家打出的牌
	std::vector<int >arr_cardsout=m_arr_players_mjs[viewid];
	for(int j=0;j<27;j++)
	{
		String *path=String::createWithFormat("mj_bg_%d",j+1);
		Sprite *sp_mj=(Sprite *)nodeCards[viewid]->getChildByName("node_outcard")->getChildByName(path->getCString());
		sp_mj->setVisible(false);//所有的打出的牌先设置为不可见
	}
	for(int j=0;j<arr_cardsout.size();j++)
	{
		String *path=String::createWithFormat("mj_bg_%d",j+1);
		Sprite *sp_mj=(Sprite *)nodeCards[viewid]->getChildByName("node_outcard")->getChildByName(path->getCString());
		sp_mj->setVisible(true);//按顺序找到打出的这张牌

		String *cardpath=String::createWithFormat("res/cards/mj_%d.png",arr_cardsout[j]/16*10+arr_cardsout[j]%16);
		Sprite *sp_card=(Sprite *)sp_mj->getChildByName("mj_value");
		sp_card->setTexture(cardpath->getCString());
	}
}
void Playing_three::refreshxingpaiposofothers(std::vector<operate_result>arr_mjs,Node *parent,int viewid ,int ismopai)
{
    //手牌重新整理
	if(ismopai==0)
	{
		for(int i=14;i>0;i--)
		{
			Node *n=nodeCards[viewid]->getChildByName("nodeCards");

			Sprite *i_m=(Sprite *)n->getChildByName(String::createWithFormat("poker_%d",14-i+1)->getCString());
			i_m->setPosition(arr_hand_pos[viewid].at(14-i));
			i_m->setVisible(false);

			if(i<=hands_cnt[viewid])
			{
				i_m->setVisible(true);
			}
		}
	}
	else
	{
		for(int i=14;i>0;i--)
		{
			Node *n=nodeCards[viewid]->getChildByName("nodeCards");

			Sprite *i_m=(Sprite *)n->getChildByName(String::createWithFormat("poker_%d",14-i+1)->getCString());

			i_m->setVisible(false);

			if(i<=hands_cnt[viewid])
			{
				i_m->setVisible(true);
			}
			if(i==1)
			{
				if(viewid==1)
				{
					i_m->setPosition(i_m->getPosition()+Vec2(0,30));
				}
				else if(viewid==2)
				{
					i_m->setPosition(i_m->getPosition()+Vec2(0,-30));
				}
				else if(viewid==3)
				{
					i_m->setPosition(i_m->getPosition()+Vec2(0,-30));
				}
			}
		}

	}
   
	
	//形牌进行整理

	float hegigh=22.5;
	float bottom_lenth=44;
	float top_lenth=44;
	float middle_lenth=82;

	float hegigh1=-10.24;
	float bottom_lenth1=43;
	float top_lenth1=43;
	float middle_lenth1=105;

	float hegigh2=0;
	float bottom_lenth2=44;
	float top_lenth2=44;
	float middle_lenth2=82;

	

    for(int i=0;i<arr_mjs.size();i++)
    {
		if(viewid==2)
		{
			viewid=3;
		}
        String *name_big=String::createWithFormat("node_chengxing_%d",i+1);

        Node *n_big=(Node *)parent->getChildByName(name_big->getCString());

        n_big->setVisible(true);

        operate_result o_p=arr_mjs[i];
      
		
		//刷新形牌
		if(o_p.operate_code==operate_zuopeng)
			{
					n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_1")->setVisible(false);

					n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);
					n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
					n_big->getChildByName("mj_sp_chengxing_6")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_6")->getChildByName("mj_value"),o_p.card_id);
				

				if(viewid==1)
				{
					
						n_big->setPosition(Vec2(0,hegigh));
						hegigh=hegigh+10+230-128;
					
				} 
				else if(viewid==2)
				{
					
					
						n_big->setPosition(Vec2(hegigh1,0));
						hegigh1=hegigh1-(937-827)-10;
					
				}
				else if(viewid==3)
				{
						n_big->setPosition(Vec2(0,hegigh2));
						hegigh2=hegigh2-(679-584)-10;
					
				}

		   }
		   else if(o_p.operate_code==operate_peng)
		   {
			   n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);

				if(viewid==1)
				{
					n_big->setPosition(Vec2(0,hegigh-bottom_lenth));
					hegigh=hegigh+middle_lenth+10;
					
				} 
				else if(viewid==2)
				{
					n_big->setPosition(Vec2(hegigh1+bottom_lenth1,0));
					hegigh1=hegigh1-middle_lenth1-10;
				}
				else if(viewid==3)
				{
					n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
					hegigh2=hegigh2-middle_lenth2-10;
					
				}
	        }
		else if(o_p.operate_code==operate_duimenpeng)//1碰 2左杠 3右杠 4对门杠
		{
			
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_8")->getChildByName("mj_value"),o_p.card_id);
			

			if(viewid==1)
			{
				
				
					n_big->setPosition(Vec2(0,hegigh-bottom_lenth));
					hegigh=hegigh+10+231-172;
				
			} 
			else if(viewid==2)
			{
				
					n_big->setPosition(Vec2(hegigh1+bottom_lenth1,0));
					hegigh1=hegigh1-(896-827)-10;
				

			}
			else if(viewid==3)
			{
				
					n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
					hegigh2=hegigh2-(636-584)-10;
				
			}

		}
		else if(o_p.operate_code==operate_youpeng)//1碰 2左杠 3右杠 4对门杠
		{
			
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_4")->getChildByName("mj_value"),o_p.card_id);
			
			if(viewid==1)
			{
				
					n_big->setPosition(Vec2(0,hegigh-(206-129)));
					hegigh=hegigh+10+299-206;
				
			} 
			else if(viewid==2)
			{
				
				
					n_big->setPosition(Vec2(hegigh1+(937-862),0));
					hegigh1=hegigh1-(862-749)-10;
				
			}
			else if(viewid==3)
			{
				
					n_big->setPosition(Vec2(0,hegigh2+(680-612)));
					hegigh2=hegigh2-(612-511)-10;
				

			}

		}
			else if(o_p.operate_code==operate_zuogang)//左杠
			{
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_6")->getChildByName("mj_value"),o_p.card_id);
				if(viewid==1)
				{
					n_big->setPosition(Vec2(0,hegigh));
					hegigh=hegigh+middle_lenth+10+top_lenth;
				}
				else if(viewid==2)
				{
					n_big->setPosition(Vec2(hegigh1,0));
					hegigh1=hegigh1-middle_lenth1-10-top_lenth1;
				}
				else if(viewid==3)
				{
					n_big->setPosition(Vec2(0,hegigh2));
					hegigh2=hegigh2-middle_lenth2-10-top_lenth2;
				}
				
			}
			else if(o_p.operate_code==3)//右杠
			{
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_4")->getChildByName("mj_value"),o_p.card_id);
				if(viewid==1)
				{
					n_big->setPosition(Vec2(0,hegigh-bottom_lenth));
					hegigh=hegigh+middle_lenth+10+top_lenth;
				}
				else if(viewid==2)
				{
					n_big->setPosition(Vec2(hegigh1+bottom_lenth1,0));
					hegigh1=hegigh1-middle_lenth1-10-top_lenth1;
				}
				else if(viewid==3)
				{
					n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
					hegigh2=hegigh2-middle_lenth2-10-top_lenth2;
				}
				
			}
			else if(o_p.operate_code==4)//对门杠
			{
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_5")->getChildByName("mj_value"),o_p.card_id);
				if(viewid==1)
				{
					n_big->setPosition(Vec2(0,hegigh-top_lenth));
					hegigh=hegigh+middle_lenth+10;
				}
				else if(viewid==2)
				{
					n_big->setPosition(Vec2(hegigh1+bottom_lenth1,0));
					hegigh1=hegigh1-middle_lenth1-10-top_lenth1;
				}
				else if(viewid==3)
				{
					n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
					hegigh2=hegigh2-middle_lenth2-10;
				}
				
			}
			else if(o_p.operate_code==5)//补杠
			{
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_7")->getChildByName("mj_value"),o_p.card_id);
				if(viewid==1)
				{
					n_big->setPosition(Vec2(0,hegigh-top_lenth));
					hegigh=hegigh+middle_lenth+10;
				}
				else if(viewid==2)
				{
					n_big->setPosition(Vec2(hegigh1+bottom_lenth1,0));
					hegigh1=hegigh1-middle_lenth1-10-top_lenth1;
				}
				else if(viewid==3)
				{
					n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
					hegigh2=hegigh2-middle_lenth2-10;
				}
			}
			else if(o_p.operate_code==6)//暗杠
			{
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_7")->getChildByName("mj_value"),o_p.card_id);
				

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
				if(viewid==0)
				{
					sp_big1->setTexture("res/cards/mj_bg4.png");
					sp_big2->setTexture("res/cards/mj_bg4.png");
					sp_big3->setTexture("res/cards/mj_bg4.png");


				}
				else if(viewid==1)
				{
					sp_big1->setTexture("res/cards/mj_bg6.png");
					sp_big2->setTexture("res/cards/mj_bg6.png");
					sp_big3->setTexture("res/cards/mj_bg6.png");
					
					n_big->setPosition(Vec2(0,hegigh-top_lenth));
					hegigh=hegigh+middle_lenth+10;
					
				}
				else if(viewid==2)
				{
					sp_big1->setTexture("res/cards/mj_bg4.png");
					sp_big2->setTexture("res/cards/mj_bg4.png");
					sp_big3->setTexture("res/cards/mj_bg4.png");
				
					n_big->setPosition(Vec2(hegigh1+bottom_lenth1,0));
					hegigh1=hegigh1-middle_lenth1-10-top_lenth1;
				
				}
				else if(viewid==3)
				{
					sp_big1->setTexture("res/cards/mj_bg6.png");
					sp_big2->setTexture("res/cards/mj_bg6.png");
					sp_big3->setTexture("res/cards/mj_bg6.png");
				
					n_big->setPosition(Vec2(0,hegigh2+bottom_lenth2));
					hegigh2=hegigh2-middle_lenth2-10;
				
				}
			}
		}
}
void Playing_three::sortpokersbywhx(std::vector<MjNode *>arr_mjs)
{
    std::sort(arr_mjs.begin(), arr_mjs.end(), [](MjNode* a,MjNode* b){
        if(a->getLogicValue() != b->getLogicValue() ) return a->getLogicValue()< b->getLogicValue();
        else return a->id < b->id;
    });
}
void Playing_three::sortMjByLaiya(std::vector<int > &arr_mjs)
{
	std::sort(arr_mjs.begin(), arr_mjs.end(), [](int a,int b){
		return a<b;
	});
}
void Playing_three::sortMjByLaiya_cardshow(std::vector<int> &arr_poker)
{
	std::sort(arr_poker.begin(), arr_poker.end(), [](int a,int b){
		return a>b;
	});
}
void Playing_three::refreshxingpaipos(std::vector<operate_result>arr_poker, Node *parent)
{
	int pos_origin_x=0;
	int pos_origin_y=1.13;
	int jiange=20;
		//形牌进行整理
		for(int i=0;i<arr_poker.size();i++)
		{
			String *name_big=String::createWithFormat("node_chengxing_%d",i+1);

			Node *n_big=(Node *)parent->getChildByName(name_big->getCString());

			n_big->setVisible(true);

			operate_result o_p=arr_poker[i];

			//刷新形牌
			
				if(o_p.operate_code==operate_peng)
				{
					n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);


					n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
					n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
					n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);
					n_big->setPosition(Vec2(pos_origin_x-43,pos_origin_y));
					pos_origin_x=pos_origin_x+10+138;
				}
				else if(o_p.operate_code==operate_zuopeng)
				{
					n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_3")->setVisible(false);


					n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
					n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
					n_big->getChildByName("mj_sp_chengxing_6")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_6")->getChildByName("mj_value"),o_p.card_id);

					n_big->setPosition(Vec2(pos_origin_x,pos_origin_y));
					pos_origin_x=pos_origin_x+10+147;
				}
				else if(o_p.operate_code==operate_youpeng)
				{
					n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_1")->setVisible(false);

					n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
					n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);
					n_big->getChildByName("mj_sp_chengxing_4")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_4")->getChildByName("mj_value"),o_p.card_id);

					n_big->setPosition(Vec2(pos_origin_x-99,pos_origin_y));
					pos_origin_x=pos_origin_x+10+147;
				}
				else if(o_p.operate_code==operate_duimenpeng)
				{
					n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
					n_big->getChildByName("mj_sp_chengxing_3")->setVisible(false);

					n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
					n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
					n_big->getChildByName("mj_sp_chengxing_8")->setVisible(true);
					initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_8")->getChildByName("mj_value"),o_p.card_id);

					n_big->setPosition(Vec2(pos_origin_x-43,pos_origin_y));
					pos_origin_x=pos_origin_x+10+97;
				}
			else if(o_p.operate_code==operate_zuogang)//左杠
			{
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_6")->getChildByName("mj_value"),o_p.card_id);

				n_big->setPosition(Vec2(pos_origin_x,pos_origin_y));
				pos_origin_x=pos_origin_x+jiange+138+43;
			}
			else if(o_p.operate_code==3)//右杠
			{
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_4")->getChildByName("mj_value"),o_p.card_id);

				n_big->setPosition(Vec2(pos_origin_x-43,pos_origin_y));
				pos_origin_x=pos_origin_x+jiange+138+46;
			}
			else if(o_p.operate_code==4)//对门杠
			{
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_5")->getChildByName("mj_value"),o_p.card_id);

				n_big->setPosition(Vec2(pos_origin_x-43,pos_origin_y));
				pos_origin_x=pos_origin_x+jiange+138;
			}
			else if(o_p.operate_code==5)//补杠
			{
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);

				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_1")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_2")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_3")->getChildByName("mj_value"),o_p.card_id);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_7")->getChildByName("mj_value"),o_p.card_id);

				n_big->setPosition(Vec2(pos_origin_x-43,pos_origin_y));
				pos_origin_x=pos_origin_x+jiange+138;
			}
			else if(o_p.operate_code==6)//暗杠
			{
				n_big->getChildByName("mj_sp_chengxing_4")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_5")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_6")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_8")->setVisible(false);
				n_big->getChildByName("mj_sp_chengxing_7")->setVisible(true);
				initcardWithCardIds((Sprite *)n_big->getChildByName("mj_sp_chengxing_7")->getChildByName("mj_value"),o_p.card_id);
				

				n_big->getChildByName("mj_sp_chengxing_1")->setVisible(true);
				Sprite *sp_big1=(Sprite *)n_big->getChildByName("mj_sp_chengxing_1");
				Sprite *sp_1=(Sprite *)sp_big1->getChildByName("mj_value");//暗杠要把最上面那个牌变成暗杠的
				sp_1->setVisible(false);
				sp_big1->setTexture("res/cards/mj_bg4.png");

				n_big->getChildByName("mj_sp_chengxing_2")->setVisible(true);
				Sprite *sp_big2=(Sprite *)n_big->getChildByName("mj_sp_chengxing_2");
				Sprite *sp_2=(Sprite *)sp_big2->getChildByName("mj_value");//暗杠要把最上面那个牌变成暗杠的
				sp_2->setVisible(false);
				sp_big2->setTexture("res/cards/mj_bg4.png");

				n_big->getChildByName("mj_sp_chengxing_3")->setVisible(true);
				Sprite *sp_big3=(Sprite *)n_big->getChildByName("mj_sp_chengxing_3");
				Sprite *sp_3=(Sprite *)sp_big3->getChildByName("mj_value");//暗杠要把最上面那个牌变成暗杠的
				sp_3->setVisible(false);
				sp_big3->setTexture("res/cards/mj_bg4.png");

				n_big->setPosition(Vec2(pos_origin_x-43,pos_origin_y));
				pos_origin_x=pos_origin_x+jiange+138;
			}
		}

}
 //}
	

//过回调
void  Playing_three::guo_callfunc()
{
    ::google::protobuf::RepeatedField< ::google::protobuf::int32 > cards;
    TableCommand::getInstance()->requestoperate(0,0);
}
//吃牌回调
void Playing_three::chi_callfunc(std::vector<operate_me >arr_chi)
{
    if(arr_chi.size()!=0)
    {
        if(arr_chi.size()==1)//只吃一套 直接吃
        {
            operate_chi(arr_chi[0]);
        }
        else//吃多套 显示可吃牌型 并在牌型按钮上添加回调
        {
            showcards_chi(arr_chi);
        }
    }
}
//碰牌回调
void Playing_three::peng_callfunc(int opreratecode,int action_card)
{
    TableCommand::getInstance()->requestoperate(opreratecode,action_card);
}
//杠牌回调
void Playing_three::gang_callfunc(std::vector<operate_me>gang_arr)
{
    if(gang_arr.size()!=0)
    {
        if(gang_arr.size()==1)
        {
            oprate_gang(gang_arr[0]);
        }
        else
        {
            refreshactionsbutton(false);
            showcards_gang(gang_arr);
        }
    }
}
//胡牌回调
void Playing_three::hu_callfunc(int actioncard)
{
    TableCommand::getInstance()->requestoperate(7,actioncard);
}
//明楼回调
void Playing_three::minglou_callfunc()
{
    //点击明楼 要发起请求
    TableCommand::getInstance()->requestminglouask();
}
void Playing_three::responseready(EventCustom *evt)
{
	UserDefault::getInstance()->setBoolForKey("iscanbreak",true);

	GS2C_Ready *ready=(GS2C_Ready *)evt->getUserData();
	int bankerid=ready->banker_uid();
	MjData::getInstance()->setbanker(bankerid);
	int bankerviewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(MjData::getInstance()->getbanker())->getSeatId());
	auto controlLayer = (GameController *)(this->getParent()->getChildByName("mj_controller"));
	controlLayer->setArrowRoatation(MjData::getInstance()->getfangzhu_viewid());
	controlLayer->arrowvisible(false);
	refreshhead();
	//SEND_CUSTOM_MSG("readySuccessForRemoveResult");
	
}
void Playing_three::responsereadybroadcast(EventCustom *evt)
{
    GS2C_ReadyBroadcast   * outcard = (GS2C_ReadyBroadcast  *) evt->getUserData();
    int uid=outcard->uid();

	int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uid)->getSeatId());
	nodePlayers[viewid]->getChildByName("icon_ready")->setVisible(true);
}
void Playing_three::responseminglouask(EventCustom *evt)
{
    refreshactionsbutton(false);
    GS2C_MinglouAsk   * outcard = (GS2C_MinglouAsk  *) evt->getUserData();
    ::google::protobuf::RepeatedField< ::google::protobuf::int32 > cards=outcard->can_discard_cards();

    for(int i=0;i<m_mjList.size();i++)
    {
        m_mjList.at(i)->setstatecantoperate(false);
        m_mjList.at(i)->btnMj->setColor(Color3B(100,100,100));
        m_mjList.at(i)->valueMj->setColor(Color3B(100,100,100));
    }

    for(int i=0;i<m_mjList.size();i++)
    {
        for (int j = 0; j < cards.size() ; j++)
        {
            if(m_mjList.at(i)->id==cards.Get(j))
            {
                m_mjList.at(i)->setstatecantoperate(true);
                m_mjList.at(i)->btnMj->setColor(Color3B(255,255,255));
                m_mjList.at(i)->valueMj->setColor(Color3B(255,255,255));
                isminglou_ing=true;
                break;
            }
        }
    }
}
void Playing_three::responsemingloubroadcast(EventCustom *evt)
{
    GS2C_MinglouBroadcast   * outcard = (GS2C_MinglouBroadcast  *) evt->getUserData();
    ::google::protobuf::RepeatedField< ::google::protobuf::int32 > cards=outcard->minglou_cards();
    int uid=outcard->minglou_uid();
    //展示明楼用户的牌组
    GamerData* pGamerData = GamerDataDeal::getInstance()->getGamerData(uid);
    BYTE viewId = GetViewID(GamerData::getInstance()->getSeatId(),pGamerData->getSeatId());
  
	GamerData *g=GamerDataDeal::getInstance()->getGamerData(uid);
	g->setistingpai(1);
    //判断当前明楼用户是不是自己是的话把手牌按钮设置为不可点击并且设置为正常颜色
    if(GamerData::getInstance()->getUId()==uid)
    {
		//这里要设置 听牌 状态
		GamerData::getInstance()->setistingpai(1);
        for(int i=0;i<m_mjList.size();i++)
        {
            m_mjList.at(i)->setstatecantoperate(false);
            m_mjList.at(i)->btnMj->setColor(Color3B(255,255,255));
            m_mjList.at(i)->valueMj->setColor(Color3B(255,255,255));
        }
    }
	int viewid=GetViewID(GamerData::getInstance()->getSeatId(),g->getSeatId());
	playeraction_animation(viewId,operate_ting); 
	Tools::playOperateByGender(11,g->getSex());
	Sprite *sp_icon_ting=(Sprite *)nodePlayers[viewid]->getChildByName("icon_tingpai");
	sp_icon_ting->setVisible(true);
}
void Playing_three::responseonroundendbroadcast(EventCustom *evt)
{
	//数据
	GS2C_RoundResultBroadcast    * outcard = (GS2C_RoundResultBroadcast   *) evt->getUserData();
	::google::protobuf::RepeatedPtrField< ::pb::ResultItem > cards=outcard->result_list();
	
	  
	std::vector<resultitem>arr_resultitem;
	for(int i=0;i<cards.size();i++)
	{
		resultitem r_i_one;

		std::vector<weaveitem>arr_weaves;

		::google::protobuf::RepeatedPtrField< ::pb::WeaveItem > weave=cards.Get(i).weaves();
		for(int j=0;j<weave.size();j++)
		{
			weaveitem w_struct;
			WeaveItem w=weave.Get(j);
			w_struct.weavekin=w.weave_kind();
			w_struct.cardid=w.card_id();
			arr_weaves.push_back(w_struct);
		}
		r_i_one.arr_weaves=arr_weaves;
		r_i_one.gold_change=cards.Get(i).win_fan_cnt();
		r_i_one.uid=cards.Get(i).uid();
		r_i_one.hu_type=cards.Get(i).hupai_type();
		r_i_one.gang_type=cards.Get(i).hupai_fangshi();
		r_i_one.jinum=cards.Get(i).ji_num();
		r_i_one.total_gold=cards.Get(i).total_gold();
		r_i_one.hu_cardid=cards.Get(i).hu_cardid();
		//更新玩家的金币值
		GamerData* pGamerData = GamerDataDeal::getInstance()->getGamerData(r_i_one.uid); 
		if(pGamerData == NULL) 
			return;
		pGamerData->setGold(r_i_one.total_gold);

		std::vector<int >hand_cards;
		for(int l=0;l<cards.Get(i).hand_cards().size();l++)
		{
			hand_cards.push_back(cards.Get(i).hand_cards().Get(l));
		}
		r_i_one.handcards=hand_cards;
		arr_resultitem.push_back(r_i_one);
	}
	r_i.arr_resluts=arr_resultitem;
	r_i.fanpaiji_id=outcard->fanpaiji_cardid();
	r_i.is_huangzhuang=outcard->is_huangzhuang();
	fanpai_cardid=r_i.fanpaiji_id;
	
	MjData::getInstance()->setleftjushu(MjData::getInstance()->getleftjushu()-1);
	GameMain *g_main=(GameMain *)this->getParent();
	g_main->mj_controller->refreshjushu();
	

	//数据解析完毕 这里可以进行创建界面 进行显示(r_i里存放了全部的结果数据)
	layer_result *l_r=layer_result::create();
	l_r->initwithdata(r_i);
	l_r->setVisible(false);
	l_r->setName("result");
	CCDirector::getInstance()->getRunningScene()->addChild(l_r,999);
	//记录下一句的庄家
	//解析数据
	::google::protobuf::RepeatedPtrField< ::pb::DetailItem > cards_de=outcard->details().result_list();
	result_detail_struct r_s;

	std::vector<result_DetailItem>arr_result_detail;
	for(int i=0;i<cards_de.size();i++)
	{
		result_DetailItem r_i_one;

		std::vector<result_LittleItem>arr_littles;

		::google::protobuf::RepeatedPtrField< ::pb::LittleItem > littles=cards_de.Get(i).weaves();

		for(int j=0;j<littles.size();j++)
		{
			result_LittleItem r_l;
			r_l.kind_type=littles.Get(j).kind();
			r_l.color=littles.Get(j).color();
			r_l.fenzhi=littles.Get(j).fen();
			r_l.zhuang2bei=littles.Get(j).is_zhuang2bei();
			arr_littles.push_back(r_l);
		}
		r_i_one.arr_littleitem=arr_littles;
		r_i_one.uid=cards_de.Get(i).uid();
		arr_result_detail.push_back(r_i_one);
	}

	if(MjData::getInstance()->getleftjushu()==-1)
	{
		UserDefault::getInstance()->setBoolForKey("iscanbreak",false);
	}
	else
	{
		UserDefault::getInstance()->setBoolForKey("iscanbreak",true);
	}
	

	r_s.arr_detailitem=arr_result_detail;

	l_r->l_detail=layer_result_detail::create();
	l_r->addChild(l_r->l_detail);
	l_r->l_detail->setVisible(false);
	l_r->l_detail->initwithdata(r_s);
	
	l_r->l_detail->setZOrder(-1);
	playAction_hu_animation();
	refreshcard_show(r_i);
	if(arr_hutype.size()!=0)
	{
		//展示翻牌鸡
		CCLOG("zhanshifanpaiji");
		scheduleOnce(schedule_selector(Playing_three::showfanpaiji),time_all);
		time_all=time_all+3;
	}
	
	//展示结果界面
	scheduleOnce(schedule_selector(Playing_three::showRresultLayerByOverAnimation),time_all);

}
void Playing_three::refreshcard_show(oneroundresult r_show)
{
	std::vector<resultitem >arr_re=r_show.arr_resluts;
	for(int i=0;i<arr_re.size();i++)
	{
		nodeCards[i]->getChildByName("nodeCards")->setVisible(false);//手牌隐藏
		resultitem r_r_one=arr_re[i];
		sortMjByLaiya_cardshow(r_r_one.handcards);
		int uid=r_r_one.uid;
		int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uid)->getSeatId());

		bool ishavezimo=false;
		if(r_r_one.gang_type==1||r_r_one.gang_type==4)//是否是自摸
		{
			ishavezimo=true;
			//如果是自摸 就要把 胡的牌放到最后
			
					std::vector<int >arr_temp;
					arr_temp.push_back(r_r_one.hu_cardid);
					for(int  m=0;m<r_r_one.handcards.size();m++)
					{
						arr_temp.push_back(r_r_one.handcards[m]);
					}
					r_r_one.handcards.clear();
					for(int y=0;y<arr_temp.size();y++)
					{
						r_r_one.handcards.push_back(arr_temp[y]);
					}
					
			
		}
		Node *n_re=nodeCards[viewid]->getChildByName("nodeCards_show");
		for(int j=0;j<14;j++)
		{
			String *path_s=String::createWithFormat("poker_%d",j+1);
			Sprite *sp_mj=(Sprite *)n_re->getChildByName(path_s->getCString());
			if(j>=r_r_one.handcards.size())
			{
				sp_mj->setVisible(false);
			}
			else
			{
				sp_mj->setVisible(true);
				Sprite *mj_value=(Sprite *)sp_mj->getChildByName("mj_value");
				int value_card=r_r_one.handcards[j]/16*10+r_r_one.handcards[j]%16;
				String *str_value=String::createWithFormat("res/cards/mj_%d.png",value_card);
				mj_value->setTexture(str_value->getCString());

				if(ishavezimo==true&&j==0)
				{
					if(viewid==0)
					{
						sp_mj->setPosition(sp_mj->getPosition()+Vec2(10,0));
					}
					else if(viewid==1)
					{
						sp_mj->setPosition(sp_mj->getPosition()+Vec2(0,10));
					}
					else if(viewid==2)
					{
						sp_mj->setPosition(sp_mj->getPosition()+Vec2(0,-10));
					}
				}
			}
		}

	}
}
void Playing_three::showfanpaiji(float dt)
{
	CCLOG("zhanshifanpaijiid==%d",fanpai_cardid);
	TipContent *tip_fan=TipContent::create();
	tip_fan->showUiFanpaiji(fanpai_cardid);
	CCDirector::getInstance()->getRunningScene()->addChild(tip_fan,2220);
}
void Playing_three::dismisssuccessbroadcast(EventCustom *evt)
{
	diamisssuccess=2;
}
void Playing_three::dismissAskBroadcast(EventCustom *evt)
{
    //数据
    GS2C_DismissAskBroadcast    * outcard = (GS2C_DismissAskBroadcast   *) evt->getUserData();
    int ask_uid=outcard->ask_uid();
	layer_dismiss *l_d=layer_dismiss::create();
	l_d->initwithaskuid(ask_uid);
	this->getParent()->addChild(l_d,10);
}
void Playing_three::refreshhead()
{
    for(int i=0;i<3;i++)
    {
        nodePlayers[i]->setVisible(true);
        Node *uerinfo=(Node *)nodePlayers[i];
        Text *tx_name=(Text *)uerinfo->getChildByName("nickName");
        Text *tx_score=(Text *)uerinfo->getChildByName("score");
        Sprite *sp_head=(Sprite *)uerinfo->getChildByName("icon");
        Sprite *iszhuang=(Sprite *)uerinfo->getChildByName("isHost");
        GamerData *p=GamerDataDeal::getInstance()->getGamerDataBySeat(i);
        if(p->getUId()==MjData::getInstance()->getbanker())
        {
            iszhuang->setVisible(true);
        }
        else
        {
            iszhuang->setVisible(false);
        }
		if(p->getJi_type()==0)
		{
			 Sprite *ji_type_icon=(Sprite *)uerinfo->getChildByName("icon_chongfengji");
			 ji_type_icon->setVisible(false);
		}
        tx_name->setString(p->getNick().c_str());
        tx_score->setString(String::createWithFormat("%d",p->getGold())->getCString() );
        std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
        String *s=String::createWithFormat("%s%d.png",path.c_str(),p->getUId());
        sp_head->setTexture(s->getCString());

        float scale_rate= float(46*1.5)/sp_head->getContentSize().height;
        sp_head->setScale(scale_rate);
    }
}
//显示可以吃的牌
void Playing_three::showcards_chi(std::vector<operate_me > chi_arr)
{
    refreshactionsbutton(false);
    setcards_detail_actionsisvisible(true);
    for(int i=0;i<3;i++)
    {
        String *name=String::createWithFormat("Button_action_arr_%d",i+1);
        Button *bt_call_chi=(Button *)node_detail_actions->getChildByName(name->getCString());
        if(chi_arr.size()>i)
        {
            bt_call_chi->setVisible(true);
        }
        else
        {
            bt_call_chi->setVisible(false);
        }
    }
    for(int i=0;i<chi_arr.size();i++)
    {
        String *name=String::createWithFormat("Button_action_arr_%d",i+1);
        Button *bt_call_chi=(Button *)node_detail_actions->getChildByName(name->getCString());

        int mj_vule=chi_arr[i].card_id/16*10+chi_arr[i].card_id%16;
        int mj_real_value=chi_arr[i].card_id;
        int mj_real_value_next;
        int mj_real_value_last;
        if(chi_arr[i].operatecode==1)//坐吃
        {
            mj_vule=mj_vule;
            mj_real_value_next=mj_real_value+1;
            mj_real_value_last=mj_real_value+2;
        }
        else if(chi_arr[i].operatecode==2)//中翅
        {
            mj_vule=mj_vule-1;
            mj_real_value_next=mj_real_value-1;
            mj_real_value_last=mj_real_value+1;
        }
        else if(chi_arr[i].operatecode==3)//有吃
        {
            mj_vule=mj_vule-2;
            mj_real_value_next=mj_real_value-1;
            mj_real_value_last=mj_real_value-2;
        }
        for(int j=0;j<3;j++)
        {
            String *name_mj=String::createWithFormat("mj_sp_%d",3-j);
            Sprite *sp_mj=(Sprite *)bt_call_chi->getChildByName(name_mj->getCString());
            sp_mj->setAnchorPoint(Vec2(0.5,0.5));
			sp_mj->removeAllChildren();
            String *path_majiangmian=String::createWithFormat("res/cards/mj_%d.png",mj_vule+j);
            Sprite *sp_mj_num=Sprite::create(path_majiangmian->getCString());
            sp_mj_num->setAnchorPoint(Vec2(0.5,0.5));
            sp_mj_num->setPosition(Vec2(49,80));
            sp_mj->addChild(sp_mj_num);
        }
        //隐藏不用的提示块
        Sprite *sp_mm=(Sprite *)bt_call_chi->getChildByName("mj_sp_4");
        sp_mm->setVisible(false);
        //为麻将添加监听
        std::vector<int >arr_cars;
        arr_cars.push_back(mj_real_value);
        arr_cars.push_back(mj_real_value_next);
        arr_cars.push_back(mj_real_value_last);
        bt_call_chi->addClickEventListener(CC_CALLBACK_0(Playing_three::chi_final_request,this,chi_arr[i].operatecode,arr_cars));
    }
}
void Playing_three::chi_final_request(int opcode,std::vector<int >arr_cards)
{
    TableCommand::getInstance()->requestoperate(opcode,arr_cards[0]);
    setcards_detail_actionsisvisible(false);
}
//显示可以杠的牌
void Playing_three::showcards_gang(std::vector<operate_me>gang_arr)
{
    setcards_detail_actionsisvisible(true);

    for(int i=0;i<3;i++)
    {
        String *name=String::createWithFormat("Button_action_arr_%d",i+1);
        Button *bt_call_chi=(Button *)node_detail_actions->getChildByName(name->getCString());
        if(gang_arr.size()>i)
        {
            bt_call_chi->setVisible(true);
        }
        else
        {
            bt_call_chi->setVisible(false);
        }
    }
    for(int i=0;i<gang_arr.size();i++)
    {
        String *name=String::createWithFormat("Button_action_arr_%d",i+1);
        Button *bt_call_chi=(Button *)node_detail_actions->getChildByName(name->getCString());

        int mj_vule=gang_arr[i].arr_gang_mjs[0]/16*10+gang_arr[i].arr_gang_mjs[0]%16;
        int mj_real_value=gang_arr[i].arr_gang_mjs[0];

        for(int j=0;j<4;j++)
        {
            String *name_mj=String::createWithFormat("mj_sp_%d",4-j);
            Sprite *sp_mj=(Sprite *)bt_call_chi->getChildByName(name_mj->getCString());
			sp_mj->removeAllChildren();
            sp_mj->setAnchorPoint(Vec2(0.5,0.5));
            String *path_majiangmian=String::createWithFormat("res/cards/mj_%d.png",mj_vule);
            Sprite *sp_mj_num=Sprite::create(path_majiangmian->getCString());
            sp_mj_num->setAnchorPoint(Vec2(0.5,0.5));
            sp_mj_num->setPosition(Vec2(49,80));
            sp_mj->addChild(sp_mj_num);
        }

        //为麻将添加监听
        std::vector<int >arr_cars;
        arr_cars.push_back(mj_real_value);
        arr_cars.push_back(mj_real_value);
        arr_cars.push_back(mj_real_value);
        arr_cars.push_back(mj_real_value);
        bt_call_chi->addClickEventListener(CC_CALLBACK_0(Playing_three::chi_final_request,this,gang_arr[i].operatecode,arr_cars));
    }
}
//直接吃牌
void Playing_three::operate_chi(operate_me op)
{
    int opcode=op.operatecode;
    int cardid=op.card_id;
    
    TableCommand::getInstance()->requestoperate(opcode,cardid);
}
//杠牌
void Playing_three::oprate_gang(operate_me op)
{
    int opcode=op.operatecode;
    int cardid=op.card_id;
    
    TableCommand::getInstance()->requestoperate(opcode,cardid);
}
//当前玩家出牌返回（服务器）
void Playing_three::outCard(EventCustom* evt)
{
    if(isminglou_ing==true)
    {
        isminglou_ing=false;
        isminglou_over=true;
        TableCommand::getInstance()->requestminglou();
    }
}
//刷新麻将位置
void Playing_three::refreshMjsPos()
{
    this->sortMjs(m_mjList);
    Node* nodePlayer_1 = nodeCards[0]->getChildByName("nodeCards");
    
	int fanweiqian;
	int fanweihou;
	if(GamerData::getInstance()->getquedemen()==1)
	{
		fanweiqian=1;
		fanweihou=9;
	}
	else if(GamerData::getInstance()->getquedemen()==2)
	{
		fanweiqian=11;
		fanweihou=19;
	}
	else if(GamerData::getInstance()->getquedemen()==3)
	{
		fanweiqian=21;
		fanweihou=29;
	}
	else
	{
		fanweiqian=0;
		fanweihou=100;
	}
    //屏蔽
	Vector<MjNode *>arr_qian;
	Vector<MjNode *>arr_hou;
	for(int i=0;i<m_mjList.size();i++)
	{
		if(m_mjList.at(i)->getLogicValue()>=fanweiqian&&m_mjList.at(i)->getLogicValue()<=fanweihou)
		{
			arr_hou.pushBack(m_mjList.at(i));
		}
	}
	for(int i=0;i<m_mjList.size();i++)
	{
		if(m_mjList.at(i)->getLogicValue()>=fanweiqian&&m_mjList.at(i)->getLogicValue()<=fanweihou)
		{
			//arr_hou.pushBack(m_mjList.at(i));
		}
		else
		{
			if(arr_hou.size()!=0)
			{
				m_mjList.at(i)->btnMj->setColor(Color3B(100,100,100));
				m_mjList.at(i)->valueMj->setColor(Color3B(100,100,100));
				arr_qian.pushBack(m_mjList.at(i));
			}
			else
			{
				m_mjList.at(i)->btnMj->setColor(Color3B(255,255,255));
				m_mjList.at(i)->valueMj->setColor(Color3B(255,255,255));
				arr_qian.pushBack(m_mjList.at(i));
			}
		}
	}
	m_mjList.clear();
	for(int i=0;i<arr_hou.size();i++)
	{
		m_mjList.pushBack(arr_hou.at(i));
	}
	for(int i=0;i<arr_qian.size();i++)
	{
		m_mjList.pushBack(arr_qian.at(i));
	}
	for(int j = 0; j <m_mjList.size(); j++){
		MjNode* pMjNode = this->m_mjList.at(j);
		pMjNode->setPosition(nodePlayer_1->getChildByName(String::createWithFormat("poker_%d",j+1)->getCString())->getPosition());
	}
}
void Playing_three::refreshcolor()
{
	//this->sortMjs(m_mjList);
	Node* nodePlayer_1 = nodeCards[0]->getChildByName("nodeCards");

	int fanweiqian;
	int fanweihou;
	if(GamerData::getInstance()->getquedemen()==1)
	{
		fanweiqian=1;
		fanweihou=9;
	}
	else if(GamerData::getInstance()->getquedemen()==2)
	{
		fanweiqian=11;
		fanweihou=19;
	}
	else if(GamerData::getInstance()->getquedemen()==3)
	{
		fanweiqian=21;
		fanweihou=29;
	}
	else
	{
		fanweiqian=0;
		fanweihou=100;
	}
	bool ishavequemen=false;
	for(int i=0;i<m_mjList.size();i++)
	{
		if(m_mjList.at(i)->getLogicValue()>=fanweiqian&&m_mjList.at(i)->getLogicValue()<=fanweihou)
		{
			ishavequemen=true;
			break;
		}
	}
	for(int i=0;i<m_mjList.size();i++)
	{
		if(m_mjList.at(i)->getLogicValue()>=fanweiqian&&m_mjList.at(i)->getLogicValue()<=fanweihou)
		{
			m_mjList.at(i)->btnMj->setColor(Color3B(255,255,255));
			m_mjList.at(i)->valueMj->setColor(Color3B(255,255,255));
		}
		else
		{
			if(ishavequemen)
			{
				m_mjList.at(i)->btnMj->setColor(Color3B(100,100,100));
				m_mjList.at(i)->valueMj->setColor(Color3B(100,100,100));
			}
			else
			{
				m_mjList.at(i)->btnMj->setColor(Color3B(255,255,255));
				m_mjList.at(i)->valueMj->setColor(Color3B(255,255,255));
			}
		}
	} 
}

///排列pMjNode 从大到小
void Playing_three::sortMjs(Vector<MjNode*> &_pokerVec)
{
    std::sort(_pokerVec.begin(), _pokerVec.end(), [](MjNode* a,MjNode* b){
       return a->id > b->id;
    });
}
//补花动画显示并且修改其数量
void Playing_three::buhuaActionManage(int uid,int numHua)
{
    auto action = Sequence::create(DelayTime::create(1.0f),FadeOut::create(0.25f),CallFuncN::create( CC_CALLBACK_1(Playing_three::buHuaActionEndcallback, this)),nullptr);

    if(uid == GamerData::getInstance()->getUId())
    {
        //BYTE viewId = GetViewID(GamerData::getInstance()->getSeatId(),pGamerData->getSeatId());
        auto nodePlayer = (Node*)nodePlayers[0]->getChildByName("nodePlayer");
        auto iconBuHua = (Sprite *)nodePlayers[0]->getChildByName("iconBuHua");//补花提示
        auto nodeHua = (Node*)nodePlayer->getChildByName("nodeHua");  //带花icon
        auto numHuaT = (Text*)nodeHua->getChildByName("numHua");       //花的数量
        numHuaT->setText(StringUtils::format("%d",numHua));
        iconBuHua->setVisible(true);
        iconBuHua->setOpacity(255);
        iconBuHua->runAction(action);
    }else{
        GamerData* pGamerData = GamerDataDeal::getInstance()->getGamerData(uid);
        BYTE viewId = GetViewID(GamerData::getInstance()->getSeatId(),pGamerData->getSeatId());
        auto nodePlayer = (Node*)nodePlayers[viewId]->getChildByName("nodePlayer");
        auto iconBuHua = (Sprite *)nodePlayers[viewId]->getChildByName("iconBuHua");//补花提示
        Node *n_hua=(Node *)nodePlayer->getChildByName("nodeHua");
        auto text_hua=(Text *)n_hua->getChildByName("numHua");
        text_hua->setText(StringUtils::format("%d",numHua));
        iconBuHua->setVisible(true);
        iconBuHua->setOpacity(255);
        iconBuHua->runAction(action);
    }
}
//补花提示icon显示结束
void Playing_three::buHuaActionEndcallback(Node* sender )
{
    sender->setVisible(false);
    sender->setOpacity(255);
}
//出牌本地动画结束后的回调函数
void Playing_three::outCard1Action(Node* sender )
{
    MjNode* card = (MjNode*)sender;
    TableCommand::getInstance()->requestOutCard(card->id);
}
void Playing_three::setcardoperateornot(bool is)
{
    for(int i=0;i<m_mjList.size();i++)
    {
      //  m_mjList.at(i)->setstatecantoperate(is);
    }
}
void Playing_three::cleanallscene()
{
    this->removeAllChildren();
	
    for(int i=0;i<3;i++)
    {
		GamerData *g=GamerDataDeal::getInstance()->getGamerDataBySeat(i);
		g->setJi_type(0);
		g->setistingpai(false);
		g->setquedemen(0);
        hands_cnt[i]=0;
        nodePlayers[i]=nullptr;
        m_arr_players_mjs[i].clear();
        m_players_chengxing_mjs[i].clear();
        headimage_url_loading[i]=0;
		nodeCards[i]=nullptr;
		arr_jipai[i].clear();
    }
	GamerData::getInstance()->setquedemen(0);
	m_current_diamond->removeFromParent();
    arr_actions.clear();
    arr_operates.clear();

	time_all=0;
    isminglou_over=false;
	outcardingId=-1;
	isOutCarding=false;
    m_mjList.clear();
    mj_isSelectedMj=false; //是否有已经选中的麻将(true:是;false:否)
    mj_selectedMj=nullptr;	
    right_card_alive=nullptr;//当前牌桌上活动的牌（可吃 可碰 可 杠的 活跃的牌）

    isminglou_ing=false;//是否正在进行名楼操作 只针对当前用户

	dingqueshu=0;

}

void Playing_three::playEffectCustom(std::string kName,int viewid)
{

    Tools::pauseBackMusic();
    //experimental::AudioEngine::stopAll();
    int custom_id = experimental::AudioEngine::play2d(kName);
    log("%s",kName.c_str());
    experimental::AudioEngine::setFinishCallback(custom_id,CC_CALLBACK_0(Playing_three::on_effect_over,this,viewid));

}

void Playing_three::on_effect_over(int viewid)
{
	if(viewid==0)
	{
		UserDefault::getInstance()->setBoolForKey("isplayluyin",false) ;
	}
    Node *head_n=nodePlayers[viewid];
    ImageView *im=(ImageView*)head_n->getChildByName("Image_pao");
    im->setVisible(false);
    Sprite *sp_yuyin=(Sprite *)im->getChildByName("Sprite_yuyin");
    sp_yuyin->stopAllActions();
    sp_yuyin->setVisible(false);
    log("continuc back music");
    Tools::resumeBackMusic();
}
void Playing_three::responsechatbroadcast(EventCustom *evt)
{
	GS2C_ChatBroadcast* udata  = (GS2C_ChatBroadcast *)evt->getUserData();
	int index=udata->chat_index();
	int uid=udata->uid();

	int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uid)->getSeatId());

	for(int i=0;i<3;i++)
	{
		if(i==viewid)
		{
			nodePlayers[i]->setZOrder(99);
		}
		else
		{
			nodePlayers[i]->setZOrder(90);
		}
	}

	if(UserDefault::getInstance()->getBoolForKey("isplayluyin")==false)
	{
		if(index>100&&index<200)
		{
			UserDefault::getInstance()->setBoolForKey("isplayluyin",true);
			Node *head_n=nodePlayers[viewid];
			ImageView *im=(ImageView*)head_n->getChildByName("Image_pao");
			im->setVisible(true);
			Sprite *sp_yuyin=(Sprite *)im->getChildByName("Sprite_yuyin");
			sp_yuyin->setVisible(false);
			int tag=index-100;
			String *name=String::createWithFormat("changyongyu%d",tag);
			std::string tx_chat1= Tools::getChineseByKey(name->getCString());
			Text *tx_content=(Text *)im->getChildByName("Text_chat");
			tx_content->setString(tx_chat1.c_str());
			tx_content->setVisible(true);
			if(36*(tx_content->getStringLength())+30>118)
			{
				im->setContentSize(Size(36*(tx_content->getStringLength())+30,66));
			}
			Sprite *sp=Sprite::create("res/cards/mj_1.png");
			sp->setVisible(false);
			addChild(sp);
			Sequence *se=Sequence::create(DelayTime::create(2.0f),CallFunc::create(CC_CALLBACK_0(Playing_three::recoverchat,this,viewid,sp)),nullptr);
		    sp->runAction(se);
			GamerData *g=GamerDataDeal::getInstance()->getGamerData(uid);
			Tools::playMsgByGender(index,g->getSex());
		}
	}
	if(index>200)
	{
		int tag=index-200;

		Node *head_n=nodePlayers[viewid];
		Sprite *emoji=(Sprite *)head_n->getChildByName("emoji");
		emoji->stopAllActions();

		emoji->setVisible(true);
		
		Vector<SpriteFrame *>arr_frames;
		for(int i=0;i<emoji_num[tag-1];i++)
		{
			String *name=String::createWithFormat("res/srcRes/emoji/emoji_%d_%d.png",tag,i);
			Sprite *sp=Sprite::create(name->getCString());
			arr_frames.pushBack(sp->getSpriteFrame());
		}
		Animation *ani=Animation::createWithSpriteFrames(arr_frames);
		ani->setDelayPerUnit(1.0/4);
		Animate *an=Animate::create(ani);
		RepeatForever *re=RepeatForever::create(an);
		emoji->runAction(re);
		Sequence *se=Sequence::create(DelayTime::create(2.0f),CallFunc::create(CC_CALLBACK_0(Playing_three::sp_visible,this,emoji,false)),nullptr);
		emoji->runAction(se);
	}
}
void Playing_three::recoverchat(int viewid,Sprite *sp)
{
	UserDefault::getInstance()->setBoolForKey("isplayluyin",false); 

	Node *head_n=nodePlayers[viewid];
	ImageView *im=(ImageView*)head_n->getChildByName("Image_pao");
	im->setVisible(false);
	Sprite *sp_yuyin=(Sprite *)im->getChildByName("Sprite_yuyin");
	sp_yuyin->setVisible(false);

	Text *tx_content=(Text *)im->getChildByName("Text_chat");

	tx_content->setVisible(false);
	sp->removeFromParent();
}
void Playing_three::responsecustomchatbroadcast(EventCustom *evt)
{
	GS2C_ChatCustomBroadcast* udata  = (GS2C_ChatCustomBroadcast *)evt->getUserData();
	std::string  content=udata->chat_content();
	int uid=udata->uid();
	int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uid)->getSeatId());

	if(UserDefault::getInstance()->getBoolForKey("isplayluyin")==false)
	{
			UserDefault::getInstance()->setBoolForKey("isplayluyin",true);
			Node *head_n=nodePlayers[viewid];
			ImageView *im=(ImageView*)head_n->getChildByName("Image_pao");
			im->setVisible(true);
			Sprite *sp_yuyin=(Sprite *)im->getChildByName("Sprite_yuyin");
			sp_yuyin->setVisible(false);
			
			
			Text *tx_content=(Text *)im->getChildByName("Text_chat");
			tx_content->setString(content.c_str());
			tx_content->setVisible(true);
			if(36*(tx_content->getStringLength())+30>118)
			{
				im->setContentSize(Size(36*(tx_content->getStringLength())+30,66));
			}
			Sprite *sp=Sprite::create("res/cards/mj_1.png");
			sp->setVisible(false);
			addChild(sp);
			Sequence *se=Sequence::create(DelayTime::create(2.0f),CallFunc::create(CC_CALLBACK_0(Playing_three::recoverchat,this,viewid,sp)),nullptr);
			sp->runAction(se);
	}
}


void Playing_three::initcardWithCardIds(Sprite *sp_card,int cardid)
{
	int cardreal=cardid/16*10+cardid%16;//传过来的麻将的牌值必须是16进制的
	String *path=String::createWithFormat("res/cards/mj_%d.png",cardreal);
	sp_card->setTexture(path->getCString());
}