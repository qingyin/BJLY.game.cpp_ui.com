#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

#define USE_WIN32_CONSOLE 

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
//#ifdef USE_WIN32_CONSOLE  
//    AllocConsole();  
//    freopen("CONIN$","r",stdin);  
//    freopen("CONOUT$","w",stdout);  
//    freopen("CONOUT$","w",stderr); 
//#endif

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();

//#ifdef USE_WIN32_CONSOLE  
//    FreeConsole();  
//#endif
}
