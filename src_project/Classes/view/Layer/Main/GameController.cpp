#include "GameController.h"
#include "controller/table/TableCommand.h"
#include "tool/Tools.h"
#include "model/MjData.h"
#include "view/Layer/Tip/TipContent.h"
#include "platform/JniFun.h"
#include "SimpleAudioEngine.h"
#include "Sound/ArmFun.h"
#include "view/Layer/Main/layer_chat.h"
#include "platform/MissionWeiXin.h"

#include "view/Layer/Lobby/LobbyView.h"

void GameController::onEnter()
{
    ParentInfo::onEnter();
	this->_eventDispatcher->addCustomEventListener("onresultunschedule",CC_CALLBACK_1(GameController::onresult,this));
	this->_eventDispatcher->addCustomEventListener("onresultunscheduleQuake",CC_CALLBACK_1(GameController::stopQuake,this));
	this->_eventDispatcher->addCustomEventListener("WeiXinShareInGame",CC_CALLBACK_1(GameController::WeiXinShareInGame,this));
	schedule(schedule_selector(GameController::refreshberrty),2);
}
void GameController::onExit()
{
	this->_eventDispatcher->removeCustomEventListeners("onresultunschedule");
	this->_eventDispatcher->removeCustomEventListeners("onresultunscheduleQuake");
	this->_eventDispatcher->removeCustomEventListeners("WeiXinShareInGame");
	unschedule(schedule_selector(GameController::refreshberrty));
    ParentInfo::onExit();
}
void GameController::refreshberrty(float dt)
{
	float power = UserDefault::getInstance()->getFloatForKey("level_beterry");
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	power = JniFun::getPower();
#endif
	LoadingBar *l_be=(LoadingBar *)node_system->getChildByName("LoadingBar_1");
	float rate=(power*1.0)/100.0f;
	l_be->setPercent(power*1.0f);

	Text * tx_baifenbi=(Text *)node_system->getChildByName("Text_174");
	String *baifenbi=String::createWithFormat("%0.0lf%%",power);
	tx_baifenbi->setString(baifenbi->getCString());

	Text *tx_hour=(Text *)node_system->getChildByName("Text_174_0");
	Text *tx_min=(Text *)node_system->getChildByName("Text_174_2");
  std::vector<int >arr_time=Tools::getcurrentTime();
  if(arr_time.size()==2)
  {
	  tx_hour->setString(String::createWithFormat("%d",arr_time[0])->getCString());
	  if(arr_time[1]<10)
	  {
		   tx_min->setString(String::createWithFormat("0%d",arr_time[1])->getCString());
	  }
	  else
	  {
		  tx_min->setString(String::createWithFormat("%d",arr_time[1])->getCString());
	  }
	 
  }

}
void GameController::onresult(EventCustom* evt)
{
	unschedule(schedule_selector(GameController::begintimehjisshiqi)); 
}
void GameController::stopQuake(EventCustom* evt)
{
    unschedule(schedule_selector(GameController::begintimehjisshiqiQuake)); 
}

bool GameController::init()
{
    if(!ParentInfo::init()) return false;
    setSwallowTouches(false);
    setOpacity(0);
    //UI加载并且显示
    uiLoadAndShow();
    return true;
}
//UI加载并且显示
void GameController::uiLoadAndShow()
{
    auto controller = CSLoader::createNode("res/loading/controller.csb") ;   //游戏控制层
    this->addChild(controller);

	//电量
	 node_system=(Node *)controller->getChildByName("node_system");

    //等待其他玩家UI
    nodeWait = (Node*)controller->getChildByName("nodeWait");
    auto btnExitRoom = (Button*)nodeWait->getChildByName("btnExitRoom");//退出房间
    btnExitRoom->addTouchEventListener(CC_CALLBACK_2(GameController::ButtonHandler, this));	
    auto btnGetFriends = (Button*)nodeWait->getChildByName("btnGetFriends");//微信邀请好友
    btnGetFriends->addTouchEventListener(CC_CALLBACK_2(GameController::ButtonHandler, this));

	if(MjData::getInstance()->getisinapple()==1)
	{
		btnGetFriends->setEnabled(false);
		btnGetFriends->setVisible(false);
	}
    auto btnDismiss = (Button*)nodeWait->getChildByName("btnDismiss");//解散房间
    btnDismiss->addTouchEventListener(CC_CALLBACK_2(GameController::ButtonHandler, this));
	if(GamerData::getInstance()->getSeatId()!=0)
	{
		btnDismiss->setVisible(false);
		btnDismiss->setEnabled(false);
	}
	else
	{
		btnDismiss->setVisible(true);
		btnDismiss->setEnabled(true);
	}
    //游戏主体底层
    nodeBottom = (Node*)controller->getChildByName("nodeBottom");
    auto btnSet = (Button*)nodeBottom->getChildByName("btnSet");//设置
    btnSet->addTouchEventListener(CC_CALLBACK_2(GameController::ButtonHandler, this));
    auto btnHelp = (Button*)nodeBottom->getChildByName("btnHelp");//帮助
    btnHelp->addTouchEventListener(CC_CALLBACK_2(GameController::ButtonHandler, this));
	bg_rule=(Sprite *)nodeBottom->getChildByName("bg_rule_zhuomian_1");
	bt_go=(Button *)bg_rule->getChildByName("Button_go");
	bt_go->setTag(1);
	bt_go->addTouchEventListener(CC_CALLBACK_2(GameController::ButtonHandler,this));

	Text *tx_id=(Text *)bg_rule->getChildByName("Text_fangjian_0");
	tx_id->setText(String::createWithFormat("%d", GamerData::getInstance()->getTableId())->getCString());
	Text *tx_jushu=(Text *)bg_rule->getChildByName("Text_fangjian_0_0");
	if(MjData::getInstance()->getjushu()==4)
	{
		tx_jushu->setText(Tools::getChineseByKey("8ju").c_str());
	}
	else if(MjData::getInstance()->getjushu()==8)
	{
		tx_jushu->setText(Tools::getChineseByKey("16ju").c_str());
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

    std::string rule;
    if (MjData::getInstance()->getis258()==1)
    {
        rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("with258").c_str())->getCString();
    }
    if (MjData::getInstance()->getisfeng()==1)
    {
        rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("withfeng").c_str())->getCString();
    }
    if (MjData::getInstance()->getishua()==1)
    {
        rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("withhua").c_str())->getCString();
    }
    if (MjData::getInstance()->getisjiangyise()==1)
    {
        rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("withjiangyise").c_str())->getCString();
    }
    if (MjData::getInstance()->getisqidui()==1)
    {
        rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("withqidui").c_str())->getCString();
    }
    if (MjData::getInstance()->getisminglou()==1)
    {
        rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("minglou").c_str())->getCString();
    }

    auto tipGame = (Text*)nodeBottom->getChildByName("tipGame");//游戏规则提示
    tipGame->setText(rule.c_str());


    auto idRoom = (Text*)nodeBottom->getChildByName("idRoom");  //房间号
    idRoom->setText(String::createWithFormat("%d", GamerData::getInstance()->getTableId())->getCString());
    CCLOG("%d",GamerData::getInstance()->getTableId() );

    auto powerBar = (LoadingBar*)nodeBottom->getChildByName("powerBar");//设备电量
    auto btnChat = (Button*)nodeBottom->getChildByName("btnChat");//聊天
    btnChat->addTouchEventListener(CC_CALLBACK_2(GameController::ButtonHandler, this));
    //游戏中
    nodeGame = (Node*)controller->getChildByName("nodeGame");
  //  nodeGame->setPositionY(nodeGame->getPositionY()+30);
    nodeGame->setVisible(false);
    numTime_game = (TextAtlas*)nodeGame->getChildByName("num");
    numCards_game = (Text*)((ImageView*)nodeGame->getChildByName("bgShow1"))->getChildByName("texts2");
    numJuShu_game = (Text*)((ImageView*)nodeGame->getChildByName("bgShow1"))->getChildByName("texts_0");
	bgtime=(ImageView *)nodeGame->getChildByName("bgTime");
	for(int i=0;i<4;i++)
	{
		String *path_arrow=String::createWithFormat("arrow%d",i+1);
		Sprite *sp_arrow=(Sprite *)bgtime->getChildByName(path_arrow->getCString());
		arr_arrows.push_back(sp_arrow);
		sp_arrow->setVisible(false);
		sp_arrow->setTag(i);
		FadeOut *fo=FadeOut::create(0.5);
		FadeIn *fi=FadeIn::create(0.5);
		Sequence *se=Sequence::create(fo,fi,NULL);
		RepeatForever *re=RepeatForever::create(se);
		sp_arrow->runAction(re);
	}


    Button *bt_luyin=(Button *)nodeBottom->getChildByName("Button_luyin");
    bt_luyin->addTouchEventListener(CC_CALLBACK_2(GameController::ButtonHandler, this));

    n_luyinanimate=controller->getChildByName("Node_luyin");

}
void GameController::shouhuibgrule()
{
	bg_rule->stopAllActions();
	MoveTo *mt=MoveTo::create(0.3,Vec2(-51,594));
	bg_rule->runAction(mt);
	bt_go->setTag(0);
	bt_go->loadTextures("res/loading/layer_result/btn_jiantou_suo.png","res/loading/layer_result/btn_jiantou_suo.png","res/loading/layer_result/btn_jiantou_suo.png");
}
void GameController::showLuxiangController()
{
	nodeWait->setVisible(false);
	nodeGame->setVisible(true);
	nodeBottom->setVisible(false);
	n_luyinanimate->setVisible(false);
	numJuShu_game->setVisible(false);
	numCards_game->setVisible(false);
	numTime_game->setVisible(false);


	Text *tx_shengyu1 = (Text*)((ImageView*)nodeGame->getChildByName("bgShow1"))->getChildByName("texts1");
	tx_shengyu1->setVisible(false);
	Text *tx_shengyu2 = (Text*)((ImageView*)nodeGame->getChildByName("bgShow1"))->getChildByName("texts3");
	tx_shengyu2->setVisible(false);
	Text *tx_shengyu3 = (Text*)((ImageView*)nodeGame->getChildByName("bgShow1"))->getChildByName("texts");
	tx_shengyu3->setVisible(false);
	Text *tx_shengyu4= (Text*)((ImageView*)nodeGame->getChildByName("bgShow1"))->getChildByName("texts_1");
	tx_shengyu4->setVisible(false);
}
static int luyin_time=0;
void GameController::update(float dt)
{
    luyin_time++;
}
void GameController::arrowvisible(bool isvisible)
{
	for(int i=0;i<arr_arrows.size();i++)
	{
		arr_arrows[i]->setVisible(isvisible);
	}
}
void GameController::refreshjushu()
{
	numTime_game = (TextAtlas*)nodeGame->getChildByName("num");
	numTime_game->setString("10");

	const string  shengyuStr = Tools::getChineseByKey("ShengYu");
	const string  zhangStr = Tools::getChineseByKey("Zheng");
	const string  juStr = Tools::getChineseByKey("Ju");

	numCards_game = (Text*)((ImageView*)nodeGame->getChildByName("bgShow1"))->getChildByName("texts2");
	String  *left_cntString  = String::createWithFormat("%d",0);
	numCards_game->setText(left_cntString->getCString());
	numJuShu_game = (Text*)((ImageView*)nodeGame->getChildByName("bgShow1"))->getChildByName("texts_0");
	//0121
	String  *ju_cntString  = String::createWithFormat("%d",MjData::getInstance()->getleftjushu());
	numJuShu_game->setText(ju_cntString->getCString());
}
void GameController::playluyin(float dt)
{
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(luyin_path.c_str());
}
//按钮回调函数
void GameController::ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType)
{
    Button *bt_luyin=(Button *)pRef;
    if(bt_luyin->getName()=="Button_luyin")//luyin
    {
        if(UserDefault::getInstance()->getBoolForKey("isplayluyin")==false)
        {
            if(touchType==ui::Widget::TouchEventType::BEGAN)
            {
                //暂停背景音乐
                Tools::pauseBackMusic();

                JniFun::startSoundRecord();//开始录音

                n_luyinanimate->setVisible(true);

                Vector<SpriteFrame *>arr_frames;
                for(int i=0;i<7;i++)
                {
                    String *path=String::createWithFormat("res/srcRes/animate/startRecord/%d.png",i);
                    Sprite *sp=Sprite::create(path->getCString());
                    arr_frames.pushBack(sp->getSpriteFrame());
                }
                Animation *an=Animation::createWithSpriteFrames(arr_frames);
                an->setDelayPerUnit(2.0f/6); 
                Animate *amt=Animate::create(an);
                RepeatForever *re=RepeatForever::create(amt);
                Sprite *sp_xinhao=(Sprite *)n_luyinanimate->getChildByName("Sprite_3");
                sp_xinhao->runAction(re);

				
                log("kaishi luyin");

            }
            else if(touchType==ui::Widget::TouchEventType::ENDED||touchType==ui::Widget::TouchEventType::CANCELED)
            {
                n_luyinanimate->setVisible(false);
                Sprite *xinhao=(Sprite *)n_luyinanimate->getChildByName("Sprite_3");
                xinhao->stopAllActions();
                std::string path=JniFun::stopSoundRecord();
               // luyin_path=path;

                ssize_t iSize = 0;
                std::string kDestFile = cocos2d::CCFileUtils::getInstance()->getWritablePath()+"talk.arm";
                log("kDestFile: %s", kDestFile.c_str());

				remove(kDestFile.c_str());

                ArmFun::WavToArm(path.c_str(),kDestFile.c_str());

				remove(path.c_str());

                log("kDestFile-----------: %s", kDestFile.c_str());
                unsigned char* pData = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(kDestFile,"rb",&iSize);
                if (!pData)
                {
                    log("kDestFile-----------1111: %s", kDestFile.c_str());
                    return;
                }
                char *p=(char *)pData;
				UserDefault::getInstance()->setBoolForKey("isplayluyin",true);
                TableCommand::getInstance()->requestyuyin(p,iSize);

                //继续背景音乐
                Tools::resumeBackMusic();

            }
        }
    }
    if (touchType != ui::Widget::TouchEventType::ENDED) 
        return;
    Button* pBtn = (Button*) pRef;
    string name = pBtn->getName();
    if (name == "btnExitRoom"){
        //退出房间
        //SEND_CUSTOM_MSG("gamemainexit");
        TableCommand::getInstance()->requestLeaveTable(0);
		

    }else if (name == "btnGetFriends"){
        //微信邀请好友
      //  SEND_CUSTOM_MSG("gamemainstart"); //测试使用
		//微信邀请好友
		std::string jinping=Tools::getChineseByKey("jinping");
		std::string rule;
		
		rule  = String::createWithFormat("%s %d",Tools::getChineseByKey("roomid").c_str(),GamerData::getInstance()->getTableId())->getCString();
		
		if (MjData::getInstance()->getjushu()==4)
		{
			rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("8ju").c_str())->getCString();
		}
		if (MjData::getInstance()->getjushu()==8)
		{
			rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("16ju").c_str())->getCString();
		}
		if (MjData::getInstance()->getIsgang_men()==1)
		{
			rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("zigang").c_str())->getCString();
		}
		else
		{
			rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("zhuanwan").c_str())->getCString();
		}
		if (MjData::getInstance()->getIsgenZhuang()==1)
		{
			rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("gen").c_str())->getCString();
		}
		if(MjData::getInstance()->getpalyrule()==1)
		{
			rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("4renfang").c_str())->getCString();
		}
		else if(MjData::getInstance()->getpalyrule()==2)
		{
			rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("sandingguai").c_str())->getCString();
		}
		else if(MjData::getInstance()->getpalyrule()==3)
		{
			rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("2dingguai").c_str())->getCString();
		}
		else if(MjData::getInstance()->getpalyrule()==4)
		{
			rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("sandingliangfang").c_str())->getCString();
		}
		else if(MjData::getInstance()->getpalyrule()==5)
		{
			rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("erdingliangfang").c_str())->getCString();
		}
		MissionWeiXin::getinstance()->shareUrlWeiXin("http://d.laiyagame.com/jinping/download.html",jinping.c_str(),rule.c_str(),0);

		//auto mLobbyView = LobbyView::create();
		//mLobbyView->showUIWeiXinShare(1);
		//this->addChild(mLobbyView);

    }else if (name == "btnDismiss")
    {//解散房间
        TableCommand::getInstance()->requestLeaveTable(1);
    }else if (name == "btnSet")
    {//设置
		auto lobbyView = LobbyView::create();
		lobbyView->showUISetting(true);
		this->getParent()->addChild(lobbyView,9);
    }else if (name == "btnHelp")
    {//帮助
        auto tipConent = TipContent::create();
        tipConent->showUIHelp();
        this->getParent()->addChild(tipConent,9);
    }else if (name == "btnChat")
    {//聊天
		//TableCommand::getInstance()->requestchat(2);
		//TableCommand::getInstance()->requestcustomchat("hahaha");

		layer_chat *l_c=layer_chat::create();
		l_c->refreshchat(1);
		this->getParent()->addChild(l_c, 10);
    }
	else if(name=="Button_go")
	{
		 if(bt_go->getTag()==0)
		 {
			 bg_rule->stopAllActions();
			 MoveTo *mt=MoveTo::create(0.3,Vec2(90,594));
			 bg_rule->runAction(mt);
			 bt_go->setTag(1);
			 bt_go->loadTextures("res/loading/layer_result/btn_jiantou_shen.png","res/loading/layer_result/btn_jiantou_shen.png","res/loading/layer_result/btn_jiantou_shen.png");
		 }
		 else
		 {
			 bg_rule->stopAllActions();
			 MoveTo *mt=MoveTo::create(0.3,Vec2(-51,594));
			 bg_rule->runAction(mt);
			 bt_go->setTag(0);
			 bt_go->loadTextures("res/loading/layer_result/btn_jiantou_suo.png","res/loading/layer_result/btn_jiantou_suo.png","res/loading/layer_result/btn_jiantou_suo.png");
		 }
	}

}
//游戏开始
void GameController::startGame_gameController(int left_card_cnt, int left_round_cnt)
{
    nodeWait->setVisible(false);
    nodeGame->setVisible(true);
    numTime_game = (TextAtlas*)nodeGame->getChildByName("num");
    numTime_game->setString("10");

    const string  shengyuStr = Tools::getChineseByKey("ShengYu");
    const string  zhangStr = Tools::getChineseByKey("Zheng");
    const string  juStr = Tools::getChineseByKey("Ju");

    numCards_game = (Text*)((ImageView*)nodeGame->getChildByName("bgShow1"))->getChildByName("texts2");
    String  *left_cntString  = String::createWithFormat("%d",left_card_cnt);
    numCards_game->setText(left_cntString->getCString());


    numJuShu_game = (Text*)((ImageView*)nodeGame->getChildByName("bgShow1"))->getChildByName("texts_0");
    //0121
    String  *ju_cntString  = String::createWithFormat("%d",left_round_cnt);
    numJuShu_game->setText(ju_cntString->getCString());


	shouhuibgrule();
}

//设置剩余张数
void GameController::setLeftCardCnt(int left_card_cnt)
{
    const string  shengyuStr = Tools::getChineseByKey("ShengYu");
    const string  zhangStr = Tools::getChineseByKey("Zheng");

    numCards_game = (Text*)((ImageView*)nodeGame->getChildByName("bgShow1"))->getChildByName("texts2");
    String  *left_cntString  = String::createWithFormat("%d",left_card_cnt);
    numCards_game->setText(left_cntString->getCString());
}


static int time_daojishi=10;
static int uid=0;
void GameController::begintimehjisshiqi(float dt)
{
	time_daojishi=time_daojishi-1;
	if(time_daojishi>3)
	{
		String *time=String::createWithFormat("%d",time_daojishi);
		numTime_game->setString(time->getCString());
	}
	else  if(time_daojishi<=3&&time_daojishi>=0)
	{
	   String *time=String::createWithFormat("%d",time_daojishi);
	   numTime_game->setString(time->getCString());
	}
}

static int time_daojishiQuake=10;
void GameController::begintimehjisshiqiQuake(float dt)
{
    time_daojishiQuake=time_daojishiQuake-1;

    if(time_daojishiQuake==3)
    {
        if(uid==0)
        {
          //  JniFun::variable();
			Tools::playEffect("alarm.mp3");
        }

    }
}
//根据 庄的 viewid对 箭头数组重新排序
void GameController::setArrowRoatation(int bankerViewId)
{
	std::vector<Sprite *>arr_arrows_temp;
	if(bankerViewId==0)
	{
		bgtime->setRotation(90);
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==1)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==2)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==3)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==0)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
	}
	else if(bankerViewId==1)
	{
		bgtime->setRotation(0);
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==0)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==1)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==2)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==3)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
	}
	else if(bankerViewId==2)
	{
		bgtime->setRotation(-90);
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==3)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==0)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==1)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==2)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
	}
	else if(bankerViewId==3)
	{
		bgtime->setRotation(180);
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==2)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==3)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==0)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
		for(int i=0;i<arr_arrows.size();i++)
		{
			if(arr_arrows[i]->getTag()==1)
			{
				arr_arrows_temp.push_back(arr_arrows[i]);
			}
		}
	}
	arr_arrows.clear();
	for(int i=0;i<arr_arrows_temp.size();i++)
	{
		arr_arrows.push_back(arr_arrows_temp[i]);
	}
}

//修改箭头指向方位根据玩家[0:当前玩家;1:下家;2:对门;3:上家]
void GameController::setArrowDirection(int index)
{
	if(index==0)
	{
		UserDefault::getInstance()->setBoolForKey("iscanoperatecard",true);
	}


	uid=index;

	if(MjData::getInstance()->getpalyrule()==2||MjData::getInstance()->getpalyrule()==4)
	{
		if(index==2)
		{
			index=index+1;
		}
	}
	else if(MjData::getInstance()->getpalyrule()==3||MjData::getInstance()->getpalyrule()==5)
	{
		if(index==1)
		{
			index=2;
		}
	}


	time_daojishi=10;
	schedule(schedule_selector(GameController::begintimehjisshiqi),1.0f);

    time_daojishiQuake=10;
    schedule(schedule_selector(GameController::begintimehjisshiqiQuake),1.0f);

	
	for(int i=0;i<arr_arrows.size();i++)
	{
		arr_arrows[i]->setVisible(false);
	}
	arr_arrows[index]->setVisible(true);
}

void GameController::WeiXinShareInGame(EventCustom* evt)
{
	int* type = (int*)evt->getUserData();
	std::string jinping=Tools::getChineseByKey("jinping");
	std::string rule;

	rule  = String::createWithFormat("%s %d",Tools::getChineseByKey("roomid").c_str(),GamerData::getInstance()->getTableId())->getCString();

	if (MjData::getInstance()->getjushu()==4)
	{
		rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("8ju").c_str())->getCString();
	}
	if (MjData::getInstance()->getjushu()==8)
	{
		rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("16ju").c_str())->getCString();
	}
	if (MjData::getInstance()->getIsgang_men()==1)
	{
		rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("zigang").c_str())->getCString();
	}
	else
	{
		rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("zhuanwan").c_str())->getCString();
	}
	if (MjData::getInstance()->getIsgenZhuang()==1)
	{
		rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("gen").c_str())->getCString();
	}
	if(MjData::getInstance()->getpalyrule()==1)
	{
		rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("4renfang").c_str())->getCString();
	}
	else if(MjData::getInstance()->getpalyrule()==2)
	{
		rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("sandingguai").c_str())->getCString();
	}
	else if(MjData::getInstance()->getpalyrule()==3)
	{
		rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("2dingguai").c_str())->getCString();
	}
	else if(MjData::getInstance()->getpalyrule()==4)
	{
		rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("sandingliangfang").c_str())->getCString();
	}
	else if(MjData::getInstance()->getpalyrule()==5)
	{
		rule  = String::createWithFormat("%s %s",rule.c_str(),Tools::getChineseByKey("erdingliangfang").c_str())->getCString();
	}
	if(*type==0)
	{
		MissionWeiXin::getinstance()->shareUrlWeiXin("http://d.laiyagame.com/jinping/download.html",jinping.c_str(),rule.c_str(),*type);
	}
	else
	{
		MissionWeiXin::getinstance()->shareUrlWeiXin("http://d.laiyagame.com/jinping/download.html",rule.c_str(),rule.c_str(),*type);
	}
	
}