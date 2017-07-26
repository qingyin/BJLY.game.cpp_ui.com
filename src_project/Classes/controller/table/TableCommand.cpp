
#include "TableCommand.h"
#include "model/GamerDataDeal.h"
#include "model/MjData.h"
#include "Sound/ArmFun.h"
#include "SimpleAudioEngine.h"
#include "tool/Tiperror.h"
#include "tool/Tools.h"
#include "controller/lobby/LobbyController.h"
#include "util/GameConst.h"
TableCommand* TableCommand::m_tableCommand = nullptr;
TableCommand* TableCommand::getInstance()
{
    if (m_tableCommand == nullptr){
        m_tableCommand = new TableCommand();
    }
    return m_tableCommand;
}
TableCommand::~TableCommand()
{
    CC_SAFE_DELETE(m_tableCommand);
}
// 接收消息
void TableCommand::onRecv(const int opcode,const char* buf,const int len) 
{
    switch (opcode)
    {
    case Opcode::MSG_JOIN_TABLE:  //加入桌子
        responseJoinTable(buf,len);
        break;
    case Opcode::MSG_LEAVE_TABLE://离开桌子
        responseLeaveTable(buf,len);
        break;
    case Opcode::MSG_JOIN_TABLE_BROADCAST: //加入桌子广播
        responseJoinTableBroadcast(buf,len);
        break;
    case Opcode::MSG_LEAVE_TABLE_BROADCAST://离开桌子广播
        responseLeaveTableBroadcast(buf,len);
        break;
    case Opcode::MSG_ROUND_START_BROADCAST://一局开始广播
        responseRoundStartBroadcast(buf,len);
        break;
  
    case Opcode::MSG_OUT://出牌
        responseOutCard(buf,len);
        break;
    case Opcode::MSG_OUT_BROADCAST:
        responseoutcardbroadcast(buf,len);
        break;
    case Opcode::MSG_DISPATCH_BROADCAST:
        responsesystendispathercardbroadcast(buf,len);
        break;
    case  Opcode::MSG_OPERATE_ASK_BROADCAST :
        responseopreateaskbroadcast(buf,len);
        break;
    case Opcode::MSG_OPERATE:
        //log("opreate success!");
        responseoperate(buf,len);
        break;
    case Opcode::MSG_OPERATE_RESULT_BROADCAST:
        responseoperatesuccessbroadcast(buf,len);
        break;
    case Opcode::MSG_MINGLOU_BROADCAST:
        responsemingloubroadcast(buf,len);
        break;
    case Opcode::MSG_ROUND_RESULT_BROADCAST:
        responseonroundresultbroadcast(buf,len);
        break;
    case Opcode::MSG_MINGLOU_ASK:
        responseminglouask(buf,len);
        break;
    case Opcode::MSG_READY_BROADCAST:
        responsereadybroadcast(buf,len);
        break;
    case Opcode::MSG_READY:
       responseready(buf,len); 
        break;
    case Opcode::MSG_BREAK_BACK_BROADCAST:
        responsebreakback(buf,len);
        break;
    case  Opcode::MSG_VOICE_TALK_BROADCAST:
        responseyuyinbroadcast(buf,len);
        break;
	case  Opcode::MSG_CHAT_BROADCAST:
		responsechatbroadcast(buf,len);
		break;
	case  Opcode::MSG_CHAT_CUSTOM_BROADCAST:
		responsecustomchatbroadcast(buf,len);
		break;
	case Opcode::MSG_DISMISS_ASK_BROADCAST:
		 responsedismissaskbroadcast(buf,len);
		break;
	case Opcode::MSG_DISMISS_ANSWER:

		break;
	case Opcode::MSG_DISMISS_ANSWER_BROADCAST:
		responsepalyeragreornotbroadcast(buf,len);
		break;
	case Opcode::MSG_DISMISS_BROADCAST:
		responsedissmisssuccessbroadcast(buf,len);
		break;
	case Opcode::MSG_BREAK_BROADCAST:
		responsebreakbroadcast(buf,len);
		break;
	case Opcode::MSG_GET_JU_CNT:
		LobbyController::getInstance()->setLayerLoadingVisible(false);
		responseplayerinfo(buf,len);
		break;
	case  Opcode::MSG_GET_RESULT_DETAIL:
		responsegetruiltdetail(buf,len);
		break;
	case  Opcode::MSG_RESULT_TOTAL:
		responsegetotalresultbroadcast(buf,len);
		break;
	case Opcode::MSG_RESULT_PK:
		responsegetpkreslutbroadcast(buf,len);
		break;
	case Opcode::MSG_DINGQUE_ASK_BROADCAST:
		responsedingqueaskBroadcast(buf,len);
		break;
	case Opcode::MSG_DINGQUE_ANSWER:
		responsedingqueAnser(buf,len);
		break;
	case Opcode::MSG_DINGQUE_ANSWER_BROADCAST:
		responsedingqueanserBroadcast(buf,len);
		break;
    default:
        break;
    }	
}
void TableCommand::responsedingqueaskBroadcast(const char *buf,const int len)
{
	GS2C_AskDingQueBroadcast pk_res;
	pk_res.ParseFromArray(buf,len);
	int error=pk_res.errorcode();
	if(error==0)
	{
		SEND_CUSTOM_MSG("dingqueaskbroadcast",&pk_res);
	}
}
void TableCommand::requestdingque(int quedemen)
{
    pb::C2GS_DingQue resultdetail;
	string buf;
	resultdetail.set_quemen(quedemen);
	resultdetail.SerializeToString(&buf);
	SEND_BUF_MSG(Opcode::MSG_DINGQUE_ANSWER,buf);
}
void TableCommand::responsedingqueAnser(const char *buf,const int len)
{
	GS2C_DingQue pk_res;
	pk_res.ParseFromArray(buf,len);
	int error=pk_res.errorcode();
	if(error==0)
	{
		SEND_CUSTOM_MSG("mydingquesuccess");
	}
}
void TableCommand::responsedingqueanserBroadcast(const char *buf,const int len)
{
	GS2C_DingQueBroadcast pk_res;
	pk_res.ParseFromArray(buf,len);
	int error=pk_res.errorcode();
	if(error==0)
	{
		SEND_CUSTOM_MSG("userdingquebroadcast",&pk_res);
	}
}
void TableCommand::responsegetpkreslutbroadcast(const char *buf,const int len)
{
	GS2C_ResultPKBroadcast pk_res;
	pk_res.ParseFromArray(buf,len);
	int error=pk_res.errorcode();
	if(error==0)
	{
		SEND_CUSTOM_MSG("responseresultpk",&pk_res);
	}
}
void TableCommand::responsegetotalresultbroadcast(const char *buf,const int len)
{
	GS2C_ResultTotalBroadcast total_result;
	total_result.ParseFromArray(buf,len);
	int ertr=total_result.errorcode();
	if(ertr==0)
	{
		SEND_CUSTOM_MSG("responsegetresulttotal",&total_result); //
	}

}
void TableCommand::resquestresultdetail()
{
	/*
    pb::C2GS_GetResultDetail resultdetail;
	string buf;
	resultdetail.SerializeToString(&buf);
	SEND_BUF_MSG(Opcode::MSG_GET_RESULT_DETAIL,buf);
	*/
}
void TableCommand::responsegetruiltdetail(const char *buf ,const int len)
{
	/*
	pb::GS2C_GetResultDetail resultdetail;
	resultdetail.ParseFromArray(buf,len);
	int ertr=resultdetail.errorcode();
	if(ertr==0)
	{
		SEND_CUSTOM_MSG("responsegetresultdetail",&resultdetail); //
	}
	*/
}
void TableCommand::responsebreakbroadcast(const char *buf,const int len)
{
	pb::GS2C_BreakBroadcast  joinTableBroadcast;
	joinTableBroadcast.ParseFromArray(buf,len);

	int wee=joinTableBroadcast.errorcode();
	if(wee==0)
	{
		SEND_CUSTOM_MSG("responsebreakbroadcast",&joinTableBroadcast); //加入桌子
	}
}
void TableCommand::responsebreakback(const char *buf,const int len)
{
    pb::GS2C_BreakBackBroadcast joinTableBroadcast;
    joinTableBroadcast.ParseFromArray(buf,len);

    int wee=joinTableBroadcast.errorcode();
    if(wee==0)
    {
        SEND_CUSTOM_MSG("responsebreakbackbroadcast",&joinTableBroadcast); //加入桌子
    }


}
void TableCommand::requestplayerinfo(const int uid)
{
	if(MjData::getInstance()->getisinapple()==0)
	{
		LobbyController::getInstance()->setLayerLoadingVisible(true);
		pb::C2GS_GetJuCnt  joinTable;
		joinTable.set_uid(uid);
		string buf;
		joinTable.SerializeToString(&buf);
		SEND_BUF_MSG(Opcode::MSG_GET_JU_CNT,buf);
	}
	
}
void TableCommand::responseplayerinfo(const char* buf,const int len)
{
	pb::GS2C_GetJuCnt joinTableBroadcast;
	joinTableBroadcast.ParseFromArray(buf,len);

	int wee=joinTableBroadcast.errorcode();
	if(wee==0)
	{
		SEND_CUSTOM_MSG("responsegetplayerinfo",&joinTableBroadcast); //加入桌子
	}
}
void TableCommand::requestready()
{
    pb::C2GS_Ready  joinTable;
    string buf;
    joinTable.SerializeToString(&buf);
    SEND_BUF_MSG(Opcode::MSG_READY,buf);
}
void TableCommand::requestagreeornot(bool  isagree)
{
	pb::C2GS_DismissAnswer  joinTable;
	int is;
	if(isagree==true)
	{
		is=1;
	}
	else if(isagree==false)
	{
		is=0;
	}
	joinTable.set_is_agree(is);
	string buf;
	joinTable.SerializeToString(&buf);
	SEND_BUF_MSG(Opcode::MSG_DISMISS_ANSWER,buf);
}
void TableCommand::responsepalyeragreornotbroadcast(const char *buf,const int len)
{
	GS2C_DismissAnswerBroadcast leaveTable;
	leaveTable.ParseFromArray(buf,len);
	int error  = leaveTable.errorcode();
	if(error==0)
	{
		SEND_CUSTOM_MSG("responseplayergareeornotbroadcast",&leaveTable);
	}
}
void TableCommand::responsedissmisssuccessbroadcast(const char *buf,const int len)
{
	GS2C_DismissBroadcast  leaveTable;
	leaveTable.ParseFromArray(buf,len);
	int error  = leaveTable.errorcode();
	
	if(error==0)
	{
		int result=leaveTable.is_dismiss();
		if(result==0)
		{
			//解散不成功 发通知去掉解散房间界面
			SEND_CUSTOM_MSG("failddissmiss",&leaveTable);
		}
		else if(result==1)
		{
			SEND_CUSTOM_MSG("responsedismisssuccessbroadcast",&leaveTable);
		}
		
	}
}
void TableCommand::responsereadybroadcast(const char *buf,const int len)
{
    
    GS2C_ReadyBroadcast leaveTable;
    leaveTable.ParseFromArray(buf,len);
    int error  = leaveTable.errorcode();
    if (error == 0)
    {
	  int uid=leaveTable.uid();
	  GamerData *g=GamerDataDeal::getInstance()->getGamerData(uid);
	  g->setStatus(6);
	  if(uid==GamerData::getInstance()->getUId())
	  {
		  GamerData::getInstance()->setStatus(6);
	  }
      SEND_CUSTOM_MSG("responsereadybroadcast",&leaveTable);
    }
}

void TableCommand::responseready(const char *buf,const int len)
{
    //自己ready的时候，状态设为6,中间暂停状态，这个时候是不能退出的，退出算断线
	GS2C_Ready ready_;
	ready_.ParseFromArray(buf,len);
	int error=ready_.errorcode();
	if(error==0)
	{
		 SEND_CUSTOM_MSG("responseready",&ready_);
	}
   
}
void TableCommand::responseyuyinbroadcast(const char *buf,const int len)
{
    GS2C_VoiceTalkBroadcast leaveTable;
    leaveTable.ParseFromArray(buf,len);
    int error  = leaveTable.errorcode();
    if (error == 0)
    {
        int uid=leaveTable.uid();
        std::string yuyin=leaveTable.voice_data();
        static int iIdex = 0;
        iIdex++;
        std::string kFileHead = (String::createWithFormat("%s%s%d",FileUtils::getInstance()->getWritablePath().c_str(),"record",iIdex))->getCString();
        std::string kFile=kFileHead+".arm";
        log("kFile: %s", kFile.c_str());
        FILE *fp = fopen(kFile.c_str(), "wb");
        fseek(fp,0,SEEK_SET);
        fwrite(&(yuyin[0]),sizeof(unsigned char),yuyin.size(),fp);
        log("yuyin_size%d",yuyin.size());
        fclose(fp);
        std::string kDestFile=kFileHead+".wav";
        ArmFun::ArmToWav(kFile.c_str(),kDestFile.c_str());
        int viewid=GetViewID(GamerData::getInstance()->getSeatId(),GamerDataDeal::getInstance()->getGamerData(uid)->getSeatId());
        String *wav_path=String::createWithFormat("path_wav_%d",viewid);
        UserDefault::getInstance()->setStringForKey(wav_path->getCString(),kDestFile.c_str());
        SEND_CUSTOM_MSG("responseplayeffect",&viewid);
    }
}
//解散房间询问广播
void TableCommand::responsedismissaskbroadcast(const char *buf,const int len)
{

    GS2C_DismissAskBroadcast leaveTable;
    leaveTable.ParseFromArray(buf,len);
    int error  = leaveTable.errorcode();
    if (error == 0)
    {
        SEND_CUSTOM_MSG("responsedismissask",&leaveTable);
    }

}

void TableCommand::requestoperate(int operatecode, int cardid)
{
    pb::C2GS_Operate  joinTable;
    joinTable.set_operate_code(operatecode);
   joinTable.set_operate_cardid(cardid);
    string buf;
    joinTable.SerializeToString(&buf);
    SEND_BUF_MSG(Opcode::MSG_OPERATE,buf);
}
void TableCommand::requestyuyin(char * yuyin,int size)
{
    if(size>=150&&size<=6000)
    {
        pb::C2GS_VoiceTalk  joinTable;
        joinTable.set_voice_data(yuyin,size);
        string buf;
        joinTable.SerializeToString(&buf);
        SEND_BUF_MSG(Opcode::MSG_VOICE_TALK,buf);
    }
	else
	{
		UserDefault::getInstance()->setBoolForKey("isplayluyin",false);
	}
}
void TableCommand::requestminglouask()
{
    pb::C2GS_MinglouAsk joinTable;

    string buf;
    joinTable.SerializeToString(&buf);
    SEND_BUF_MSG(Opcode::MSG_MINGLOU_ASK,buf);
}
void TableCommand::responseminglouask(const char *buf,const int len)
{
    GS2C_MinglouAsk leaveTable;
    leaveTable.ParseFromArray(buf,len);
    int error  = leaveTable.errorcode();
    if (error == 0)
    {
        SEND_CUSTOM_MSG("responseminglouask",&leaveTable);
    }
}
void TableCommand::requestminglou()
{
    pb::C2GS_Minglou  joinTable;

    string buf;
    joinTable.SerializeToString(&buf);
    SEND_BUF_MSG(Opcode::MSG_MINGLOU,buf);
}
//加入桌子
void  TableCommand::requestJoinTable(const int tableId, const int seat_id) 
{
    pb::C2GS_JoinTable joinTable;
    joinTable.set_table_id(tableId);
    joinTable.set_seat_id(seat_id);
    string buf;
    joinTable.SerializeToString(&buf);
    SEND_BUF_MSG(Opcode::MSG_JOIN_TABLE,buf);
}
void  TableCommand::responseJoinTable(const char* buf,const int len)
{
	bool b = false;
	SEND_CUSTOM_MSG(CustomEvent::key_set_visible_loading_layer,&b);

    bool isReconnect = false; ///是否重连
    pb::GS2C_JoinTable joinTable;
    joinTable.ParseFromArray(buf,len);
    int error = joinTable.errorcode();
    if(error != 0)
	{
		//SEND_CUSTOM_MSG("gameMainJointableFailed");
		return;
	}

	SEND_CUSTOM_MSG(CustomEvent::key_show_game_main);
	SEND_CUSTOM_MSG("gameMainBeginHeart");
    GamerDataDeal::getInstance()->removeallGamerData();
    google::protobuf::RepeatedPtrField< ::pb::UsrInfo > usr_info_list = joinTable.usr_info_list();
    int banker=joinTable.banker_uid();
    MjData::getInstance()->setbanker(banker);
    int size = joinTable.usr_info_list_size();
    int uids[4];


    for (int i = 0; i <size;i++)
    {
        UsrInfo userinfo = usr_info_list.Get(i);	
        GamerData* pGamerData = new GamerData();
        pGamerData->setUId(userinfo.uid());	 
        pGamerData->setNick(userinfo.weichat_nick());   //微信昵称
        pGamerData->setHeadUrl(userinfo.weichat_face_address()); //头像地址
        pGamerData->setRoomCard(userinfo.big_gold()); //房卡
        pGamerData->setGold(userinfo.gold()); //用户金币
        pGamerData->setSex(userinfo.sex()); //用户金币
        pGamerData->setUserip(userinfo.ip());
        pGamerData->setStatus(userinfo.status());   //0自由状态，1ready, 2正在打牌，3断线，4房主退出但未解散房间
		
			 pGamerData->setSeatId(userinfo.seatid());//椅子   (站起的是255)
		
       
        uids[i] = userinfo.uid();
		
        //当前玩家
        if(userinfo.uid() == GamerData::getInstance()->getUId())
        {
            //if(GamerData::getInstance()->getStatus() == 3 && userinfo.status()==3)
            //{
            //    const string  shengyuStr = Tools::getChineseByKey("InGame");
            //    Director::getInstance()->getRunningScene()->addChild(Tiplayerr::create(shengyuStr), 10);
            //    return;
            //}
            //else
            {
                //断线重连判断
                if(GamerData::getInstance()->getStatus() == 3 && userinfo.status()!=1 && userinfo.status()!=4)
                {
                    isReconnect = true;
                }else 
				{
                    isReconnect = false;
                }
                GamerData::getInstance()->setUId(userinfo.uid());
                GamerData::getInstance()->setNick(userinfo.weichat_nick());   //微信昵称
                GamerData::getInstance()->setHeadUrl(userinfo.weichat_face_address()); //头像地址
                GamerData::getInstance()->setRoomCard(userinfo.big_gold()); //房卡
                GamerData::getInstance()->setGold(userinfo.gold()); //用户金币
                GamerData::getInstance()->setSex(userinfo.sex()); //用户金币
                GamerData::getInstance()->setUserip(userinfo.ip());
                GamerData::getInstance()->setStatus(userinfo.status());   //0自由状态，1ready, 2正在打牌，3断线，4房主退出但未解散房间
				
				GamerData::getInstance()->setSeatId(userinfo.seatid());//椅子   (站起的是255)
				GamerData::getInstance()->setquedemen(0);
				
            }
        }

        GamerDataDeal::getInstance()->addGamerData(userinfo.uid(),pGamerData); 

        if(userinfo.seatid() != 255)
        {
            SEND_CUSTOM_MSG("playerjointable",pGamerData);  //加入桌子
        }
    }

    int seatId = GamerData::getInstance()->getSeatId();
    if(isReconnect)
    {
        SEND_CUSTOM_MSG("playerreconnect",&joinTable); 
    }
}
//离开桌子
void TableCommand::requestLeaveTable(const int leaveReason)
{
    C2GS_LeaveTable leaveTable;
    leaveTable.set_leave_reason(leaveReason); /// (0正常退出、1解散桌子)
    string buf;
    leaveTable.SerializeToString(&buf);
    SEND_BUF_MSG(Opcode::MSG_LEAVE_TABLE,buf);
}
void TableCommand::responseLeaveTable(const char* buf,const int len)
{
    GS2C_LeaveTable leaveTable;
    leaveTable.ParseFromArray(buf,len);
    int error  = leaveTable.errorcode();
    int reason = leaveTable.leave_reason();
    int is_banker_no_dismiss = leaveTable.is_banker_no_dismiss();
    if (error == 0)
    {
        if(GamerData::getInstance()->getStatus()<2)//只有未正式开始打牌时，才能推出，其他算断线
        {
            MjData::getInstance()->setisingame(is_banker_no_dismiss);
            if(reason==1)
            {
                    GamerData::getInstance()->setStatus(0);
                    SEND_CUSTOM_MSG("gamenotbegindismissnodeduct");
            }
            else
            {
                if(is_banker_no_dismiss==1)
                {
                    GamerData::getInstance()->setStatus(4);//房主未解散退出
                }
                else
                {
                    GamerData::getInstance()->setStatus(0);//房主未解散退出
                }
                SEND_CUSTOM_MSG("gamemainexit");
            }
        }
        else
        {
            GamerData::getInstance()->setStatus(3);//断线
        }
    }
}
//加入桌子广播
void TableCommand::responseJoinTableBroadcast(const char* buf,const int len)
{
    pb::GS2C_JoinTableBroadcast joinTableBroadcast;
    joinTableBroadcast.ParseFromArray(buf,len);
    UsrInfo userinfo = joinTableBroadcast.usr_info();
    GamerData* pGamerData = new GamerData();
    pGamerData->setUId(userinfo.uid());
    pGamerData->setNick(userinfo.weichat_nick());   //微信昵称
    pGamerData->setHeadUrl(userinfo.weichat_face_address()); //头像地址
    pGamerData->setRoomCard(userinfo.big_gold()); //房卡
    pGamerData->setGold(userinfo.gold()); //用户金币
    pGamerData->setUserip(userinfo.ip());
    pGamerData->setStatus(userinfo.status());   //0自由状态，1ready, 2正在打牌，3断线，4房主退出但未解散房间
	
		pGamerData->setSeatId(userinfo.seatid());//椅子   (站起的是255)
	
	
    
	pGamerData->setSex(userinfo.sex());
    GamerDataDeal::getInstance()->addGamerData(userinfo.uid(),pGamerData);
    if(userinfo.seatid() != 255)
    {
        SEND_CUSTOM_MSG("playerjointable",pGamerData); //加入桌子
    }
}
//离开桌子广播
void TableCommand::responseLeaveTableBroadcast(const char* buf,const int len)
{
    GS2C_LeaveTableBroadcast leaveTableBroadcast;
    leaveTableBroadcast.ParseFromArray(buf,len);
    if(leaveTableBroadcast.errorcode() == 0)
    {
        int uid = leaveTableBroadcast.uid();
        GamerData* pGamerData = GamerDataDeal::getInstance()->getGamerData(uid); 
        if(pGamerData == NULL) return;
        pGamerData->setStatus(0);
        if (uid == GamerData::getInstance()->getUId())
        {
            GamerData::getInstance()->setStatus(0);
        }
        if(leaveTableBroadcast.leave_reason() == 0)
        {//正常退出
            SEND_CUSTOM_MSG("playerleavetablebroadcast",&leaveTableBroadcast);
        }else{
            //解散桌子
            SEND_CUSTOM_MSG("playerleavetablebroadcast",&leaveTableBroadcast);
        }
    }
}
///游戏开始广播
void TableCommand::responseRoundStartBroadcast(const char* buf,const int len)
{
    GS2C_RoundStartBroadcast start;
    start.ParseFromArray(buf,len);
    int error = start.errorcode();
    if(error == 0){
        SEND_CUSTOM_MSG("gamemainstart",&start);

    }
    //设置玩家的状态为2
    GamerData::getInstance()->setStatus(2);
}
//补花广播
void TableCommand::responseBuHuaBroadcast(const char* buf,const int len)
{
	/*
    GS2C_StartReplaceBroadcast  buhua;
    buhua.ParseFromArray(buf,len);
    int error = buhua.errorcode();
    if(error == 0)
    {
        SEND_CUSTOM_MSG("PlayingBroadcast_BuHua",&buhua);
    }
	*/
}
//出牌请求
void  TableCommand::requestOutCard(const int cardId)
{
    pb::C2GS_Out out;
    out.set_card(cardId);
    string buf;
    out.SerializeToString(&buf);
    SEND_BUF_MSG(Opcode::MSG_OUT,buf);

    //停止震动
    SEND_CUSTOM_MSG("onresultunscheduleQuake");
}
//出牌返回
void  TableCommand::responseOutCard(const char* buf,const int len)
{
    pb::GS2C_Out out;
    out.ParseFromArray(buf,len);
    int error = out.errorcode();
    if(error == 0)
    {
        SEND_CUSTOM_MSG("playerout");
    }
}
void TableCommand::responseoutcardbroadcast(const char *buf,const int len)
{
    pb::GS2C_OutBroadcast  out;
    out.ParseFromArray(buf,len);
    int error = out.errorcode();
    if(error == 0)
    {
        SEND_CUSTOM_MSG("realoutcard",&out);
    }
}
void TableCommand::responsesystendispathercardbroadcast(const char *buf,const int len)
{
    pb::GS2C_DispatchBroadcast  dispath;
    dispath.ParseFromArray(buf,len);
    int error=dispath.errorcode();
    if(error==0)
    {
        SEND_CUSTOM_MSG("getsiglecardbroadcast",&dispath);//获取单张牌
    }

}
void TableCommand::responseopreateaskbroadcast(const char *buf,const int len)
{
    pb::GS2C_OperateAskBroadcast   dispath;
    dispath.ParseFromArray(buf,len);
    int error=dispath.errorcode();
    if(error==0)
    {
        SEND_CUSTOM_MSG("operateaskbroadcast",&dispath);//获取单张牌
    }
}

void TableCommand::responseoperate(const char *buf,const int len)
{
    pb::GS2C_Operate   dispath;
    dispath.ParseFromArray(buf,len);
    int error=dispath.errorcode();

    SEND_CUSTOM_MSG("operatesuccess", &dispath);//服务器返回操作成功消息

}
void TableCommand::responseoperatesuccessbroadcast(const char *buf, const int len)
{
    pb::GS2C_OperateResultBroadcast   dispath;
    dispath.ParseFromArray(buf,len);
    int error=dispath.errorcode();
    if(error==0)
    {
        SEND_CUSTOM_MSG("operatesuccessbroadcast",&dispath);//服务器返回某用户进行某种操作成功的消息
    }
}
void TableCommand::responsemingloubroadcast(const char *buf,const int len)
{
    pb::GS2C_MinglouBroadcast   dispath;
    dispath.ParseFromArray(buf,len);
    int error=dispath.errorcode();
    if(error==0)
    {
        SEND_CUSTOM_MSG("responsemingloubroadcast",&dispath);//服务器返回某用户进行某种操作成功的消息
    }
}
void TableCommand::responseonroundresultbroadcast(const char *buf,const int len)
{
    pb::GS2C_RoundResultBroadcast   dispath;
    dispath.ParseFromArray(buf,len);
    int error=dispath.errorcode();
    if(error==0)
    {
        SEND_CUSTOM_MSG("responseoneroundendbroadcast",&dispath);//服务器返回某用户进行某种操作成功的消息
    }
    //自己ready的时候，状态设为5,中间暂停状态，这个时候是不能退出的，退出算断线
    GamerData::getInstance()->setStatus(5);
}

void TableCommand::requestchat(int index)
{
	pb::C2GS_Chat  joinTable;
	joinTable.set_chat_index(index);
	string buf;
	joinTable.SerializeToString(&buf);
	SEND_BUF_MSG(Opcode::MSG_CHAT,buf);
}
void TableCommand::requestcustomchat(std::string chat_content)
{
	pb::C2GS_ChatCustom  joinTable;
	joinTable.set_chat_content(chat_content);
	string buf;
	joinTable.SerializeToString(&buf);
	SEND_BUF_MSG(Opcode::MSG_CHAT_CUSTOM,buf);
}
void TableCommand::responsechatbroadcast(const char *buf,const int len)
{
	pb::GS2C_ChatBroadcast    dispath;
	dispath.ParseFromArray(buf,len);
	int error=dispath.errorcode();
	int uid=dispath.uid();
	int idnex=dispath.chat_index();
	if(error==0)
	{
		SEND_CUSTOM_MSG("chat",&dispath);
	}
}
void TableCommand::responsecustomchatbroadcast(const char *buf,const int len)
{
	pb::GS2C_ChatCustomBroadcast    dispath;
	dispath.ParseFromArray(buf,len);
	int error=dispath.errorcode();
	int uid=dispath.uid();
	std::string content=dispath.chat_content();
	if(error==0)
	{
		SEND_CUSTOM_MSG("customchat",&dispath);
	}
}
