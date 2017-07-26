#include "Platform.h"
#include "cocos2d.h"
#if(CC_PLATFORM_IOS == CC_TARGET_PLATFORM)
//#include "iOSPlatform.h"
#endif
USING_NS_CC;
void Platform::Login()
{
#if( CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/AppActivity", "WxLogin","()V");
	if (isHave)
	{
		 methodInfo.env->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
	}
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_IOS)
	
#endif
}
string Platform::getVersion()
{
    std::string str="1.2";
#if( CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/AppActivity", "getVersion", "()Ljava/lang/String;");
    if (isHave)
    {
        jstring jstr;
        jstr = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID,methodInfo.methodID);
        str = JniHelper::jstring2string(jstr);
    }
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_IOS)
	//str = IOSPlatform::getVersion();
    str = "123";
#endif
    return str;

}

std::string  Platform::getPower()
{
    std::string str="";
#if( CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID)

    JniMethodInfo methodInfo; //用于获取函数体
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/AppActivity", "getPower", "()Ljava/lang/String;");

    if (isHave)
    {
        jstring jstr;
        jstr = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID,methodInfo.methodID);
        str = JniHelper::jstring2string(jstr);
    }
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_IOS)
//	float power = IOSPlatform::getPower();
//	str = StringUtils::format("%f",power);
    str = "123";
#endif
	
    return str;
}

