#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "view/ParentInfo/ParentInfo.h"
class CellItemRecord : public ParentInfo
{
public:
	virtual bool init();
	CREATE_FUNC(CellItemRecord);
	void setData(string roomCode,string dateTime,string play1NameScore,string play2NameScore,string play3NameScore,string play4NameScore,int indexID);
private:
	int indexID;
	Text* roomCode;
	Text* dateTime;
	Text* playNameScore[4];
	void BtnEvent(Ref* sender);
};

