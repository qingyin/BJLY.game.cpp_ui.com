#pragma once

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

class LobbyData
{
public:
	~LobbyData(void);
	static LobbyData* getInstance();

	bool	getBoolForKey(const string key);
	bool	getBoolForKey(const string key, bool defaultValue);
	int getIntegerForKey(const string key);
	int getIntegerForKey(const string key, int defaultValue);
	float	getFloatForKey(const string key);
	float	getFloatForKey(const string key, float defaultValue);
	double	getDoubleForKey(const string key);
	double	getDoubleForKey(const string key, double defaultValue);
	string getStringForKey(const string key);
	string getStringForKey(const string key, const string & defaultValue);

	void	setBoolForKey(const string key, bool value);
	void	setIntegerForKey(const string key, int value);
	void	setFloatForKey(const string key, float value);
	void	setDoubleForKey(const string key, double value);
	void	setStringForKey(const string key, const string & value);

private:
	LobbyData(void);
	static LobbyData* mLobbyData;
};

