#pragma once


#include "json/document.h"
#include "json/rapidjson.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

#include <string>
#include <vector>
using namespace std;
struct BindParentInfo
{
	string userId;
	string nickName;
};
struct ActivityInfo
{
	string createTime;
	string id;
	string picUrl;
	string sort;
	string title;
};
struct MessageInfo
{
	string content;
	string createTime;
	int id;
	string owner;
	string title;
};

class LobbyAdapter
{
public:
	static LobbyAdapter* getInstance();
	vector<MessageInfo> parseMessageInfo(rapidjson::Value& value);
	vector<MessageInfo*> parseMessageInfoData(rapidjson::Value& value);
	vector<ActivityInfo> parseActivityInfo(rapidjson::Value& value);
	bool checkActiviyInfoSame(rapidjson::Value& value);

	BindParentInfo parseBindParentInfo(rapidjson::Value& value);
	BindParentInfo* parseBindParentInfoData(rapidjson::Value& value);
	void saveAllWXCode(rapidjson::Value& value);
	void saveGameStats(rapidjson::Value& value);
	void saveWeiXinLogin(rapidjson::Value& value);
private:
	static LobbyAdapter* mLobbyAdapter;
}; 