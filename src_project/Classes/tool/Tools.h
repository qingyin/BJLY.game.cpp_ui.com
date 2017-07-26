#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class Tools
{
public:
	static string getChineseByKey(const string keyInput);

    static void playBackMusic(std::string kName);
    static void stopBackMusic();
    static void pauseBackMusic();
    static void resumeBackMusic();
	static void stopallbgmusic();

    static void saveEffectVolume(float volume);
    static float getEffectVolume();

    static void saveMusicVolume(float volume);
    static float getMusicVolume();

	static void setLanguage(int languageIndex);//1:本地话，2：普通话
	static int getLanguage();

    static void setBackMusicVolume(float volume);


    static int playEffect(std::string kName);
    static int playCardByGender(int cardid , int iGender,int kindofnative);
    static int playOperateByGender(int operate, int iGender);
	static int playMsgByGender(int msg_tag,int gender);

    static  int g_backGroundMusicID;
	static std::string WStrToUTF8(const std::wstring& str); 
	static std::string StrToUTF8(const std::string &str);

	static std::vector<int> getcurrentTime();
private:
	static void MyWStrToUTF8(std::string& dest, const std::wstring& src);
};

#include "cocos2d.h"
USING_NS_CC;
//类型定义
#ifndef BYTE
typedef unsigned char BYTE;
#endif

#define isLogin					   "IsLogin"					//当前用户是否为登录状态（true:是;false:否)
#define isAgreeUseInfo             "IsAgreeUser"				//用户是否同意用户使用协议(true:同意;false:不同意)
/// function
#define  SEND_CUSTOM_MSG              Director::getInstance()->getEventDispatcher()->dispatchCustomEvent
#define  SEND_BUF_MSG(opcode,buf)       SocketUtil::getInstance()->sendMsg(opcode, buf, 0);
#define  SOCKET_INT_LTOB(num)       SocketUtil::getInstance()->EndianConvertLToB(num);
BYTE GetViewID(BYTE cbMeChair, BYTE cbOtherChair);

