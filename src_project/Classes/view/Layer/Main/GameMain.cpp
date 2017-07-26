#include "GameMain.h"
#include "controller/login/LoginCommand.h"
#include "model/MjData.h"
#include "view/Layer/Menu/GameMenu.h"
#include "model/GamerDataDeal.h"
#include "tool/Tiperror.h"
#include "view/Layer/Main/Playing_three.h"
#include "view/Layer/Main/Playing_two.h"
void GameMain::onEnter()
{
	ParentInfo::onEnter();
	this->_eventDispatcher->addCustomEventListener("gamemainstart",CC_CALLBACK_1(GameMain::gameMainStart,this));
	this->_eventDispatcher->addCustomEventListener("gamemainexit",CC_CALLBACK_1(GameMain::gameMainExit,this));
	this->_eventDispatcher->addCustomEventListener("gamenotbegindismiss",CC_CALLBACK_1(GameMain::gameMainDismiss,this));
	this->_eventDispatcher->addCustomEventListener("gamenotbegindismissnodeduct",CC_CALLBACK_1(GameMain::gameMainDismissNoDeduct,this));
	this->_eventDispatcher->addCustomEventListener("gamemainstopschedule",CC_CALLBACK_1(GameMain::gameMainStopSchedule,this));
	this->_eventDispatcher->addCustomEventListener("stopHerat",CC_CALLBACK_1(GameMain::gameMainStopHeart,this));
	this->_eventDispatcher->addCustomEventListener("gameMainBeginHeart",CC_CALLBACK_1(GameMain::gameMainBeginHeart,this));
	this->_eventDispatcher->addCustomEventListener("gameMainJointableFailed",CC_CALLBACK_1(GameMain::gameMainJointableFailed,this));
	this->_eventDispatcher->addCustomEventListener("net_offline",CC_CALLBACK_1(GameMain::revNetOffline,this));
	
}
void GameMain::onExit()
{
	this->_eventDispatcher->removeCustomEventListeners("gamemainstart");
	this->_eventDispatcher->removeCustomEventListeners("gamemainexit");
	this->_eventDispatcher->removeCustomEventListeners("gamenotbegindismiss");
	this->_eventDispatcher->removeCustomEventListeners("gamenotbegindismissnodeduct");
	this->_eventDispatcher->removeCustomEventListeners("gamemainstopschedule");
	this->_eventDispatcher->removeCustomEventListeners("stopHerat");
	this->_eventDispatcher->removeCustomEventListeners("gameMainBeginHeart");
	this->_eventDispatcher->removeCustomEventListeners("gameMainJointableFailed");
	this->_eventDispatcher->removeCustomEventListeners("net_offline");
    unschedule(schedule_selector(GameMain::send_heart));
	mj_controller = nullptr;
	mj_player = nullptr;
	MjData::getInstance()->setstatus_my(0);//不在游戏中
	ParentInfo::onExit();
}

void GameMain::gameMainBeginHeart(EventCustom *evt)
{
	UserDefault::getInstance()->setBoolForKey("iscanbreak",true);
	unschedule(schedule_selector(GameMain::send_heart));
	schedule(schedule_selector(GameMain::send_heart),10);
	UserDefault::getInstance()->setBoolForKey("isfirestjilu",false);
	UserDefault::getInstance()->setBoolForKey("qiehuanwanluo",false);//初始化断网标志
	MjData::getInstance()->setstatus_my(1);//游戏中
}
void GameMain::gameMainJointableFailed(EventCustom *evt)
{
	this->removeFromParent();
}
void GameMain::beginheart()
{
	unschedule(schedule_selector(GameMain::send_heart));
	schedule(schedule_selector(GameMain::send_heart),10);
}
void GameMain::gameMainStopHeart(EventCustom *evt)
{
	stopjiance();
}
bool GameMain::init()
{
	if(!ParentInfo::init()) return false;
	loseNum = 0;
	setOpacity(0);
	//麻将控制层
	mj_controller = GameController::create();
	mj_controller->setName("mj_controller");
	this->addChild(mj_controller,4);
	
	//玩家层
	if(MjData::getInstance()->getpalyrule()==1)
	{
		mj_player = Playing_Laiya::create();
	}
	else if(MjData::getInstance()->getpalyrule()==2)
	{
		mj_player = Playing_three::create();
	}
	else if(MjData::getInstance()->getpalyrule()==4)
	{
		mj_player = Playing_three::create();
	}
	else if(MjData::getInstance()->getpalyrule()==3)
	{
		mj_player = Playing_two::create();
	}
	else if(MjData::getInstance()->getpalyrule()==5)
	{
		mj_player = Playing_two::create();
	}
	
    Sprite *sp_bg=Sprite::create("res/loading/wait/qd1_0018_bd.png");
    sp_bg->setPosition(Vec2(640,360));
    mj_player->addChild(sp_bg);
	mj_player->setName("mj_player");
	this->addChild(mj_player,2);
	mj_player->chushihua(false);
	
	return true;
}
void GameMain::login()
{
	//玩家登陆申请(socket)
	LoginCommand::getInstance()->requestLogin(GamerData::getInstance()->getUId(),GamerData::getInstance()->getTableId());
}
//游戏开始
void GameMain::gameMainStart(EventCustom* evt)
{
	GS2C_RoundStartBroadcast* start = (GS2C_RoundStartBroadcast*) evt->getUserData();
	int round = start->left_round();		//剩余局数
	int gold_now = start->gold_now(); //当前玩家积分
	int banker   = start->banker_uid();	  //庄家用户
	int left_cnt = start->left_cnt(); //剩下的牌数
	MjData::getInstance()->setbanker(banker);
	MjData::getInstance()->setleftjushu(round);
	mj_controller->startGame_gameController(left_cnt, round);
	mj_player->startGame_gamePlayer(banker, left_cnt);

	if(round==MjData::getInstance()->getjushu()-1)
	{
		//第一句 设置 房主
		MjData::getInstance()->setfangzhu_viewid(GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(banker)->getSeatId()));
	}
 
    for(int j=0;j<4;j++)
    {
        GamerData *p=GamerDataDeal::getInstance()->getGamerDataBySeat(j);
		Tools::playOperateByGender(12,p->getSex());
        if(p->getUId()==MjData::getInstance()->getbanker())
        {
			if(MjData::getInstance()->getpalyrule()==1)
			{
                mj_controller->setArrowRoatation(j);
			}
			else if(MjData::getInstance()->getpalyrule()==2||MjData::getInstance()->getpalyrule()==4)
			{
				if(j==2)
				{
					mj_controller->setArrowRoatation(j+1);
				}
				else
				{
					mj_controller->setArrowRoatation(j);
				}
			}
			else if(MjData::getInstance()->getpalyrule()==3||MjData::getInstance()->getpalyrule()==5)
			{
				if(j==1)
				{
					mj_controller->setArrowRoatation(j+1);
				}
				else
				{
					mj_controller->setArrowRoatation(j);
				}
			}
            
            break;
        }
    }
	google::protobuf::RepeatedField< ::google::protobuf::int32 > cards = start->hand_cards();//剩余扑克     
	mj_player->dispacherCard(cards);
	if(banker==GamerData::getInstance()->getUId())
	{
		mj_player->setcardoperateornot(true);
	}
	else
	{
		mj_player->setcardoperateornot(false);
	}
}
//游戏退出
void GameMain::gameMainExit(EventCustom* evt)
{
	GameMenu *g_m=(GameMenu *)this->getParent();
	g_m->refreshjoinroom();

	GamerDataDeal::getInstance()->removeallGamerData();
	if (GamerData::getInstance()->getStatus()!=4)
	{
		CCLOG("============GameMain::gameMainExit===========StopConnect==");
		SocketUtil::getInstance()->StopConnect();
	}

	this->removeFromParentAndCleanup(true);
}

//游戏退出
void GameMain::gameMainStopSchedule(EventCustom* evt)
{
    unschedule(schedule_selector(GameMain::send_heart));
}

//游戏退出
void GameMain::gameMainDismiss(EventCustom* evt)
{
	GameMenu *g_m=(GameMenu *)this->getParent();
	g_m->refreshjoinroom();

    const string  shengyuStr = Tools::getChineseByKey("Dismiss");
    g_m->addChild(Tiplayerr::create(shengyuStr), 10);

	GamerDataDeal::getInstance()->removeallGamerData();


	this->removeFromParentAndCleanup(true);
}

//游戏退出
void GameMain::gameMainDismissNoDeduct(EventCustom* evt)
{
	GameMenu *g_m=(GameMenu *)this->getParent();
	g_m->refreshjoinroom();
	if(MjData::getInstance()->getisinapple()==0)
	{
		const string  shengyuStr = Tools::getChineseByKey("DismissNoDeduct");
		g_m->addChild(Tiplayerr::create(shengyuStr), 10);
	}
	GamerDataDeal::getInstance()->removeallGamerData();
	this->removeFromParentAndCleanup(true);
}
void GameMain::send_heart(float dt) 
{
	CCLOG("sendheart----------------");
	UserDefault::getInstance()->setBoolForKey("isconnect",false);
	LoginCommand::getInstance()->requestHeart(); 
	//开启检测 2s后 还是 0 那就是掉线了
	unschedule(schedule_selector(GameMain::checkHeart));
	schedule(schedule_selector(GameMain::checkHeart),1);
}
void GameMain::checkHeart(float dt)
{
	if(UserDefault::getInstance()->getBoolForKey("isconnect")==true)
	{
		loseNum=0;
		schedule(schedule_selector(GameMain::send_heart),10);
		unschedule(schedule_selector(GameMain::checkHeart));
	}
	else
	{
		if(UserDefault::getInstance()->getBoolForKey("iscanbreak")==true)
		{
			loseNum++;
			if(loseNum<=3)
			{
				unschedule(schedule_selector(GameMain::checkHeart));
				unschedule(schedule_selector(GameMain::send_heart));
				send_heart(0);
			}
			else
			{
				loseNum=0;
				CCLOG("checkheart------loseconnect");
				unschedule(schedule_selector(GameMain::checkHeart));
				unschedule(schedule_selector(GameMain::send_heart));
				bool b = true;
				SEND_CUSTOM_MSG("loseconnect",&b);
			}
		}
	}
}
void GameMain::stopjiance()
{
	unschedule(schedule_selector(GameMain::checkHeart));
	unschedule(schedule_selector(GameMain::send_heart));
}

void GameMain::revNetOffline(EventCustom* evt)
{
	unschedule(schedule_selector(GameMain::checkHeart));
	unschedule(schedule_selector(GameMain::send_heart));
	bool b = true;
	SEND_CUSTOM_MSG("loseconnect",&b);
}