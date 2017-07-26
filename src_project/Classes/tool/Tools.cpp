#include "Tools.h"
#include "AudioEngine.h"
int Tools::g_backGroundMusicID = 0;
#include "model/MjData.h"
string Tools::getChineseByKey(const string keyInput)
{
	auto fileUtils = FileUtils::getInstance();
	std::string fullPathForFilename = fileUtils->fullPathForFilename("res/srcRes/ConstInput.plist");
	bool isFileExist = false;
	isFileExist = fileUtils->isFileExist(fullPathForFilename);
	if (!isFileExist)
    {
		CCLOG("ConstInput.plist doesn't exist.");
		return "";
	}
	ValueMap map = fileUtils->getValueMapFromFile(fullPathForFilename);
	Value valueOut =  map[keyInput];
	if (valueOut.isNull())
    {
		CCLOG("%s doesn't exist.",keyInput.c_str());
		return "";
	}
	return valueOut.asString();
}

BYTE GetViewID(BYTE cbMeChair, BYTE cbOtherChair)
{
    //参数判断
    if (cbOtherChair<0 && cbOtherChair>3) 
        return 255;

    //转换椅子
    BYTE cbViewSeat=(cbOtherChair+4-cbMeChair)%4;

	if(MjData::getInstance()->getpalyrule()==2||MjData::getInstance()->getpalyrule()==4)
	{
		 cbViewSeat=(cbOtherChair+3-cbMeChair)%3;
	}
	else if(MjData::getInstance()->getpalyrule()==3||MjData::getInstance()->getpalyrule()==5)
	{
		 cbViewSeat=(cbOtherChair+2-cbMeChair)%2;
	}

    return cbViewSeat;
}

void Tools::saveEffectVolume(float volume)
{
    UserDefault::getInstance()->setFloatForKey("EffectVolume", volume);
}

float Tools::getEffectVolume()
{
    return UserDefault::getInstance()->getFloatForKey("EffectVolume", 1.0);
}

void Tools::saveMusicVolume(float volume)
{
    UserDefault::getInstance()->setFloatForKey("MusicVolume", volume);
}

float Tools::getMusicVolume()
{
    return UserDefault::getInstance()->getFloatForKey("MusicVolume", 1.0);
}

void Tools::setLanguage(int languageIndex)
{
	UserDefault::getInstance()->setIntegerForKey("Language",languageIndex);
}
int Tools::getLanguage()
{
	return UserDefault::getInstance()->getIntegerForKey("Language",1);
}

static const std::string s_soundPath = "sound/";
void Tools::playBackMusic(std::string kName)
{
	
    kName = s_soundPath + kName;
    g_backGroundMusicID = experimental::AudioEngine::play2d(kName.c_str(), true);
    experimental::AudioEngine::setVolume(g_backGroundMusicID, getMusicVolume());
	
}
void Tools::stopallbgmusic()
{
	experimental::AudioEngine::stopAll();
}
void Tools::stopBackMusic()
{
    experimental::AudioEngine::stop(g_backGroundMusicID);
}
void Tools::pauseBackMusic()
{
    experimental::AudioEngine::pause(g_backGroundMusicID);
}
void Tools::resumeBackMusic()
{
	
    experimental::AudioEngine::setVolume(g_backGroundMusicID, getMusicVolume());
    experimental::AudioEngine::resume(g_backGroundMusicID);	
	
}
void Tools::setBackMusicVolume(float volume)
{
    saveMusicVolume(volume);
    experimental::AudioEngine::setVolume(g_backGroundMusicID, volume);	
}

int Tools::playEffect(std::string kName)
{
	
    int iEffectID = 0;
    kName = s_soundPath + kName;
    iEffectID = experimental::AudioEngine::play2d(kName.c_str());
    experimental::AudioEngine::setVolume(iEffectID, getEffectVolume());
    return iEffectID;
	
	return 0;//恢复时要删除
}

//0是男
int Tools::playCardByGender(int cardid , int iGender,int kindofnative)
{
     int value_card=cardid/16*10+cardid%16;
	 std::string tiaoortong;
	 if(value_card>=0&&value_card<=10)
	 {
		 tiaoortong="wan";
	 }
	 else if(value_card>=11&&value_card<=20)
	 {
		 tiaoortong="tiao";
	 }
	 else if(value_card>=21&&value_card<=30)
	 {
		 tiaoortong="tong";
	 }
	 int num_value=cardid%16;

	 std::string sex_;
	 if(iGender==1)
	 {
		 sex_="man";
	 }
	 else
	 {
		 sex_="woman";
	 }
	 std::string nativeorgenneral;
	 if(kindofnative==1)//本地化
	 {
		 nativeorgenneral="d";
	 }
	 else
	 {
		 nativeorgenneral="p";
	 }
	 String *s_kname=String::createWithFormat("%s%d_%s_%s.mp3",tiaoortong.c_str(),num_value,sex_.c_str(),nativeorgenneral.c_str());
	
    return playEffect(s_kname->getCString());
}

//0是男
int Tools::playOperateByGender(int operatecode, int iGender)
{
    string sOperate;
    if (operatecode==1)
    {
        sOperate = "peng";
    } 
    else if (operatecode==2||operatecode==3||operatecode==4)
    {
        sOperate = "minggang";
    } 
    else if (operatecode==5)
    {
        sOperate = "bugang";
    } 
    else if (operatecode==6)
    {
        sOperate = "angang";
    } 
    else if(operatecode==7)
    {
		sOperate="chongfengji";
    }
	else if(operatecode==8)
	{
		sOperate="dianpao";
	}
	else if(operatecode==9)
	{
		sOperate="hu";
	}
	else if(operatecode==10)
	{
		sOperate="hupai";
	}
	else if(operatecode==11)
	{
		sOperate="tianting";
	}
	else if(operatecode==12)
	{
		sOperate="zhengqi";
	}
	else if(operatecode==13)
	{
		sOperate="zimo";
	}
	else if(operatecode==14)
	{
		sOperate="zerenji";
	}
	else if(operatecode==20)
	{
		sOperate = "peng";
	}
	else if(operatecode==21)
	{
		sOperate = "gangkai";
	}
	else if(operatecode==22)
	{
		sOperate = "repao";
	}
	else if(operatecode==23)
	{
		sOperate = "qianggang";
	}
    string kName;
    if (iGender==1)
    {
        kName="man_";
    }
    else
    {
        kName ="woman_";
    }
	String *path=String::createWithFormat("%s%s.mp3",kName.c_str(),sOperate.c_str());
    return playEffect(path->getCString());
}
int Tools::playMsgByGender(int msg_tag,int gender)
{
	int x=msg_tag-100;
	std::string sex_;
	if(gender==1)
	{
		sex_="man";
	}
	else
	{
		sex_="woman";
	}
	String *path=String::createWithFormat("msg_%d_%s.mp3",x,sex_.c_str());
	return playEffect(path->getCString());
}
void Tools::MyWStrToUTF8(std::string& dest, const std::wstring& src)
{  
	dest.clear();  

	for (size_t i = 0; i < src.size(); i++){  
		wchar_t w = src[i];  
		if (w <= 0x7f)  
			dest.push_back((char)w);  
		else if (w <= 0x7ff)  
		{  
			dest.push_back(0xc0 | ((w >> 6)& 0x1f));  
			dest.push_back(0x80| (w & 0x3f));  
		}  
		else if (w <= 0xffff)  
		{  
			dest.push_back(0xe0 | ((w >> 12)& 0x0f));  
			dest.push_back(0x80| ((w >> 6) & 0x3f));  
			dest.push_back(0x80| (w & 0x3f));  
		}  
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)  
		{  
			dest.push_back(0xf0 | ((w >> 18)& 0x07)); // wchar_t 4-bytes situation  
			dest.push_back(0x80| ((w >> 12) & 0x3f));  
			dest.push_back(0x80| ((w >> 6) & 0x3f));  
			dest.push_back(0x80| (w & 0x3f));  
		}  
		else  
			dest.push_back('?');  
	}  
}  
std::string Tools::WStrToUTF8(const std::wstring& str) 
{  
	std::string result;  
	MyWStrToUTF8(result, str);  
	return result;
}
std::string Tools::StrToUTF8(const std::string &str)
{
	// string转wstring
	unsigned len = str.size() * 2;// 预留字节数
	setlocale(LC_CTYPE, "");     //必须调用此函数
	wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
	mbstowcs(p,str.c_str(),len);// 转换
	std::wstring wstr(p);
	delete[] p;// 释放申请的内存
	return WStrToUTF8(wstr); 
}
std::vector<int> Tools::getcurrentTime()
{
	std:;vector<int>arr_time;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
	 timeval now;  
	 tm* time;  
	gettimeofday(&now, NULL);  
	time = localtime(&now.tv_sec);  
	arr_time.push_back(time->tm_hour);
	arr_time.push_back(time->tm_min);
#endif
	return arr_time;
}