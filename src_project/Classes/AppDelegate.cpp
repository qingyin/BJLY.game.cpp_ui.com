#include "AppDelegate.h"
#include "view/Scene/SceneLoading.h"
#include "AudioEngine.h"
#include "controller/MainCommand.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "bugly/CrashReport.h"     
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CrashReport.h"
#endif

AppDelegate::AppDelegate() {
	CC_SAFE_RETAIN(MainCommand::getInstance());

}

AppDelegate::~AppDelegate() 
{
	CC_SAFE_RELEASE(MainCommand::getInstance());
	

}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
/**
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
    Image::setPVRImagesHavePremultipliedAlpha(true);
    // Í¼¼¯½âÃÜ   95104826951048269510482695104826
    ZipUtils::setPvrEncryptionKey(0x95104826, 0x95104826, 0x95104826, 0x95104826);
**/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CrashReport::initCrashReport("d93edd5f72", true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	CrashReport::initCrashReport("3b8059e943", true);
#endif

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("MaJiang", Rect(0, 0, 1280.0f, 720.0f));
#else
        glview = GLViewImpl::create("MaJiang");
#endif
        director->setOpenGLView(glview);

		glview->setFrameSize(1280.0f,720.0f);
    }

    // turn on display FPS

	int  version=8;
	int version_now=UserDefault::getInstance()->getIntegerForKey("verion_now");
	if(version_now!=0)
	{
		if(version!=version_now)
		{
			cocos2d::UserDefault::getInstance()->setStringForKey("accesstoken","");
			cocos2d::UserDefault::getInstance()->setStringForKey("openid","");
			UserDefault::getInstance()->setIntegerForKey("verion_now",version);
		}
	}
	else
	{
		UserDefault::getInstance()->setIntegerForKey("verion_now",version);
	}

   	glview->setDesignResolutionSize(1280.0f,720.0f,ResolutionPolicy::EXACT_FIT);
    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f/ 30.0f);
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getWritablePath());
	FileUtils::getInstance()->addSearchPath("res");
    register_all_packages();	

	
    auto loadingScene = SceneLoading::createScene();
	// run
    director->runWithScene(loadingScene);
	

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
	CCLOG("jinruhoutai");
    // if you use SimpleAudioEngine, it must be pause
	experimental::AudioEngine::pauseAll();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	CCLOG("jinruqiantai");
	experimental::AudioEngine::resumeAll();
    
}
