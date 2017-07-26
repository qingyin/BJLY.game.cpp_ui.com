#include "ParentInfo.h"
#include "view/Layer/Lobby/LobbyView.h"
bool ParentInfo::init()
{
    ccColor4B color(0,0,0,180);  //设置面板颜色及透明度
    if (!LayerColor::initWithColor(color))
    {
        return false;
    }

    m_bDelete = false;
    Size sizeTotal   = Director::getInstance()->getVisibleSize();
    setContentSize(sizeTotal);
    m_customListener = EventListenerTouchOneByOne::create();
    m_customListener->setSwallowTouches(true);
    m_customListener->onTouchBegan =  CC_CALLBACK_2(ParentInfo::onTouchBegan,this);
    m_customListener->onTouchEnded = CC_CALLBACK_2(ParentInfo::onTouchEnded,this);

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(m_customListener,this);


	

    return true;
}

void ParentInfo::setSwallowTouches(bool bSwallow)
{
    m_customListener->setSwallowTouches(bSwallow);
}

void ParentInfo::setDelete(bool bDelete)
{
    m_bDelete = bDelete;
}

bool ParentInfo::onTouchBegan(Touch *t, Event *e)
{
        return true;
}

void ParentInfo::onTouchEnded(Touch *t, Event *e)
{
    if (m_bDelete)
    {
        removeFromParent();
    }
}