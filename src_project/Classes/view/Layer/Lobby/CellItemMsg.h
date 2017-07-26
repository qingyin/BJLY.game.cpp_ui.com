#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "view/ParentInfo/ParentInfo.h"
class CellItemMsg : public ParentInfo
{
public:
	virtual bool init();
	CREATE_FUNC(CellItemMsg);
	void setData(int id,string dateTime,string msgContent,string msgTitle);
private:
	Text* txt_dateTime;
	Text* txt_msgTitle;
	Text* txt_msgContent;
	int id;
	void BtnEvent(Ref* sender);
};

