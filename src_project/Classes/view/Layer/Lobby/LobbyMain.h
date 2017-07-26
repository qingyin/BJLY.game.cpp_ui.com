#pragma once

#include "view/ParentInfo/ParentInfo.h"
class LobbyMain : public ParentInfo
{
public:
	void onEnter();
	void onExit();
	virtual bool init();
	CREATE_FUNC(LobbyMain);

private:
	void BtnHandler(Ref* pRef, ui::Widget::TouchEventType touchType);
};

