#include "MjData.h"
MjData* MjData::m_mjData = nullptr;

MjData::MjData()
{
    m_jushu           = 0;
    m_is258           = 0;
    m_isfeng          = 0 ;
    m_ishua           = 0;
    m_isminglou       = 0;
    m_banker          = 255;
    m_isingame        = 0;
    m_leftcards       = 0;
    m_leftjushu       = 0;
    m_isjiangyise       = 0;
    m_isqidui       = 0;	

	m_is_gang_men = 0;
	m_is_gang_zhuangwan = 0;
	m_is_genZhuang = 0;
	m_status=0;
	m_fangzhu=0;
	m_palyrule=1;
	m_isinapple=0;//0Õý³£ 1ÉóºË
}

MjData::~MjData()
{
}
MjData* MjData::getInstance()
{
    if (m_mjData == nullptr){
        m_mjData = new MjData();
    }
    return  m_mjData;
}

bool MjData::IsVisitorLogin()
{
	return (m_isinapple == 1);
}