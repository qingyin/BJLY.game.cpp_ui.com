#pragma once

#include <map>
using namespace std;

#include "GamerData.h"


class GamerDataDeal
{
public:
    static GamerDataDeal* getInstance();
    void addGamerData(const int uid,GamerData* pGamerData);
    void removeGamerData(const int uid);
    GamerData* getGamerDataBySeat(const int viewid);
    GamerData* getGamerData(const int uid);
    void   removeallGamerData();

	public:
    static GamerDataDeal* m_gamerDataDeal;
    map<int,GamerData*> m_gamerDataM;
    map<int,GamerData*> m_gamerDataMSeat;

};
