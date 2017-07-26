#include "JniCallback.h"
#include "cocos2d.h"
#include "platform/MissionWeiXin.h"
#include "model/MjData.h"
#include "model/GamerData.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <Jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

using namespace cocos2d;

namespace JniFun
{
	extern "C" 
	{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

		JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_Native_WxLoginGetAccessToken (JNIEnv* env, jclass method, jstring param)
		{
			const char* data = env->GetStringUTFChars(param, 0);
			cocos2d::log("JinCallBack :%s",data);
			MissionWeiXin::getinstance()->Req_Access_token(data);
			env->ReleaseStringUTFChars(param, data);
		}

		JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_Native_WxLoginGetFailToken (JNIEnv* env, jclass method, jstring param)
		{
			const char* data = env->GetStringUTFChars(param, 0);
			cocos2d::log("JinCallBack :%s",data);
			MissionWeiXin::getinstance()->Req_Fail_token(data);
			env->ReleaseStringUTFChars(param, data);
		}
		JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_Native_setNetworkState (JNIEnv* env, jclass method, jint param)
		{
			CCLOG("%parm---------%d",param);
			if(MjData::getInstance()->getstatus_my()==1)//游戏中开启
			{
					//检查网络是否变化
					//MissionWeiXin::getinstance()->checknetwork(param);
					CCLOG("parm___1%d",param);
			}
		}
		JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_Native_setBatteryState (JNIEnv* env, jclass method, jint param)
		{
			CCLOG("%parm---------%d",param);
			
				//检查网络是否变化
				MissionWeiXin::getinstance()->setBatteryRate(param);
			
		}
#endif
	}

} 