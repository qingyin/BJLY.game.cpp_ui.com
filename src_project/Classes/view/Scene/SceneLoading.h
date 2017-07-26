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
	//UI ���ز�����ʾ
	void uiLoadAndShow();



	//��ת�������ʹ��
	void goGame(float ft);
	void versionVerify(EventCustom *evt);
private:
	LoadingBar* loadingBar;    //���ؽ�����
	Text*		nameValue;	   //���ذٷֱ���ʾ

	void tick(float ft);
	float tickTime;
#define TICK_TIME 1.5
	bool isVersionVerify;
};
