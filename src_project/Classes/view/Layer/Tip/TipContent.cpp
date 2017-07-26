#include "TipContent.h"
#include "model/GamerData.h"
#include "model/MjData.h"
#include "view/Layer/Menu/GameMenu.h"
#include "controller/table/TableCommand.h"
#include "net/Http.h"
#include "view/Layer/Main/Playing_three.h"
#include "view/Layer/Main/Playing_Laiya.h"
#include "view/Layer/Main/Playing_two.h"
#include "model/GamerDataDeal.h"
#include "tool/Tools.h"
#include "tool/Tiperror.h"
#include "AudioEngine.h"
#include "view/Layer/Main/GameController.h"
#include "platform/JniFun.h"
#include "view/Scene/SceneLoading.h"
#include "util/GameConst.h"
#include "model/LobbyData.h"
#include "view/Layer/Login/LayerLogin.h"
bool TipContent::init()
{
	if(!ParentInfo::init()) return false;

	return true;
}
//显示用户协议
void TipContent::showUIPlayAgreement()
{
	auto playAgreementUI = CSLoader::createNode("res/loading/PlayAgreement.csb") ;   //用户使用协议
	this->addChild(playAgreementUI);
	auto btnBack = (Button*)playAgreementUI->getChildByName("btnBack");
	btnBack->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler, this));	
}
//显示通知信息
void TipContent::showUINotice()
{
	auto playAgreementUI = CSLoader::createNode("res/loading/Notice.csb") ;   //通知
	this->addChild(playAgreementUI);
	auto btnBack = (Button*)playAgreementUI->getChildByName("btnBack");
	btnBack->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler, this));	
	scheduleOnce(schedule_selector(TipContent::closeUI),20.0f);

    
    for(int i=0;i<7;i++)
    {
        String *name=String::createWithFormat("Text_%d",i+1);
        Text *tx_name=(Text*)(playAgreementUI->getChildByName(name->getCString()));
        tx_name->setVisible(false);

        text_Relation.push_back(tx_name);
    }
    httpReqRelation();
}

void TipContent::httpReqRelation()
{
    //获取公告内容
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();
    Http::getInstance()->sendData("querryrelation",CC_CALLBACK_1(TipContent::httpResRelation,this),d,true);
}
void TipContent::httpResRelation(std::string res)
{
    log("%s",res.c_str());
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    if(!d.HasMember("ResultCode")){
        return;
    }
    int  resultCode  = d["ResultCode"].GetInt();
    if(resultCode==0)
    {
        rapidjson::Value& uerdetail=d["Context"];
        for(int i=0;i<uerdetail.Size();i++)
        {
            rapidjson::Value&vale=uerdetail[i];
            std::string msg=vale["msg"].GetString();
            text_Relation[i]->setText(msg);
            text_Relation[i]->setVisible(true);
        }
    }
}
//显示个人战绩
void TipContent::showUIAchievement(std::string res)
{
	setSwallowTouches(true);
	auto achievementUI = CSLoader::createNode("res/loading/Achievement.csb") ;   //个人战绩
	this->addChild(achievementUI);
	auto btnBack = (Button*)achievementUI->getChildByName("btnBack_achive");
	btnBack->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler, this));	
	
	list=(ListView *)achievementUI->getChildByName("ListView_1");
	
	list1=(ListView *)achievementUI->getChildByName("ListView_2");
	list1->setVisible(false);

	rapidjson::Document d;
	d.Parse<0>(res.c_str());
	rapidjson::Value& arr = d["HistoryData"];
	
	for(int i=0;i<arr.Size();i++)
	{
		rapidjson::Value& vale=arr[i];
		std::string time=vale["Time"].GetString();
		int RoomID=vale["RoomID"].GetInt();
		arr_roomid.push_back(RoomID);
		int Round=vale["Round"].GetInt();
		arr_round.push_back(Round);
		int playrule=vale["PlayRule"].GetInt();
		arr_playrule.push_back(playrule);

		String *s=String::createWithFormat("Button_%d",i+1);
		Button *bt_list=(Button *)list->getChildByName(s->getCString());
		bt_list->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler_list,this));	
		bt_list->setTag(i+1);

		Text *tx_num=(Text *)bt_list->getChildByName("tx_num");
		if(i+1<10)
		{
			String *num=String::createWithFormat("0%d",i+1);
			tx_num->setString(num->getCString());
		}
		else
		{
			String *num=String::createWithFormat("%d",i+1);
			tx_num->setString(num->getCString());
		}

		Text *tx_roomid=(Text *)bt_list->getChildByName("tx_roomid");
		String *roomid=String::createWithFormat("%d",RoomID);
		tx_roomid->setString(roomid->getCString());
		Text *tx_time=(Text *)bt_list->getChildByName("tx_time");
		tx_time->setString(time);
		
		int num_people=0;
		
		if(playrule==1)
		{
			num_people=4;
		}
		else if(playrule==2||playrule==4)
		{
			num_people=3;
		}
		else
		{
			num_people=2;
		}

		for(int j=0;j<num_people;j++)
		{
			String *nick=String::createWithFormat("Nick%d",j);
			std::string nick0=vale[nick->getCString()].GetString();

			String *score=String::createWithFormat("Record%d",j);
			int score0=vale[score->getCString()].GetInt();
			String *score1=String::createWithFormat("%d",score0);

			String *str_name=String::createWithFormat("tx_name%d",j+1);
			TextField *name=(TextField *)bt_list->getChildByName(str_name->getCString());
			name->setText(nick0);
			String *str_score=String::createWithFormat("tx_score%d",j+1);
			Text *tx_score=(Text *)bt_list->getChildByName(str_score->getCString());
			tx_score->setString(score1->getCString());
		}
		for(int x=0;x<4;x++)
		{
			if(x>=num_people)
			{
				String *str_name=String::createWithFormat("tx_name%d",x+1);

				TextField *name=(TextField *)bt_list->getChildByName(str_name->getCString());
				

				String *str_score=String::createWithFormat("tx_score%d",x+1);

				Text *tx_score=(Text *)bt_list->getChildByName(str_score->getCString());

				name->setVisible(false);
				tx_score->setVisible(false);
			}
			

			
		}
	}
	for(int i=0;i<12;i++)
	{
		String *bt_nam=String::createWithFormat("Button_%d",i+1);
		Button *bt_list=(Button *)list->getChildByName(bt_nam->getCString());
		if(i<arr.Size())
		{
			bt_list->setVisible(true);
		}
		else
		{
			bt_list->removeFromParent();
		}
	}
	list->setInnerContainerSize(Size(1200,106*arr.Size()));
}
void TipContent::ButtonHandler_list(Ref* pRef, ui::Widget::TouchEventType touchType)
{
	Button *bt=(Button *)pRef;
	if(list->getTouchStartPos().getDistance(list->getTouchEndPos())<10&&touchType==ui::Widget::TouchEventType::ENDED)
	{
		log("bt_tag=====%d",bt->getTag());
		
		MjData::getInstance()->setpalyrule(arr_playrule[bt->getTag()-1]);
		initlist1withdata(arr_roomid[bt->getTag()-1],arr_round[bt->getTag()-1]);
		
	}
}
void TipContent::ButtonHandler_list1(Ref* pRef, ui::Widget::TouchEventType touchType)
{
	Button *bt=(Button *)pRef;
	if(list->getTouchStartPos().getDistance(list->getTouchEndPos())<10&&touchType==ui::Widget::TouchEventType::ENDED)
	{
		log("bt_tag=====%d",bt->getTag());
		reqplay(bt->getTag());
	}
}
void TipContent::reqplay(int round)
{
	rapidjson::Document d;
	d.SetObject();
	rapidjson::Document::AllocatorType& alloctor = d.GetAllocator();

	d.AddMember("UserID",GamerData::getInstance()->getUId(),alloctor);
	d.AddMember("TableID",right_roomid,alloctor);
	d.AddMember("Round",round,alloctor);
	Http::getInstance()->sendData("get_history_detail",CC_CALLBACK_1(TipContent::resplay,this),d,true);
}
void TipContent::resplay(std::string res)
{
	
	log("res====%s",res.c_str());
	rapidjson::Document d;
	d.Parse<0>(res.c_str());
    int  resultCode  = d["ResultCode"].GetInt(); //状态
    if(resultCode != 0){
        const string errStr = d["ErrMsg"].GetString();
        addChild(Tiplayerr::create(errStr), 10);
        return;
    }
	
	
	rapidjson::Value& arr = d["HistoryDataDetail"];

	int bankerid=arr["BankerUid"].GetInt();

	rapidjson::Value& uerdetail=arr["UserDetail"];
	rapidjson::Value& rounddetail=arr["RoundDetail"];
	std::vector<playluxiang>arr_playluxiang;

	for(int i=0;i<rounddetail.Size();i++)
	{
		playluxiang p;
		rapidjson::Value&vale=rounddetail[i];
		int cardlen=vale["CardLen"].GetInt();
		p.cardlen=cardlen;
		std::vector<int>arr_cardid;
		for(int j=0;j<cardlen;j++)
		{
			String *name=String::createWithFormat("%d",j);
			int cardid=vale[name->getCString()].GetInt();
			arr_cardid.push_back(cardid);
		}
		p.cardid=arr_cardid;

		int actionuserid=vale["ActionUser"].GetInt();
		p.actionuerid=actionuserid;

		int provideuerid=vale["ProvideUser"].GetInt();
		p.provideuserid=provideuerid;

		int actioncard=vale["ActionKind"].GetInt();
		p.actionkind=actioncard;

		arr_playluxiang.push_back(p);
	}
	for(int i=0;i<uerdetail.Size();i++)
	{
		rapidjson::Value&vale=uerdetail[i];
		int uerid=vale["UserID"].GetInt();
		std::string nickname=vale["Nick"].GetString();
		std::string faceid=vale["Face"].GetString();
		int goldnum=vale["Gold"].GetInt();
		int seatid=vale["SeatID"].GetInt();
		int quedemen=vale["QueMen"].GetInt();
		if(uerid==GamerData::getInstance()->getUId())
		{
			GamerData* pData = GamerData::getInstance();
			pData->setUId(uerid);	
			pData->setNick(nickname);   //微信昵称
			pData->setHeadUrl(faceid); //头像地址
			pData->setGold(goldnum); //用户金币
			pData->setSeatId(seatid);
			pData->setquedemen(quedemen);
		}
	}
	for(int i=0;i<uerdetail.Size();i++)
	{
		rapidjson::Value&vale=uerdetail[i];
		int uerid=vale["UserID"].GetInt();
		std::string nickname=vale["Nick"].GetString();
		std::string faceid=vale["Face"].GetString();
		int goldnum=vale["Gold"].GetInt();
		int seatid=vale["SeatID"].GetInt();
		int quedemen=vale["QueMen"].GetInt();
		GamerData* pGamerData = new GamerData();
		pGamerData->setUId(uerid);	
		pGamerData->setNick(nickname);   //微信昵称
		pGamerData->setHeadUrl(faceid); //头像地址
		pGamerData->setGold(goldnum); //用户金币
		pGamerData->setSeatId(seatid);
		pGamerData->setquedemen(quedemen);
		GamerDataDeal::getInstance()->addGamerData(uerid,pGamerData);//将加入游戏的玩家数据加入本地
	}
	
	int bankerviewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(bankerid)->getSeatId());

	MjData::getInstance()->setbanker(bankerid);
	
	
	Playing_parent* gameMain;
	if(MjData::getInstance()->getpalyrule()==3||MjData::getInstance()->getpalyrule()==5)
	{
		gameMain=Playing_two::create();
	}
	else if(MjData::getInstance()->getpalyrule()==1)
	{
		gameMain=Playing_Laiya::create();
	}
	else if(MjData::getInstance()->getpalyrule()==2||MjData::getInstance()->getpalyrule()==4)
	{
		gameMain=Playing_three::create();
	}
	Sprite *sp_bg=Sprite::create("res/loading/wait/qd1_0018_bd.png");
	sp_bg->setAnchorPoint(Vec2(0,0));
	gameMain->addChild(sp_bg);
	this->getParent()->addChild(gameMain,100);
	
	
	GameController *c=GameController::create();
	c->startGame_gameController(0,0);
	c->showLuxiangController();
	c->setArrowRoatation(bankerviewid);
	c->setTag(119);
	gameMain->addChild(c,101);
	
	gameMain->chushihua(true);
	
	gameMain->playluxiang_player(arr_playluxiang);

//	this->removeFromParent();


}
void TipContent::showUiBreakFromServer()
{
	auto playAgreementUI = CSLoader::createNode("res/loading/Layer_loseconnect.csb") ;//通知
	this->addChild(playAgreementUI);
	auto btnBack = (Button*)playAgreementUI->getChildByName("btnLoginout");
	btnBack->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler, this));	
	auto btnconfirm = (Button*)playAgreementUI->getChildByName("Button_1");
	btnconfirm->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler, this));	

	//scheduleOnce(schedule_selector(TipContent::restart2miao),2);
}
void TipContent::showUiFanpaiji(int card_id)
{
	Node *n_fanpaiji=CSLoader::createNode("res/loading/Layer_fanpaiji.csb");
	addChild(n_fanpaiji);
	int card_real=1;
	if(card_id==1)
	{
		card_real=9;
	}
	else if(card_id==17)
	{
		card_real=25;
	}
	else if(card_id==33)
	{
		card_real=41;
	}
	else
	{
		card_real=card_id-1;
	}


	Sprite *sp_card=(Sprite *)n_fanpaiji->getChildByName("mj_bg1_2");
	Sprite *sp_huase=(Sprite *)sp_card->getChildByName("mj_37_3");
	String *str_qian=String::createWithFormat("res/cards/mj_%d.png",card_real/16*10+card_real%16);
	sp_huase->setTexture(str_qian->getCString());
	DelayTime *de=DelayTime::create(3);
	CallFunc *call_delay=CallFunc::create(CC_CALLBACK_0(TipContent::removeself__fanpai,this));
    Sequence *se_fan=Sequence::create(de,call_delay,nullptr);
	sp_card->runAction(se_fan);
}
void TipContent::removeself__fanpai()
{
	this->removeFromParent();
}
void TipContent::sp_settexture(Sprite *sp,std::string path)
{
	String *str_hou=String::createWithFormat("res/cards/mj_%d.png",fanpaijicard/16*10+fanpaijicard%16);
	sp->setTexture(str_hou->getCString());
}
void TipContent::restart2miao(float dt)
{
	//JniFun::restartapp();
	auto *scene_l=SceneLoading::createScene();
	CCDirector::getInstance()->replaceScene(scene_l);
}
void TipContent::initlist1withdata(int roomid,int round)
{
	right_roomid=roomid;
	list->setVisible(false);
	list1->setVisible(true);
	for(int i=0;i<round;i++)
	{
		String *s=String::createWithFormat("Button_%d",i+1);
		Button *bt_list=(Button *)list1->getChildByName(s->getCString());
		bt_list->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler_list1,this));	
		bt_list->setTag(i+1);

		Text *tx_num=(Text *)bt_list->getChildByName("tx_num");
		if(i+1<10)
		{
			String *num=String::createWithFormat("%d",i+1);
			tx_num->setString(num->getCString());
		}
		else
		{
			String *num=String::createWithFormat("%d",i+1);
			tx_num->setString(num->getCString());
		}

		Text *tx_roomid=(Text *)bt_list->getChildByName("tx_roomid");
		String *roomid_str=String::createWithFormat("%d",roomid);
		tx_roomid->setString(roomid_str->getCString());
	}
	for(int i=0;i<16;i++)
	{
		String *bt_nam=String::createWithFormat("Button_%d",i+1);
		Button *bt_list=(Button *)list1->getChildByName(bt_nam->getCString());
		if(i<round)
		{
			bt_list->setVisible(true);
		}
		else
		{
			bt_list->setVisible(false);
		}
	}
}
//显示攻略
void TipContent::showUIHelp()
{
	auto help = CSLoader::createNode("res/loading/Help.csb") ;   //攻略
	this->addChild(help);
	auto btnBack = (Button*)help->getChildByName("btnBack");
	btnBack->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler, this));	

	auto views = (ScrollView*)((ImageView*)help->getChildByName("bgContent"))->getChildByName("contents");
}
//显示设置
void TipContent::showUISet()
{
	auto set = CSLoader::createNode("res/loading/Set.csb");  //设置界面
	this->addChild(set);
	auto btnBack = (Button*)set->getChildByName("btnBack");
	btnBack->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler, this));	

	auto SliderMusic = (Slider*)set->getChildByName("SliderMusic");
    SliderMusic->setPercent(Tools::getMusicVolume()*100);
    SliderMusic->addEventListener(CC_CALLBACK_2(TipContent::slider_callback_music, this)); 


	auto SliderSound = (Slider*)set->getChildByName("SliderSound");
    SliderSound->addEventListener(CC_CALLBACK_2(TipContent::slider_callback_effect, this)); 
    SliderSound->setPercent(Tools::getEffectVolume()*100);

	auto btnLoginout = (Button*)set->getChildByName("btnLoginout");//退出登录
	btnLoginout->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler, this));	
	//scheduleOnce(schedule_selector(TipContent::closeUI),10.0f);

}

void TipContent::slider_callback_music(Ref *pSender, ui::Slider::EventType type)
{
    if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider* slider = dynamic_cast<ui::Slider*>(pSender);
        int percent = slider->getPercent();
        Tools::saveMusicVolume(percent*1.0/100.0);
        experimental::AudioEngine::setVolume(Tools::g_backGroundMusicID, Tools::getMusicVolume());
    }
}
void TipContent::slider_callback_effect(Ref *pSender, ui::Slider::EventType type)
{
    if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider* slider = dynamic_cast<ui::Slider*>(pSender);
        int percent = slider->getPercent();
        Tools::saveEffectVolume(percent*1.0/100.0);
    }
}

//显示设置
void TipContent::showUISet_ingame()
{
	auto set = CSLoader::createNode("res/loading/Set_InGame.csb");  //设置界面
	this->addChild(set);
	auto btnBack = (Button*)set->getChildByName("btnBack");
	btnBack->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler, this));	

    auto SliderMusic = (Slider*)set->getChildByName("SliderMusic");
    SliderMusic->setPercent(Tools::getMusicVolume()*100);
    SliderMusic->addEventListener(CC_CALLBACK_2(TipContent::slider_callback_music, this)); 


    auto SliderSound = (Slider*)set->getChildByName("SliderSound");
    SliderSound->addEventListener(CC_CALLBACK_2(TipContent::slider_callback_effect, this)); 
    SliderSound->setPercent(Tools::getEffectVolume()*100);

	auto btnLoginout = (Button*)set->getChildByName("btnLoginout");//解散房间
	btnLoginout->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler_ingame, this));	
	if(GamerData::getInstance()->getStatus()>=2)
	{
		btnLoginout->setVisible(true);
		btnLoginout->setEnabled(true);
	}
	else
	{
		if(GamerData::getInstance()->getSeatId()!=0)
		{
			btnLoginout->setVisible(false);
			btnLoginout->setEnabled(false);
		}
		else
		{
			btnLoginout->setVisible(true);
			btnLoginout->setEnabled(true);
		}
	}
	
	
	//scheduleOnce(schedule_selector(TipContent::closeUI),10.0f);

}


//显示是否同意解散房间
void TipContent::showUIDismissAsk()
{
	auto set = CSLoader::createNode("res/loading/dismissRoom.csb");  //设置界面
	this->addChild(set);
	auto btn_ok = (Button*)set->getChildByName("btnAgree");
	btn_ok->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler_ingame, this));	

	auto btn_no = (Button*)set->getChildByName("btnDecline");//解散房间
	btn_no->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler_ingame, this));

}

//显示免费领取
void TipContent::showUIFreeGold()
{
	Node *n_freegold=CSLoader::createNode("res/loading/ActivityCenter.csb");
	addChild(n_freegold);
	auto bg=(ImageView *)n_freegold->getChildByName("bg");
	Button *bt_back=(Button *)bg->getChildByName("btnBack");
	bt_back->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler,this));

}
//显示新手礼包
void TipContent::showUiNewPlayerGift()
{
	Node *n_freegold=CSLoader::createNode("res/loading/Layer_giftBag.csb");
	addChild(n_freegold);
	setDelete(true);
}
//显示创建房间
void TipContent::showUICreateRoom()
{
    this->setName("enterroom");

	Node *n_freegold=CSLoader::createNode("res/loading/Layer_createroom.csb");
	addChild(n_freegold);
	ImageView *bg=(ImageView *)n_freegold->getChildByName("bg");
	Button *bt_back=(Button *)bg->getChildByName("btnBack");
	bt_back->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler,this));
    
    c_jushu_4=(CheckBox *)bg->getChildByName("CheckBox_1");
    c_jushu_8=(CheckBox *)bg->getChildByName("CheckBox_1_0");
    CheckBox *c_jushu_258=(CheckBox *)bg->getChildByName("CheckBox_1_0_0");
    CheckBox *c_jushu_hua=(CheckBox *)bg->getChildByName("CheckBox_1_0_0_0_0");
    CheckBox *c_jushu_feng=(CheckBox *)bg->getChildByName("CheckBox_1_0_0_0");
    CheckBox *c_jushu_minglou=(CheckBox *)bg->getChildByName("CheckBox_1_0_0_0_0_0");
	CheckBox *c_jushu_jiangyise=(CheckBox *)bg->getChildByName("CheckBox_1_0_0_0_0_0_0");
	CheckBox *c_jushu_qidui=(CheckBox *)bg->getChildByName("CheckBox_1_0_0_0_0_0_0_0");

    Button *bt_createroom=(Button *)bg->getChildByName("Button_1");
    bt_createroom->addClickEventListener(CC_CALLBACK_0(TipContent::createroom, this));
    
	c_jushu_4->addEventListenerCheckBox(this,checkboxselectedeventselector(TipContent::selectedEvent));
    c_jushu_8->addEventListenerCheckBox(this,checkboxselectedeventselector(TipContent::selectedEvent));
    c_jushu_258->addEventListenerCheckBox(this,checkboxselectedeventselector(TipContent::selectedEvent));
    c_jushu_hua->addEventListenerCheckBox(this,checkboxselectedeventselector(TipContent::selectedEvent));
    c_jushu_feng->addEventListenerCheckBox(this,checkboxselectedeventselector(TipContent::selectedEvent));
    c_jushu_minglou->addEventListenerCheckBox(this,checkboxselectedeventselector(TipContent::selectedEvent));
	c_jushu_jiangyise->addEventListenerCheckBox(this,checkboxselectedeventselector(TipContent::selectedEvent));
	c_jushu_qidui->addEventListenerCheckBox(this,checkboxselectedeventselector(TipContent::selectedEvent));
	MjData::getInstance()->setjushu(4);
	MjData::getInstance()->setis258(1);
	MjData::getInstance()->setisfeng(1);
	MjData::getInstance()->setishua(1);
	MjData::getInstance()->setisminglou(1);
	MjData::getInstance()->setisjiangyise(1);
	MjData::getInstance()->setisqidui(1);
	MjData::getInstance()->setpalyrule(1);
}
void TipContent::selectedEvent(cocos2d::Ref *pSender, CheckBoxEventType type)
{
    CheckBox *c=(CheckBox *)pSender;
    string name=c->getName();
    switch (type) {
        case cocos2d::ui::CHECKBOX_STATE_EVENT_SELECTED:
            if(name=="CheckBox_1")
            {
                c_jushu_8->setSelected(false);
                MjData::getInstance()->setjushu(4);
            }
            if(name=="CheckBox_1_0")
            {
                c_jushu_4->setSelected(false);
                MjData::getInstance()->setjushu(8);
            }
            if(name=="CheckBox_1_0_0")
            {
                MjData::getInstance()->setis258(1);
            }
            if(name=="CheckBox_1_0_0_0")
            {
                MjData::getInstance()->setisfeng(1);
            }
            if(name=="CheckBox_1_0_0_0_0")
            {
                MjData::getInstance()->setishua(1);
            }
            if(name=="CheckBox_1_0_0_0_0_0")
            {
                MjData::getInstance()->setisminglou(1);
            }
			if(name=="CheckBox_1_0_0_0_0_0_0")
			{
				 MjData::getInstance()->setisjiangyise(1);
			}
			if(name=="CheckBox_1_0_0_0_0_0_0_0")
			{
				MjData::getInstance()->setisqidui(1);
			}
            
            break;
        case cocos2d::ui::CHECKBOX_STATE_EVENT_UNSELECTED:
            if(name=="CheckBox_1")
            {
                c_jushu_8->setSelected(true);
                MjData::getInstance()->setjushu(8);
            }
            if(name=="CheckBox_1_0")
            {
                c_jushu_4->setSelected(true);
                MjData::getInstance()->setjushu(4);
            }
            if(name=="CheckBox_1_0_0")
            {
                MjData::getInstance()->setis258(0);
            }
            if(name=="CheckBox_1_0_0_0")
            {
                MjData::getInstance()->setisfeng(0);
            }
            if(name=="CheckBox_1_0_0_0_0")
            {
                MjData::getInstance()->setishua(0);
            }
            if(name=="CheckBox_1_0_0_0_0_0")
            {
                MjData::getInstance()->setisminglou(0);
            }
			if(name=="CheckBox_1_0_0_0_0_0_0")
			{
				MjData::getInstance()->setisjiangyise(0);
			}
			if(name=="CheckBox_1_0_0_0_0_0_0_0")
			{
				MjData::getInstance()->setisqidui(0);
			}
            break;
        default:
            break;
    }
}
void TipContent::createroom()
{
    GameMenu *g=(GameMenu *)this->getParent();
    g->createroom();
}
//显示加入房间
void TipContent::showUIEnterRoom()
{
    this->setName("enterroom");
	Node *n_freegold=CSLoader::createNode("res/loading/Layer_enterroom.csb");
	addChild(n_freegold);
	Sprite *bg=(Sprite *)n_freegold->getChildByName("bac_03_4");
	Button *bt_back=(Button *)bg->getChildByName("btnBack");
	bt_back->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler,this));


	Button *bt_delete=(Button *)bg->getChildByName("Button_delete");
	Button *bt_re=(Button *)bg->getChildByName("Button_re");
	Button *bt_ok=(Button *)bg->getChildByName("Button_ok");
	bt_delete->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler_enterroom,this));
	bt_re->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler_enterroom,this));
	bt_ok->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler_enterroom,this));
	enterroom_tx_num=0;



	for(int i=0;i<6;i++)
	{
		String *s=String::createWithFormat("Text_%d",i+1);
	    Text *tx_=(Text *)bg->getChildByName(s->getCString());
		tx_enterroom.push_back(tx_);
		tx_->setString("");
	}
	for(int i=0;i<10;i++)
	{
	   String *s=String::createWithFormat("Button_%d",i);
	   Button *bt_=(Button *)bg->getChildByName(s->getCString());
	   bt_enterroom.push_back(bt_);
	   bt_->setTag(i);
	   bt_->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler_enterroom,this));
	}
}
void TipContent::ButtonHandler_enterroom(Ref* pRef, ui::Widget::TouchEventType touchType)
{
	if (touchType != ui::Widget::TouchEventType::ENDED) return;
	Button* pBtn = (Button*) pRef;
	string name = pBtn->getName();
	if (name == "btnBack"){
		this->unschedule(schedule_selector(TipContent::closeUI));
		this->removeAllChildrenWithCleanup(true);
	}else if (name == "Button_delete"){
		//删除一个字符
		if(room_id.size()>0&&enterroom_tx_num==room_id.size())
		{
			room_id.erase(room_id.end()-1);
			enterroom_tx_num--;
			tx_enterroom.at(enterroom_tx_num)->setString("");
		}
    }else if(name == "Button_ok")
    {//
        if(enterroom_tx_num==6)
        {
            GameMenu *g=(GameMenu *)this->getParent();
            char s_room[10]={0};
            sprintf(s_room,"%d%d%d%d%d%d",room_id[0],room_id[1],room_id[2],room_id[3],room_id[4],room_id[5]);
            g->enterroom(s_room);
        }
	}else if(name == "Button_re")
	{//重新输入
		room_id.clear();
		enterroom_tx_num=0;
		for(int i=0;i<6;i++)
		{
			tx_enterroom[i]->setString("");
		}
	}else
	{
		if(enterroom_tx_num!=6)
		{
			tx_enterroom.at(enterroom_tx_num)->setString(String::createWithFormat("%d",pBtn->getTag())->getCString());
			enterroom_tx_num=enterroom_tx_num+1;
			if(enterroom_tx_num==6)
			{
				room_id.push_back(pBtn->getTag());
			}
			else
			{
				room_id.push_back(pBtn->getTag());
			}
		}
		
	}
}
void TipContent::showuiupdate(std::string url,bool isForceUpdate)
{
	Node *n_update=CSLoader::createNode("res/loading/Layer_update.csb");
	addChild(n_update);
	if (isForceUpdate)
	{
		Button *bt_update=(Button *)n_update->getChildByName("Button_update");
		bt_update->addClickEventListener(CC_CALLBACK_0(TipContent::openurl,this,url));
		n_update->getChildByName("btn_ok")->setVisible(false);
		n_update->getChildByName("btn_cancel")->setVisible(false);
	}
	else
	{
		Button *btn_ok=(Button *)n_update->getChildByName("btn_ok");
		btn_ok->addClickEventListener(CC_CALLBACK_0(TipContent::openurl,this,url));

		Button *btn_cancel=(Button *)n_update->getChildByName("btn_cancel");
		btn_cancel->addClickEventListener(CC_CALLBACK_0(TipContent::clickcanle,this));

		n_update->getChildByName("Button_update")->setVisible(false);
	}
}
void TipContent::clickcanle()
{
	UserDefault::getInstance()->setBoolForKey("isupdate",false);
	LayerLogin *l_l=(LayerLogin *)this->getParent();
	l_l->loginwithbreak();
	this->removeFromParent();
}
void TipContent::openurl(std::string url)
{
	Application::getInstance()->openURL(url.c_str());
}
//显示个人信息
void TipContent::showUIplayerInfoInGame(int viewid)
{    
	Node *n_freegold=CSLoader::createNode("res/loading/Layer_palyerinfo.csb");
	addChild(n_freegold);
	Button *bt_back=(Button *)n_freegold->getChildByName("btnBack");
	bt_back->addTouchEventListener(CC_CALLBACK_2(TipContent::ButtonHandler,this));
    
    
    Sprite *touxiang=(Sprite *)n_freegold->getChildByName("Sprite_icon");
    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();

	//String *s_viewid=String::createWithFormat("%d",viewid);
	if (viewid==0)
	{
		//path+="download_image.png";
		path += GamerData::getInstance()->getOpenid()+".png";
	}
	else
	{
		string strViewid = String::createWithFormat("%d",GamerDataDeal::getInstance()->getGamerDataBySeat(viewid)->getUId() )->getCString();
		path=path + strViewid +".png";
	}
    Sprite *sp=Sprite::create(path.c_str());
	if(sp!=nullptr)
	{
		  touxiang->setTexture(sp->getTexture());
	}  

    if (viewid==0)
    {   
        Text *tx_name=(Text *)n_freegold->getChildByName("Text_1");
        tx_name->setString(GamerData::getInstance()->getNick().c_str());

        Text *tx_id=(Text *)n_freegold->getChildByName("Text_1_0_0");
        String *s_id=String::createWithFormat("%d",GamerData::getInstance()->getUId());
        tx_id->setString(s_id->getCString());

        Text *tx_biggold=(Text *)n_freegold->getChildByName("Text_1_1_0");
        String *s_biggold=String::createWithFormat("%d",GamerData::getInstance()->getRoomCard());
        tx_biggold->setString(s_biggold->getCString());

        Text *tx_ip=(Text *)n_freegold->getChildByName("Text_1_1_1_0");
		tx_ip->setString(GamerData::getInstance()->getUserip().c_str());

		Text *txt_InvitationCode=(Text *)n_freegold->getChildByName("txt_code");
		txt_InvitationCode->setString(LobbyData::getInstance()->getStringForKey(GameConst::key_myInviteCode));
    } 
    else
    {
        Text *tx_name=(Text *)n_freegold->getChildByName("Text_1");
        tx_name->setString(GamerDataDeal::getInstance()->getGamerDataBySeat(viewid)->getNick().c_str());

        Text *tx_id=(Text *)n_freegold->getChildByName("Text_1_0_0");
        String *s_id=String::createWithFormat("%d",GamerDataDeal::getInstance()->getGamerDataBySeat(viewid)->getUId());
        tx_id->setString(s_id->getCString());

        Text *tx_biggold=(Text *)n_freegold->getChildByName("Text_1_1_0");
        String *s_biggold=String::createWithFormat("%d",GamerDataDeal::getInstance()->getGamerDataBySeat(viewid)->getRoomCard());
        tx_biggold->setString(s_biggold->getCString());

        Text *tx_ip=(Text *)n_freegold->getChildByName("Text_1_1_1_0");
		tx_ip->setString(GamerDataDeal::getInstance()->getGamerDataBySeat(viewid)->getUserip().c_str());

		Text *txt_InvitationCode=(Text *)n_freegold->getChildByName("txt_code");
		//txt_InvitationCode->setString(GamerDataDeal::getInstance()->getGamerDataBySeat(viewid)->getMyInviteCode().c_str());
		txt_InvitationCode->setString("");
    }


	Text *tx_juwin=(Text *)n_freegold->getChildByName("Text_2_1");
	Text *tx_juping=(Text *)n_freegold->getChildByName("Text_2_0_0_0");
	Text *tx_julose=(Text *)n_freegold->getChildByName("Text_2_0_1");
	Text *txt_gameNum=(Text *)n_freegold->getChildByName("txt_gameNum");
	Text *txt_shengLv=(Text *)n_freegold->getChildByName("txt_shengLv");

	String *str1=String::createWithFormat("%d",UserDefault::getInstance()->getIntegerForKey("juwin"))	;
	tx_juwin->setString(str1->getCString());

	String *str2=String::createWithFormat("%d",UserDefault::getInstance()->getIntegerForKey("juping"))	;
	tx_juping->setString(str2->getCString());

	String *str3=String::createWithFormat("%d",UserDefault::getInstance()->getIntegerForKey("julose"))	;
	tx_julose->setString(str3->getCString());

	str3=String::createWithFormat("%d",UserDefault::getInstance()->getIntegerForKey("zongJu"))	;
	txt_gameNum->setString(str3->getCString());
	str3=String::createWithFormat("%0.2lf%%",UserDefault::getInstance()->getFloatForKey("shengLv"))	;
	txt_shengLv->setString(str3->getCString());

}

//按钮回调函数
void TipContent::ButtonHandler(Ref* pRef, ui::Widget::TouchEventType  touchType)
{
	if (touchType != ui::Widget::TouchEventType::ENDED) return;
	Button* pBtn = (Button*) pRef;
	string name = pBtn->getName();
	if (name == "btnBack"){
		this->unschedule(schedule_selector(TipContent::closeUI));
		this->removeAllChildrenWithCleanup(true);
        removeFromParent();
	}else if (name == "btnLoginout"){
		//退出登录
		CCDirector::getInstance()->end();
	//	JniFun::restartapp();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
	}
	else if (name == "Button_1"){
		SEND_CUSTOM_MSG("restartbyconfirm");
		removeFromParent();
	}
	else if (name == "btnBack_achive"){
		if(list1->isVisible()==false)
		{
			this->removeFromParent();
		}
		else
		{
			list->setVisible(true);
			list1->setVisible(false);
		}
		
	}
}	
//按钮回调函数
void TipContent::ButtonHandler_ingame(Ref* pRef, ui::Widget::TouchEventType  touchType)
{
	if (touchType != ui::Widget::TouchEventType::ENDED) return;
	Button* pBtn = (Button*) pRef;
	string name = pBtn->getName();
	if (name == "btnBack"){
		this->unschedule(schedule_selector(TipContent::closeUI));
		this->removeAllChildrenWithCleanup(true);
        removeFromParent();
	}else if (name == "btnLoginout"){
		//解散房间
        TableCommand::getInstance()->requestLeaveTable(1);
		this->removeFromParent();
	}else if(name == "btnAgree")
	{//游戏中【同意解散房间】

	}else if(name == "btnDecline")
	{//游戏中【拒绝解散房间】

	}
}


//定时器：10秒自动关闭当前界面
void TipContent::closeUI(float ft)
{
	this->removeAllChildrenWithCleanup(true);
}