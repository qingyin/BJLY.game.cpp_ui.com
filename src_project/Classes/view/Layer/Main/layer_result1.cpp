#include "layer_result1.h"
#include "model/GamerDataDeal.h"
#include "model/MjData.h"
#include "platform/MissionWeiXin.h"
#include "view/Layer/Main/layer_result.h"
#include "view/Layer/Main/Playing_three.h"
void layer_result_detail::onEnter()
{
	ParentInfo::onEnter();
	
}
void layer_result_detail::onExit()
{
	
	ParentInfo::onExit();
}

bool layer_result_detail::init()
{
	if(!ParentInfo::init())
	{
		return false;
	}
	n_root=CSLoader::createNode("res/loading/Layer_result2.csb");
	addChild(n_root);
	
	return true;
}
void layer_result_detail::removesthis()
{
	this->setVisible(false);
	this->setZOrder(-1);
}
void layer_result_detail::initwithdata(result_detail_struct r_d_s)
{
	layer_result *l=(layer_result *)this->getParent();
	std::vector<hu_type>arrhu=l->arr_hu;

	Sprite *bg=(Sprite *)n_root->getChildByName("bg_tankuang_jiexuan_1");
	Sprite *win_tag=(Sprite *)bg->getChildByName("title_win_3");
	if(l->win_tag==1)
	{
		win_tag->setTexture("res/srcRes/title_win.png");
	}
	else if(l->win_tag==2)
	{
		win_tag->setTexture("res/loading/layer_result/title_title_lose.png");
	}
	else if(l->win_tag==3)
	{
		win_tag->setTexture("res/loading/layer_result/title_title_lose.png");
	}

	Button *bt_remove=(Button *)bg->getChildByName("Button_1");
	bt_remove->addClickEventListener(CC_CALLBACK_0(layer_result_detail::removesthis,this));


	std::vector<result_DetailItem >arr_details=r_d_s.arr_detailitem;


	for(int i=0;i<arr_details.size();i++)
	{
		result_DetailItem r_d=arr_details[i];
		int uid=r_d.uid;
		GamerData *p_palyerinfo=GamerDataDeal::getInstance()->getGamerData(uid);
		int viewid=GetViewID(GamerData::getInstance()->getSeatId(),p_palyerinfo->getSeatId());
		std::vector<result_LittleItem>arr_r_l=r_d.arr_littleitem;

		String *sp_path=String::createWithFormat("bg_suanfen_others_%d",i+1);

		Sprite *sp_onedetail=(Sprite *)bg->getChildByName(sp_path->getCString());

		Sprite *sp_head=(Sprite *)sp_onedetail->getChildByName("touxiang_4");
		std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
		String *s=String::createWithFormat("%s%d.png",path.c_str(),p_palyerinfo->getUId());
		sp_head->setTexture(s->getCString());//保存到本地的别的玩家的头像
		float acle=73/sp_head->getContentSize().width;
		sp_head->setScale(acle);

		Sprite *sp_tingpai=(Sprite *)sp_onedetail->getChildByName("icon_baoting_39");
		if(p_palyerinfo->getistingpai()==1)
		{
			sp_tingpai->setVisible(true);
		}
		else
		{
			sp_tingpai->setVisible(false);
		}

		Sprite *sp_banker=(Sprite *)sp_onedetail->getChildByName("qd1_0013_z_415");
		if(uid==MjData::getInstance()->getbanker())
		{
			sp_banker->setVisible(true);
		}
		else
		{
			sp_banker->setVisible(false);
		}



		Text *tx_fenshu=(Text *)sp_onedetail->getChildByName("Text_total_gold");
		String *fenshu=String::createWithFormat("%d",p_palyerinfo->getGold());
		tx_fenshu->setString(fenshu->getCString());

		Text *tx_name=(Text *)sp_onedetail->getChildByName("Text_name_user");
		tx_name->setString(p_palyerinfo->getNick());

		Text *tx_jiao=(Text *)sp_onedetail->getChildByName("Text_hupaitype");
	    Text *tx_fangshi=(Text *)sp_onedetail->getChildByName("Text_fangshi");
		Sprite *sp_di=(Sprite *)sp_onedetail->getChildByName("bg_hupaifanshi_little_6");
		for(int j=0;j<l->arr_hu.size();j++)
		{
			if(l->arr_hu[j].uid==uid)
			{
				String *hu_path=String::createWithFormat("hu_%d",l->arr_hu[j].hutype+1);
				std::string s_=Tools::getChineseByKey(hu_path->getCString());
				tx_jiao->setString(s_);

				if(l->arr_hu[j].gang_type==1)//1自摸 2点炮 3放热跑 4杠上花 5抢杠胡（有杠上花就没有自摸）
				{
					std::string path=Tools::getChineseByKey("zimo");
					tx_fangshi->setString(path.c_str());
					
				}
				else if(l->arr_hu[j].gang_type==2)
				{
					std::string path=Tools::getChineseByKey("dianpao");
					tx_fangshi->setString(path.c_str());
				}
				else if(l->arr_hu[j].gang_type==3)
				{
					std::string path=Tools::getChineseByKey("fangrepao");
					tx_fangshi->setString(path.c_str());
				}
				else if(l->arr_hu[j].gang_type==4)
				{
					std::string path=Tools::getChineseByKey("gangshanghua");
					tx_fangshi->setString(path.c_str());
				}
				else if(l->arr_hu[j].gang_type==5)
				{
					std::string path=Tools::getChineseByKey("qiangganghu");
					tx_fangshi->setString(path.c_str());
				}
				else
				{
					sp_di->setVisible(false);
					tx_fangshi->setVisible(false);
					
				}

				Text *tx_win_gold=(Text *)sp_onedetail->getChildByName("Text_addgold");
				String *win_gold=String::createWithFormat("%d",l->arr_hu[j].fenzhi_win);
				tx_win_gold->setString(win_gold->getCString());

			}
		}
		
		for(int j=0;j<9;j++)
		{
			String *detail_path=String::createWithFormat("Node_tx_%d",j+1);
			Node *n_de=sp_onedetail->getChildByName(detail_path->getCString());
			n_de->setVisible(false);
		}
		
		for(int j=0;j<arr_r_l.size();j++)
		{

			String *detail_path=String::createWithFormat("Node_tx_%d",j+1);
			Node *n_de=sp_onedetail->getChildByName(detail_path->getCString());
			n_de->setVisible(true);
			
			CCLOG("-------%s %d",arr_r_l[j].kind_type.c_str(),arr_r_l[j].color);
			
			

			Text *tx_1=(Text *)n_de->getChildByName("Text_name");
			tx_1->setString(arr_r_l[j].kind_type);

			Text *tx_2=(Text *)n_de->getChildByName("num");
			tx_2->setString(arr_r_l[j].fenzhi);

			Text *tx_3=(Text *)n_de->getChildByName("Text_tag_1_0_0");
			if(arr_r_l[j].zhuang2bei==1)
			{
				tx_3->setVisible(true);
			}
			else
			{
				tx_3->setVisible(false);
			}
			CCLOG(" %d %s  %d",arr_r_l[j].color,arr_r_l[j].kind_type.c_str(),i);
			if(arr_r_l[j].color==1)
			{
				
				tx_1->setTextColor(Color4B::RED);
				tx_2->setTextColor(Color4B::RED);
				tx_3->setTextColor(Color4B::RED);
			}
			else if(arr_r_l[j].color==2)
			{
				tx_1->setTextColor(Color4B::GREEN);
				tx_2->setTextColor(Color4B::GREEN);
				tx_3->setTextColor(Color4B::GREEN);
			}
			else if(arr_r_l[j].color==3||arr_r_l[j].color==4)
			{
				tx_1->setTextColor(Color4B(48,48,48,255));
				tx_2->setTextColor(Color4B(48,48,48,255));
				tx_3->setTextColor(Color4B(48,48,48,255));
			}
		}
	}
	for(int i=0;i<4;i++)
	{
		String *sp_path=String::createWithFormat("bg_suanfen_others_%d",i+1);
		Sprite *sp_onedetail=(Sprite *)bg->getChildByName(sp_path->getCString());
		if(i>=arr_details.size())
		{
			sp_onedetail->setVisible(false);
		}
	}
}
