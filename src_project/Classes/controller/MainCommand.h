#pragma once
#include "cocos2d.h"
#include <mutex>
USING_NS_CC;
class  MainCommand : public Ref
{
public:
    static MainCommand* getInstance();
    bool   init();
    void   update(float dt);
    void   sendMsg( int opcode, char* buf,  int len); 
public:
    static MainCommand* m_mainCommand;
    std::mutex m_mutex;
    std::deque<int> opcodeDeque;
    std::deque<char*> msgDeque;
    std::deque<int> lenDeque;

};
