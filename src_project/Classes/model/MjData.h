#pragma once

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class MjData
{
public:
    MjData();
    ~MjData();
    static MjData* getInstance();
    CC_SYNTHESIZE(int,m_jushu,jushu);  //jushu
    CC_SYNTHESIZE(int,m_is258,is258);  //jushu
    CC_SYNTHESIZE(int,m_isfeng,isfeng);  //jushu
    CC_SYNTHESIZE(int,m_ishua,ishua);  //jushu
    CC_SYNTHESIZE(int,m_isminglou,isminglou);  //jushu
	CC_SYNTHESIZE(int,m_banker,banker);  //jushu
	CC_SYNTHESIZE(int,m_isingame,isingame);  //jushu
    CC_SYNTHESIZE(int,m_leftcards,leftcards);  //jushu
    CC_SYNTHESIZE(int,m_leftjushu,leftjushu);  //jushu
	CC_SYNTHESIZE(int,m_isjiangyise,isjiangyise);  //jushu
	CC_SYNTHESIZE(int,m_isqidui,isqidui);  //jushu


	CC_SYNTHESIZE(int,m_is_gang_men,Isgang_men);  //jushu
	CC_SYNTHESIZE(int,m_is_gang_zhuangwan,Isgang_zhuangwan);  //jushu
	CC_SYNTHESIZE(int,m_is_genZhuang,IsgenZhuang);  //jushu
	CC_SYNTHESIZE(int,m_status,status_my);  //jushu
	
	CC_SYNTHESIZE(int,m_fangzhu,fangzhu_viewid);  //jushu
	CC_SYNTHESIZE(int,m_palyrule,palyrule);  //jushu
	CC_SYNTHESIZE(int,m_isinapple,isinapple);  //jushu
    
	bool IsVisitorLogin();
private:
    static MjData* m_mjData;
}; 

