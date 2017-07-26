#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"

#include "ui/UIPageView.h"


USING_NS_CC;
using namespace  ui;
using namespace cocostudio;

class PageViewEx : public PageView
{
public:
	int getPageCount();
	void setPageCount(int pageNum);
	int getScrollToIndex();
	PageViewEx();
	~PageViewEx();
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	TouchDirection _touchMoveDirection;
	int pageViewNum;
#endif
};
