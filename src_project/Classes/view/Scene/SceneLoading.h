#pragma once

#include "view/ParentInfo/ParentInfo.h"

class SceneLoading : public ParentInfo
{
public:
	static Scene* createScene();
	virtual bool init();

	void onEnter();
	void onExit();
	CREATE_FUNC(SceneLoading);

private:
	//UI 加载并且显示
	void uiLoadAndShow();



	//跳转界面测试使用
	void goGame(float ft);
	void versionVerify(EventCustom *evt);
private:
	LoadingBar* loadingBar;    //加载进度条
	Text*		nameValue;	   //加载百分比显示

	void tick(float ft);
	float tickTime;
#define TICK_TIME 1.5
	bool isVersionVerify;
};
