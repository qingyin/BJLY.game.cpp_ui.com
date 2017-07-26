#include "LobbyData.h"

LobbyData* LobbyData::mLobbyData = nullptr;
LobbyData* LobbyData::getInstance()
{
	if (mLobbyData == nullptr)
	{
		mLobbyData = new LobbyData();
	}
	return mLobbyData;
}
LobbyData::~LobbyData(void)
{
}

LobbyData::LobbyData(void)
{
}
bool	LobbyData::getBoolForKey(const string key)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey(key.c_str());
}
bool	LobbyData::getBoolForKey(const string key, bool defaultValue)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey(key.c_str(), defaultValue);
}
int LobbyData::getIntegerForKey(const string key)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(key.c_str());
}
int LobbyData::getIntegerForKey(const string key, int defaultValue)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(key.c_str(), defaultValue);
}
float	LobbyData::getFloatForKey(const string key)
{
	return CCUserDefault::sharedUserDefault()->getFloatForKey(key.c_str());
}
float	LobbyData::getFloatForKey(const string key, float defaultValue)
{
	return CCUserDefault::sharedUserDefault()->getFloatForKey(key.c_str(), defaultValue);
}
double	LobbyData::getDoubleForKey(const string key)
{
	return CCUserDefault::sharedUserDefault()->getDoubleForKey(key.c_str());
}
double	LobbyData::getDoubleForKey(const string key, double defaultValue)
{
	return CCUserDefault::sharedUserDefault()->getDoubleForKey(key.c_str(), defaultValue);
}
string LobbyData::getStringForKey(const string key)
{
	return CCUserDefault::sharedUserDefault()->getStringForKey(key.c_str());
}
string LobbyData::getStringForKey(const string key, const std::string & defaultValue)
{
	return CCUserDefault::sharedUserDefault()->getStringForKey(key.c_str(), defaultValue);
}

void	LobbyData::setBoolForKey(const string key, bool value)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey(key.c_str(), value);
}
void	LobbyData::setIntegerForKey(const string key, int value)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey(key.c_str(), value);
}
void	LobbyData::setFloatForKey(const string key, float value)
{
	CCUserDefault::sharedUserDefault()->setFloatForKey(key.c_str(), value);
}
void	LobbyData::setDoubleForKey(const string key, double value)
{
	CCUserDefault::sharedUserDefault()->setDoubleForKey(key.c_str(), value);
}

void LobbyData::setStringForKey(const string key, const std::string & value)
{
	CCUserDefault::sharedUserDefault()->setStringForKey(key.c_str(), value);
}
