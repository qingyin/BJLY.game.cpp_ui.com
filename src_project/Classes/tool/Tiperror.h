#pragma once
#include "view/ParentInfo/ParentInfo.h"


USING_NS_CC;
class Tiplayerr : public  ParentInfo
{
public:
	static Tiplayerr* create(const std::string content){
		Tiplayerr* tip = new Tiplayerr();
		if (tip && tip->init(content))
		{
			tip->autorelease();
			return tip;
		}
		CC_SAFE_RELEASE_NULL(tip);
		return tip;
	}
	bool init(string game_msg = "");
	void onExit();
private:
  Node * m_root;
  string msg;
};
