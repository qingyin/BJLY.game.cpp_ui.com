#pragma once

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class GamerData
{
public:
	GamerData();
	~GamerData();
	static GamerData* getInstance();
	CC_SYNTHESIZE(int,m_uid,UId);
	CC_SYNTHESIZE(string, m_nick,Nick);
	CC_SYNTHESIZE(string, m_headurl,HeadUrl);
    CC_SYNTHESIZE(string, m_openid,Openid);
	CC_SYNTHESIZE(string,m_userip,Userip);
	CC_SYNTHESIZE(int,m_gold,Gold);
	CC_SYNTHESIZE(int,m_roomcard,RoomCard);
	CC_SYNTHESIZE(int,m_status,Status);
	CC_SYNTHESIZE(string,m_accessKey,AccessKey);
    CC_SYNTHESIZE(int,m_viewid,ViewId);
    CC_SYNTHESIZE(int, m_seatid,SeatId);
    CC_SYNTHESIZE(int, m_tableid,TableId);
	CC_SYNTHESIZE(int,m_serverport,ServerPort);
	CC_SYNTHESIZE(string, m_serverip,ServerIP);
	CC_SYNTHESIZE(int,m_sex,Sex);
	CC_SYNTHESIZE(int,m_ji_type,Ji_type);//0无 1 冲风机 2 责任及

	CC_SYNTHESIZE(int,m_istingpai,istingpai);
	CC_SYNTHESIZE(string, m_my_invite_code ,MyInviteCode);
	CC_SYNTHESIZE(int,m_quemen,quedemen);

	CC_SYNTHESIZE(string,m_host_url,HostUrl);

private:
	static GamerData* m_gamerData;


}; 
