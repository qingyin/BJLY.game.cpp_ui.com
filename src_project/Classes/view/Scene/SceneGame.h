#pragma once

#include "view/ParentInfo/ParentInfo.h"
class SceneGame : public ParentInfo
{
public:
	static Scene* createScene();
	virtual bool init();

	void connectServer();
	void loginTest();


	CREATE_FUNC(SceneGame);

private:
	//模块显示{1:登录;2:游戏大厅}
	void showModels(int index);
private:
	Layer* m_mainLayer;				///主背景层
	Layer* m_uiLayer;				///增加模块层
	Layer* m_gameLayer;				///游戏层
};

