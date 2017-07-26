#include "JniFun.h"
#include "cocos2d.h"


#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <Jni.h>
#include "platform/android/jni/JniHelper.h"
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "IosHelper.h"
#endif

#define JAVA_CLASSNAME  "org/cocos2dx/cpp/Native"
#define JAVA_CLASS_APPACTIVITY  "org/cocos2dx/cpp/AppActivity"
using namespace cocos2d;
using namespace std;
namespace JniFun
{

	void longinWX(const char* APP_ID,const char* AppSecret)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME,"LoginWX","(Ljava/lang/String;Ljava/lang/String;)V");
		if (isHave)
		{
			jstring jAPP_ID = minfo.env->NewStringUTF(APP_ID);
			jstring jAppSecret = minfo.env->NewStringUTF(AppSecret);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jAPP_ID,jAppSecret);

			minfo.env->DeleteLocalRef(jAPP_ID);
			minfo.env->DeleteLocalRef(jAppSecret);
			minfo.env->DeleteLocalRef(minfo.classID); 
			cocos2d::log("JniFun call LoginWX over!");
		}
		else
		{
			cocos2d::log("JniFun call LoginWX error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        WeiChatLogin::getInstance()->sendAuthReq();
#endif
	}

	void shareImageWX(const char* ImgPath,int nType)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME,"ShareImageWX","(Ljava/lang/String;I)V");
		if (isHave)
		{
			jstring jImgPath = minfo.env->NewStringUTF(ImgPath);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jImgPath,nType);
			cocos2d::log("JniFun call ShareImageWX over!");

			minfo.env->DeleteLocalRef(jImgPath);
			minfo.env->DeleteLocalRef(minfo.classID); 
		}
		else
		{
			cocos2d::log("JniFun call ShareImageWX error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		if (nType == 0)
		{
			WeiChatLogin::shareWithWeixinFriendImg("",ImgPath);
		}
		else
		{
			WeiChatLogin::shareWithWeixinCircleImg("",ImgPath);
		}
#endif
	}

	void shareTextWX(const char* kText,int nType)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
			JniMethodInfo minfo;
			bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME,"ShareTextWX","(Ljava/lang/String;I)V");
			if (isHave)
			{
				jstring jkText = minfo.env->NewStringUTF(kText);
				minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jkText,nType);
				cocos2d::log("JniFun call ShareTextWX over!");

				minfo.env->DeleteLocalRef(jkText);
				minfo.env->DeleteLocalRef(minfo.classID); 
			}
			else
			{
				cocos2d::log("JniFun call ShareTextWX error!");
			}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
			if (nType == 0)
			{
                //WeiChatLogin::shareWithWeixinFriendTxt(kText,"www.baidu.com");
                WeiChatLogin::shareWithWeixinFriendTxt("","",kText);
			}
			else
			{
                //WeiChatLogin::shareWithWeixinCircleTxt(kText,"www.baidu.com");
                WeiChatLogin::shareWithWeixinFriendTxt("","",kText);
			}
#endif
	}

	void shareUrlWX(const char* kUrl,const char* kTitle,const char* kDesc,int nType)
	{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME,"ShareUrlWX","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V");
		if (isHave)
		{
			jstring jkUrlt = minfo.env->NewStringUTF(kUrl);
			jstring jkTitle = minfo.env->NewStringUTF(kTitle);
			jstring jkDesc = minfo.env->NewStringUTF(kDesc);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jkUrlt,jkTitle,jkDesc,nType);
			cocos2d::log("JniFun call ShareUrlWX over!");

			minfo.env->DeleteLocalRef(jkUrlt);
			minfo.env->DeleteLocalRef(jkTitle);
			minfo.env->DeleteLocalRef(jkDesc);
			minfo.env->DeleteLocalRef(minfo.classID); 
		}
		else
		{
			cocos2d::log("JniFun call ShareUrlWX error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		if (nType == 0)
		{
            //WeiChatLogin::shareWithWeixinFriendTxt(kTitle,kUrl);
            WeiChatLogin::shareWithWeixinFriendTxt(kUrl,kTitle,kDesc);
		}
		else
		{
            //WeiChatLogin::shareWithWeixinCircleTxt(kTitle,kUrl);
            WeiChatLogin::shareWithWeixinCircleTxt(kUrl,kTitle,kDesc);
		}
#endif
	}

	void showWebView(const char* url )
	{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME,"showWebView","(Ljava/lang/String;)V");
		if (isHave)
		{
			jstring jurl = minfo.env->NewStringUTF(url);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jurl);
			cocos2d::log("JniFun call showWebView over!");

			minfo.env->DeleteLocalRef(jurl);
			minfo.env->DeleteLocalRef(minfo.classID); 
		}
		else
		{
			cocos2d::log("JniFun call showWebView error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		WeiChatLogin::startBrowserJni(url);
#endif
	}

	// 版本更新
	void versionUpdate(const char* url ,const char* desc, const int filesize, const int isUpdate)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;  
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME, "versionUpdate", "(Ljava/lang/String;Ljava/lang/String;II)V");
		if (isHave)  
		{  
			jstring jFileName = minfo.env->NewStringUTF(url);
			jstring jDes = minfo.env->NewStringUTF(desc);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jFileName,jDes, filesize, isUpdate); 

			cocos2d::log("JniFun call versionUpdate over!");

			minfo.env->DeleteLocalRef(jFileName);
			minfo.env->DeleteLocalRef(jDes);
			minfo.env->DeleteLocalRef(minfo.classID);  
		}  
		else
		{
			cocos2d::log("JniFun call versionUpdate error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		WeiChatLogin::startBrowserJni(url);
#endif
	}

	static std::string kRecordFileName = "";
	void startSoundRecord()
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;  
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME, "startSoundRecord", "()V");
		if (isHave)  
		{  
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID); 
			cocos2d::log("JniFun call startSoundRecord over!");

			minfo.env->DeleteLocalRef(minfo.classID);  
		}  
		else
		{
			cocos2d::log("JniFun call startSoundRecord error!");
		}
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		kRecordFileName = cocos2d::FileUtils::getInstance()->getWritablePath()+"SoundRecord.wav";
		WeiChatLogin::beginRecord(kRecordFileName.c_str());
#endif
	}
	const char* stopSoundRecord()
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		std::string str;
		JniMethodInfo minfo;  
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASSNAME, "stopSoundRecord", "()Ljava/lang/String;");
		if (isHave)  
		{  
			jstring jFileName = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID); 
			const char *newStr = minfo.env->GetStringUTFChars(jFileName, 0);
			str = newStr;
			cocos2d::log("JniFun call stopSoundRecord over :");
			cocos2d::log("%s",str.c_str());
			minfo.env->ReleaseStringUTFChars(jFileName, newStr);
			minfo.env->DeleteLocalRef(minfo.classID); 
		}  
		else
		{
			cocos2d::log("JniFun call stopSoundRecord error!");
		}
		return str.c_str();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		WeiChatLogin::endRecord();
		return kRecordFileName.c_str();
#endif
		return "";
	}

	void variable()
	{
	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	
		JniMethodInfo minfo;  
		bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity", "Vibrate", "()V");
		if (isHave)  
		{  
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID); 
			cocos2d::log("JniFun call bibrate over!");
			minfo.env->DeleteLocalRef(minfo.classID);  
		}  
		else
		{
			cocos2d::log("JniFun call vibrate error!");
		}
	
	#endif
	}
	void restartapp()
	{
	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

		JniMethodInfo minfo;  
		bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity", "restartApp", "()V");
		if (isHave)  
		{  
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID); 
			minfo.env->DeleteLocalRef(minfo.classID);  
		}  
	#endif
	}

	void copyText(const char* copyTxt)
	{
	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;  
		bool isHave = JniHelper::getStaticMethodInfo(minfo,JAVA_CLASS_APPACTIVITY, "CopyText", "(Ljava/lang/String;)Z");
		if (isHave)  
		{
			jstring jCopyTxt = minfo.env->NewStringUTF(copyTxt);
			minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID,jCopyTxt); 
			minfo.env->DeleteLocalRef(jCopyTxt);
			minfo.env->DeleteLocalRef(minfo.classID);  
		}  
	#endif
	#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		WeiChatLogin::copyText(copyTxt);
	#endif
	}	

	float getPower()
	{
		float power = 0.5 * 100;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		power = WeiChatLogin::getPower()*100;
#endif
		return power;
	}
	string getVersion()
	{
		std::string str="1.0";
#if( CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/AppActivity", "getAppVersion", "()Ljava/lang/String;");
		if (isHave)
		{
			jstring jstr;
			jstr = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID,methodInfo.methodID);
			str = JniHelper::jstring2string(jstr);
		}
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_IOS)
		str = WeiChatLogin::getVersion();
#endif
		return str;
	}

}