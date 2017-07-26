#include "LobbyAdapter.h"
#include "model/LobbyData.h"
#include "util/GameConst.h"
#include "cocos2d.h"
#include "model/GamerData.h"
USING_NS_CC;

LobbyAdapter* LobbyAdapter::mLobbyAdapter = nullptr;
LobbyAdapter* LobbyAdapter::getInstance()
{
	if (mLobbyAdapter == nullptr)
	{
		mLobbyAdapter = new LobbyAdapter();
	}
	return mLobbyAdapter;
}
vector<MessageInfo> LobbyAdapter::parseMessageInfo(rapidjson::Value& value)
{
	vector<MessageInfo> vectorInfo;
	for(int i=0;i<value.Size();i++)
	{
		rapidjson::Value& msg =value[i];
		MessageInfo info;
		info.content = msg["content"].GetString();
		info.createTime = msg["createTime"].GetString();
		info.title = msg["title"].GetString();
		info.id = msg["id"].GetInt();
		vectorInfo.push_back(info);
	}
	return vectorInfo;
}

vector<MessageInfo*> LobbyAdapter::parseMessageInfoData(rapidjson::Value& value)
{
	vector<MessageInfo*> vectorInfo;
	for(int i=0;i<value.Size();i++)
	{
		rapidjson::Value& msg =value[i];
		MessageInfo* info = new MessageInfo();
		info->content = msg["content"].GetString();
		info->createTime = msg["createTime"].GetString();
		info->title = msg["title"].GetString();
		info->id = msg["id"].GetInt();
		vectorInfo.push_back(info);
	}
	return vectorInfo;
}

bool LobbyAdapter::checkActiviyInfoSame(rapidjson::Value& value)
{
	bool flag = false;
	int num = LobbyData::getInstance()->getIntegerForKey(GameConst::key_activity_num,0);
	if (value.Size() == num)
	{
		for(int i=0;i<value.Size();i++)
		{
			rapidjson::Value& msg =value[i];
			string picUrl = msg["picUrl"].GetString();
			bool has = false;
			for(int j=0;j<num;j++)
			{
				string temp = LobbyData::getInstance()->getStringForKey(GameConst::key_activity_pic_url_+StringUtils::format("%d",j));
				if (picUrl.compare(temp) ==0)
				{
					has = true;
				}			
			}
			if (has == false)
			{
				return false;
			}
		}
	}
	return flag;
}
vector<ActivityInfo> LobbyAdapter::parseActivityInfo(rapidjson::Value& value)
{
	vector<ActivityInfo> vectorInfo;
	for(int i=0;i<value.Size();i++)
	{
		rapidjson::Value& msg =value[i];
		ActivityInfo info;
		info.picUrl = msg["picUrl"].GetString();
		info.sort = StringUtils::format("%d",msg["sort"].GetInt());;
		info.title = msg["title"].GetString();
		info.id = StringUtils::format("%d",msg["id"].GetInt());
		//info.createTime = StringUtils::format("%llu",msg["createTime"].GetUint64());
		vectorInfo.push_back(info);		
		LobbyData::getInstance()->setStringForKey(GameConst::key_activity_pic_url_+StringUtils::format("%d",i),info.picUrl);
	}
	LobbyData::getInstance()->setIntegerForKey(GameConst::key_activity_num,value.Size());

	return vectorInfo;
}
BindParentInfo LobbyAdapter::parseBindParentInfo(rapidjson::Value& value)
{
	BindParentInfo info;
	info.nickName = value["nickName"].GetString();
	info.userId = StringUtils::format("%lld",value["userId"].GetInt64());
	return info;
}

BindParentInfo* LobbyAdapter::parseBindParentInfoData(rapidjson::Value& value)
{
	BindParentInfo* info = new BindParentInfo();
	info->nickName = value["nickName"].GetString();
	info->userId = StringUtils::format("%lld",value["userId"].GetInt64());
	return info;
}

void LobbyAdapter::saveAllWXCode(rapidjson::Value& value)
{
	//ÇåÊý¾Ý
	LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_buy_+"2","");
	LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_service_+"2","");
	LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_agent_+"2","");

	rapidjson::Value& buyCard = value["buyCard"];
	rapidjson::Value& support = value["support"];
	rapidjson::Value& joinAgent = value["joinAgent"];
	string feedback = value["feedback"].GetString();
	LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_feedback,feedback);
	for(int i=0;i<buyCard.Size();i++)
	{
		string strNum = StringUtils::format("%d",i+1);
		LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_buy_+strNum,buyCard[i].GetString());
	}
	for(int i=0;i<support.Size();i++)
	{
		string strNum = StringUtils::format("%d",i+1);
		LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_service_+strNum,support[i].GetString());
	}

	for(int i=0;i<joinAgent.Size();i++)
	{
		string strNum = StringUtils::format("%d",i+1);
		LobbyData::getInstance()->setStringForKey(GameConst::key_wx_base_agent_+strNum,joinAgent[i].GetString());
	}
	LobbyData::getInstance()->setStringForKey(GameConst::key_speaker_content,value["speakerContent"].GetString());
}

void LobbyAdapter::saveGameStats(rapidjson::Value& value)
{	
		int juwin=value["JuWin"].GetInt();
		int juping=value["JuDraw"].GetInt();
		int julose=value["JuLose"].GetInt();
		int big_gold_=value["BigGold"].GetInt();
		int zong = juwin+juping+julose;
		float shengLv = 0;
		if (zong == 0)
		{
			shengLv = 0;
		}
		else
		{
			shengLv = juwin*100.0/zong;
		}	
		UserDefault::getInstance()->setIntegerForKey("juwin",juwin);
		UserDefault::getInstance()->setIntegerForKey("juping",juping);
		UserDefault::getInstance()->setIntegerForKey("julose",julose);
		UserDefault::getInstance()->setIntegerForKey("zongJu",zong);
		UserDefault::getInstance()->setFloatForKey("shengLv",shengLv);
		GamerData::getInstance()->setRoomCard(big_gold_);
}
void LobbyAdapter::saveWeiXinLogin(rapidjson::Value& d)
{
	int userid=d["UserID"].GetInt();
	GamerData::getInstance()->setUId(userid);
	int biggold=d["BigGold"].GetInt();
	GamerData::getInstance()->setRoomCard(biggold);

	int status=d["Status"].GetInt();
	GamerData::getInstance()->setStatus(status);

	std::string acceesskey=d["accessKey"].GetString();
	GamerData::getInstance()->setAccessKey(acceesskey);

	std::string ip=d["IP"].GetString();
	GamerData::getInstance()->setUserip(ip);

	int roomid=d["RoomID"].GetInt();
	GamerData::getInstance()->setTableId(roomid);

	LobbyData::getInstance()->setStringForKey(GameConst::key_myPromoterID,d["PromoterID"].GetString());
	LobbyData::getInstance()->setStringForKey(GameConst::key_myInviteCode,d["InviteCode"].GetString());
	LobbyData::getInstance()->setStringForKey(GameConst::key_RefereeCode,d["RefereeID"].GetString());
	GamerData::getInstance()->setMyInviteCode(d["InviteCode"].GetString());
}