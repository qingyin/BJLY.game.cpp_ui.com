#include "view/Scene/SceneLoading.h"
#include "view/Scene/SceneGame.h"
#include "tool/Tools.h"
#include "view/Layer/Menu/GameMenu.h"
//#include "IosHelper.h"
#include "view/Layer/Login/LayerLogin.h"

#include "view/Layer/Lobby/LobbyMain.h"
#include "controller/lobby/LobbyController.h"
#include "util/GameConst.h"
Scene* SceneLoading::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneLoading::create();
	scene->addChild(layer);
	return scene;
}
bool SceneLoading::init()
{
	if(!ParentInfo::init())
		return false;
	/**  **/
	//UI 加载并且显示

	if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	{
		isVersionVerify = true;
	}
	else
	{
		isVersionVerify = false;
		LobbyController::getInstance()->versionVerify();
	}
	uiLoadAndShow();
	Tools::stopallbgmusic();
	Tools::stopBackMusic();

	return true;
}
//UI 加载并且显示
void SceneLoading::uiLoadAndShow()
{
	Node* loadUI = CSLoader::createNode("res/loading/Loading.csb") ;   //Loading
	this->addChild(loadUI);

	
	cocostudio::timeline::ActionTimeline* action = CSLoader::createTimeline("res/loading/Loading.csb");
	action->play("spotAnim",true);
	this->runAction(action);
	tickTime = 0;
	loadingBar = (LoadingBar*)(loadUI->getChildByName("bg_loading_9")->getChildByName("LoadingBarCtrl"));
	schedule(CC_SCHEDULE_SELECTOR(SceneLoading::tick),0.25f);

	this->_eventDispatcher->addCustomEventListener(CustomEvent::key_version_verify,CC_CALLBACK_1(SceneLoading::versionVerify,this));
}

void SceneLoading::tick(float ft)
{
	tickTime = tickTime + ft;
	log("%f",ft);
	if (tickTime > TICK_TIME)
	{
		unschedule(CC_SCHEDULE_SELECTOR(SceneLoading::tick));
		goGame(0);
	}else{
		loadingBar->setPercent(100*tickTime/TICK_TIME);
	}
}

//跳转界面测试使用
void SceneLoading::goGame(float ft)
{
	if (isVersionVerify)
	{
		Scene *s=Scene::create();
		LayerLogin *g=LayerLogin::create();
		s->addChild(g);
		s->setName("login");
		Director::getInstance()->replaceScene(s); 
	}
}

void SceneLoading::onEnter()
{
	ParentInfo::onEnter();
}
void SceneLoading::onExit()
{
	this->_eventDispatcher->removeCustomEventListeners(CustomEvent::key_version_verify);
	ParentInfo::onExit();
}

void SceneLoading::versionVerify(EventCustom *evt)
{
	isVersionVerify = true;
	if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	{
		if (tickTime > TICK_TIME)
		{
			unschedule(CC_SCHEDULE_SELECTOR(SceneLoading::tick));
			goGame(0);
		}
	}
}