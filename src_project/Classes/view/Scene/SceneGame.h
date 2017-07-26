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
	//ģ����ʾ{1:��¼;2:��Ϸ����}
	void showModels(int index);
private:
	Layer* m_mainLayer;				///��������
	Layer* m_uiLayer;				///����ģ���
	Layer* m_gameLayer;				///��Ϸ��
};

