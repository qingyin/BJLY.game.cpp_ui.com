#include "MainCommand.h"
#include "BaseCommand.h"
#include "socket/SocketUtil.h"
#include "controller/login/LoginCommand.h"
#include "controller/table/TableCommand.h"
MainCommand* MainCommand::m_mainCommand = nullptr;


MainCommand* MainCommand::getInstance()
{
	if (m_mainCommand == nullptr)  {
		m_mainCommand = new MainCommand();
		m_mainCommand->init();
	}
    return m_mainCommand;
}
bool MainCommand::init()
{
    Director::getInstance()->getScheduler()->scheduleSelector(
        schedule_selector(MainCommand::update),this,0.08f,false);
    return true;
}				  
void   MainCommand::update(float dt)
{
    if (SocketUtil::getInstance()->isConnected() == false){
        return;
	}
	m_mutex.lock();
    int size = opcodeDeque.size();
    if(size > 0) {

        for(int i = 0; i < size; i++) {
            int    opcode = opcodeDeque.front();
            char* buf     = msgDeque.front();	
            int len       = lenDeque.front();
            opcodeDeque.pop_front();
            msgDeque.pop_front();
            lenDeque.pop_front();
            BaseCommand* pBaseCommand = nullptr;
            switch (opcode)
            {
			CCLOG("opcode====%d",opcode);
            case Opcode::MSG_LOGIN: //2 账号登陆 
            case Opcode::MSG_PING_PONG:  
                pBaseCommand = LoginCommand::getInstance();
                break;
            case Opcode::MSG_JOIN_TABLE:  //加入桌子
            case Opcode::MSG_LEAVE_TABLE://离开桌子
            case Opcode::MSG_JOIN_TABLE_BROADCAST: //加入桌子广播
            case Opcode::MSG_LEAVE_TABLE_BROADCAST://离开桌子广播
            case Opcode::MSG_ROUND_START_BROADCAST://一局开始广播
            case Opcode::MSG_OUT://出牌
            case Opcode::MSG_OUT_BROADCAST:
            case Opcode::MSG_DISPATCH_BROADCAST://系统单张发牌
            case Opcode::MSG_OPERATE_ASK_BROADCAST ://操作询问
            case Opcode::MSG_OPERATE://操作
            case Opcode::MSG_OPERATE_RESULT_BROADCAST://操作结果
            case Opcode::MSG_MINGLOU_ASK://明楼请求
            case Opcode::MSG_MINGLOU_BROADCAST://明楼结果响应
			case Opcode::MSG_ROUND_RESULT_BROADCAST://一局结束广播
			case Opcode::MSG_READY://响应
			case Opcode::MSG_READY_BROADCAST:
			case Opcode::MSG_BREAK_BACK_BROADCAST:
			case Opcode::MSG_VOICE_TALK:
			case Opcode::MSG_VOICE_TALK_BROADCAST:
			case Opcode::MSG_CHAT:
			case Opcode::MSG_CHAT_BROADCAST:
			case Opcode::MSG_CHAT_CUSTOM:
			case Opcode::MSG_CHAT_CUSTOM_BROADCAST:
            case Opcode::MSG_DISMISS_ASK_BROADCAST:
            case Opcode::MSG_DISMISS_ANSWER:
            case Opcode::MSG_DISMISS_ANSWER_BROADCAST:
            case Opcode::MSG_DISMISS_BROADCAST:
			case Opcode::MSG_BREAK_BROADCAST:
			case Opcode::MSG_GET_JU_CNT:
			case Opcode::MSG_GET_RESULT_DETAIL:
			case Opcode::MSG_RESULT_TOTAL:
			case Opcode::MSG_RESULT_PK:
			case Opcode::MSG_DINGQUE_ASK_BROADCAST:
			case Opcode::MSG_DINGQUE_ANSWER:
			case  Opcode::MSG_DINGQUE_ANSWER_BROADCAST:
                pBaseCommand = TableCommand::getInstance();
                break;
            default:
                //CCAssert(false, "some mainCmd not Deal!");
                break;
            };
            if(pBaseCommand != nullptr) pBaseCommand->onRecv(opcode,buf,len);
            //opcodeDeque.pop_front();
            //msgDeque.pop_front();
            //lenDeque.pop_front();
            delete[] buf; 
        }
	}
	m_mutex.unlock();
}
void MainCommand::sendMsg( int opcode , char* buf, int len)
{
	m_mutex.lock();
    opcodeDeque.push_back(opcode);
    msgDeque.push_back(buf);
    lenDeque.push_back(len);
	m_mutex.unlock();
}
