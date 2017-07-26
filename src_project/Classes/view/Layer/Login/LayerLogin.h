/*
 *   ClassName   :   LayerLogin.h
 *   Description :    ��Ϸ��¼����
 *   Author      :      
 *   Date        :	  12.21
*/
#ifndef   _LayerLogin_H_
#define   _LayerLogin_H_

#include "view/ParentInfo/ParentInfo.h"
class LayerLogin : public ParentInfo
{
public:
	virtual bool init();
	CREATE_FUNC(LayerLogin);

	void onEnter();
	void onExit();
	public:
	//UI���ز�����ʾ
	void uiLoadAndShow();
	//��ť�ص�����
	void LoginButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType);
	//��ѡ��ص�����
	void LoginCheckBoxHandler(Ref* sender,ui::CheckBox::EventType type);

	//
	void checkupdate();
	void responseupdate(std::string res);
	

	void loginwithbreak();

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	void showGameMenu(EventCustom* evt);
	void visitorLogin();
private:
	Text* txt_logining;
	Button* btnLogin;
	Button* btn_yk_login;	
	void UpdateBtn(float time);
};
#endif
