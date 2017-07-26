#pragma once

#include "controller/BaseCommand.h"

class TableCommand : public BaseCommand
{
public:
	~TableCommand();
	static TableCommand* getInstance();
	
	void onRecv(const int opcode,const char* buf,const int len) ; // 接收消息

	///加入桌子
	void requestJoinTable(const int tableId, const int seat_id);
	void responseJoinTable(const char* buf,const int len);

	///
	void requestplayerinfo(const int uid);
	void responseplayerinfo(const char* buf,const int len);
	//离开桌子
	void requestLeaveTable(const int leaveReason);
	void responseLeaveTable(const char* buf,const int len);
	//加入桌子广播
	void responseJoinTableBroadcast(const char* buf,const int len);
	//离开桌子广播
	void responseLeaveTableBroadcast(const char* buf,const int len); 
	///游戏开始广播
    void responseRoundStartBroadcast(const char* buf,const int len);
	//补花广播
	void responseBuHuaBroadcast(const char* buf,const int len);
	//出牌请求
	void requestOutCard(const int cardId);
	//出牌返回
	void responseOutCard(const char* buf,const int len);

	//出牌广播(只有收到这个消息才能代表出牌成功）
	void responseoutcardbroadcast(const char *buf,const int len);

	//系统单张发牌广播
	void responsesystendispathercardbroadcast(const char *buf,const int len);
	//操作询问广播
	void responseopreateaskbroadcast(const char *buf,const int len);

	//操作请求
	void requestoperate(int operatecode, int cardid);
	//操作相应
	void responseoperate(const char *buf,const int len);

	//操作全局响应广播(内容是哪个玩家进行了什么成功的操作 ***碰牌 吃牌 杠牌 成功)
	void responseoperatesuccessbroadcast(const char *buf, const int len);
	//明楼请求
	void requestminglouask();
	//明楼响应
	void responseminglouask(const char *buf,const int len);

	//明楼请求
	void requestminglou();
	//明楼结果广播
	void responsemingloubroadcast(const char *buf,const int len);
	//一局结束广播
	void responseonroundresultbroadcast(const char *buf,const int len);
	//ready请求
	void requestready();
	//ready响应
	void responseready(const char *buf,const int len);
	//ready广播
	void responsereadybroadcast(const char *buf,const int len);
	//重连广播
	void responsebreakback(const char *buf,const int len);



    //解散房间询问广播
    void responsedismissaskbroadcast(const char *buf,const int len);
	//解散房间同意或者拒绝请求
	void requestagreeornot(bool isagree);
    void responsepalyeragreornotbroadcast(const char *buf,const int len);
	void responsedissmisssuccessbroadcast(const char *buf,const int len);



	void responseyuyinbroadcast(const char *buf,const int len);

	void requestyuyin( char * yuyin,int size);


	void requestchat(int index);
	void requestcustomchat(std::string chat_content);

	void resquestresultdetail();

	void responsechatbroadcast(const char *buf,const int len);
	void responsecustomchatbroadcast(const char *buf,const int len);


	void responsebreakbroadcast(const char *buf,const int len);

	void responsegetruiltdetail(const char *buf,const int len);

	void responsegetotalresultbroadcast(const char *buf,const int len);

	void responsegetpkreslutbroadcast(const char *buf,const int len);


	void responsedingqueaskBroadcast(const char *buf,const int len);
	void responsedingqueAnser(const char *buf,const int len);
	void responsedingqueanserBroadcast(const char *buf,const int len);
	void requestdingque(int quedemen);
private:
	static TableCommand* m_tableCommand;
};

