#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class Platform
{
public:
	static string getVersion();
	static string getPower();
	static void Login();
}; 
