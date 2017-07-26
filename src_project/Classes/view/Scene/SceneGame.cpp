#include "view/Scene/SceneGame.h"
#include "view/Layer/Login/LayerLogin.h"
#include "view/Layer/Menu/GameMenu.h"
#include "view/Layer/Main/GameMain.h"
#include "tool/Tools.h"
#include "socket/SocketUtil.h"
#include "controller/login/LoginCommand.h"
Scene* SceneGame::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneGame::create();
	scene->addChild(layer);
	return scene;
}
bool SceneGame::init()
{
	if(!ParentInfo::init()) return false;
	///��������
	m_mainLayer = Layer::create();
	m_mainLayer->setName("m_main");
	this->addChild(m_mainLayer,0);
	///����ģ���
	m_uiLayer = Layer::create();
	m_uiLayer->setName("m_ui");
	this->addChild(m_uiLayer,1);
	///��Ϸ��
	m_gameLayer = Layer::create();
	m_gameLayer->setName("m_game");
	this->addChild(m_gameLayer,2);
	//�жϵ�ǰ�û��Ƿ�Ϊ��¼״̬(Ĭ��Ϊfalse;����ʱΪtrue)
	if (UserDefault::getInstance()->getBoolForKey(isLogin,true))
	{
		showModels(2);
	}else{
		//δ��¼
		showModels(1);
	}
   // connectServer();
	return true;
}
void SceneGame::connectServer()
{
	bool isConnectB = SocketUtil::getInstance()->isConnected();
	if(isConnectB)
	{
		CCLOG("============SceneGame::connectServer()===========StopConnect==");
		SocketUtil::getInstance()->StopConnect();
	}
	bool isConnect = SocketUtil::getInstance()->connectServer();
	if (isConnect)
	{
	   loginTest();
	}
}
void SceneGame::loginTest()
{
//	LoginCommand::getInstance()->requestLogin("111111","haha","192.168.1.1","http://wx.qlogo.cn/mmopen/g3MonUZtNHkdmzicIlibx6iaFqAc56vxLSUfpb6n5WKSYVY0ChQKkiaJSgQ1dZuTOgvLLrhJbERQQ4eMsv84eavHiaiceqxibJxCfHe/0",1);
}
//ģ����ʾ{1:��¼;2:��Ϸ����}
void SceneGame::showModels(int index)
{
	if(index == 1)
	{//��¼��
		auto loginLayer = LayerLogin::create();
		loginLayer->setName("m_ui_login");
		this->m_uiLayer->addChild(loginLayer);
	}else if (index == 2)
	{
		auto gameMenu = GameMenu::create();
		gameMenu->setName("m_ui_gameMenu");
		this->m_uiLayer->addChild(gameMenu);
	}
}
