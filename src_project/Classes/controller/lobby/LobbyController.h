#pragma once
#include "net/HttpManager.h"
#include "json/rapidjson.h"
#include "json/document.h"

#include "adapter/LobbyAdapter.h"

class LobbyController : public HttpManagerDelegate
{
public:
	static LobbyController* getInstance();
	virtual ~LobbyController(void);
	virtual void onHttpManagerRequestCompleted(HttpClient* sender,HttpResponse* response);

	void bindPromoterID();
	void bindInvitationCode();
	void bindUser();

	void getPromoterInfo(string promoterID);
	void getInviterInfo(string inviteCode);

	void getMsgList();

	void getAllWXCode();
	void getActivityPicList();

	void getActivityInfo(bool isShowActivityPic);
	
	void loadImg(string url,string tag);
	void getShengLv(int uid,bool isHeadClicked = false);
	void getHistoryRecord();

	void testReadTimeout();

	void setLayerLoadingVisible(bool isVisible);
	void setLayerNetworkErrorVisible(bool isVisible);
	void weixinLogin();
	void versionVerify();

private:
	void sendRequest(string tag,rapidjson::Document& doc);
	void onHttpRequestCompletedDataHandle(string data,string tag);

	void saveImg(string data,string tag);

	LobbyController();
	static LobbyController* mLobbyController;
	HttpManager* mHttpManager;


	string inputUserIdCode;
	string userId;
	enum BindType{
		PROMOTER_ID,
		INVITATION_CODE
	};
	BindType mBindType;
	int loadedImgNum;
	bool isShowActivityPic;
	bool isHeadClicked;
};

