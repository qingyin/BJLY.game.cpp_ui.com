#include "model/GamerData.h"
#include "util/GameConst.h"
GamerData* GamerData::m_gamerData = nullptr;

GamerData::GamerData()
{
	m_uid= 0;

    m_headurl="";
    m_openid="";
	m_nick= "" ;
	m_sex= 1;

    m_userip="";
	m_gold= 0;
    m_roomcard= 0;
	m_status= 0; 

	m_seatid= 0;
	m_tableid= 0;
	m_viewid= 0;

	m_accessKey="";


    m_serverip = "";
    m_serverport = 0;
	m_istingpai=0;
	m_my_invite_code = "null";
	m_ji_type=0;
	m_istingpai=0;
	m_my_invite_code="";

	m_quemen=0;
	m_host_url = GameConst::URL;
}

GamerData::~GamerData()
{
}
GamerData* GamerData::getInstance()
{
	if (m_gamerData == nullptr){
		m_gamerData = new GamerData();
	}
    return  m_gamerData;
}
