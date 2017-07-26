#pragma  once
#include <string>
namespace JniFun
{
	void longinWX(const char* APP_ID,const char* AppSecret);
	void shareImageWX(const char* ImgPath,int nType);
	void shareTextWX(const char* kText,int nType);
	void shareUrlWX(const char* kUrl,const char* kTitle,const char* kDesc,int nType);

	void showWebView(const char* url );
	void versionUpdate(const char* url ,const char* desc, const int filesize, const int isUpdate);

	void startSoundRecord();
	void restartapp();
	const char* stopSoundRecord();

	void variable();
	void copyText(const char* copyTxt);
	float getPower();

	std::string getVersion();
} 

