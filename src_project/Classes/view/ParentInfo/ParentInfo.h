#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace  ui;
using namespace cocostudio;
using namespace std;

class ParentInfo : public LayerColor
{
public:
    bool init();
    void setSwallowTouches(bool bSwallow = true);
    void setDelete(bool bDelete = true);

    bool onTouchBegan(Touch *t, Event *e); 
    void onTouchEnded(Touch *t, Event *e);
	

private:
    bool m_bDelete;
    EventListenerTouchOneByOne * m_customListener;
};
